#pragma once
#include "GameObject.h"
#include "../texturing/BallSkin.h"
class Paddle;

class Ball : public GameObject{

private:
	std::unique_ptr<BallSkin> skin_;
	float speed_ = 0.f;
	bool isOut_ = false;
	sf::CircleShape ballShape_;
public:

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void setSkin(std::unique_ptr<BallSkin> newSkin);
	void bounceFromPaddle(const Paddle& paddle);
	void resetPosition(const sf::Vector2f &pos);
};