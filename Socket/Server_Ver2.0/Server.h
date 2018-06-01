#pragma once
#include "SocketUnit.h"
#include <string>

class Server : public SocketUnit
{
private:

	const std::string kAddressNumber = "127.0.0.1";


	int length_;
	int mesSize_;

public:
	Server();
	~Server();

	void InitializeSocket();

	void SendData(std::string data);
};