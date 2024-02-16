//
// Created by beloin on 13/02/24.
//

#ifndef ONE_LEFT_GAMESTATEMACHINE_H
#define ONE_LEFT_GAMESTATEMACHINE_H

#include <string>
#include "Messages/Command.h"

namespace StateMachine {
    enum State {
        IDLE,
        GAME,
        GAME_2,
        CHAT,
        OPTION
    };

    class GameStateMachine {
    private:
        State currentState{IDLE};
        int x{0}, y{0};
        bool myTurn{false};


    public:
        void addPosition(int x, int y);

        void sendChat(std::string);

        void sendOption(const Option &option);

        void reset();

        // TODO: Add from "other" here too?
        //  I mean, use all bypass from here, to control how game works?


    };
}

#endif //ONE_LEFT_GAMESTATEMACHINE_H
