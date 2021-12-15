#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ G_WINDOW_WIDTH, G_WINDOW_HEIGHT, 32U }, "Tag - Server" },
	m_exitGame{ false },
	m_server(1111)
{	
	for (int i = 0; i < G_CON_COUNT; i++)
	{
		m_server.ListenForNewConnection();
	}
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps);

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == event.type)
		{
			processKeys(event);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_deltaTime = t_deltaTime;
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_window.display();
}