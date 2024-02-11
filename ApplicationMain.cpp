//
// Created by beloin on 11/02/24.
//

#include <QPushButton>
#include "ApplicationMain.h"

ApplicationMain::ApplicationMain(QWidget *parent) {
    auto *button = new QPushButton("Hello world!", nullptr);
    button->resize(200, 100);

    setCentralWidget(button);


}
