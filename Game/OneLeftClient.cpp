//
// Created by beloin on 11/02/24.
//

#include "OneLeftClient.h"
#include "Messages/Command.h"
#include "internal_rpc/types.h"
#include "socket_utils.h"
#include <csignal>
#include <iostream>

Board &OneLeftClient::board() { return _board; }

int OneLeftClient::requestGame(const std::string &game, const std::string &host,
                               const std::string &port) {
  std::cout << "Requesting game..." << std::endl;
  if (game.length() > 255)
    return ClientError::BIG_GAME_NAME;

  ssize_t status = ConnectTo(host, port);
  if (status != 0)
    return ClientError::CONNECTION;
  _isConnected = true;

  // Start Command

  // TODO: Wait for server response.
  int turnResult = rpcClient->call("requestGame", game).as<int>();
  if (!turnResult) {
    _isConnected = false;
    return ClientError::NOT_ACCEPTED;
  }

  _board.setup();
  isStartTurn = turnResult == 4;

  return 0;
}

void OneLeftClient::listen() {
  if (!_isConnected)
    return;

  char buffer[65536]; // High to receive TEXT
  ssize_t status = 1;

  int oldServerFd = server_fd;
  while (status > 0 && hasConnected) {
    Result res = rpcClient->call("listen")
                     .as<Result>();
    // TODO: Here we will use result to call those callables!

    // Command
    status = Utils::rbytes(server_fd, (unsigned char *)buffer, 1);
    if (status <= 0)
      break;

    int len;
    switch (buffer[0]) {
    case CommandType::GAME:
      status = Utils::rbytes(server_fd, (unsigned char *)buffer, 4);
      if (status <= 0)
        break;

      gameCommand = GameCommand{buffer[0], buffer[1], buffer[2], buffer[3]};
      if (gameCallable != nullptr)
        gameCallable(gameCommand);

      break;
    case CommandType::CHAT:
      status = Utils::rbytes(server_fd, (unsigned char *)buffer, 2);
      if (status <= 0)
        break;
      len = (((int)buffer[0]) << 8) | buffer[1];
      status = Utils::rbytes(server_fd, (unsigned char *)buffer, len);

      chatCommand = ChatCommand{std::string(buffer, len - 1)};
      if (chatCallable != nullptr)
        chatCallable(chatCommand);

      break;
    case CommandType::OPTION:
      status = Utils::rbytes(server_fd, (unsigned char *)buffer, 1);
      if (status <= 0)
        break;
      // IF is FLEE, remove from here
      // Check for winners... Where?

      optionCommand = OptionCommand{(Option)(buffer[0] & 0xF)};
      if (optionCallable != nullptr)
        optionCallable(optionCommand);

      break;
    default:
      break;
    }
  }

  close(server_fd);
  std::cout << "Connection Closed with Server { fd: " << oldServerFd
            << ", addr: " << server_addr << " }" << std::endl;
}

int OneLeftClient::movePiece(int fromX, int fromY, int toX, int toY) {
  char buffer[4];
  buffer[0] = CommandType::GAME;

  ssize_t status = Utils::sbytes(server_fd, (unsigned char *)(buffer), 1);
  if (status <= 0) {
    closeConnection();
    return ClientError::CONNECTION;
  }

  buffer[0] = (char)fromX;
  buffer[1] = (char)fromY;
  buffer[2] = (char)toX;
  buffer[3] = (char)toY;
  status = Utils::sbytes(server_fd, (unsigned char *)(buffer), 4);
  if (status <= 0) {
    closeConnection();
    return ClientError::CONNECTION;
  }

  return 0;
}

int OneLeftClient::sendMessage(const std::string &msg) {
  rpcClient->call("message", msg);
  return 0;
}

void OneLeftClient::closeConnection() {
  _isConnected = false;
  this->disconnect();
}

int OneLeftClient::flee() {
  char buffer[1];
  buffer[0] = CommandType::OPTION;

  ssize_t status = Utils::sbytes(server_fd, (unsigned char *)(buffer), 1);
  if (status <= 0) {
    closeConnection();
    return ClientError::CONNECTION;
  }

  buffer[0] = Option::FLEE;
  status = Utils::sbytes(server_fd, (unsigned char *)(buffer), 1);
  if (status <= 0) {
    closeConnection();
    return ClientError::CONNECTION;
  }

  return 0;
}

OneLeftClient::OneLeftClient() = default;

void OneLeftClient::bindCallable(const CommandType &type,
                                 CommandCallable callable) {
  if (type == CommandType::GAME) {
    this->gameCallable = callable;
  }

  if (type == CommandType::CHAT) {
    this->chatCallable = callable;
  }

  if (type == CommandType::OPTION) {
    this->optionCallable = callable;
  }
}

bool OneLeftClient::isConnected() const { return _isConnected; }
