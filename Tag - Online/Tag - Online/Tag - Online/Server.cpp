#include "Server.h"

Server::Server(int PORT, bool BroadcastPublically) // Port = Port to broadcast on - BroadcastPublically = true or false if open to public
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	if (BroadcastPublically)
	{
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast Locally
	}

	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET; //IPV4 Socket
	sListen = socket(AF_INET, SOCK_STREAM, NULL); // Create socket to listen for new connections

	if (bind(sListen, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		std::string ErrorMsg = "Failed to bind the address to the listening docket. Winsock Error: " + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	if (listen(sListen, SOMAXCONN) == SOCKET_ERROR) //Make sListen socket listen for a connection
	{
		std::string ErrorMsg = "Failed to listen on listening socket. Winsock Error:" + std::to_string(WSAGetLastError());
		MessageBoxA(NULL, ErrorMsg.c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	serverptr = this;
}

bool Server::ListenForNewConnection()
{
	SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); // Accept a new connection

	if (newConnection == 0)
	{
		std::cout << "Failed to accept client's connection" << std::endl;
		return false;
	}
	else // If client connection properly accepted
	{
		std::cout << "Client Connected! ID: " << TotalConnections << std::endl;
		Connections[TotalConnections] = newConnection;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(TotalConnections), NULL, NULL);
		 
	}

	return true;
}

void Server::ClientHandlerThread(int ID) // ID = the index  in the SOCKET connections array
{
	Packet PacketType;

	while (true)
	{
		if (!serverptr->GetPacketType(ID, PacketType))
		{
			break;
		}

		if (!serverptr->ProcessPacket(ID, PacketType))
		{
			break;
		}
	}

	std::cout << "Lost Connection to client ID: " << ID << std::endl;
	closesocket(serverptr->Connections[ID]);
	return;
}

bool Server::ProcessPacket(int ID, Packet _packettype)
{
	switch (_packettype)
	{
	case P_Position: // Packet Type: player position
	{
		sf::Vector2f Position;

		if (!GetVector(ID, Position))
		{
			return false;
		}

		for (int i = 0; i < TotalConnections; i++)
		{
			if (i == ID)
			{
				continue;
			}

			if (!SendVector(i, Position))
			{
				std::cout << "Failed to send position from client ID: " << ID << " to client ID" << i << std::endl;
				break;
			}
		}

		return true;
	}
	default:
	{
		std::cout << "Unrecognized packet: " << _packettype << std::endl;
	}
	}

	return true;
}