#include "Game.h"
#include "../Utils.h"
#include "../../texturing/SkinFactory.h"

Game::Game() :
	window_(sf::VideoMode({ minWindowWidth,minWindowHeight }), "Pong"), score_(fontSize), pauseText_(FontManager::getFont()),
	pauseHintText_(FontManager::getFont())
{

	initUI();
	initAudio();
	initEntities();
}
Game::~Game() {
	AudioManager::instance().setMainMusic(nullptr);
}
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
			sf::View view(sf::FloatRect({ 0.f, 0.f }, { static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) }));
			window_.setView(view);
			this->onResize(resized->size);
		}

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->code == sf::Keyboard::Key::Escape) {
				if (state_ == GameState::Menu) window_.close();
				else { state_ = GameState::Menu; resetBall(); }
			}
			if (keyPressed->code == sf::Keyboard::Key::Space || keyPressed->code == sf::Keyboard::Key::P) {
				togglePause();
			}
			if (keyPressed->code == sf::Keyboard::Key::Equal) AudioManager::instance().setVolume(AudioManager::instance().getVolume() + 5.f);
			if (keyPressed->code == sf::Keyboard::Key::Hyphen) AudioManager::instance().setVolume(AudioManager::instance().getVolume() - 5.f);
		}
		if (state_ == GameState::Menu) {
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
				skinsMenu_.handleMouse(mouseMoved->position, false);
			}
			if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseBtn->button == sf::Mouse::Button::Left) {
					int skinIdx = skinsMenu_.handleMouse(mouseBtn->position, true);
					if (skinIdx != -1) {
						ball_.setSkin(SkinFactory::CreateSkin(skinsMenu_.getSkinType(skinIdx)));
						state_ = GameState::Playing;
					}
				}
			}
		}
		else if (state_ == GameState::Playing) {
			player_.handleInput();
		}
		else if (state_ == GameState::GameOver) {
			if (gameOverTimer_ > 1.f) {
				if (event->is<sf::Event::KeyPressed>() || event->is<sf::Event::MouseButtonPressed>()) {
					score_.reset(window_);
					resetBall();
					state_ = GameState::Playing;
				}
			}
		}
	}
}
void Game::update(float deltaTime) {
	if (state_ == GameState::Playing) {
		ball_.update(deltaTime, window_);
		player_.update(deltaTime, window_);
		cpu_.update(deltaTime, window_);
		score_.updateScore();
		if (score_.getLeftScore() >= winConditionState) {
			state_ = GameState::GameOver;
			gameOverTimer_ = 0.f;
			score_.showGameOver("YOU WIN!", window_);
			AudioManager::instance().playSound("win");
		}
		else if (score_.getRightScore() >= winConditionState) {
			state_ = GameState::GameOver;
			gameOverTimer_ = 0.f;
			score_.showGameOver("YOU LOSE!", window_);
			AudioManager::instance().playSound("lose");
		}
		if (ball_.getPosition().x < 0) {
			AudioManager::instance().playSound("miss");
			resetBall();
			player_.setPosition({ player_.getPosition().x, window_.getSize().y / 2.f });
			cpu_.setPosition({ cpu_.getPosition().x,  window_.getSize().y / 2.f });
		}
		else if (ball_.getPosition().x > window_.getSize().x) {
			AudioManager::instance().playSound("goal");
			resetBall();
			player_.setPosition({ player_.getPosition().x, window_.getSize().y / 2.f });
			cpu_.setPosition({ cpu_.getPosition().x,  window_.getSize().y / 2.f });
		}
		if (ball_.getBounds().findIntersection(player_.getBounds())) {
			ball_.bounceFromPaddle(player_);
			AudioManager::instance().playSound("hit");
		}
		if (ball_.getBounds().findIntersection(cpu_.getBounds())) {
			ball_.bounceFromPaddle(cpu_);
			AudioManager::instance().playSound("hit");
		}
		float direction = cpu_.cpuPaddleDirectionVelocity(ball_.getPosition().y, cpu_.getPosition().y);
		cpu_.move(0, direction * cpu_.getSpeed() * deltaTime);

	}
	if (state_ == GameState::GameOver) {
		gameOverTimer_ += deltaTime;

	}
	AudioManager::instance().update();
}
void Game::render() {
	window_.clear(sf::Color::Black);

	if (state_ == GameState::Menu) {
		skinsMenu_.draw(window_);
	}
	else {
		score_.draw(window_);
		player_.draw(window_);
		cpu_.draw(window_);
		ball_.draw(window_);

		if (state_ == GameState::Paused) {
			sf::Vector2f center = getWindowCenter(window_);

			pauseOverlay_.setSize(sf::Vector2f(window_.getSize()));
			window_.draw(pauseOverlay_);

			pauseText_.setPosition(center);
			window_.draw(pauseText_);

			pauseHintText_.setPosition({ center.x, center.y + 100.f });
			window_.draw(pauseHintText_);
		}
	}
	window_.display();
}
void Game::resetBall() {
	sf::Vector2f center = getWindowCenter(window_);
	ball_.resetPosition(center);
}
void Game::onResize(const sf::Vector2u& newSize) {

	float scale = static_cast<float>(newSize.y) / minWindowHeight;
	skinsMenu_.updateLayout({ newSize }, scale);
	player_.setScale({ scale, scale });
	cpu_.setScale({ scale, scale });
	ball_.setScale({ scale, scale });


	float w = static_cast<float>(newSize.x);
	float h = static_cast<float>(newSize.y);

	player_.setPosition({ paddleOffsetFromSide * scale, h / 2.f });
	cpu_.setPosition({ w - (paddleOffsetFromSide * scale), h / 2.f });
	ball_.updateSpeed(scale);
	resetBall();
	player_.updateSpeed(scale);
	cpu_.updateSpeed(scale);
	score_.setPositionAtCenter(window_);
}
void Game::initUI() {
	window_.setFramerateLimit(framerateLimit);
	window_.setMinimumSize(sf::Vector2u{ minWindowWidth, minWindowHeight });
	pauseText_.setString("PAUSE");
	pauseText_.setCharacterSize(80);
	pauseText_.setFillColor(sf::Color::White);
	centerOrigin(pauseText_);
	pauseHintText_.setString("Press SPACE to Resume | Press ESC for Menu");
	pauseHintText_.setCharacterSize(20);
	pauseHintText_.setFillColor(sf::Color(200, 200, 200));
	centerOrigin(pauseHintText_);
	pauseOverlay_.setFillColor(sf::Color(0, 0, 0, 150));

	score_.setPositionAtCenter(window_);
}
void Game::initAudio() {
	auto& audio = AudioManager::instance();
	audio.loadAllEmbeddedAssets();
	audio.setupMainMusic(mainTheme_);
	audio.setVolume(10.f);
}
void Game::initEntities() {
	sf::Vector2f center = getWindowCenter(window_);
	ball_.addObserver(&score_);

	player_.setPosition({ paddleOffsetFromSide, center.y });
	cpu_.setPosition({ window_.getSize().x - paddleOffsetFromSide, center.y });
	resetBall();
}

void Game::togglePause() {
	if (state_ == GameState::Playing) state_ = GameState::Paused;
	else if (state_ == GameState::Paused) state_ = GameState::Playing;
}