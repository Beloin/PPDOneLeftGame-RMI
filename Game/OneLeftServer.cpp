//
// Created by beloin on 11/02/24.
//

#include <iostream>
#include <algorithm>
#include <csignal>
#include "OneLeftServer.h"
#include "socket_utils.h"

void OneLeftServer::handle_socket(int client_fd, std::string client_addr) {
    char buffer[255];

    ssize_t status = Utils::rbytes(client_fd, (unsigned char *) buffer, 255); // Read Game Name
    if (status <= 0) {
        std::cout << "Could not receive game name. closing connection..." << std::endl;
        return;
    }

    const std::basic_string<char> &gameName = std::string(buffer);

    const std::vector<Game>::iterator &iterator = std::find_if(
            games.begin(), games.end(),
            [&gameName](const Game &game) {
                return game.name == gameName;
            }
    );

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
    Game newGame{gameName};
    newGame.setGamer(g);
    games.push_back(std::move(newGame));
}
