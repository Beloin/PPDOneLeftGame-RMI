//
// Created by beloin on 04/01/24.
//
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <rpc/server.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

using Network::Server;

using namespace Network;

// TODO: Here we will add RMI server
int Server::serve(const std::string &port) {
  std::cout << "Starting RMI server in localhost:" << port << std::endl;
  srv = rpc::server(std::stoi(port));
  server_on = true;

  // Here add bindings to calls
  srv.run();

  // TODO: Now we need a new way to use handle_socket
  return 0;
}

Server::Server()
    : should_run(true), server_on(false), isClosed(false), srv(0) {}

Network::Server::~Server() {
  if (isClosed)
    return;

  isClosed = true;
  server_on = false;
  should_run = false;

  srv.stop();
}

bool Network::Server::IsRunning() const { return server_on; }

void Network::Server::dispose() {
  if (isClosed)
    return;

  isClosed = true;
  server_on = false;
  should_run = false;

  srv.stop();
}
