#include "TextureSkin.h"
#include <stdexcept>

TextureSkin::TextureSkin(const unsigned char* data, unsigned int size) {
	if (!texture_.loadFromMemory(data, size)) {

		throw std::runtime_error("Critical error: Failed to load texture from memory");
	}

}
void TextureSkin::apply(sf::CircleShape& ballShape) {

	ballShape.setTexture(&texture_);

}