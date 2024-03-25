#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <iostream>
#include "ApplicationMain.h"
#include "Game/OneLeftServer.h"


int main(int argc, char *argv[]) {
//    if (std::string(argv[1]) == "server")
    int i = 12;
    std::cout << "Starting Application" << std::endl;
    if (argc > 1 && strcmp(argv[1], "server") == 0) {
        OneLeftServer server; // TODO: Use this part of server to add RMI
        server.serve("6969");

       exit(0);
    }

    QApplication a(argc, argv);

    ApplicationMain applicationMain;
    applicationMain.show();

    return QApplication::exec();
}
