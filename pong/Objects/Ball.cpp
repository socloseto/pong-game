#include "Ball.h"
#include "Paddle.h"


void Ball::bounceFromPaddle(const Paddle& paddle) {
    float paddleCenter = paddle.getPosition().y + paddle.getSize().y / 2.f;
    float ballCenter = position_.y + shape_.getRadius();

    float offset = (ballCenter - paddleCenter) / (paddle.getSize().y / 2.f);

    velocity_.x = -velocity_.x;
    velocity_.y = speed_ * offset;
}

void Ball::setSkin(std::unique_ptr<BallSkin> newSkin){
    this->skin_ = std::move(newSkin);
    skin_-> apply(ballShape_);
}
void Ball::draw(sf::RenderWindow& window) {
    window.draw(ballShape_);
}