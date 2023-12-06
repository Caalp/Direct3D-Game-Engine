//#include "Server.h"
//
//Server::Server(int maxPlayer)
//{
//	numSockets = 1;
//	numIPs = 1;
//	maxPlayers = maxPlayer;
//	serverPort = "6001";
//}
//
//void Server::CreateServerInterface()
//{
//	server = RakNet::RakPeerInterface::GetInstance();
//	server->SetIncomingPassword("yoyo", (int)strlen("yoyo"));
//	server->SetTimeoutTime(30000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
//
//	if (!server)
//	{
//		MessageBoxA(0, "Failed to create a server", "ERROR SERVER FAILED",0);
//	}
//}
//
//void Server::StartupServer()
//{
//	socketDescriptor.port = atoi(serverPort.c_str());
//	socketDescriptor.socketFamily = AF_INET;
//	bool b = server->Startup(8, &socketDescriptor, 1) == RakNet::RAKNET_STARTED;
//	if (!b)
//	{
//		MessageBoxA(0, "Failed to start a server", "FAILED STARTING SERVER", 0);
//	}
//	server->SetMaximumIncomingConnections(8);
//	server->SetOccasionalPing(true);
//	server->SetUnreliableTimeout(1000);
//
//	DebugServerInfo();
//}
//
//void Server::ShutdownServer()
//{
//	server->Shutdown(300);
//	RakNet::RakPeerInterface::DestroyInstance(server);
//}
//
//void Server::ReceivePackets()
//{
//	for (p = server->Receive(); p; server->DeallocatePacket(p), p = server->Receive())
//	{
//		packetIdentifier = GetPacketIdentifier(p);
//		RakNet::BitStream bsIn(p->data, p->length, false);
//		RakNet::BitStream bsOut;
//
//		switch (packetIdentifier)
//		{
//		case ID_DISCONNECTION_NOTIFICATION:
//			//disconnected normally
//			OutputDebugString("ID_DISCONNECTION_NOTIFICATION from %s\n");
//			printf("ID_DISCONNECTION_NOTIFICATION from %s\n", p->systemAddress.ToString(true));
//			break;
//		case ID_ALREADY_CONNECTED:
//			OutputDebugString("ID_ALREADY_CONNECTED\n");
//			printf("ID_ALREADY_CONNECTED\n");
//			break;
//		case ID_NEW_INCOMING_CONNECTION:
//			OutputDebugString("ID_NEW_INCOMING_CONNECTION");
//			break;
//		case ID_INCOMPATIBLE_PROTOCOL_VERSION:
//			OutputDebugString("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
//			printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
//			break;
//		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
//			OutputDebugString("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
//			printf("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
//			break;
//		case ID_REMOTE_NEW_INCOMING_CONNECTION:
//			OutputDebugString("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
//			printf("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
//			break;
//		case ID_CONNECTION_BANNED:
//			OutputDebugString("You are banned from this server\n");
//			printf("You are banned from this server\n");
//			break;
//		case ID_CONNECTION_ATTEMPT_FAILED:
//			OutputDebugString("Connection attempt failed\n");
//			printf("Connection attempt failed\n");
//			break;
//		case ID_CONNECTION_LOST:
//			OutputDebugString("ID_CONNECTION_LOST from %s\n");
//			printf("ID_CONNECTION_LOST from %s\n", p->systemAddress.ToString(true));
//			break;
//		case ID_NO_FREE_INCOMING_CONNECTIONS:
//			OutputDebugString("ID_NO_FREE_INCOMING_CONNECTIONS");
//			printf("Sorry, the server is full\n");
//			break;
//		case ID_INVALID_PASSWORD:
//			OutputDebugString("Access Denied: Incorrect client password\n");
//			printf("Access Denied: Incorrect client password\n");
//			break;
//		case ID_CONNECTION_REQUEST_ACCEPTED:
//			OutputDebugString("ID_CONNECTION_REQUEST_ACCEPTED");
//			printf("Your connection has been accepted to %s with GUID %s\n",
//				p->systemAddress.ToString(true), p->guid.ToString());
//			break;
//		//case ID_SPAWN_PLAYER:
//
//		default:
//			break;
//		}
//		
//	}
//}
//
//unsigned char Server::GetPacketIdentifier(RakNet::Packet * p)
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
//
//void Server::DebugServerInfo()
//{
//	DataStructures::List<RakNet::RakNetSocket2*> sockets;
//	server->GetSockets(sockets);
//	printf("Server Started!\n");
//	printf("Socket addresses used:\n");
//
//	for (unsigned int i = 0; i < sockets.Size(); i++)
//	{
//		//printf("%i. %s\n", i + 1, sockets[i]->boundAddress.ToString(true));
//		numSockets += 1;
//	}
//	printf("My IP address:\n");
//
//	for (unsigned int i = 0; i < server->GetNumberOfAddresses(); i++)
//	{
//		printf("%i. %s\n", i + 1, server->GetLocalIP(i));
//		numIPs += 1;
//	}
//	printf("My GUID is %s\n", server->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
//
//}
