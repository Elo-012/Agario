#include "pch.h"
#include "OnLineSystem.h"
#include <ws2tcpip.h>
#include <iostream>

OnLineSystem::OnLineSystem() {
    error = WSAStartup(MAKEWORD(2, 2), &wsadata);
    clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    serveurAddr.sin_family = AF_INET;
    serveurAddr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serveurAddr.sin_addr);
}

void OnLineSystem::ChangeName(std::string newName) {
    name = newName;
}

void OnLineSystem::Send(std::string message) {
    sendto(clientSocket, message.c_str(), message.length(), 0, (sockaddr*)&serveurAddr, sizeof(serveurAddr));
    sMessage++;
}

void OnLineSystem::Recive() {
    HANDLE hThread = CreateThread(
        NULL,
        0,
        receiverMessage,      // Fonction du thread
        &clientSocket,        // Paramètre passé
        0,
        NULL
    );

    if (hThread == NULL) {
        std::cerr << "Erreur de création du thread." << std::endl;
    }
    else {
        CloseHandle(hThread); // On ferme le handle côté créateur
    }
}

void OnLineSystem::Connect() {
    connect(clientSocket, (sockaddr*)&serveurAddr, sizeof(serveurAddr));
}

void OnLineSystem::Deconection() {
    closesocket(clientSocket);
    WSACleanup();
}

std::string OnLineSystem::getName() {
    return name;
}

SOCKET OnLineSystem::getSocket() {
    return clientSocket;
}

DWORD WINAPI OnLineSystem::receiverMessage(LPVOID lpParam) {
    OnLineSystem* _Online = static_cast<OnLineSystem*>(lpParam);
    SOCKET sock = *(SOCKET*)lpParam;
    char buffer[512];
    sockaddr_in from;
    int fromLen = sizeof(from);

    while (true) {
        int byteReceived = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&from, &fromLen);
        if (byteReceived <= 0) {
            std::cout << "Erreur recv" << std::endl;
            break;
        }

        buffer[byteReceived] = '\0';

        std::string name = nullptr;
        sf::Vector2i pos(0, 0);
        int size = 0;

        int compte = 0;
        std::string temp;

        for (size_t i = 0; i < strlen(buffer); ++i) {
            char cut = buffer[i];
            if (cut == ':') {
                switch (compte) {
                    case 0:
                        name = temp;
                        break;
                    case 1:
                        pos.x = std::stoi(temp);
                        break;
                    case 2:
                        pos.y = std::stoi(temp);
                        break;
                    }
                temp.clear();
                compte++;
            }
            else {
                temp += cut;
            }
            
        }
        size = std::stoi(temp);
        Entity* exist = nullptr;
        for (auto lName : _Online->lOtherPlayer) {
            if (lName->username == name) {
                exist = lName;
            }
        }

        if (exist == nullptr) {
            Entity e;
            e.SetPosition(pos.x, pos.y);
            e.Size = size;
            e.username = name;
            _Online->lOtherPlayer.push_back(&e);
        }
        else {
            exist->SetPosition(pos.x, pos.y);
            exist->Size = size;
        }



    }

    return 0;
}