//
// Created by beloin on 11/02/24.
//

#ifndef ONE_LEFT_ONELEFTSERVER_H
#define ONE_LEFT_ONELEFTSERVER_H


#include <string>
#include <vector>
#include "server.h"
#include "Game.h"

class OneLeftServer : public Network::Server {

private:
    std::vector<Game> games{};
    int currentId{0};

public:

    void handle_socket(int client_fd, std::string client_addr) override;
};


#endif //ONE_LEFT_ONELEFTSERVER_H
