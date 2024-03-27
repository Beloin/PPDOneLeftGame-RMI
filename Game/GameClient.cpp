// Created by beloin on 11/02/24.
//

#include <iostream>
#include <utility>
#include <csignal>
#include "GameClient.h"
#include "socket_utils.h"
#include "Messages/Command.h"

// TODO: Pratically this will be all removed
void GameClient::operator()(const GameClient &other, bool isStartTurn) const {
    // std::cout << "Started Gateway for Client " << *this << std::endl;
    // char buffer[65536]; // High to receive TEXT
    // ssize_t status = 0;
    //
    // buffer[0] = isStartTurn ? 4 : 1;
    // status = Utils::sbytes(fd, (unsigned char *) buffer, 1);
    //
    // std::cout << "Sent start command for Client " << this << std::endl;
    //
    // while (status > 0) {
    //     // Command
    //     status = Utils::rbytes(fd, (unsigned char *) buffer, 1);
    //     if (status <= 0) break;
    //     status = Utils::sbytes(other.fd, (unsigned char *) buffer, 1);
    //     if (status <= 0) break;
    //
    //     int len;
    //     switch (buffer[0]) {
    //         case CommandType::GAME:
    //             std::cout << "Proxying GAME COMMAND for Client " << this << std::endl;
    //             status = Utils::rbytes(fd, (unsigned char *) buffer, 4);
    //             if (status <= 0) break;
    //             status = Utils::sbytes(other.fd, (unsigned char *) buffer, 4);
    //             break;
    //         case CommandType::CHAT:
    //             std::cout << "Proxying CHAT COMMAND for Client {" << id << "}" << std::endl;
    //             status = Utils::rbytes(fd, (unsigned char *) buffer, 2);
    //             if (status <= 0) break;
    //
    //             status = Utils::sbytes(other.fd, (unsigned char *) buffer, 2);
    //             if (status <= 0) break;
    //
    //             len = (((int) buffer[0]) << 8) | buffer[1];
    //             status = Utils::rbytes(fd, (unsigned char *) buffer, len);
    //
    //             if (status <= 0) break;
    //             status = Utils::sbytes(other.fd, (unsigned char *) buffer, len);
    //             break;
    //         case CommandType::OPTION:
    //             std::cout << "Proxying OPTION COMMAND for Client {" << id << "}" << std::endl;
    //             status = Utils::rbytes(fd, (unsigned char *) buffer, 1);
    //             if (status <= 0) break;
    //             // IF is FLEE, remove from here
    //             // Check for winners... Where?
    //             status = Utils::sbytes(other.fd, (unsigned char *) buffer, 1);
    //             break;
    //         default:
    //             break;
    //     }
    // }
    //
    // std::cout << "Connection Closed with Client " << this << std::endl;
//    close(other.fd);
}

GameClient::GameClient(int id) : id(id) {}

GameClient::GameClient(int id, std::string clientAddr) : id(id), clientAddr(std::move(clientAddr)) {

}

std::ostream &operator<<(std::ostream &os, const GameClient &client) {
    os << "{ id: " << client.id << ", clientAddr: " << client.clientAddr << " }";
    return os;
}

std::ostream &operator<<(std::ostream &os, const GameClient *client) {
    return os << "{ id: " << client->id << " }";
}
