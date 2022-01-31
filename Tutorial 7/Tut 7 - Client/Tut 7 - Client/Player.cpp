#include "Player.h"

Player::Player(sf::RenderWindow& t_window) :
	m_window{t_window}
{
	m_player.setPosition(G_WINDOW_WIDTH / 2 - 100, G_WINDOW_HEIGHT / 2);
	m_player.setOrigin(m_player.getGlobalBounds().width/2, m_player.getGlobalBounds().height / 2);
	m_player.setScale(.3,.3);
	m_rotation = 0.0f;
	m_rotateSpeed = 0.0f;
	m_maxSpeed = 5.0f;
	m_turn = 3.0f;
	m_angle = 0.0f;
	m_velocity = { 0,0 };
}

void Player::update()
{
	m_player.setRotation(m_rotation);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= m_turn;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += m_turn;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_angle = m_rotation * (3.14 / 180);
		m_velocity.x = cosf(m_angle) * m_rotateSpeed;
		m_velocity.y = sinf(m_angle) * m_rotateSpeed;
		if (m_rotateSpeed <= m_maxSpeed)
		{
			m_rotateSpeed = m_rotateSpeed + 0.05;
		}
		m_player.move(m_velocity);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_velocity.x = cosf(m_angle) * m_rotateSpeed;
		m_velocity.y = sinf(m_angle) * m_rotateSpeed;
		if (m_rotateSpeed > 0)
		{
			m_rotateSpeed = m_rotateSpeed - 0.05;
		}
		m_player.move(m_velocity);
	}
	else if (m_rotateSpeed >= 0)
	{
		m_rotateSpeed = m_rotateSpeed * 0.995;
		m_velocity.x = cosf(m_angle) * m_rotateSpeed;
		m_velocity.y = sinf(m_angle) * m_rotateSpeed;
		m_player.move(m_velocity);
	}

	if (m_player.getPosition().x > G_WINDOW_WIDTH + 50)
	{
		m_player.setPosition(0, m_player.getPosition().y);
	}
	if (m_player.getPosition().x < -50)
	{
		m_player.setPosition(G_WINDOW_WIDTH, m_player.getPosition().y);
	}
	if (m_player.getPosition().y > G_WINDOW_HEIGHT + 26)
	{
		m_player.setPosition(m_player.getPosition().x, 0);
	}
	if (m_player.getPosition().y < -26)
	{
		m_player.setPosition(m_player.getPosition().x, G_WINDOW_HEIGHT);
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	m_window.draw(m_player);
}

void Player::damageTaken()
{
	//take damage
}

void Player::setPosition(sf::Vector2f t_pos)
{
	m_player.setPosition(t_pos);
}

void Player::setSuit(sf::Color t_col)
{
	if (t_col == sf::Color::Blue)
	{
		m_texture.loadFromFile("ASSETS/Player3.png");
		m_player.setTexture(m_texture);
	}
	if (t_col == sf::Color::Red)
	{
		m_texture.loadFromFile("ASSETS/Player4.png");
		m_player.setTexture(m_texture);
	}
	if (t_col == sf::Color::Green)
	{
		m_texture.loadFromFile("ASSETS/Player2.png");
		m_player.setTexture(m_texture);
	}
	if (t_col == sf::Color::Yellow)
	{
		m_texture.loadFromFile("ASSETS/Player1.png");
		m_player.setTexture(m_texture);
	}
}

sf::Vector2f Player::getPosition()
{
	return m_player.getPosition();
}
