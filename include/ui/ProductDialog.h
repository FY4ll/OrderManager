#pragma once 
#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

class ProductDialog : public QDialog
{
public:
    ProductDialog();
private:
    QLineEdit *nameInput;
    QDoubleSpinBox *priceInput;
    QPushButton *addButton;
    void onAddProductClicked();
};

