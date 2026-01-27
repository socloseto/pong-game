#pragma once

#include <SFML/Graphics.hpp>

#include "../common/GoalObserver.h"
#include "TextPanel.h"

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
  void draw(sf::RenderWindow& window) override;
  void setScorePosition(sf::Vector2f sceneSize);
  void reset(sf::Vector2f sceneSize);
  void showGameOver(const std::string& result, sf::Vector2f sceneSize);
};