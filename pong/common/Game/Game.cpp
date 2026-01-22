#include "Game.h"
#include "../Utils.h"
#include "../../texturing/SkinFactory.h"


Game::Game() :
	window_(sf::VideoMode({ 800,600 }), "Pong"), score_(40) {
	window_.setFramerateLimit(60);
	sf::Vector2f center = getWindowCenter(window_);
	score_.setPositionAtCenter(window_);
	ball_.addObserver(&score_);

	player_.setPosition({ 40.f, center.y });
	cpu_.setPosition({ 760.f, center.y });
	resetBall();
}
void Game::run(){
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
			sf::View view(sf::FloatRect({ 0.f, 0.f }, { 800.f, 600.f }));
			window_.setView(view);
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

					score_.reset();
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
		player_.update(deltaTime,window_);
		cpu_.update(deltaTime, window_);
		if (score_.getLeftScore() >= 11) {
			state_ = GameState::GameOver;
			gameOverTimer_ = 0.f;
			score_.showFinalMessage("YOU WIN!\nPress Any Key To RESTART");	
		}
		else if (score_.getRightScore() >= 11) {
			state_ = GameState::GameOver;
			gameOverTimer_ = 0.f;
			score_.showFinalMessage("YOU LOSE!\nPress Any Key To RESTART");
		}
		if (ball_.getPosition().x < 0 || ball_.getPosition().x > window_.getSize().x) {
			resetBall();
		}
		if (ball_.getBounds().findIntersection(player_.getBounds())) {
			ball_.bounceFromPaddle(player_);
		}
		if (ball_.getBounds().findIntersection(cpu_.getBounds())) {
			ball_.bounceFromPaddle(cpu_);
		}
		float ballY = ball_.getPosition().y;
		float cpuY = cpu_.getPosition().y;
		if (ballY > cpuY) cpu_.move(0, 300.f * deltaTime);
		else cpu_.move(0, -300.f * deltaTime);
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
