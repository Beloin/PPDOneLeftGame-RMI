//
// Created by beloin on 11/02/24.
//

#include <QPushButton>
#include <iostream>
#include <QBoxLayout>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "ApplicationMain.h"
#include "ui/QTBoard.h"
#include "ui/QTChat.h"
#include <QLabel>

static ApplicationMain *onCall = nullptr;

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(1200, 800);
    setLayoutDirection(Qt::RightToLeft);

    this->game = StateMachine::GameStateMachine::getInstance();
    this->game->setObserver(this);

    auto scene = new QGraphicsScene{this};
    qtBoard = new QTBoard{this->game->board(), scene, this};

    QInputDialog dialog = new QInputDialog(this);

    auto button = new QPushButton("Connect");
    connect(button, &QPushButton::released, this, &ApplicationMain::handle);

    auto mainWidget = new QWidget();
    auto hbox = new QHBoxLayout();
    hbox->addWidget(button);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(qtBoard);
    vbox->addItem(hbox);

    auto mainHorizontalBox = new QHBoxLayout();
    pChat = new QTChat();
    mainHorizontalBox->addItem(pChat);
    mainHorizontalBox->addItem(vbox);

    mainWidget->setLayout(mainHorizontalBox);
    setCentralWidget(mainWidget);

    auto fleeButton = new QPushButton{"Flee", this};
    fleeButton->setLayoutDirection(Qt::RightToLeft);
    connect(fleeButton, &QPushButton::released, this, [this]() {
        game->flee();
    });

    pStatusLabel = new QLabel("Se conecte ao servidor", qtBoard);
    pStatusLabel->setFrameStyle(QFrame::Panel | QFrame::Box);
    pStatusLabel->setAlignment(Qt::AlignCenter);
    pStatusLabel->setGeometry(150, 10, 300, 30);

    // TODO: What is missin?
    //  1. Game end, check for each piece if can be moved, if not, the current turn user has lost
    //  2. Add game name choice
    //  3. Game movement validation
    //  4. Add remove game when it has finished
    //  5. Add when game is finished call again
    //  6. Better UI
}

void ApplicationMain::handle() {
    bool gameHasEnded = game->getState() == StateMachine::WON || game->getState() == StateMachine::LOST;
    if (this->game->isConnected() && !gameHasEnded) {
        QMessageBox msgBox;
        msgBox.setText("Já conectado!");
        msgBox.exec();
        return;
    } else {
        if (gameHasEnded) {
            this->game->disconnect();
        }
    }

    // TODO: Get  game name too:
    //  https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qt
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
    int status = game->requestGame("NewGame", serverAddress, "6969");
    if (status != 0) {
        QMessageBox msgBox;
        msgBox.setText("Could not connect to Game");
        msgBox.exec();
        return;
    }

    game->resetBoard();
    std::cout << "Connected." << std::endl;
    qtBoard->updateCells(); // TODO: See if necessary

    game->listen();
}

void ApplicationMain::OnMove(int fromX, int fromY, int toX, int toY) {
    qtBoard->updateCells();
}

void ApplicationMain::OnMessage(std::string message) {
    std::cout << "Received Chat: " << message << std::endl;
    pChat->addOpponentMessage(message);
}

void ApplicationMain::OnOption(Option &option) {

}

void ApplicationMain::OnStatusUpdate(StateMachine::State state) {
    std::cout << "State Updated: " << state << std::endl;

    this->qtBoard->updateCells();

    if (state == StateMachine::CHOICE_TWO) {
        game->sendMove();
    }

    updateStatusLabel(state);
}

void ApplicationMain::updateStatusLabel(const StateMachine::State &state) {
    switch (state) {
        case StateMachine::IDLE:
            pStatusLabel->setText("Vez do Oponente");
            break;
        case StateMachine::MY_TURN:
            pStatusLabel->setText("Sua vez");
            break;
        case StateMachine::CHOICE_ONE:
            pStatusLabel->setText("Escolha outra pedra");
            break;
        case StateMachine::WON:
            pStatusLabel->setText("Parabéns! Ganhastes");
            break;
        case StateMachine::LOST:
            pStatusLabel->setText("Perdestes!");
            break;
        default:
            pStatusLabel->setText("Em espera");
            break;
    }
}

