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

    this->game.setObserver(this);

    auto scene = new QGraphicsScene{this};
    qtBoard = new QTBoard{this->game.board(), scene, this};

    QInputDialog dialog = new QInputDialog(this);

    auto button = new QPushButton("Connect");
    connect(button, &QPushButton::released, this, &ApplicationMain::handle);

    auto mainWidget = new QWidget();

    auto hbox = new QHBoxLayout();
    hbox->addWidget(button);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(qtBoard);
    vbox->addItem(hbox);

    mainWidget->setLayout(vbox);
    setCentralWidget(mainWidget);

    auto fleeButton = new QPushButton{"Flee", this};
    fleeButton->setLayoutDirection(Qt::RightToLeft);
    connect(fleeButton, &QPushButton::released, this, [this]() {
        game.flee();
    });

}

void ApplicationMain::handle() {
    if (this->game.isConnected()) {
        QMessageBox msgBox;
        msgBox.setText("Already Connected");
        msgBox.exec();
        return;
    }

    bool ok;
    const QString &serverName = QInputDialog::getText(this, tr("Endereço do Servidor"),
                                                      tr("Servidor"), QLineEdit::Normal, "localhost", &ok);

    if (ok && !serverName.isEmpty()) {
        serverAddress = serverName.toStdString();
        clientListen = std::thread{&ApplicationMain::listen, this};
        clientListen.detach();
    }
}

void ApplicationMain::listen() {
    int status = game.requestGame("NewGame", serverAddress, "6969");
    if (status != 0) {
        QMessageBox msgBox;
        msgBox.setText("Could not connect to Game");
        msgBox.exec();
        return;
    }

    std::cout << "Connected." << std::endl;
    qtBoard->updateCells();

    game.listen();
}

void ApplicationMain::OnMove(int fromX, int fromY, int toX, int toY) {
    qtBoard->updateCells();
}

void ApplicationMain::OnMessage(std::string message) {

}

void ApplicationMain::OnOption(Option &option) {

}

void ApplicationMain::OnStatusUpdate(const StateMachine::State &state) {
    std::cout << "State Updated: " << state << std::endl;
}

