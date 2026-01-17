#include "Ball.h"
#include "Paddle.h"


void Ball::bounceFromPaddle(const Paddle& paddle) {
    float paddleCenter = paddle.getPosition().y + paddle.getSize().y / 2.f;
    float ballCenter = position_.y + shape_.getRadius();

    float offset = (ballCenter - paddleCenter) / (paddle.getSize().y / 2.f);

    velocity_.x = -velocity_.x;
    velocity_.y = speed_ * offset;
}
