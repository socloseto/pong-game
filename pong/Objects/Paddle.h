	#pragma once
	#include "GameObject.h"
	#include "Ball.h"

	class Paddle : public GameObject {

	public:
		enum class Direction {
			None,
			Up,
			Down
		};
	private:
		const float baseSpeed_ = 400.f;
		float speed_=400;
		sf::RectangleShape paddleShape_;
		Direction direction_ = Direction::None;
	public:
		Paddle();
		void update(float deltaTime, const sf::RenderWindow& window) override;
		void draw(sf::RenderWindow& window) override;
		void handleInput();
		sf::FloatRect getBounds() const;
		sf::Vector2f getSize() const;
		sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f& pos);
		void move(float offsetX, float offsetY);
		float cpuPaddleDirectionVelocity(float BallY, float CpuY );
		void setScale(const sf::Vector2f& factors);
		float getSpeed();
		float updateSpeed(float scale);
		//void resetPosition();
	};