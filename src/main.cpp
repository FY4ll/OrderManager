#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow; //create an instance of the MainWindow class
    mainWindow.show(); //show the main window
    return app.exec();
}