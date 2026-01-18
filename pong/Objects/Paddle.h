#pragma once
#include "GameObject.h"
class Paddle : public GameObject {

public:
	enum class Direction {
		None,
		Up,
		Down
	};
private:
	float speed_;

	Direction direction_ = Direction::None;
public:

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void handleInput();
};