#include "pch.h"
#include "serveurSystem.h"
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

serveurSystem::serveurSystem() {
	error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error != 0) {
		std::cout << "error wsastartup" << std::endl;
		return;
	}
	serveurSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serveurSocket == INVALID_SOCKET) {
		std::cout << "socket error" << std::endl;
		WSACleanup();
		return;
	}
	serveurAddr.sin_family = AF_INET;
	serveurAddr.sin_port = htons(12345);
	serveurAddr.sin_addr.s_addr = INADDR_ANY;
	if (bind(serveurSocket, (sockaddr*)&serveurAddr, sizeof(serveurAddr)) == SOCKET_ERROR) {
		std::cout << "error" << std::endl;
		closesocket(serveurSocket);
		WSACleanup();
		return;
	}
}

void serveurSystem::start() {
	receiveAndSend();
}

void serveurSystem::receiveAndSend() {
	char buffer[512];
	while (true) {
		sockaddr_in clienAddr;
		int clientAddrLen = sizeof(clienAddr);
		int byteReceive = recvfrom(serveurSocket, buffer, sizeof(buffer), 0, (sockaddr*)&clienAddr, &clientAddrLen);
		if (byteReceive <= 0) {
			std::cout << "error" << std::endl;
			continue;
		}
		buffer[byteReceive] = '\0';
		
		sockaddr_in client;

		bool exist = false;
		for (auto& c : lClients) {
			if (ClientSame(c, clienAddr)) {
				exist = true;
				client = c;
				break;
			}
		}
		if (!exist) {
			lClients.push_back(clienAddr);
			std::cout << "new client" << std::endl;
		}
		for (auto& c : lClients) {
			if (&c != &client) {
				sendto(serveurSocket, buffer, byteReceive, 0, (sockaddr*)&c, sizeof(c));
			}
		}
	}
}

bool serveurSystem::ClientSame(const sockaddr_in& a, const sockaddr_in& b) {
	return (a.sin_addr.s_addr == b.sin_addr.s_addr) && (a.sin_port == b.sin_port);
}