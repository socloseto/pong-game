#include "SkinsMenu.h"
#include "../common/Utils.h"

SkinsMenu::SkinsMenu()
    : title_(FontManager::getFont()),
      volumeHint_(FontManager::getFont()),
      controlsHint_(FontManager::getFont()) {
	title_.setString("CHOOSE YOUR SKIN");
	title_.setCharacterSize(skinsMenuTitleFontSize);
	title_.setFillColor(sf::Color::Cyan);
	centerOrigin(title_);
	title_.setPosition({ baseWidth / 2.f, baseHeight * titleYPercent });
	controlsHint_.setString("Press ESC to Quit | P or SPACE to pause game");
    controlsHint_.setCharacterSize(22);
    controlsHint_.setFillColor(sf::Color(200, 200, 200));

	volumeHint_.setString("Press [+] or [-] to change volume");
	volumeHint_.setCharacterSize(20);
	volumeHint_.setFillColor(sf::Color(150, 150, 150));


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
		item.text.setCharacterSize(skinsMenuItemFontSize);
		centerOrigin(item.text);
		item.text.setPosition({ baseWidth/2.f, baseHeight* itemsStartYPercent + static_cast<float>(i) * menuItemsOffset });
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
void SkinsMenu::updateLayout(sf::Vector2u windowSize) {
	const float centerX = windowSize.x / 2.f;
	const float titleY = windowSize.y * titleYPercent;
	title_.setCharacterSize(static_cast<unsigned int>(skinsMenuTitleFontSize));
	centerOrigin(title_);
	title_.setPosition({ centerX, titleY });
	controlsHint_.setCharacterSize(static_cast<unsigned int>(20));
	volumeHint_.setCharacterSize(static_cast<unsigned int>(20));
	const float startY = windowSize.y * itemsStartYPercent;
	for (size_t i = 0; i < items_.size(); i++) {
		items_[i].text.setCharacterSize(static_cast<unsigned int>(skinsMenuItemFontSize));
		centerOrigin(items_[i].text);
		const float verticalOffset = i * (menuItemsOffset);
		items_[i].text.setPosition({ centerX, startY + verticalOffset });
	}
}

int SkinsMenu::handleMouse(sf::Vector2i mousePos, bool isClicked) {
	sf::Vector2f mouseCoords = static_cast<sf::Vector2f>(mousePos);
	int lastHover = hoveredIndex_;
	hoveredIndex_ = -1;
	for (int i = 0; i < (int)items_.size(); i++) {
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
        float rightEdge = baseWidth * hintPercent;
        float bottomY = baseHeight * hintPercent;

        sf::FloatRect volBounds = volumeHint_.getGlobalBounds();
        volumeHint_.setPosition({rightEdge - volBounds.size.x, bottomY});
        window.draw(volumeHint_);

        sf::FloatRect ctrlBounds = controlsHint_.getGlobalBounds();
        controlsHint_.setPosition({rightEdge - ctrlBounds.size.x, bottomY - spacing});
        window.draw(controlsHint_);

}