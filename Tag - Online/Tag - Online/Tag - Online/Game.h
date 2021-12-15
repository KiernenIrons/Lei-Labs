#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Server.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

private:

	Server m_server;

	sf::RenderWindow m_window;
	sf::Time m_deltaTime;

	bool m_exitGame;
};
#endif