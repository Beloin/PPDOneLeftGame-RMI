//
// Created by beloin on 11/02/24.
//

#include <iostream>
#include <utility>
#include "GameClient.h"
#include "socket_utils.h"
#include "Messages/Command.h"

void GameClient::operator()(const GameClient &other) const {
    char buffer[65536]; // High to receive TEXT

    ssize_t status = 0;
    while (status >= 0) {
        status = Utils::rbytes(fd, (unsigned char *) buffer, 1); // Add error validation
        if (status < 0) break;
        status = Utils::sbytes(other.fd, (unsigned char *) buffer, 1);
        if (status < 0) break;

        int len;
        switch (buffer[0]) {
            case CommandType::GAME:
                status = Utils::rbytes(fd, (unsigned char *) buffer, 2);
                if (status < 0) break;
                status = Utils::sbytes(other.fd, (unsigned char *) buffer, 2);
                break;
            case CommandType::CHAT:
                status = Utils::rbytes(fd, (unsigned char *) buffer, 2);
                if (status < 0) break;
                len = (((int) buffer[0]) << 8) | buffer[1];
                status = Utils::rbytes(fd, (unsigned char *) buffer, len);
                if (status < 0) break;
                status = Utils::sbytes(other.fd, (unsigned char *) buffer, len);
                break;
            case CommandType::OPTION:
                status = Utils::rbytes(fd, (unsigned char *) buffer, 1);
                if (status < 0) break;
                // IF is giveup, remove from here
                // Check for winners... Where?
                status = Utils::rbytes(fd, (unsigned char *) buffer, 1);
                break;
            default:
                break;
        }
    }

    std::cout << "Connection Closed with " << clientAddr << std::endl;
}

GameClient::GameClient(int id, int fd) : id(id), fd(fd) {}

GameClient::GameClient(int id, int fd, std::string clientAddr) : id(id), fd(fd), clientAddr(std::move(clientAddr)) {

}
