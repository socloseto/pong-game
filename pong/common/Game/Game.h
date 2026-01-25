#pragma once
#include <SFML/Graphics.hpp>
#include "../../Objects/Ball.h"
#include "../../Objects/Paddle.h"
#include "../../ui/SkinsMenu.h"
#include "../../ui/ScorePanel.h"
#include "../../audio/AudioManager.h"
#include <iostream>
#include <stdexcept>

class Game {
public:
	Game();
	~Game();
	void run();
private:
	void processInput();
	void update(float deltaTime);
	void render();
	void resetBall();
	void onResize(const sf::Vector2u& newSize);

	float gameOverTimer_ = 0.f;
	const unsigned short framerateLimit=60;
	unsigned short fontSize = 40;
	const unsigned short minWindowWidth=800;
	const unsigned short minWindowHeight=600;
	const float paddleOffsetFromSide = 40.f;
	const unsigned short winConditionState = 11;
	float basePaddleSpeed = 450.f;

	sf::RenderWindow window_;
	sf::Music mainTheme_;
	Ball ball_;
	Paddle player_;
	Paddle cpu_;
	ScorePanel score_;
	SkinsMenu skinsMenu_;

	enum class GameState { Menu, Playing, GameOver };
	GameState state_ = GameState::Menu;
};