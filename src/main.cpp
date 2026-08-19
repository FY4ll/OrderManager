#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window; // create an instance of the MainWindow class
    window.show(); // show the window on the screen

    return app.exec();
}