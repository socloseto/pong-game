#pragma once

#include <SFML/Graphics.hpp>
#include "TextPanel.h"

class ScorePanel: public TextPanel,public GoalObserver{
	sf::Text scoreDisplay;
	short leftPlayerScore;
	short rightPlayerScore;
public:
	ScorePanel(sf::Font& font, unsigned size, sf::Vector2f position);

	void addLeftPoint();
	void addRightPoint();

	void updateScore();
	void draw(sf::RenderWindow& window)override;


};