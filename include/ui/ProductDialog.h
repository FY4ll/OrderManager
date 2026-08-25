#pragma once 
#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "models/ProductsManager.h"

class ProductDialog : public QDialog
{
public:
    ProductDialog(ProductManager& productManager, Product* product = nullptr);
private:
    Product* product;
    void onAddProductClicked();
    ProductManager& productManager;
    QLineEdit *nameInput;
    QDoubleSpinBox *priceInput;
    QPushButton *addButton;
};

