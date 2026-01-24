#include "Game.h"
#include "../Utils.h"
#include "../../texturing/SkinFactory.h"


Game::Game() :
	window_(sf::VideoMode({ 800,600 }), "Pong"), score_(40) {
	window_.setFramerateLimit(60);
	window_.setMinimumSize(sf::Vector2u{ 800, 600 });
	sf::Vector2f center = getWindowCenter(window_);
	score_.setPositionAtCenter(window_);
	ball_.addObserver(&score_);

	player_.setPosition({ 40.f, center.y });
	cpu_.setPosition({ window_.getSize().x - 40.f , center.y });
	resetBall();
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
			float newWidth = static_cast<float>(resized->size.x);
			float newHeight = static_cast<float>(resized->size.y);
			sf::View view(sf::FloatRect({ 0.f, 0.f }, { newWidth, newHeight }));
			window_.setView(view);
			this->onResize(resized->size);
		}
		if (state_ == GameState::Menu) {
			if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseBtn->button == sf::Mouse::Button::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
					int skinIdx = skinsMenu_.handleMouse(mousePos, true);
					if (skinIdx != -1) {
						auto skin = SkinFactory::CreateSkin(skinsMenu_.getSkinType(skinIdx));
						try {

							ball_.setSkin(std::move(skin));
							state_ = GameState::Playing;
							resetBall();
						}
						catch (const std::runtime_error& e) {

							std::cerr << "Skin error: " << e.what() << std::endl;
						}
					}
				}
			}
		}
		if (state_ == GameState::Playing) {
			player_.handleInput();
		}
		if (state_ == GameState::GameOver) {
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
		const short winConditionState = 11;
		if (score_.getLeftScore() >= winConditionState) {
			state_ = GameState::GameOver;
			gameOverTimer_ = 0.f;
			score_.showFinalMessage("YOU WIN! Press Any Key To RESTART");
		}
		else if (score_.getRightScore() >= winConditionState) {
			state_ = GameState::GameOver;
			gameOverTimer_ = 0.f;
			score_.showFinalMessage("YOU LOSE! Press Any Key To RESTART");
		}
		if (ball_.getPosition().x < 0 || ball_.getPosition().x > window_.getSize().x) {
			resetBall();
			player_.setPosition({ player_.getPosition().x, window_.getSize().y / 2.f });
			cpu_.setPosition({ cpu_.getPosition().x,  window_.getSize().y / 2.f });
		}
		if (ball_.getBounds().findIntersection(player_.getBounds())) {
			ball_.bounceFromPaddle(player_);
		}
		if (ball_.getBounds().findIntersection(cpu_.getBounds())) {
			ball_.bounceFromPaddle(cpu_);
		}
		float direction = cpu_.cpuPaddleDirectionVelocity(ball_.getPosition().y, cpu_.getPosition().y);
		cpu_.move(0, direction * cpu_.getSpeed() * deltaTime);

	}
	if (state_ == GameState::GameOver) {
		gameOverTimer_ += deltaTime;

	}
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
	}

	window_.display();
}
void Game::resetBall() {
	sf::Vector2f center = getWindowCenter(window_);
	ball_.resetPosition(center);
}
void Game::onResize(const sf::Vector2u& newSize) {
	float baseHeight = 600.f;
	float basePaddleSpeed = 450.f;
	float scale = static_cast<float>(newSize.y) / baseHeight;

	player_.setScale({ scale, scale });
	cpu_.setScale({ scale, scale });
	ball_.setScale({ scale, scale });


	float w = static_cast<float>(newSize.x);
	float h = static_cast<float>(newSize.y);

	player_.setPosition({ 40.f * scale, h / 2.f });
	cpu_.setPosition({ w - (40.f * scale), h / 2.f });
	ball_.updateSpeed(scale);
	resetBall();
	player_.updateSpeed(scale);
	cpu_.updateSpeed(scale);
	score_.setPositionAtCenter(window_);
}