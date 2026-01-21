#pragma once
#include "GameObject.h"
#include "../texturing/BallSkin.h"

#include <vector>
#include "../common/GoalObserver.h"

class Paddle;

class Ball : public GameObject{

private:
	std::unique_ptr<BallSkin> skin_;
	float speed_ = 400.f;
	bool isOut_ = false;
	sf::CircleShape ballShape_;
	std::vector<GoalObserver*>observers_;
public:
	Ball();
	void addObserver(GoalObserver* obs);

	void notifyGoal(GoalObserver::Side side);
	void update(float deltaTime, const sf::RenderWindow &window) override;
	void draw(sf::RenderWindow& window) override;
	void setSkin(std::unique_ptr<BallSkin> newSkin);
	void bounceFromPaddle(const Paddle& paddle);
	void resetPosition(const sf::Vector2f &pos);
	sf::FloatRect getBounds() const;
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& pos);
};