//
// Created by beloin on 11/02/24.
//

#include <QPushButton>
#include <iostream>
#include <QBoxLayout>
#include "ApplicationMain.h"

void handle() {
    std::cout << "Button Pressed" << std::endl;
}


ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(1200, 800);
    setLayoutDirection(Qt::RightToLeft);

    auto button = new QPushButton("Hello world!");
    connect(button, &QPushButton::released, this, handle);

    auto button2 = new QPushButton("Nice to Meet Ya!");
//    button2->move(QPoint{button2->x() + 200, button2->y() + 200});
//    button2->setFixedSize(100, 200);
    connect(button2, &QPushButton::released, this, handle);

    auto *mainWidget = new QWidget();

    auto *hbox = new QHBoxLayout();
    hbox->addWidget(button);
    hbox->addWidget(button2);

    auto vbox = new QVBoxLayout();
//    vbox->addWidget(<>);
    vbox->addItem(hbox);

    mainWidget->setLayout(vbox);
    setCentralWidget(mainWidget);
}

