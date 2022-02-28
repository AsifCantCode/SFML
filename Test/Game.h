#pragma once

#include<iostream>
#include<vector>
#include<ctime>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
/*
* Class that acts as the game engine.
* Wrapper class.
*/
class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse Position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game Logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxenemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private functions
	void intializeVariables();
	void initWindow();
	void initEnemies();
public:
	//Constructor / Destructor
	Game();
	virtual ~Game();
	//accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePosition();
	void updateEnemies();
	void update();

	void renderEnemies();
	void render();
};

