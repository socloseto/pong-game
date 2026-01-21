#pragma once
#include <SFML/Graphics.hpp>


template <typename T>
void centerOrigin(T& object) {
	sf::FloatRect bounds = object.getLocalBounds();

	object.setOrigin({
		bounds.position.x + bounds.size.x / 2.f,
		bounds.position.y + bounds.size.y / 2.f

		});
}

static sf::Vector2f getWindowCenter(const sf::RenderWindow &window) {
	return { window.getSize().x / 2.0f, window.getSize().y / 2.0f };
}
template <typename T>
void positionAtCenter(T &object, const sf::RenderWindow& window) {
	centerOrigin(object);
	object.setPosition(getWindowCenter(window));
}

class FontManager {
public:

	static sf::Font& getFont() {
		static sf::Font font;
		static bool isLoaded = false;
		if (!isLoaded) {
			const std::string fontPath = "fonts/Roboto-Black.ttf";
			if(!font.openFromFile(fontPath)){
				throw std::runtime_error("Failed to load font"+fontPath);
			}
			isLoaded = true;
		}
		return font;
	}
private:
	FontManager() = delete;

};