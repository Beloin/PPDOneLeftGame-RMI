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
#include "Utils/GameUtils.h"
#include <QLabel>
#include <sstream>
#include <QFormLayout>
#include <QDialogButtonBox>

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

    auto fleeButton = new QPushButton{"Desistir", this};
    fleeButton->setLayoutDirection(Qt::RightToLeft);
    connect(fleeButton, &QPushButton::released, this, [this]() {
        game->disconnect();
    });

    auto disconnectButton = new QPushButton{"Desconectar", this};
    const QRect &currentGeometry = disconnectButton->geometry();
    disconnectButton->setGeometry(0, 30, currentGeometry.width(), currentGeometry.height());
    fleeButton->setLayoutDirection(Qt::RightToLeft);
    connect(disconnectButton, &QPushButton::released, this, [this]() {
        game->disconnect();
    });

    pStatusLabel = new QLabel("Se conecte ao servidor", qtBoard);
    pStatusLabel->setFrameStyle(QFrame::Panel | QFrame::Box);
    pStatusLabel->setAlignment(Qt::AlignCenter);
    pStatusLabel->setGeometry(150, 10, 300, 30);

    // TODO: What is missing?
    //  3. [Client] Game movement validation
    //  4. [Server] Add remove game when it has finished
    //  6. [Client] Better UI
}

void ApplicationMain::handle() {
    bool gameHasEnded = game->getState() == StateMachine::WON || game->getState() == StateMachine::LOST ||
                        game->getState() == StateMachine::DRAW || game->getState() == StateMachine::NOT_STARTED;
    if (this->game->isConnected() && !gameHasEnded) {
        QMessageBox msgBox;
        msgBox.setText("Já conectado!");
        msgBox.exec();
        return;
    } else {
        game->disconnect();
    }

    auto ok2 = connectionDialog();

    if (ok2) {
        clientListen = std::thread{&ApplicationMain::listen, this};
        clientListen.detach();
    }
}

void ApplicationMain::listen() {
    std::ostringstream osstr;
    osstr << "Esperando em \"" << gameRoom << "\"";
    pStatusLabel->setText(QString::fromStdString(osstr.str()));

    int status = game->requestGame(gameRoom, serverAddress, "6969");
    if (status != 0) {
        QMessageBox msgBox;
        msgBox.setText("Não foi possível se conectar");
        msgBox.exec();

        pStatusLabel->setText("Tente novamente");
        return;
    }

    game->resetBoard();
    std::cout << "Connected." << std::endl;
    qtBoard->updateCells();

    game->listen();
}

void ApplicationMain::OnMove(int fromX, int fromY, int toX, int toY) {
    this->update();
    this->qtBoard->updateCells();
}

void ApplicationMain::OnMessage(std::string message) {
    std::cout << "Received Chat: " << message << std::endl;
    pChat->addOpponentMessage(message);
}

void ApplicationMain::OnOption(Option &option) {
    std::cout << "Opponent Gave Up!" << std::endl;
    pStatusLabel->setText("Parabéns! Ganhastes");
}

void ApplicationMain::OnStatusUpdate(StateMachine::State state) {
    std::cout << "State Updated: {" << state << "} " << getTimestamp() << std::endl;
    this->qtBoard->updateCells();

    updateStatusLabel(state);

    if (state == StateMachine::CHOICE_TWO) {
        game->sendMove();
    }
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
            this->pChat->clearAll();
            break;
        case StateMachine::LOST:
            pStatusLabel->setText("Perdestes!");
            this->pChat->clearAll();
            break;
        case StateMachine::NOT_STARTED:
            pStatusLabel->setText("Fim do jogo.");
            break;
        case StateMachine::DRAW:
            pStatusLabel->setText("Empate!");
            this->pChat->clearAll();
            break;
        default:
            pStatusLabel->setText("Em espera");
            break;
    }

    this->update();
}

bool ApplicationMain::connectionDialog() {
    QDialog dialog(this);
    QFormLayout form(&dialog);

    form.addRow(new QLabel("End. do Servidor:"));

    auto *serverAddressField = new QLineEdit(&dialog);
    serverAddressField->setText("localhost");
    form.addRow(serverAddressField);

    std::ostringstream osstr0;
    osstr0 << "Game#" << getRandomString(5);
    form.addRow(new QLabel("Nome da Sala:"));
    auto *roomName = new QLineEdit(&dialog);
    roomName->setText(QString::fromStdString(osstr0.str()));
    form.addRow(roomName);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        if (roomName->text().isEmpty() || serverAddressField->text().isEmpty()) { return false; }

        gameRoom = roomName->text().toStdString();
        serverAddress = serverAddressField->text().toStdString();
        return true;
    }

    return false;
}

