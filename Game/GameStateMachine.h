//
// Created by beloin on 13/02/24.
//

#ifndef ONE_LEFT_GAMESTATEMACHINE_H
#define ONE_LEFT_GAMESTATEMACHINE_H

#include <string>
#include "Messages/Command.h"
#include "Board.h"

namespace StateMachine {

    class Observable {
        virtual void OnOption(Option &option) = 0;

        virtual void OnMessage(std::string message) = 0;

        virtual void OnMove(int x, int y) = 0;
    };

    enum State {
        NOT_STARTED,
        IDLE,
        MY_TURN,
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
        Observable *observable;

        Board board{};


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
