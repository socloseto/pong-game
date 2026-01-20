#include "SkinsMenu.h"


SkinsMenu::SkinsMenu(sf::Font& font) {
	title_.setFont(font);
	title_.setString("CHOOSE YOUR SKIN");
	title_.setCharacterSize(50);
	title_.setFillColor(sf::Color::Cyan);
	title_.setPosition({ 400,100 });

}

int SkinsMenu::handleMouse(sf::Vector2i mousePos, bool isClicked) {
	sf::Vector2f mouseCoords = static_cast<sf::Vector2f>(mousePos);
	hoveredIndex_ = -1;
	for (int i = 0; i < items_.size(); i++) {
		if (items_[i].text.getGlobalBounds().contains(mouseCoords)) {
			hoveredIndex_ = i;
			if (isClicked) {
				return i;
			}
		}
	}
	return -1;
}
void SkinsMenu::draw(sf::RenderWindow& window) {
	window.draw(title_);
	for (int i = 0; i < items_.size(); i++) {
		if (i == hoveredIndex_) {
			items_[i].text.setFillColor(sf::Color::Yellow);
		}
		else {
			items_[i].text.setFillColor(sf::Color::White);
		}
		window.draw(items_[i].text);
	}

}