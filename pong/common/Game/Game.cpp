#include "Game.h"

#include "../../texturing/SkinFactory.h"
#include "../Utils.h"

Game::Game()
    : window_(sf::VideoMode({static_cast<unsigned int>(virtualWidth),
                             static_cast<unsigned int>(virtualHeight)}),
              "Pong"),
      score_(fontSize),
      pauseText_(FontManager::getFont()),
      pauseHintText_(FontManager::getFont()) {
  initUI();
  initAudio();
  initEntities();
}
Game::~Game() { AudioManager::instance().setMainMusic(nullptr); }
void Game::run() {
  sf::Clock clock;
  while (window_.isOpen()) {
    float dt = clock.restart().asSeconds();
    processInput();
    update(dt);
    render();
  }
}
void Game::processInput() {
  while (const std::optional event = window_.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window_.close();
    }

    if (const auto* resized = event->getIf<sf::Event::Resized>()) {
      sf::View view(
          sf::FloatRect({0.f, 0.f}, {static_cast<float>(resized->size.x),
                                     static_cast<float>(resized->size.y)}));
      window_.setView(view);
      this->onResize(resized->size);
    }

    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->code == sf::Keyboard::Key::Escape) {
        if (state_ == GameState::Menu)
          window_.close();
        else {
          state_ = GameState::Menu;
          resetBall();
        }
      }
      if (keyPressed->code == sf::Keyboard::Key::Space ||
          keyPressed->code == sf::Keyboard::Key::P) {
        togglePause();
      }
      if (keyPressed->code == sf::Keyboard::Key::Equal)
        AudioManager::instance().setVolume(
            AudioManager::instance().getVolume() + 5.f);
      if (keyPressed->code == sf::Keyboard::Key::Hyphen)
        AudioManager::instance().setVolume(
            AudioManager::instance().getVolume() - 5.f);
    }
    if (state_ == GameState::Menu) {
      if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
        sf::Vector2f worldPos = window_.mapPixelToCoords(mouseMoved->position);
        skinsMenu_.handleMouse(sf::Vector2i(worldPos), false);
      }
      if (const auto* mouseBtn =
              event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseBtn->button == sf::Mouse::Button::Left) {
          sf::Vector2f worldPos = window_.mapPixelToCoords(mouseBtn->position);
          int skinIdx = skinsMenu_.handleMouse(sf::Vector2i(worldPos), true);
          if (skinIdx != -1) {
            ball_.setSkin(
                SkinFactory::CreateSkin(skinsMenu_.getSkinType(skinIdx)));
            state_ = GameState::Playing;
          }
        }
      }
    } else if (state_ == GameState::Playing) {
      player_.handleInput();
    } else if (state_ == GameState::GameOver) {
      if (gameOverTimer_ > 1.f) {
        if (event->is<sf::Event::KeyPressed>() ||
            event->is<sf::Event::MouseButtonPressed>()) {
          score_.reset({virtualWidth, virtualHeight});
          resetBall();
          state_ = GameState::Playing;
        }
      }
    }
  }
}
void Game::update(float deltaTime) {
  if (state_ == GameState::Playing) {
    ball_.update(deltaTime);
    player_.update(deltaTime);
    cpu_.update(deltaTime);
    score_.updateScore();
    if (score_.getLeftScore() >= winConditionState) {
      state_ = GameState::GameOver;
      gameOverTimer_ = 0.f;
      score_.showGameOver("YOU WIN!", {virtualWidth, virtualHeight});
      AudioManager::instance().playSound("win");
    } else if (score_.getRightScore() >= winConditionState) {
      state_ = GameState::GameOver;
      gameOverTimer_ = 0.f;
      score_.showGameOver("YOU LOSE!", {virtualWidth, virtualHeight});
      AudioManager::instance().playSound("lose");
    }
    if (ball_.getPosition().x < 0) {
      AudioManager::instance().playSound("miss");
      resetBall();
      player_.setPosition({paddleOffset, virtualHeight / 2.f});
      cpu_.setPosition({virtualWidth - paddleOffset, virtualHeight / 2.f});
    } else if (ball_.getPosition().x > virtualWidth) {
      AudioManager::instance().playSound("goal");
      resetBall();
      player_.setPosition({paddleOffset, virtualHeight / 2.f});
      cpu_.setPosition({virtualWidth - paddleOffset, virtualHeight / 2.f});
    }
    if (ball_.getBounds().findIntersection(player_.getBounds())) {
      ball_.bounceFromPaddle(player_);
      AudioManager::instance().playSound("hit");
    }
    if (ball_.getBounds().findIntersection(cpu_.getBounds())) {
      ball_.bounceFromPaddle(cpu_);
      AudioManager::instance().playSound("hit");
    }
    float direction = cpu_.cpuPaddleDirectionVelocity(ball_.getPosition().y,
                                                      cpu_.getPosition().y);
    cpu_.move(0, direction * cpu_.getSpeed() * deltaTime);
  }
  if (state_ == GameState::GameOver) {
    gameOverTimer_ += deltaTime;
  }
  AudioManager::instance().update();
}
void Game::render() {
  window_.clear(sf::Color(10, 10, 15));
  sf::Vector2f sceneCenter(virtualWidth / 2.f, virtualHeight / 2.f);
  if (state_ == GameState::Menu) {
    skinsMenu_.draw(window_);
  } else {
    field_.draw(window_);
    score_.draw(window_);
    player_.draw(window_);
    cpu_.draw(window_);
    ball_.draw(window_);

    if (state_ == GameState::Paused) {
      pauseOverlay_.setSize({virtualWidth, virtualHeight});
      pauseText_.setPosition(sceneCenter);
      pauseHintText_.setPosition({sceneCenter.x, sceneCenter.y + 100.f});
      window_.draw(pauseOverlay_);
      window_.draw(pauseText_);
      window_.draw(pauseHintText_);
    }
  }
  window_.display();
}
void Game::resetBall() {
  ball_.resetPosition({virtualWidth / 2.f, virtualHeight / 2.f});
}
void Game::onResize(const sf::Vector2u& newSize) {
  float windowWidth = static_cast<float>(newSize.x);
  float windowHeight = static_cast<float>(newSize.y);
  float targetAspectRatio = 16.0f / 9.0f;
  float windowAspectRatio = windowWidth / windowHeight;

  sf::FloatRect viewport({0.f, 0.f}, {1.f, 1.f});

  if (windowAspectRatio > targetAspectRatio) {
    float viewWidth = targetAspectRatio / windowAspectRatio;
    viewport.position.x = (1.0f - viewWidth) / 2.0f;
    viewport.size.x = viewWidth;
  } else {
    float viewHeight = windowAspectRatio / targetAspectRatio;
    viewport.position.y = (1.0f - viewHeight) / 2.0f;
    viewport.size.y = viewHeight;
  }

  sf::View view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
  view.setViewport(viewport);
  window_.setView(view);
  score_.setScorePosition({virtualWidth, virtualHeight});
}
void Game::initUI() {
  window_.setFramerateLimit(framerateLimit);
  window_.setMinimumSize(
      sf::Vector2u{static_cast<unsigned int>(virtualWidth / 2),
                   static_cast<unsigned int>(virtualHeight / 2)});
  pauseText_.setString("PAUSE");
  pauseText_.setCharacterSize(80);
  pauseText_.setFillColor(sf::Color::White);
  centerOrigin(pauseText_);
  pauseHintText_.setString("Press SPACE or P to Resume | Press ESC for Menu");
  pauseHintText_.setCharacterSize(20);
  pauseHintText_.setFillColor(sf::Color(200, 200, 200));
  centerOrigin(pauseHintText_);
  pauseOverlay_.setFillColor(sf::Color(0, 0, 0, 150));

  score_.setScorePosition({virtualWidth, virtualHeight});
}
void Game::initAudio() {
  auto& audio = AudioManager::instance();
  audio.loadAllEmbeddedAssets();
  audio.setupMainMusic(mainTheme_);
  audio.setVolume(10.f);
}
void Game::initEntities() {
  ball_.addObserver(&score_);
  player_.setPosition({paddleOffset, virtualHeight / 2.f});
  cpu_.setPosition({virtualWidth - paddleOffset, virtualHeight / 2.f});
  resetBall();
}

void Game::togglePause() {
  if (state_ == GameState::Playing)
    state_ = GameState::Paused;
  else if (state_ == GameState::Paused)
    state_ = GameState::Playing;
}