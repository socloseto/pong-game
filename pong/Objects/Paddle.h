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
	float speed_=400;
	sf::RectangleShape paddleShape_;
	Direction direction_ = Direction::None;
public:
	Paddle();
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void handleInput();
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;

};