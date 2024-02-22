//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_APPLICATIONMAIN_H
#define TEST_QT5_APPLICATIONMAIN_H


#include <QMainWindow>
#include "OneLeftClient.h"
#include "ui/QTBoard.h"
#include "GameStateMachine.h"
#include "ui/QTChat.h"
#include <thread>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>

class ApplicationMain : public QMainWindow, public StateMachine::Observer {

private:
    std::thread clientListen;

    std::string gameRoom{};
    std::string serverAddress{};
    QTBoard *qtBoard;

    void listen();

    void handle();

    StateMachine::GameStateMachine *game;

    QTChat *pChat;

    QLabel *pStatusLabel;

    bool connectionDialog();

public:
    explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

    void OnMove(int fromX, int fromY, int toX, int toY) override;

    void OnMessage(std::string message) override;

    void OnOption(Option &option) override;

    void OnStatusUpdate(StateMachine::State state) override;

    void updateStatusLabel(const StateMachine::State &state);
};


#endif //TEST_QT5_APPLICATIONMAIN_H
