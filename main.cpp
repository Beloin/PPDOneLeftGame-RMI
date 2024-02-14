#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include "ApplicationMain.h"
#include "Game/Game.h"
#include "Game/OneLeftClient.h"
#include "Game/OneLeftServer.h"


int main(int argc, char *argv[]) {
//    if (std::string(argv[1]) == "server")
    if (argc > 1 && strcmp(argv[1], "server") == 0) {
        OneLeftServer server;
        server.serve("6969");

        exit(0);
    }

    QApplication a(argc, argv);

    ApplicationMain applicationMain;
    applicationMain.show();

    return QApplication::exec();
}
