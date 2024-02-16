//
// Created by beloin on 11/02/24.
//

#include <QPushButton>
#include <iostream>
#include <QBoxLayout>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include "ApplicationMain.h"
#include "ui/QTBoard.h"

static ApplicationMain *onCall = nullptr;

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(1200, 800);
    setLayoutDirection(Qt::RightToLeft);

    auto scene = new QGraphicsScene{this};
    auto board = new QTBoard{this->client.board(), scene, this};

    // TODO: Start and setup game...
    // TODO: How to update game and board?
    //  Add observable in board? use interface instead of callable...
    //  Could use the StateMachineGame to update all UI

    QInputDialog dialog = new QInputDialog(this);

    auto button = new QPushButton("Connect");
    connect(button, &QPushButton::released, this, &ApplicationMain::handle);

    auto mainWidget = new QWidget();

    auto hbox = new QHBoxLayout();
    hbox->addWidget(button);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(board);
    vbox->addItem(hbox);

    mainWidget->setLayout(vbox);
    setCentralWidget(mainWidget);

    auto fleeButton = new QPushButton{"Flee", this};
    fleeButton->setLayoutDirection(Qt::RightToLeft);
    connect(fleeButton, &QPushButton::released, this, &ApplicationMain::flee);

    onCall = this;
    client.bindCallable(CommandType::GAME, [](const RawCommand &command) {
        onCall->gameCallable(command);
    });
    client.bindCallable(CommandType::CHAT, [](const RawCommand &command) {
        onCall->chatCallable(command);
    });
    client.bindCallable(CommandType::OPTION, [](const RawCommand &command) {
        onCall->optionCallable(command);
    });
}

void ApplicationMain::handle() {
    bool ok;

    const QString &serverName = QInputDialog::getText(this, tr("Escreva o Servidor"),
                                                      tr("Servidor"), QLineEdit::Normal, "localhost", &ok);

    if (ok && !serverName.isEmpty()) {
        serverAddress = serverName.toStdString();
        clientListen = std::thread{&ApplicationMain::listen, this};
        clientListen.detach();
//        // TODO: Start thread here
//        int status = client.requestGame("NewGame", serverName.toStdString(), "6969");
//
//        if (status == 0) std::cout << "Connected." << std::endl;
//        client.listen();
    }
}

void ApplicationMain::gameCallable(const RawCommand &command) {
    auto game = (GameCommand *) &command;
    std::cout << "Command: " << command.commandType << std::endl;
}

void ApplicationMain::chatCallable(const RawCommand &command) {
    auto chat = (ChatCommand *) &command;
    std::cout << "Command: " << command.commandType << std::endl;
}

void ApplicationMain::optionCallable(const RawCommand &command) {
    auto option = (OptionCommand *) &command;
    std::cout << "Option Command: " << option->option << std::endl;
}

void ApplicationMain::listen() {
    int status = client.requestGame("NewGame", serverAddress, "6969");
    if (status != 0) {
        QMessageBox msgBox;
        msgBox.setText("Could not connect to Game");
        msgBox.exec();
        return;
    }

    std::cout << "Connected." << std::endl;

    client.listen();
}

void ApplicationMain::flee() {
    this->client.flee();
}

void ApplicationMain::moveCell(int x, int y) {
    this->client.movePiece(x, y);
}

void ApplicationMain::sendMessage(const std::string &message) {
    this->client.sendMessage(message);
}



