#pragma once
#include "../pong/GameObject.h"
class Ball : public GameObject{
	int angle=0;
	float speed = 0.f;
	bool isOut = false;
	sf::CircleShape ballShape;
public:

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void collision();
	void setSkin();
	void resetPosition(sf::Vector2f);
};