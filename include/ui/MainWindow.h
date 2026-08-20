#pragma once //the file can't be loaded twice
#include <QMainWindow> //include the QMainWindow class from the Qt framework
#include "models/ProductsManager.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow(ProductManager& productManager);
    void onNewProductClicked();
};