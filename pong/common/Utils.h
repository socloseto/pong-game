#pragma once
#include <SFML/Graphics.hpp>

#include "../assets/fonts/Roboto-Black_ttf.h"

template <typename T>
void centerOrigin(T& object) {
  sf::FloatRect bounds = object.getLocalBounds();

  object.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f

  });
}

static sf::Vector2f getSceneCenter(sf::Vector2f sceneSize) {
  return {sceneSize.x / 2.0f, sceneSize.y / 2.0f};
}
template <typename T>
void positionAtCenter(T& object, sf::Vector2f sceneSize) {
  centerOrigin(object);
  object.setPosition(getSceneCenter(sceneSize));
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