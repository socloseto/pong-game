#include "Ball.h"
#include "Paddle.h"
#include <stdexcept>
#include <cmath>
#include "../common/Utils.h"

Ball::Ball() {
    float radius = 10.f;
    ballShape_.setRadius(radius);
    centerOrigin(ballShape_);
    ballShape_.setFillColor(sf::Color::White);
}
void Ball::update(float deltaTime, const sf::RenderWindow &window) {

    position_ += velocity_ * deltaTime;
    if (position_.y <= 0 || position_.y + ballShape_.getRadius() * 2.f >= window.getSize().y) {
        velocity_.y = -velocity_.y;
    }
    if (position_.x < 0) {
        notifyGoal(GoalObserver::Side::Left);
    }
    else if (position_.x > window.getSize().x) {
        notifyGoal(GoalObserver::Side::Right);
    }

    ballShape_.setPosition(position_);
}
void Ball::notifyGoal(GoalObserver::Side side) {
    for (auto obs : observers_) {
        obs->onGoal(side);
    }
}
void Ball::addObserver(GoalObserver* obs){ 
    observers_.push_back(obs);
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
    setPosition(pos);
    float dirX = (rand() % 2 == 0) ? speed_ : -speed_;
    float dirY = static_cast<float>((rand() % 200) - 100);
    velocity_ = { dirX, dirY };

}
sf::FloatRect Ball::getBounds() const {
    return ballShape_.getGlobalBounds();
}
sf::Vector2f Ball::getPosition() const {
    return position_; 
}
void Ball::setPosition(const sf::Vector2f &pos) {
    position_ = pos;
    ballShape_.setPosition(position_);
}