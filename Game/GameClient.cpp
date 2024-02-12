//
// Created by beloin on 11/02/24.
//

#include "GameClient.h"
#include "socket_utils.h"
#include "Messages/Command.h"

void GameClient::operator()(const GameClient &other) {
    char buffer[65536]; // High to receive TEXT
    Utils::rbytes(fd, (unsigned char *) buffer, 1); // Add error valdiation
    Utils::sbytes(other.fd, (unsigned char *) buffer, 1);

    int len;
    switch (buffer[0]) {
        case CommandType::GAME:
            Utils::rbytes(fd, (unsigned char *) buffer, 2);
            Utils::sbytes(other.fd, (unsigned char *) buffer, 2);
            break;
        case CommandType::CHAT:
            Utils::rbytes(fd, (unsigned char *) buffer, 2);
            len = (((int) buffer[0]) << 8) | buffer[1];
            Utils::rbytes(fd, (unsigned char *) buffer, len);
            Utils::sbytes(other.fd, (unsigned char *) buffer, len);
            break;
        case CommandType::OPTION:
            Utils::rbytes(fd, (unsigned char *) buffer, 1);
            // IF is giveup, remove from here
            // Check for winners... Where?
            Utils::rbytes(fd, (unsigned char *) buffer, 1);
            break;
        default:
            break;
    }


}

GameClient::GameClient(int id, int fd) : id(id), fd(fd) {}
