#pragma once
#include <string>
#include <WinSock2.h>

class clientSystem {
private:
    std::string name;

    WSAData wsadata;
    SOCKET clientSocket;
    sockaddr_in serveurAddr;

    int rMessage = 0;
    int sMessage = 0;

    bool error = false;

public:
    clientSystem();

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

