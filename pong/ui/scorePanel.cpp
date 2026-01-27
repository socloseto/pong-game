#include "ScorePanel.h"

#include <string>

#include "../common/Utils.h"

ScorePanel::ScorePanel(unsigned size)
    : leftPlayerScore(0),
      rightPlayerScore(0),
      scoreDisplay(FontManager::getFont()),
      gameOverHint_(FontManager::getFont()),
      finalMessage_(FontManager::getFont()) {
  scoreDisplay.setCharacterSize(size);
  scoreDisplay.setFillColor(sf::Color::White);

  updateScore();
}
void ScorePanel::onGoal(Side side) {
  if (side == Side::Left)
    addRightPoint();
  else
    addLeftPoint();
}
void ScorePanel::addLeftPoint() {
  leftPlayerScore++;
  updateScore();
}
void ScorePanel::addRightPoint() {
  rightPlayerScore++;
  updateScore();
}
short ScorePanel::getLeftScore() const { return leftPlayerScore; }
short ScorePanel::getRightScore() const { return rightPlayerScore; }

void ScorePanel::updateScore() {
  scoreDisplay.setString(std::to_string(leftPlayerScore) + " - " +
                         std::to_string(rightPlayerScore));
  centerOrigin(scoreDisplay);
}
void ScorePanel::draw(sf::RenderWindow& window) {
  if (isGameOver_) {
    window.draw(finalMessage_);
    window.draw(gameOverHint_);
  } else {
    window.draw(scoreDisplay);
  }
}
void ScorePanel::setScorePosition(sf::Vector2f sceneSize) {
  sf::Vector2f center = getSceneCenter(sceneSize);

  scoreDisplay.setPosition({center.x, sceneSize.y * 0.1f});
}
void ScorePanel::reset(sf::Vector2f sceneSize) {
  isGameOver_ = false;
  leftPlayerScore = 0;
  rightPlayerScore = 0;
  scoreDisplay.setFillColor(sf::Color::White);
  updateScore();
  setScorePosition(sceneSize);
}
void ScorePanel::showGameOver(const std::string& result,
                              sf::Vector2f sceneSize) {
  isGameOver_ = true;
  sf::Vector2f center = getSceneCenter(sceneSize);
  finalMessage_.setString(result);
  finalMessage_.setCharacterSize(60);
  finalMessage_.setFillColor(result == "YOU WIN!" ? sf::Color::Green
                                                  : sf::Color::Red);
  centerOrigin(finalMessage_);
  finalMessage_.setPosition({center.x, center.y - 50.f});

  gameOverHint_.setString("Press Any Key to RESTART");
  gameOverHint_.setCharacterSize(25);
  gameOverHint_.setFillColor(sf::Color::White);
  centerOrigin(gameOverHint_);
  gameOverHint_.setPosition({center.x, center.y + 50.f});
}