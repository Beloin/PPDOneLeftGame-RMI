//
// Created by beloin on 04/01/24.
//

#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <rpc/client.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include "socket_utils.h"

using Network::Client;

int Client::ConnectTo(const std::string &host, const std::string &port) {
  std::cout << "Connecting to RPCServer " << host << std::endl;
  rpcClient = new rpc::client(host, std::stoi(port));
  // auto status = ConnectToServer(host, port);
  // return status;
  return 0;
}

int Client::ConnectToServer(std::string const &host, std::string const &port) {
  struct addrinfo hints {
  }, *servinfo, *p;
  char s[INET6_ADDRSTRLEN];
  int rv;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((rv = getaddrinfo(host.data(), port.data(), &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    return 1;
  }

  for (p = servinfo; p != nullptr; p = p->ai_next) {
    if ((server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) ==
        -1) {
      //            perror("client: socket");
      continue;
    }

    if (connect(server_fd, p->ai_addr, p->ai_addrlen) == -1) {
      close(server_fd);
      //            perror("client connect");
      continue;
    }

    break;
  }

  if (p == nullptr) {
    fprintf(stderr, "client: failed to connect\n");
    return 3;
  }

  inet_ntop(p->ai_family, Utils::get_in_addr((struct sockaddr *)p->ai_addr), s,
            sizeof s);
  printf("client: connecting to %s with fd %d\n", s, server_fd);
  server_addr = s;
  freeaddrinfo(servinfo);

  hasConnected = true;

  return 0;
}

Network::Client::~Client() { delete (this->rpcClient); }

bool Network::Client::IsConnected() const { return hasConnected; }

void Network::Client::disconnect() {
  hasConnected = false;
  delete (this->rpcClient);
  server_fd = -1;
}
