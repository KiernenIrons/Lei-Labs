#ifndef SERVER_HPP
#define SERVER_HPP
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Globals.h"

enum Packet
{
	P_Position,
	P_Test
};

class Server
{
public:
	Server(int PORT, bool BroadcastPublically = false);
	bool ListenForNewConnection();

private:
	static void ClientHandlerThread(int ID);

	bool sendall(int ID, char* data, char* data2, int totalbytes);
	bool sendall(int ID, char* data, int totalbytes);
	bool recvall(int ID, char* data, int totalbytes);

	bool SendPacketType(int ID, Packet _packettype);
	bool GetPacketType(int ID, Packet& _packettype);

	bool SendInt(int ID, int _int);
	bool GetInt(int ID, int& _int);

	bool SendVector(int ID, sf::Vector2f& _vector);
	bool GetVector(int ID, sf::Vector2f& _vector);

	bool ProcessPacket(int ID, Packet _packettype);

private:

	SOCKET Connections[G_CON_COUNT];
	int TotalConnections = 0;

	SOCKADDR_IN addr; // Address that the listening socket will bind to
	int addrlen = sizeof(addr);
	SOCKET sListen;
};

static Server* serverptr; // So ClientHandler can access Server functions

#endif