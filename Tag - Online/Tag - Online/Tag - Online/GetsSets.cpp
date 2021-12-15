#include "Server.h"

bool Server::recvall(int ID, char* data, int totalbytes)
{
	int bytesreceived = 0; //Holds the total bytes received

	while (bytesreceived < totalbytes) //While we still have more bytes to recv
	{
		int RetnCheck = recv(Connections[ID], data, totalbytes - bytesreceived, NULL); //Try to recv remaining bytes
		if (RetnCheck == SOCKET_ERROR) //If there is a socket error while trying to recv bytes
			return false; //Return false - failed to recvall
		bytesreceived += RetnCheck; //Add to total bytes received
	}

	return true; //Success!
}

bool Server::sendall(int ID, char* data, char* data2, int totalbytes)
{
	int bytessent = 0; //Holds the total bytes sent

	while (bytessent < totalbytes) //While we still have more bytes to send
	{
		int RetnCheck = send(Connections[ID], data + bytessent, totalbytes - bytessent, NULL); //Try to send remaining bytes
		if (RetnCheck == SOCKET_ERROR) //If there is a socket error while trying to send bytes
			return false; //Return false - failed to sendall
		RetnCheck = send(Connections[ID], data2 + bytessent, totalbytes - bytessent, NULL);
		if (RetnCheck == SOCKET_ERROR) //If there is a socket error while trying to send bytes
			return false; //Return false - failed to sendall
		bytessent += RetnCheck; //Add to total bytes sent
	}

	return true; //Success!
}

bool Server::sendall(int ID, char* data, int totalbytes)
{
	int bytessent = 0; //Holds the total bytes sent

	while (bytessent < totalbytes) //While we still have more bytes to send
	{
		int RetnCheck = send(Connections[ID], data + bytessent, totalbytes - bytessent, NULL); //Try to send remaining bytes
		if (RetnCheck == SOCKET_ERROR) //If there is a socket error while trying to send bytes
			return false; //Return false - failed to sendall
		bytessent += RetnCheck; //Add to total bytes sent
	}

	return true; //Success!
}

bool Server::SendPacketType(int ID, Packet _packettype)
{
	if (!sendall(ID, (char*)&_packettype, sizeof(Packet))) //Try to send packet type... If packet type fails to send
	{
		return false; //Return false: packet type not successfully sent
	}

	return true; //Return true: packet type successfully sent
}

bool Server::GetPacketType(int ID, Packet& _packettype)
{
	if (!recvall(ID, (char*)&_packettype, sizeof(Packet))) //Try to receive packet type... If packet type fails to be recv'd
	{
		return false; //Return false: packet type not successfully received
	}

	return true;//Return true if we were successful in retrieving the packet type
}

bool Server::SendPacketType(int ID, Packet _packettype)
{
	if (!sendall(ID, (char*)&_packettype, sizeof(Packet))) //Try to send packet type... If packet type fails to send
	{
		return false; //Return false: packet type not successfully sent
	}

	return true; //Return true: packet type successfully sent
}

bool Server::GetPacketType(int ID, Packet& _packettype)
{
	if (!recvall(ID, (char*)&_packettype, sizeof(Packet))) //Try to receive packet type... If packet type fails to be recv'd
	{
		return false; //Return false: packet type not successfully received
	}

	return true;//Return true if we were successful in retrieving the packet type
}

bool Server::SendInt(int ID, int _int)
{
	if (!sendall(ID, (char*)&_int, sizeof(int))) //Try to send int... If int fails to send
		return false; //Return false: int not successfully sent
	return true; //Return true: int successfully sent
}

bool Server::GetInt(int ID, int& _int)
{
	if (!recvall(ID, (char*)&_int, sizeof(int))) //Try to receive int... If int fails to be recv'd
		return false; //Return false: Int not successfully received
	return true;//Return true if we were successful in retrieving the int
}

bool Server::SendVector(int ID, sf::Vector2f& _vector)
{
	if (!SendPacketType(ID, P_Position))
	{
		return false;
	}

	int bufferLength = _vector.x;

	if (!SendInt(ID, bufferLength))
	{
		return false;
	}

	int bufferLength = _vector.y;

	if (!SendInt(ID, bufferLength))
	{
		return false;
	}

	if (!sendall(ID, (char*)std::to_string(_vector.x).c_str(), (char*)std::to_string(_vector.y).c_str(), bufferLength))
	{

	}

	return true;
}

bool Server::GetVector(int ID, sf::Vector2f& _vector)
{
	return false;
}