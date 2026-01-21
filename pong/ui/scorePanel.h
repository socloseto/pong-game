#pragma once

#include <SFML/Graphics.hpp>
#include "TextPanel.h"
#include "../common/GoalObserver.h"

class ScorePanel: public TextPanel,public GoalObserver{
	sf::Text scoreDisplay;
	short leftPlayerScore;
	short rightPlayerScore;
public:
	ScorePanel( unsigned size);
	void onGoal(Side side) override;
	void addLeftPoint();
	void addRightPoint();

	void updateScore();
	void draw(sf::RenderWindow& window)override;

	void setPositionAtCenter(const sf::RenderWindow& window);
};