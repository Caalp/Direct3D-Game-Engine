#pragma once
#include "RaknetIncludes.h"
#include <string>

#define MAX_PLAYERS 10

class Server
{
public:
	Server(int);
	void CreateServerInterface();
	void StartupServer();
	void ShutdownServer();
	void ReceivePackets();

	RakNet::RakPeerInterface * server;

	std::string serverPort;
	std::string clientPort;
	std::string serverIp;
	std::string relayString;


private:
	int numSockets;
	int numIPs;
	int maxPlayers;
	unsigned char packetIdentifier;

	RakNet::SocketDescriptor socketDescriptor;
	RakNet::NetworkIDManager networkIDManager;
	RakNet::NetworkID playerNetworkID;
	RakNet::MessageID typeID;
	RakNet::Packet* p;

	unsigned char GetPacketIdentifier(RakNet::Packet* p);
	void DebugServerInfo();
};