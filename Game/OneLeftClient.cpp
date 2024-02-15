//
// Created by beloin on 11/02/24.
//

#include <iostream>
#include <csignal>
#include "OneLeftClient.h"
#include "socket_utils.h"
#include "Messages/Command.h"

const Board &OneLeftClient::board() {
    return _board;
}

int OneLeftClient::requestGame(const std::string &game, const std::string &host, const std::string &port) {
    std::cout << "Requesting game..." << std::endl;
    if (game.length() > 255) return ClientError::BIG_GAME_NAME;

    ssize_t status = ConnectTo(host, port);
    if (status != 0) return ClientError::CONNECTION;

    std::string result{game};
    for (int i = result.length(); i < 255; i++) {
        result += '\0';
    }

    // Query for game
    status = Utils::sbytes(server_fd, (unsigned char *) result.c_str(), 255);
    if (status <= 0) {
        return ClientError::CONNECTION;
    }

    // Start Command
    unsigned char buffer;
    status = Utils::rbytes(server_fd, &buffer, 1);
    if (status <= 0) {
        return ClientError::CONNECTION;
    }

    if (!buffer) {
        return ClientError::NOT_ACCEPTED;
    }

    _board.setup();
    isConnected = true;

    return 0;
}

void OneLeftClient::listen() {
    if (!isConnected) return;

    // TODO: Use dynamic memory
    char buffer[65536]; // High to receive TEXT
    ssize_t status = 1;

    while (status > 0) {
        // Command
        status = Utils::rbytes(server_fd, (unsigned char *) buffer, 1);
        if (status <= 0) break;

        int len;
        switch (buffer[0]) {
            case CommandType::GAME:
                status = Utils::rbytes(server_fd, (unsigned char *) buffer, 2);
                if (status <= 0) break;

                gameCommand = GameCommand{buffer[0], buffer[1]};
                if (gameCallable != nullptr) gameCallable(gameCommand);

                break;
            case CommandType::CHAT:
                status = Utils::rbytes(server_fd, (unsigned char *) buffer, 2);
                if (status <= 0) break;
                len = (((int) buffer[0]) << 8) | buffer[1];
                status = Utils::rbytes(server_fd, (unsigned char *) buffer, len);

                chatCommand = ChatCommand{std::string(buffer, len)};
                if (chatCallable != nullptr) chatCallable(chatCommand);

                break;
            case CommandType::OPTION:
                status = Utils::rbytes(server_fd, (unsigned char *) buffer, 1);
                if (status <= 0) break;
                // IF is FLEE, remove from here
                // Check for winners... Where?

                optionCommand = OptionCommand{(Option) (buffer[0] & 0xF)};
                if (optionCallable != nullptr) optionCallable(optionCommand);

                break;
            default:
                break;
        }
    }

    std::cout << "Connection Closed with Server { fd: " << server_fd << ", addr: " << server_addr << " }" << std::endl;
}

void OneLeftClient::bindCallable(const CommandType &type, CommandCallable callable) {
    if (type == CommandType::GAME) { this->gameCallable = callable; }

    if (type == CommandType::CHAT) { this->chatCallable = callable; }

    if (type == CommandType::OPTION) { this->optionCallable = callable; }
}

int OneLeftClient::movePiece(int from, int to) {
    char buffer[2]; // High to receive TEXT
    buffer[0] = CommandType::GAME;

    ssize_t status = Utils::sbytes(server_fd, (unsigned char *) (buffer), 1);
    if (status <= 0) return ClientError::CONNECTION;

    buffer[0] = (char) from;
    buffer[1] = (char) to;
    status = Utils::sbytes(server_fd, (unsigned char *) (buffer), 2);
    if (status <= 0) return ClientError::CONNECTION;

    return 0;
}

int OneLeftClient::sendMessage(const std::string &msg) {
    unsigned long length = msg.length();
    if (length > 0xFFFF) return ClientError::INVALID_DATA;

    char buffer[2];
    buffer[0] = CommandType::CHAT;

    ssize_t status = Utils::sbytes(server_fd, (unsigned char *) (buffer), 1);
    if (status <= 0) return ClientError::CONNECTION;

    buffer[0] = (char) (length >> 8);
    buffer[1] = (char) length;

    status = Utils::sbytes(server_fd, (unsigned char *) (buffer), 2);
    if (status <= 0) return ClientError::CONNECTION;

    status = Utils::sbytes(server_fd, (unsigned char *) (msg.c_str()), length);
    if (status <= 0) return ClientError::CONNECTION;

    return 0;
}

void OneLeftClient::closeConnection() {
    hasConnected = false;
    close(server_fd);
}

int OneLeftClient::flee() {
    char buffer[1];
    buffer[0] = CommandType::OPTION;

    ssize_t status = Utils::sbytes(server_fd, (unsigned char *) (buffer), 1);
    if (status <= 0) return ClientError::CONNECTION;

    buffer[0] = Option::FLEE;
    status = Utils::sbytes(server_fd, (unsigned char *) (buffer), 1);
    if (status <= 0) return ClientError::CONNECTION;

    return 0;
}

OneLeftClient::OneLeftClient() {}


