#pragma once
#include <SFML/Graphics.hpp>
class BallSkin {
public:
	virtual ~BallSkin() = default;
	virtual void apply(sf::CircleShape& ballShape) = 0;

};