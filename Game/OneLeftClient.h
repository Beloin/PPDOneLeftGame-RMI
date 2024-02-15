//
// Created by beloin on 11/02/24.
//

#ifndef ONE_LEFT_ONELEFTCLIENT_H
#define ONE_LEFT_ONELEFTCLIENT_H


#include "client.h"
#include "Board.h"
#include "config.h"
#include "Messages/Command.h"

enum ClientError {
    CONNECTION = 1,
    BIG_GAME_NAME = 2,
    NOT_ACCEPTED = 3,
    INVALID_DATA = 4
};

typedef void (*CommandCallable)(const RawCommand &command);

class OneLeftClient : protected Network::Client {
private:
//    Board _board{BOARD_SIZE};
    Board _board{};
    bool isConnected{false};


    CommandCallable gameCallable{nullptr};
    GameCommand gameCommand{-1, -1};

    CommandCallable chatCallable{nullptr};
    ChatCommand chatCommand{""};

    CommandCallable optionCallable{nullptr};
    OptionCommand optionCommand{Option::EXPLODE};

public:
    const Board &board();

    int movePiece(int from, int to);

    int flee();

    int sendMessage(const std::string &msg);

    void listen();

    int requestGame(std::string const &game, std::string const &host, std::string const &port);

    void bindCallable(const CommandType &type, CommandCallable callable);

    void closeConnection();

    OneLeftClient();
};


#endif //ONE_LEFT_ONELEFTCLIENT_H
