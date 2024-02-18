//
// Created by beloin on 13/02/24.
//

#include "GameStateMachine.h"

using StateMachine::GameStateMachine;

static GameStateMachine *self;
GameStateMachine *GameStateMachine::_instance = new GameStateMachine();

int GameStateMachine::requestGame(
        const std::string &game, const std::string &host, const std::string &port
) {
    int status = client.requestGame(game, host, port);
    if (status) return status;

    myTurn = client.isStartTurn;
    currentState = myTurn ? MY_TURN : IDLE;
    observer->OnStatusUpdate(currentState);

    return 0;
}

void StateMachine::GameStateMachine::listen() {
    client.listen();
}

int StateMachine::GameStateMachine::sendChat(const std::string &msg) {
    return client.sendMessage(msg);
}

int StateMachine::GameStateMachine::flee() {
    currentState = LOST;
    observer->OnStatusUpdate(currentState);

    return client.flee();
}

void StateMachine::GameStateMachine::reset() {
    _board.reset();
}

bool StateMachine::GameStateMachine::isConnected() {
    return client.isConnected();
}

StateMachine::GameStateMachine::GameStateMachine() {
    self = this; // TODO: Use instance instead of this
    client.bindCallable(CommandType::GAME, [](const RawCommand &command) {
        self->gameCallable(command);
    });
    client.bindCallable(CommandType::CHAT, [](const RawCommand &command) {
        self->chatCallable(command);
    });
    client.bindCallable(CommandType::OPTION, [](const RawCommand &command) {
        self->optionCallable(command);
    });
}

void StateMachine::GameStateMachine::gameCallable(const RawCommand &command) {
    auto game = (GameCommand *) &command;

    myTurn = true;
    currentState = MY_TURN;
    observer->OnStatusUpdate(currentState);

    int fromX = game->fromX;
    int fromY = game->fromY;
    int toX = game->toX;
    int toY = game->toY;

    // TODO: Add game validation
    _board.move(fromX, fromY, toX, toY);

    observer->OnMove(fromX, fromY, toX, toY);
}

void StateMachine::GameStateMachine::chatCallable(const RawCommand &command) {
    auto chat = (ChatCommand *) &command;

    observer->OnMessage(chat->text);
}

void StateMachine::GameStateMachine::optionCallable(const RawCommand &command) {
    auto option = (OptionCommand *) &command;

    if (option->option == FLEE) {
        currentState = WON;
        observer->OnStatusUpdate(currentState);
    }

    observer->OnOption(option->option);
}

void StateMachine::GameStateMachine::setObserver(StateMachine::Observer *pObserver) {
    this->observer = pObserver;
}

Board &StateMachine::GameStateMachine::board() {
    return _board;
}

void StateMachine::GameStateMachine::disconnect() {
    client.closeConnection();
}

bool StateMachine::GameStateMachine::selectCell(Cell *cell) {
    if (currentState != MY_TURN && currentState != CHOICE_ONE) return false;

    if (currentState == CHOICE_ONE) {
        secondCell = cell;
        secondCell->setSelected(true);
        currentState = State::CHOICE_TWO;

        observer->OnStatusUpdate(currentState);

        return true;
    }

    firstCell = cell;
    firstCell->setSelected(true);
    currentState = State::CHOICE_ONE;

    observer->OnStatusUpdate(currentState);

    return true;
}

GameStateMachine *StateMachine::GameStateMachine::getInstance() {
    return _instance;
}

bool StateMachine::GameStateMachine::sendMove() {
    if (currentState != CHOICE_TWO) return false;

    client.movePiece(firstCell->x(), firstCell->y(), secondCell->x(), secondCell->y());

    firstCell->setSelected(false);
    firstCell = nullptr;
    secondCell->setSelected(true);
    secondCell = nullptr;

    currentState = IDLE;

    observer->OnStatusUpdate(currentState);
}




