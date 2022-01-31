#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{sf::VideoMode{ G_WINDOW_WIDTH, G_WINDOW_HEIGHT, 32U }, "Multiplayer"},
	m_player{m_window}
{
	m_window.setFramerateLimit(fps);
	setup();

	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
	}

	m_player.push_back(Player(m_window));
	m_player.push_back(Player(m_window));

	m_player.at(0).setSuit(sf::Color::Blue);
	m_player.at(1).setSuit(sf::Color::Green);
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();

		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}

		if (sf::Event::KeyPressed == event.type ||
			sf::Event::MouseButtonReleased == event.type) //user pressed a key
		{
			processKeys(event);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_window.close();
	}
}

void Game::update()
{
	m_player.at(0).update();
	m_player.at(1).update();

	myClient.SendVector(m_player.at(0).getPosition());

	m_player.at(1).setPosition(myClient.m_vector);
}

void Game::render()
{
	m_window.clear();

	m_player.at(0).render(m_window);
	m_player.at(1).render(m_window);

	m_window.display();
}

void Game::setup()
{
}