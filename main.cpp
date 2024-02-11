#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include "ApplicationMain.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ApplicationMain applicationMain;
    applicationMain.show();

    return QApplication::exec();
}

