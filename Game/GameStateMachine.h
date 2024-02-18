//
// Created by beloin on 13/02/24.
//

#ifndef ONE_LEFT_GAMESTATEMACHINE_H
#define ONE_LEFT_GAMESTATEMACHINE_H

#include <string>
#include "Messages/Command.h"
#include "Board.h"
#include "OneLeftClient.h"

namespace StateMachine {

    enum State {
        NOT_STARTED = 0,
        IDLE = 1,
        MY_TURN = 2,
        CHOICE_ONE = 3,
        CHOICE_TWO = 4,
        CHAT = 5,
        OPTION = 6,
        LOST = 7,
        WON = 8
    };

    class Observer {
    public:
        virtual void OnMove(int fromX, int fromY, int toX, int toY) = 0;

        virtual void OnMessage(std::string message) = 0;

        virtual void OnOption(Option &option) = 0;

        virtual void OnStatusUpdate(State state) = 0;
    };

    // Should be Singleton
    class GameStateMachine {
    private:
        State currentState{NOT_STARTED};
        int x{0}, y{0};
        bool myTurn{false};
        Observer *observer{nullptr};
        Board _board{};
        Cell *firstCell{nullptr};
        Cell *secondCell{nullptr};

        OneLeftClient client{};

        void gameCallable(const RawCommand &command);

        void chatCallable(const RawCommand &command);

        void optionCallable(const RawCommand &command);

        static GameStateMachine *_instance;

        GameStateMachine();

    public:

        int requestGame(const std::string &game, const std::string &host, const std::string &port);

        void listen();

        bool selectCell(Cell *cell);

        bool sendMove();

        int sendChat(const std::string &);

        int flee();

        void reset();

        void disconnect();

        void setObserver(Observer *);

        bool isConnected();

        Board &board();

        static GameStateMachine *getInstance();

    };
}

#endif //ONE_LEFT_GAMESTATEMACHINE_H
