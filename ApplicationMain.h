//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_APPLICATIONMAIN_H
#define TEST_QT5_APPLICATIONMAIN_H


#include <QMainWindow>
#include "OneLeftClient.h"
#include "ui/QTBoard.h"
#include <thread>

class ApplicationMain : public QMainWindow {

private:
    void handle();

    OneLeftClient client{};
    std::thread clientListen;
    std::string serverAddress{};
    QTBoard *qtBoard;

    void gameCallable(const RawCommand &command);

    void chatCallable(const RawCommand &command);

    void optionCallable(const RawCommand &command);

    void listen();

    void flee();

    void moveCell(int x, int y);

    void sendMessage(const std::string&);

public:
    explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

};


#endif //TEST_QT5_APPLICATIONMAIN_H
