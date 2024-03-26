//
// Created by beloin on 11/02/24.
//

#ifndef ONE_LEFT_ONELEFTSERVER_H
#define ONE_LEFT_ONELEFTSERVER_H

#include "Game.h"
#include "server.h"
#include <string>
#include <vector>

class OneLeftServer : public Network::Server {

private:
  std::vector<Game> games{};
  int currentId{0};

public:
  void handle_socket(int client_fd, std::string client_addr) override;
  void bind(rpc::server &srv) override;
};

#endif // ONE_LEFT_ONELEFTSERVER_H
