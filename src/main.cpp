#include "database/Database.h"
#include "models/Products.h"
#include "models/ProductsManager.h"
#include "repositories/ProductRepository.h"
#include "ui/MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QMainWindow>
#include <QStandardPaths>
#include <QTextStream>
#include <iostream>
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Database database;
    if (!database.initialize()) {
        return 1;
    }
    ProductRepository productRepository(database);
    ProductManager manager(productRepository);
    QFile file(":/assets/styles/main.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
    }
    MainWindow window(manager);
    window.show();
    return app.exec();
}