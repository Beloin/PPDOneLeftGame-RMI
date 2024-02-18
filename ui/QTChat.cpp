//
// Created by beloin on 17/02/24.
//

#include <QAbstractButton>
#include <QPushButton>
#include <QLineEdit>
#include "QTChat.h"
#include "GameStateMachine.h"

void QTChat::addUserMessage(const std::string &msg) {
    auto *message = new QListWidgetItem(QString::fromStdString(msg));
    message->setBackground(Qt::blue);
    listView->addItem(message);
}

void QTChat::addOpponentMessage(const std::string &msg) {
    auto *message = new QListWidgetItem(QString::fromStdString(msg));
    message->setBackground(Qt::red);
    listView->addItem(message);
}

void QTChat::sendMessage() {
    // TODO: Send only when connected
    const QString &string = lineEdit->text();

    if (string.isNull() || string.isEmpty()) return;

    const std::string &basicString = string.toStdString();
    addUserMessage(basicString);

    StateMachine::GameStateMachine *machine = StateMachine::GameStateMachine::getInstance();
    machine->sendChat(basicString);

    lineEdit->clear();
}

QTChat::QTChat() {
    listView = new QListWidget();
    auto *itemO1 = new QListWidgetItem("Write something to your opponent!");
    itemO1->setBackground(Qt::red);
    listView->addItem(itemO1);

    auto button = new QPushButton("Send");
    connect(button, &QPushButton::released, this, &QTChat::sendMessage);

    QBoxLayout::addWidget(listView);

    lineEdit = new QLineEdit();

    auto hbox = new QHBoxLayout();
    hbox->setDirection(LeftToRight);
    hbox->addWidget(lineEdit);
    hbox->addWidget(button);

    QBoxLayout::addItem(hbox);
}