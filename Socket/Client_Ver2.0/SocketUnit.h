//#pragma once
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")


class SocketUnit
{
private:
	const int kHtons = 12345;

protected:
	WSADATA wsaData_;
	SOCKET sock_;

	struct sockaddr_in sockAddr_;

public:
	SocketUnit();
	~SocketUnit();


	void InitializeSocket();


	void CloseSocket();
};