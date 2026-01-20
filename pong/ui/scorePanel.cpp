#include "ScorePanel.h"
#include <string>

ScorePanel::ScorePanel(sf::Font& font, unsigned size, sf::Vector2f position)
	:leftPlayerScore(0), rightPlayerScore(0), scoreDisplay(font)
{
	scoreDisplay.setCharacterSize(size);
	scoreDisplay.setFillColor(sf::Color::White);
	scoreDisplay.setPosition(position);

	updateScore();
}
void ScorePanel::addLeftPoint() {
	leftPlayerScore++;
	updateScore();
}
void ScorePanel::addRightPoint() {
	rightPlayerScore++;
	updateScore();
}

void ScorePanel::updateScore(){
	scoreDisplay.setString(std::to_string(leftPlayerScore) + " - " + std::to_string(rightPlayerScore));
	sf::FloatRect textRect=scoreDisplay.getLocalBounds();
	float centerX = textRect.position.x + (textRect.size.x / 2.0f);
	float centerY = textRect.position.y + (textRect.size.y / 2.0f);
	scoreDisplay.setOrigin({centerX,centerY});
}
void ScorePanel::draw(sf::RenderWindow& window) {
	window.draw(scoreDisplay);
}
