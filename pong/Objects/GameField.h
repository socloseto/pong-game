#pragma once
#include <SFML/Graphics.hpp>

class GameField {
 public:
  GameField(float width, float height);
  void draw(sf::RenderWindow& window) const;

 private:
  sf::RectangleShape border_;
  sf::RectangleShape centerLine_;
  sf::Color bgColor_;
};