#include "Client.h"

Client::Client()
{
	isDataReceved_ = false;
}

Client::~Client()
{

}

void Client::InitializeSocket()
{
	SocketUnit::InitializeSocket();


	sockAddr_.sin_addr.S_un.S_addr = INADDR_ANY;

	StartReceive();
}

void Client::StartReceive()
{
	bind(sock_, (struct sockaddr *)&sockAddr_, sizeof(sockAddr_));

	memset(buf_, 0, sizeof(buf_));

	recv(sock_, buf_, sizeof(buf_), 0);
}

char *Client::GetData()
{
	return buf_;
}