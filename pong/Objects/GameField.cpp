#include "GameField.h"

GameField::GameField(float width, float height) {
  bgColor_ = sf::Color(10, 10, 15);

  centerLine_.setSize({4.f, height});
  centerLine_.setFillColor(sf::Color(255, 255, 255, 50));
  centerLine_.setPosition({width / 2.f - 2.f, 0.f});

  border_.setSize({width, height});
  border_.setFillColor(sf::Color::Transparent);
  border_.setOutlineThickness(-5.f);
  border_.setOutlineColor(sf::Color(0, 255, 255, 80));
}

void GameField::draw(sf::RenderWindow& window) const {
  window.draw(centerLine_);
  window.draw(border_);
}