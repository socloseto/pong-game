#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../texturing/SkinFactory.h"

class SkinsMenu {

	sf::Text title_;
	struct MenuItem
	{
		sf::Text text;
		SkinFactory::ballSkinType type;

		MenuItem(sf::Text&& t, SkinFactory::ballSkinType type)
			: text(std::move(t)), type(type) {
		}
	};
	std::vector<MenuItem> items_;
	int hoveredIndex_ = -1;

public:
	SkinsMenu();

	void draw(sf::RenderWindow& window);
	int handleMouse(sf::Vector2i mousePos, bool isClicked);

	SkinFactory::ballSkinType getSkinType(int index) const;
};