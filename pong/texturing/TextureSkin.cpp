#include "TextureSkin.h"
#include <stdexcept>

TextureSkin::TextureSkin(const std::string& path) {
	if (!texture_.loadFromFile(path)) {

		throw std::runtime_error("Critical error: Failed to load texture" + path);
	}

}
void TextureSkin::apply(sf::CircleShape& ballShape) {

	ballShape.setTexture(&texture_);

}