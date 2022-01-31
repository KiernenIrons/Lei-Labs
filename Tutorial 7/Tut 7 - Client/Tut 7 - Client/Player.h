#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"

class Player
{
public:
	Player(sf::RenderWindow& t_window);
	void update();
	void render(sf::RenderWindow& t_window);
	void damageTaken();
	void setPosition(sf::Vector2f t_pos);
	void setSuit(sf::Color t_col);
	sf::Vector2f getPosition();

private:
	sf::Sprite m_player;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::RenderWindow& m_window;

	float m_rotateSpeed;
	float m_maxSpeed;
	float m_angle;
	float m_turn;
	float m_rotation;
};