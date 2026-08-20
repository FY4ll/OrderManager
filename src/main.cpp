#include <QApplication>
#include <QMainWindow>
#include "ui/MainWindow.h"
#include <iostream>
#include "models/Products.h"
#include "models/ProductsManager.h"

int main(int argc, char *argv[])
{   
    Product cocaCola(2, "Coca-Cola", 1.25);
    ProductManager manager;
    manager.addProduct(cocaCola);
    QApplication app(argc, argv);
    MainWindow window(manager);
    window.show();



    return app.exec();
}