#pragma once
#include <QMainWindow>
#include <QListWidget>
#include "models/ProductsManager.h"

class MainWindow : public QMainWindow{
    public:
        MainWindow(ProductManager& productManager);
    private:
        ProductManager& productManager;
        QListWidget* productList;
        void refreshProductList();
        void onNewProductClicked();
        void onDeleteProductClicked();
        void onUpdateProductClicked();
        void updateProductSelection();
    protected:
        bool eventFilter(QObject* object, QEvent* event) override;

};
