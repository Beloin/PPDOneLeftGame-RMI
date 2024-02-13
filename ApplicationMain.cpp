//
// Created by beloin on 11/02/24.
//

#include <QPushButton>
#include <iostream>
#include <QBoxLayout>
#include "ApplicationMain.h"
#include "ui/QTBoard.h"

QTBoard *test;

void handle() {
    const QList<QGraphicsItem *> &list = test->items();
    for (const auto &item: list) {
        auto d = (QTCell *) item;
        d->cell.toggle();
        d->update();
    }
    std::cout << "Button Pressed" << std::endl;
}


ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(1200, 800);
    setLayoutDirection(Qt::RightToLeft);

    auto scene = new QGraphicsScene{this};
    auto board = new QTBoard{scene, this};

    test = board;

    auto button = new QPushButton("Start");
    connect(button, &QPushButton::released, this, handle);

    auto button2 = new QPushButton("Flee");
    connect(button2, &QPushButton::released, this, handle);
    auto mainWidget = new QWidget();

    auto hbox = new QHBoxLayout();
    hbox->addWidget(button);
    hbox->addWidget(button2);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(board);
    vbox->addItem(hbox);

    mainWidget->setLayout(vbox);
    setCentralWidget(mainWidget);
}

