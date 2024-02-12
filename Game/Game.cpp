//
// Created by beloin on 11/02/24.
//

#include "Game.h"

#include <utility>

bool Game::isClosed() const {
    return hasGamer01 && hasGamer02;
}

void Game::setGamer(GameClient gameClient) {
    if (isClosed()) return;

    if (hasGamer02) {
        gamer01 = gameClient;
        hasGamer01 = true;
        return;
    }

    gamer02 = gameClient;
    hasGamer02 = true;
}

void Game::start() {
    std::thread gamer01Thread{gamer01};
    std::thread gamer02Thread{gamer02};

//    gamer01Thread.join();
//    gamer02Thread.join();
}

Game::Game(std::string name) : name(std::move(name)) {}
