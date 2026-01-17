#pragma once
#include "../pong/GameObject.h"
class Paddle : public GameObject {
	float speed;
	enum Direction {
	None,
	Up,
	Down
	};
	Direction _direction = None;
public:
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void collision();
	void handleInput();
};