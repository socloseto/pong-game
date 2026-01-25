#pragma once

#include <SFML/Graphics.hpp>
#include "TextPanel.h"
#include "../common/GoalObserver.h"

class ScorePanel : public TextPanel, public GoalObserver {
	sf::Text scoreDisplay;
	sf::Text finalMessage_;
	sf::Text gameOverHint_;
	bool isGameOver_ = false;
	short leftPlayerScore;
	short rightPlayerScore;
public:
	ScorePanel(unsigned size);
	void onGoal(Side side) override;
	void addLeftPoint();
	void addRightPoint();
	short getLeftScore() const;
	short getRightScore() const;
	void updateScore();
	void draw(sf::RenderWindow& window)override;
	void setPositionAtCenter(const sf::RenderWindow& window);
	void reset(const sf::RenderWindow& window);
	void showGameOver(const std::string& result, const sf::RenderWindow& window);
};