#pragma once
#include <WinSock2.h>
#include <vector>

class serveurSystem
{
private:
	WSADATA wsaData;
	SOCKET serveurSocket;
	sockaddr_in serveurAddr;

	std::vector<sockaddr_in> lClients;

	bool error;

public:

	serveurSystem();

	void start();
	void receiveAndSend();

	bool ClientSame(const sockaddr_in& a, const sockaddr_in& b);
};

