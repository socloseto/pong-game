#pragma once
#include "Ball.h"
#include "GameObject.h"

class Paddle : public GameObject {
 public:
  enum class Direction { None, Up, Down };

 private:
  const float baseSpeed_ = 700.f;
  float speed_ = 700;
  float baseDeadZone = 15.f;
  float basePaddleWidth = 15.f;
  float basePaddleHeight = 100.f;
  const float sceneWidth = 1920.f;
  const float sceneHeight = 1080.f;
  sf::RectangleShape paddleShape_;
  Direction direction_ = Direction::None;

 public:
  Paddle();
  void update(float deltaTime) override;
  void draw(sf::RenderWindow& window) override;
  void handleInput();
  sf::FloatRect getBounds() const;
  sf::Vector2f getSize() const;
  sf::Vector2f getPosition() const;
  void setPosition(const sf::Vector2f& pos);
  void move(float offsetX, float offsetY);
  float cpuPaddleDirectionVelocity(float BallY, float CpuY);
  float getSpeed();
};