#pragma once
#include "SocketUnit.h"
#include <string>

class Client : public SocketUnit
{
	char buf_[512];

	bool isDataReceved_;
private:

public:
	Client();
	~Client();

	void InitializeSocket();

	void StartReceive();



	bool IsDataReceved();

	char *GetData();
};