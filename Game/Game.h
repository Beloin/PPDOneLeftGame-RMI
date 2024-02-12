//
// Created by beloin on 11/02/24.
//

#ifndef ONE_LEFT_GAME_H
#define ONE_LEFT_GAME_H


#include <string>
#include <thread>
#include "GameClient.h"

class Game {
public:
    explicit Game(std::string name);

    std::string name; // Act as ID

    GameClient gamer01{-1, -1};
    GameClient gamer02{-1, -1};

    [[nodiscard]] bool isClosed() const;

    void setGamer(GameClient gameClient);

    void start();

private:
    bool hasGamer01{false};
    bool hasGamer02{false};


};


#endif //ONE_LEFT_GAME_H
