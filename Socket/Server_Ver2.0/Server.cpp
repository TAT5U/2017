#include "Server.h"

Server::Server()
{
	length_	 = 0;
	mesSize_ = 0;
}

Server::~Server()
{
	mesSize_ = 0;
	length_	 = 0;
}

void Server::InitializeSocket()
{
	SocketUnit::InitializeSocket();


	sockAddr_.sin_addr.S_un.S_addr = inet_addr(kAddressNumber.c_str());
}

void Server::SendData(std::string data)
{
	sendto(sock_, data.c_str(), 15, 0, (struct sockaddr *)&sockAddr_, sizeof(sockAddr_));
}