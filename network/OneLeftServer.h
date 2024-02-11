//
// Created by beloin on 11/02/24.
//

#ifndef ONE_LEFT_ONELEFTSERVER_H
#define ONE_LEFT_ONELEFTSERVER_H


#include <string>
#include "server.h"

class OneLeftServer : public Network::Server {
public:
    void handle_socket(int client_fd, std::string client_addr) override;
};


#endif //ONE_LEFT_ONELEFTSERVER_H
