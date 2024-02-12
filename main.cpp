#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include "ApplicationMain.h"
#include "Game/Game.h"
#include "Game/OneLeftClient.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ApplicationMain applicationMain;
    applicationMain.show();

    return QApplication::exec();
}

