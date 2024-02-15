//
// Created by beloin on 11/02/24.
//

#ifndef TEST_QT5_APPLICATIONMAIN_H
#define TEST_QT5_APPLICATIONMAIN_H


#include <QMainWindow>
#include "OneLeftClient.h"

class ApplicationMain : public QMainWindow {

private:
    void handle();
    OneLeftClient client;

    void gameCallable(const RawCommand &command);

    void chatCallable(const RawCommand &command);
    void optionCallable(const RawCommand &command);


public:
    explicit ApplicationMain(QWidget *parent = Q_NULLPTR);

};


#endif //TEST_QT5_APPLICATIONMAIN_H
