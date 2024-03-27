//
// Created by beloin on 11/02/24.
//

#include "OneLeftServer.h"
#include "socket_utils.h"
#include <algorithm>
#include <csignal>
#include <functional>
#include <iostream>
#include <string>

void OneLeftServer::handle_socket(int client_fd, std::string client_addr) {
  char buffer[255];

  ssize_t status =
      Utils::rbytes(client_fd, (unsigned char *)buffer, 255); // Read Game Name
  if (status <= 0) {
    std::cout << "Could not receive game name. closing connection..."
              << std::endl;
    return;
  }

  const std::basic_string<char> &gameNameG = std::string(buffer);

  const std::vector<Game>::iterator &iterator =
      std::find_if(games.begin(), games.end(), [&gameNameG](const Game &game) {
        return game.name == gameNameG;
      });

  if (iterator != games.end()) {
    if (iterator->isClosed()) {
      fprintf(stderr, "Error with Game: IS_FULL"); // SEND BACK A RESPONSE
      close(client_fd);
      return;
    }

    GameClient g{currentId++, client_fd, client_addr};
    iterator->setGamer(std::move(g));

    if (iterator->isClosed()) {
      iterator->start();
    }

    return;
  }

  GameClient g{currentId++, client_fd, client_addr};
  Game newGame{gameNameG};
  newGame.setGamer(g);
  games.push_back(std::move(newGame));
}

int OneLeftServer::handleGameRequest(std::string gameName) {
  // TODO: How to wait for game start? Use semaphores?
  const std::vector<Game>::iterator &iterator =
      std::find_if(games.begin(), games.end(), [&gameName](const Game &game) {
        return game.name == gameName;
      });

  if (iterator != games.end()) {
    if (iterator->isClosed()) {
      fprintf(stderr, "Error with Game: IS_FULL"); // SEND BACK A RESPONSE
      return 0;
    }

    GameClient g{currentId++};
    iterator->setGamer(std::move(g));

    if (iterator->isClosed()) {
      iterator->start();
    }

    return 4;
  }

  GameClient g{currentId++};
  Game newGame{gameName};
  newGame.setGamer(g);
  games.push_back(std::move(newGame));

  // TODO: Wait here for a return of accpted, here use semaphore?
  return 1;
}

OneLeftServer *toBeBind;
// TODO: bind here the requestss
// requestGame
// listen
// Remember to use internal_rpc/types
void OneLeftServer::bind(rpc::server &srv) {
  toBeBind = this; // Use this or the `toBeBind` ITEM
  srv.bind("requestGame", [this](std::string game) -> int {
    return this->handleGameRequest(game );
  });
}
