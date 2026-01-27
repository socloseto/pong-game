#pragma once
#include <SFML/Graphics.hpp>

class TextPanel {
 public:
  virtual ~TextPanel() = default;
  virtual void draw(sf::RenderWindow& window) = 0;
};