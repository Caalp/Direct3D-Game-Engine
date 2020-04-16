#pragma once
#include "RaknetIncludes.h"
#include <string>

class Client
{
	Client(int = 8);
	void CreateClientInterface();
	void SetIP();
	void StartupClient();
	void ShutdownClient();
	void ReceivePackets();

	RakNet::RakPeerInterface * client;

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
	//void DebugServerInfo();
};