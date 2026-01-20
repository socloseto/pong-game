#include "Ball.h"
#include "Paddle.h"
#include <stdexcept>
#include <cmath>
#include "/projectFolder/pong-game/pong/Utils.h"

Ball::Ball() {
    float radius = 10.f;
    ballShape_.setRadius(radius);
    centerOrigin(ballShape_);
    ballShape_.setFillColor(sf::Color::White);
}
void Ball::update(float deltaTime) {

    position_ += velocity_ * deltaTime;
    ballShape_.setPosition(position_);
}

void Ball::bounceFromPaddle(const Paddle& paddle) {
    float paddleCenter = paddle.getPosition().y + paddle.getSize().y / 2.f;
    float ballCenter = position_.y + ballShape_.getRadius();

    float offset = (ballCenter - paddleCenter) / (paddle.getSize().y / 2.f);

    velocity_.x = -velocity_.x;
    velocity_.y = speed_ * offset;
}

void Ball::setSkin(std::unique_ptr<BallSkin> newSkin){
    if (!newSkin) {
        throw std::runtime_error("Ball Error: Attempted to set a null skin!");
        ballShape_.setFillColor(sf::Color::White);
    }
    this->skin_ = std::move(newSkin);
    skin_->apply(ballShape_);
}
void Ball::draw(sf::RenderWindow& window) {
    window.draw(ballShape_);
}

void Ball::resetPosition(const sf::Vector2f &pos) {
    position_ = pos;
    ballShape_.setPosition(position_);
    velocity_ = { speed_,0.f };

}
sf::FloatRect Ball::getBounds() const {
    return ballShape_.getGlobalBounds();
}
sf::Vector2f Ball::getPosition() const {
    return position_; 
}