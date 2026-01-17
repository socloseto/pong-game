#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Vector2f position;
	sf::Vector2f velocity;
public:
	virtual ~GameObject()=default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(float deltaTime)=0;
};