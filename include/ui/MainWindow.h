#pragma once //the file can't be loaded twice
#include <QMainWindow> //include the QMainWindow class from the Qt framework
#include <QListWidget> //include the QListWidget class from QT FW
#include "models/ProductsManager.h"

class MainWindow : public QMainWindow
{
    public:
        MainWindow(ProductManager& productManager);
        void onNewProductClicked();
    private:
        ProductManager& productManager;
        void refreshProductList();
        QListWidget *productList;
};