//
// Created by beloin on 13/02/24.
//

#include <iostream>
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
    board().reset();

    return 0;
}

void StateMachine::GameStateMachine::listen() {
    client.listen();
}

int StateMachine::GameStateMachine::sendChat(const std::string &msg) {
    return client.sendMessage(msg);
}

int StateMachine::GameStateMachine::flee() {
    if (!isConnected()) return 1;

    int status = client.flee();
    if (status) return status;

    currentState = LOST;
    observer->OnStatusUpdate(currentState);

    return 0;
}

void StateMachine::GameStateMachine::reset() {
    _board.reset();
    disconnect();
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

    int fromX = game->fromX;
    int fromY = game->fromY;
    int toX = game->toX;
    int toY = game->toY;

    // TODO: Add game validation
    _board.move(fromX, fromY, toX, toY);

    observer->OnMove(fromX, fromY, toX, toY);

    myTurn = true;
    currentState = MY_TURN;
    observer->OnStatusUpdate(currentState);

    if (!isBoardPlayable()) {
        currentState = LOST;
        observer->OnStatusUpdate(currentState);
    }
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

// TODO: Remove selection
bool StateMachine::GameStateMachine::selectCell(Cell *cell) {
    if ((currentState != MY_TURN && currentState != CHOICE_ONE) || !cell->isValid()) return false;

    if (currentState == MY_TURN) {
        bool hasMovement = board().hasMovement(*cell);
        if (!hasMovement) return false;
    }

    if (currentState == CHOICE_ONE) {
        if (cell->isActive()) return false;

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

bool StateMachine::GameStateMachine::removeCell(Cell *cell) {
    if (!(currentState == MY_TURN || currentState == CHOICE_ONE || currentState == CHOICE_TWO)) return false;

    if (firstCell == cell) {
        currentState = MY_TURN;
        firstCell->setSelected(false);
        firstCell = nullptr;
    }

    if (secondCell == cell) {
        currentState = CHOICE_ONE;
        secondCell->setSelected(false);
        secondCell = nullptr;
    }

    observer->OnStatusUpdate(currentState);
    return true;
}

GameStateMachine *StateMachine::GameStateMachine::getInstance() {
    return _instance;
}

bool StateMachine::GameStateMachine::sendMove() {
    if (currentState != CHOICE_TWO) return false;

    board().move(firstCell->x(), firstCell->y(), secondCell->x(), secondCell->y());
    client.movePiece(firstCell->x(), firstCell->y(), secondCell->x(), secondCell->y());

    firstCell->setSelected(false);
    firstCell = nullptr;
    secondCell->setSelected(false);
    secondCell = nullptr;

    currentState = IDLE;
    observer->OnStatusUpdate(currentState);

    if (!isBoardPlayable()) {
        currentState = WON;
        observer->OnStatusUpdate(currentState);
    }

    return true;
}

bool StateMachine::GameStateMachine::isBoardPlayable() {
    return board().isPlayableYet();
}




