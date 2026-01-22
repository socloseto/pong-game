#include "ScorePanel.h"
#include <string>
#include "../common/Utils.h"

ScorePanel::ScorePanel(unsigned size)
	:leftPlayerScore(0), rightPlayerScore(0), scoreDisplay(FontManager::getFont())
{
	scoreDisplay.setCharacterSize(size);
	scoreDisplay.setFillColor(sf::Color::White);

	updateScore();
}
void ScorePanel::onGoal(Side side) {
	if (side == Side::Left) addRightPoint();
	else addLeftPoint();
}
void ScorePanel::addLeftPoint() {
	leftPlayerScore++;
	updateScore();
}
void ScorePanel::addRightPoint() {
	rightPlayerScore++;
	updateScore();
}
short ScorePanel::getLeftScore() const {
	return leftPlayerScore;
}
short ScorePanel::getRightScore() const {
	return rightPlayerScore;
}

void ScorePanel::updateScore(){
	scoreDisplay.setString(std::to_string(leftPlayerScore) + " - " + std::to_string(rightPlayerScore));
	centerOrigin(scoreDisplay);
}
void ScorePanel::draw(sf::RenderWindow& window) {
	window.draw(scoreDisplay);
}
void ScorePanel::setPositionAtCenter(const sf::RenderWindow& window) {

	positionAtCenter(scoreDisplay, window);
	sf::Vector2f centerPos = scoreDisplay.getPosition();
	scoreDisplay.setPosition({ centerPos.x, 50.f });
}
void ScorePanel::showFinalMessage(const std::string& message) {
	scoreDisplay.setString(message);

	scoreDisplay.setFillColor(sf::Color::Yellow);
}
void ScorePanel::reset() {
	leftPlayerScore = 0;
	rightPlayerScore = 0;

	scoreDisplay.setFillColor(sf::Color::White);
	updateScore();
}