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
        gamer01 = std::move(gameClient);
        hasGamer01 = true;
        return;
    }

    gamer02 = std::move(gameClient);
    hasGamer02 = true;
}

void Game::start() {
    // TODO: We should join threads to wait for end game.
    std::thread gamer01Thread{gamer01, gamer02, true};
    std::thread gamer02Thread{gamer02, gamer01, false};

    gamer01Thread.detach();
    gamer02Thread.detach();
}

Game::Game(std::string name) : name(std::move(name)) {}
