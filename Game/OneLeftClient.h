//
// Created by beloin on 11/02/24.
//

#ifndef ONE_LEFT_ONELEFTCLIENT_H
#define ONE_LEFT_ONELEFTCLIENT_H


#include "client.h"
#include "Board.h"
#include "config.h"

class OneLeftClient : public Network::Client {
private:
    Board _board{BOARD_SIZE};

public:
    const Board &board();

    void movePiece(int from, int to);

    void flee();

    void sendMessage(const std::string msg);


};


#endif //ONE_LEFT_ONELEFTCLIENT_H
