#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include "ApplicationMain.h"
#include "Game/Game.h"
#include "Game/OneLeftClient.h"
#include "Game/OneLeftServer.h"


void serve();

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ApplicationMain applicationMain;
    applicationMain.show();

    std::thread serverThread(serve);

    return QApplication::exec();
}

void serve() {
    OneLeftServer server;
    server.Serve("6969");
}
