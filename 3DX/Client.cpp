//#include "Client.h"
//
//Client::Client(int maxPlayer)
//{
//	numSockets = 1;
//	numIPs = 1;
//	maxPlayers = maxPlayer;
//	serverPort = "6001";
//}
//
//void Client::CreateClientInterface()
//{
//	client = RakNet::RakPeerInterface::GetInstance();
//	
//	if (!client)
//	{
//		MessageBoxA(0, "Failed to create a client", "ERROR SERVER FAILED", 0);
//	}
//	RakNet::SystemAddress clientId = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
//}
//
//void Client::SetIP()
//{
//	serverIp = "127.0.0.1";
//	clientPort = "6000";
//}
//
//void Client::StartupClient()
//{
//	socketDescriptor = RakNet::SocketDescriptor(atoi(serverPort.c_str()),0);
//	socketDescriptor.socketFamily = AF_INET;
//	//bool b = server->Startup(8, &socketDescriptor, 1) == RakNet::RAKNET_STARTED;
//	client->Startup(8, &socketDescriptor, 1);
//	client->SetOccasionalPing(true);
//
//	RakNet::ConnectionAttemptResult car = client->Connect(serverIp.c_str(), std::stoul(serverPort.c_str()), "yoyo", 4);
//	RakAssert(car == RakNet::CONNECTION_ATTEMPT_STARTED);
//}
//
//void Client::ShutdownClient()
//{
//	client->Shutdown(300);
//	RakNet::RakPeerInterface::DestroyInstance(client);
//}
//
//void Client::ReceivePackets()
//{
//	for (p = client->Receive(); p; client->DeallocatePacket(p), p = client->Receive())
//	{
//		packetIdentifier = GetPacketIdentifier(p);
//		RakNet::BitStream bsIn(p->data, p->length, false);
//		RakNet::BitStream bsOut;
//
//		switch (packetIdentifier)
//		{
//		case ID_DISCONNECTION_NOTIFICATION:
//			//disconnected normally
//			printf("ID_DISCONNECTION_NOTIFICATION from %s\n", p->systemAddress.ToString(true));
//			break;
//		case ID_ALREADY_CONNECTED:
//			printf("ID_ALREADY_CONNECTED\n");
//			break;
//		case ID_NEW_INCOMING_CONNECTION:
//			break;
//		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
//			printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
//			break;
//		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
//			printf("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
//			break;
//		case ID_REMOTE_NEW_INCOMING_CONNECTION:
//			printf("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
//			break;
//		case ID_CONNECTION_BANNED:
//			printf("You are banned from this server\n");
//			break;
//		case ID_CONNECTION_ATTEMPT_FAILED:
//			printf("Connection attempt failed\n");
//			break;
//		case ID_CONNECTION_LOST:
//			printf("ID_CONNECTION_LOST from %s\n", p->systemAddress.ToString(true));
//			break;
//		case ID_NO_FREE_INCOMING_CONNECTIONS:
//			printf("Sorry, the server is full\n");
//			break;
//		case ID_INVALID_PASSWORD:
//			printf("Access Denied: Incorrect client password\n");
//			break;
//		case ID_CONNECTION_REQUEST_ACCEPTED:
//			printf("Your connection has been accepted to %s with GUID %s\n",
//				p->systemAddress.ToString(true), p->guid.ToString());
//			break;
//			//case ID_SPAWN_PLAYER:
//
//		default:
//			break;
//		}
//
//	}
//}
//
//unsigned char Client::GetPacketIdentifier(RakNet::Packet * p)
//{
//	if (p == 0)
//	{
//		return 255;
//	}
//	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
//	{
//		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
//		return (unsigned char)p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
//	}
//	else
//	{
//		return (unsigned char)p->data[0];
//	}
//}
