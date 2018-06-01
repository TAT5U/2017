#include "SocketUnit.h"

SocketUnit::SocketUnit()
{
}

SocketUnit::~SocketUnit()
{

}


void SocketUnit::InitializeSocket()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData_);
	sock_ = socket(AF_INET, SOCK_DGRAM, 0);

	sockAddr_.sin_family = AF_INET;
	sockAddr_.sin_port = htons(kHtons);
}

void SocketUnit::CloseSocket()
{
	closesocket(sock_);
	WSACleanup();
}