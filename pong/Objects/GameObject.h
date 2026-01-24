#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Vector2f position_;
	sf::Vector2f velocity_;
public:
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(float deltaTime, const sf::RenderWindow& window) = 0;
};