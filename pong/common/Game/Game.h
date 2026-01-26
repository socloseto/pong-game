#pragma once
#include <SFML/Graphics.hpp>
#include "../../Objects/Ball.h"
#include "../../Objects/Paddle.h"
#include "../../Objects/GameField.h"
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
	void initUI();
	void initEntities();
	void initAudio();
	void togglePause();
	void processInput();
	void update(float deltaTime);
	void render();
	void resetBall();
	void onResize(const sf::Vector2u& newSize);
	const float virtualWidth = 1920.f;
    const float virtualHeight = 1080.f;
    const float paddleOffset = 100.f;
    GameField field_{virtualWidth, virtualHeight};
	float gameOverTimer_ = 0.f;
	const unsigned short framerateLimit=60;
	unsigned short fontSize = 40;
	const unsigned short winConditionState = 11;
	float basePaddleSpeed = 450.f;

	sf::RenderWindow window_;
	sf::Music mainTheme_;
	Ball ball_;
	Paddle player_;
	Paddle cpu_;
	ScorePanel score_;
	SkinsMenu skinsMenu_;
	sf::Font font_;
	sf::Text pauseText_;
	sf::Text pauseHintText_;
	sf::RectangleShape pauseOverlay_;
	enum class GameState { Menu, Playing, GameOver, Paused };
	GameState state_ = GameState::Menu;
	GameState prevState_ = GameState::Playing;
};