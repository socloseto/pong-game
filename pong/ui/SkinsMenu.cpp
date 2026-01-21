#include "SkinsMenu.h"
#include "../common/Utils.h"

SkinsMenu::SkinsMenu() : title_(FontManager::getFont()) {
	title_.setString("CHOOSE YOUR SKIN");
	title_.setCharacterSize(50);
	title_.setFillColor(sf::Color::Cyan);
	centerOrigin(title_);
	title_.setPosition({ 400,100 });

	std::vector<std::pair<std::string, SkinFactory::ballSkinType>> options = {
		{ "Donut Eye", SkinFactory::DonutEye},
		{ "Watermelon", SkinFactory::Watermelon},
		{ "Blue Eye", SkinFactory::BlueEye},
		{ "Cyclope Eye", SkinFactory::CyclopeEye },
		{ "Cracked Eye", SkinFactory::CrackedEye }
	};

	for (size_t i = 0; i < options.size(); i++) {
		MenuItem item{ sf::Text(FontManager::getFont()), options[i].second };

		item.text.setString(options[i].first);
		item.text.setCharacterSize(30);
		centerOrigin(item.text);
		item.text.setPosition({ 400.f, 250.f + static_cast<float>(i) * 60.f });
		item.text.setFillColor(sf::Color::White);

		items_.push_back(std::move(item));
	}
}


SkinFactory::ballSkinType SkinsMenu::getSkinType(int index) const {
	
	if (index >= 0 && index < (int)items_.size()) {
		return items_[index].type;
	}
	return SkinFactory::BlueEye;
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