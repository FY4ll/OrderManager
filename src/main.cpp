#include <QApplication>
#include <QMainWindow>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include "models/Products.h"
#include "models/ProductsManager.h"
#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{   
    ProductManager manager;
    QApplication app(argc, argv);
    QFile file("assets/styles/main.qss");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
    }
    MainWindow window(manager); 
    window.show();
    return app.exec();
}