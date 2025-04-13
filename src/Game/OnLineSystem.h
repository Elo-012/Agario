#pragma once
#include <string>
#include <vector>
#include <WinSock2.h>
#include "Entity.h"

class OnLineSystem {
private:
    std::string name;

    WSAData wsadata;
    SOCKET clientSocket;
    sockaddr_in serveurAddr;

    std::vector<Entity*> lOtherPlayer;

    int rMessage = 0;
    int sMessage = 0;

    bool error = false;

public:
    OnLineSystem();

    void ChangeName(std::string newName);
    void Send(std::string message);
    void Recive(); // Lance un thread pour recevoir
    void Connect();
    void Deconection();

    std::string getName();
    SOCKET getSocket();

    // Fonction de thread (CreateThread)
    static DWORD WINAPI receiverMessage(LPVOID lpParam);
};

