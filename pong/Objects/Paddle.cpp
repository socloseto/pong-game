#include "Paddle.h"
#include "../common/Utils.h"


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
void Paddle::update(float deltaTime, const sf::RenderWindow& window) {
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
	float screenHeight = static_cast<float>(window.getSize().y);
	float paddleHeight = paddleShape_.getGlobalBounds().size.y;
	float halfHeight = paddleHeight / 2.f;

	if (position_.y < halfHeight) {
		position_.y = halfHeight;
	}
	else if (position_.y > screenHeight - halfHeight) {
		position_.y = screenHeight - halfHeight;
	}
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
void Paddle::move(float offsetX, float offsetY) {
	sf::Vector2f currentPos = getPosition();
	setPosition({ currentPos.x,currentPos.y + offsetY });
}
void Paddle::setPosition(const sf::Vector2f& pos) {
	paddleShape_.setPosition(pos);
}