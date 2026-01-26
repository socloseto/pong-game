#pragma once
#include <SFML/Graphics.hpp>
#include "../assets/fonts/Roboto-Black_ttf.h"

template <typename T>
void centerOrigin(T& object) {
	sf::FloatRect bounds = object.getLocalBounds();

	object.setOrigin({
		bounds.position.x + bounds.size.x / 2.f,
		bounds.position.y + bounds.size.y / 2.f

		});
}

static sf::Vector2f getWindowCenter(const sf::RenderWindow& window) {
	return { window.getSize().x / 2.0f, window.getSize().y / 2.0f };
}
template <typename T>
void positionAtCenter(T& object, const sf::RenderWindow& window) {
	centerOrigin(object);
	object.setPosition(getWindowCenter(window));
}

class FontManager {
public:

	static sf::Font& getFont() {
		static sf::Font font;
		static bool isLoaded = false;
		if (!isLoaded) {
			if (!font.openFromMemory(Roboto_Black_ttf, Roboto_Black_ttf_len)) {
				throw std::runtime_error("Failed to load embedded font from memory");
			}
			isLoaded = true;
		}
		return font;
	}
private:
	FontManager() = delete;

};