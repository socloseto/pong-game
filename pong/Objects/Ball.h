#pragma once
#include "GameObject.h"
#include "../texturing/BallSkin.h"

#include <vector>
#include "../common/GoalObserver.h"

class Paddle;

class Ball : public GameObject {

private:
	std::unique_ptr<BallSkin> skin_;
	const float baseSpeed_ = 1000.f;
	float speed_ = 1000.f;
	bool isOut_ = false;
    const float sceneWidth = 1920.f;
	const float sceneHeight = 1080.f;
	sf::CircleShape ballShape_;
	std::vector<GoalObserver*>observers_;
public:
	Ball();
	void addObserver(GoalObserver* obs);

	void notifyGoal(GoalObserver::Side side);
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void setSkin(std::unique_ptr<BallSkin> newSkin);
	void bounceFromPaddle(const Paddle& paddle);
	void resetPosition(const sf::Vector2f& pos);
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& pos);
	void checkBoundsCollision();

};