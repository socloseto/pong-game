#include "Paddle.h"
#include "/projectFolder/pong-game/pong/Utils.h"

Paddle::Paddle() {

	paddleShape_.setSize(sf::Vector2f(15.f, 100.f));
	paddleShape_.setFillColor(sf::Color::White);
	centerOrigin(paddleShape_);
}
sf::Vector2f Paddle::getPosition() const {
	return position_;
}
sf::Vector2f Paddle::getSize() const { 
	return paddleShape_.getSize(); 
}
void Paddle::draw(sf::RenderWindow& window) {
	window.draw(paddleShape_);
}
void Paddle::update(float deltaTime) {
	if (direction_ == Direction::Up) {
		velocity_.y = -speed_;
	}
	else if (direction_ == Direction::Down) {
		velocity_.y = speed_;
	}
	else {
		velocity_.y = 0.f;
	}
	position_ += velocity_ * deltaTime;
	if (position_.y < 50.f)
		position_.y = 50.f;
	if (position_.y > 550.f)
		position_.y = 550.f;

	paddleShape_.setPosition(position_);
}
void Paddle::handleInput() {
	direction_ = Direction::None;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		direction_ = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		direction_= Direction::Down;
	}
}