#pragma once
#include <SFML/Graphics.hpp>
#include "../../Objects/Ball.h"
#include "../../Objects/Paddle.h"
#include "../../ui/SkinsMenu.h"
#include "../../ui/ScorePanel.h"
#include <iostream>
#include <stdexcept>
 
class Game {
public:
	Game();
	void run();
private:
	void processInput();
	void update(float deltaTime);
	void render();
	void resetBall();
	void onResize(const sf::Vector2u& newSize);

	float gameOverTimer_ = 0.f;

	sf::RenderWindow window_;

	Ball ball_;
	Paddle player_;
	Paddle cpu_;
	ScorePanel score_;
	SkinsMenu skinsMenu_;

	enum class GameState{Menu,Playing, GameOver};
	GameState state_ = GameState::Menu;
};