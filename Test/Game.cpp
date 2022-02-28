#include "Game.h"

//Private Functions

void Game::intializeVariables()
{
	this->window = nullptr;

	//Game Logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxenemies = 10;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game Debut", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	/*this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f)*/;
}

//Constuctors / Desturctors
Game::Game()
{
	this->intializeVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//Functions

void Game::spawnEnemy()
{
	/*
		spawns enemies and sets colors and positions
		-sets random position and color
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),//in order to fit the width in screen
		0.f
	);

	this->enemy.setFillColor(sf::Color::Cyan);

	//Spawn the enemy
	this->enemies.push_back(this->enemy);
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::pollEvents()
{
	//Event Polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePosition()
{
	/*
		return void
		Relative to window
		updates mouse position
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	//Timer update
	if (this->enemies.size() < this->maxenemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies 
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 3.f);

		if (this->enemies[i].getPosition().y > window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
		}

	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Gamepoints
					this->points += 1;
					std::cout << "Points: " << this->points << "\n";
				}

			}
		}	
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePosition();

		this->updateEnemies();
	}
	
	if (this->health <= 0)
		this->endGame = true;
}

void Game::renderEnemies()
{
	for (auto &e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		Renders game objects
	*/

	this->window->clear();

	//Draw game objects
	this->renderEnemies();
	/*this->window->draw(this->enemy);*/

	this->window->display();
}