#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "../texturing/SkinFactory.h"

class SkinsMenu {
  sf::Text title_;
  sf::Text volumeHint_;
  sf::Text controlsHint_;
  unsigned short skinsMenuTitleFontSize = 50;
  unsigned short skinsMenuItemFontSize = 50;
  float menuItemsOffset = 60.f;
  const float titleYPercent = 0.15f;
  const float itemsStartYPercent = 0.35f;
  const float baseWidth = 1920.f;
  const float baseHeight = 1080.f;
  const float hintPercent = 0.9f;
  float spacing = 30.f;
  struct MenuItem {
    sf::Text text;
    SkinFactory::ballSkinType type;

    MenuItem(sf::Text&& t, SkinFactory::ballSkinType type)
        : text(std::move(t)), type(type) {}
  };
  std::vector<MenuItem> items_;
  int hoveredIndex_ = -1;

 public:
  SkinsMenu();
  void updateLayout(sf::Vector2u windowSize);
  void draw(sf::RenderWindow& window);
  int handleMouse(sf::Vector2i mousePos, bool isClicked);

  SkinFactory::ballSkinType getSkinType(int index) const;
};