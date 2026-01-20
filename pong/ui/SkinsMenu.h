#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "/projectFolder/pong-game/pong/texturing/SkinFactory.h"

class SkinsMenu {

	sf::Font font;
	sf::Text title_;
	struct MenuItem
	{
		sf::Text text;
		SkinFactory::ballSkinType type;
	};
	std::vector<MenuItem> items_;
	int hoveredIndex_ = -1;

public:
	SkinsMenu(sf::Font& font);

	void draw(sf::RenderWindow& window);
	int handleMouse(sf::Vector2i mousePos, bool isClicked);

	SkinFactory::ballSkinType getSkinType(int index) const;
};