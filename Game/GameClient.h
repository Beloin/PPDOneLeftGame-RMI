//
// Created by beloin on 11/02/24.
//

#ifndef ONE_LEFT_GAMECLIENT_H
#define ONE_LEFT_GAMECLIENT_H


#include <thread>
#include "Board.h"

class GameClient {

public:
    int id;
    int fd;
    std::string clientAddr;

    GameClient(int id, int fd);
    GameClient(int id, int fd, std::string clientAddr);

    void operator()(const GameClient &other) const;

};


#endif //ONE_LEFT_GAMECLIENT_H
