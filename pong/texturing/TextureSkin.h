#pragma once
#include <SFML/Graphics.hpp>
#include "BallSkin.h"
class TextureSkin:public BallSkin {
	sf::Texture texture_;

public:	
	TextureSkin(const std::string& path);
	void apply(sf::CircleShape& ballShape) override;
	
};