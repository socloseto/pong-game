#pragma once
#include <SFML/Graphics.hpp>
#include "../texturing/BallSkin.h"
class TextureSkin:public BallSkin {

	
	void apply(sf::CircleShape& ballShape) override;

};