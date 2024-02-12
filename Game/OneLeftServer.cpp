//
// Created by beloin on 11/02/24.
//

#include <iostream>
#include <algorithm>
#include <csignal>
#include "OneLeftServer.h"
#include "socket_utils.h"

void OneLeftServer::handle_socket(int client_fd, std::string client_addr) {
    std::cout << "Started " << client_addr << std::endl;

    char buffer[255];

    Utils::rbytes(client_fd, (unsigned char *) buffer, 255);
    const std::basic_string<char> &gameName = std::string(buffer);

    const std::vector<Game>::iterator &iterator = std::find_if(
            games.begin(), games.end(),
            [&gameName](const Game &game) {
                return game.name == gameName;
            }
    );

    if (iterator != games.end()) {
        if (iterator->isClosed()) {
            fprintf(stderr, "Error with Game: IS_FULL");
            close(client_fd);
            return;
        }

        GameClient g{currentId++, client_fd};
        iterator->setGamer(std::move(g));

        if (iterator->isClosed()) {
            iterator->start();
        }

        return;
    }

    GameClient g{currentId++, client_fd};
    Game newGame{gameName};
    newGame.setGamer(g);
    games.push_back(std::move(newGame));
}
