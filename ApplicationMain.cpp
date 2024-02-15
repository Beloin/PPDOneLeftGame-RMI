//
// Created by beloin on 11/02/24.
//

#include <QPushButton>
#include <iostream>
#include <QBoxLayout>
#include <QInputDialog>
#include <QDir>
#include "ApplicationMain.h"
#include "ui/QTBoard.h"

ApplicationMain::ApplicationMain(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(1200, 800);
    setLayoutDirection(Qt::RightToLeft);

    auto scene = new QGraphicsScene{this};
    auto board = new QTBoard{scene, this};

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

    client.bindCallable(CommandType::GAME, ApplicationMain::gameCallable);
    client.bindCallable(CommandType::GAME, &ApplicationMain::gameCallable);
}

void ApplicationMain::handle() {
    bool ok;

    const QString &serverName = QInputDialog::getText(this, tr("Escreva o Servidor"),
                                                      tr("Servidor"), QLineEdit::Normal, "localhost", &ok);

    if (ok && !serverName.isEmpty()) {
        // TODO: Start thread here
        int status = client.requestGame("NewGame", serverName.toStdString(), "6969");

        if (status == 0) std::cout << "Connected." << std::endl;
    }
}


