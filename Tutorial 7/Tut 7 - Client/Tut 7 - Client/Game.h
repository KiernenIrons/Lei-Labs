#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

//#include "Audio.h"
#include "Globals.h"
#include "Client.h"
#include "Player.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
    Client myClient{ "127.0.0.1", 1111 }; //Create client to localhost ("127.0.0.1") on port 1111

private:

    sf::RenderWindow m_window; // main SFML window

    //Audio m_audio;

    void processEvents();
    void processKeys(sf::Event t_event);
    void update();
    void render();
    void setup();


    const float fps{ 60.0f };

    std::vector<Player> m_player;
};
#endif