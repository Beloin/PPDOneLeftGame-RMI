//
// Created by beloin on 11/02/24.
//

#include "OneLeftClient.h"

const Board &OneLeftClient::board() {
    return _board;
}

int OneLeftClient::connectToServer(const std::string &host, const std::string &port) {
    int status = ConnectTo(host, port);

    if (status != 0) return status;

    // TODO: Send first Game name to start the game proc
    //  Remember: Game name is a string of 255 characters, if the name is smaller then 255, the rest of bytes will be \0
}

