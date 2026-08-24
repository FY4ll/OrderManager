#include "ui/ProductDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

ProductDialog::ProductDialog()
{
    //window size
    setWindowTitle("Add New Product");
    resize(400, 300);
    //window layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel("Add a new product to the list");
    layout->addWidget(title);
    // Name input for new product
    nameInput = new QLineEdit();
    layout->addWidget(nameInput);

    //Price input only for double value no string
    priceInput = new QDoubleSpinBox(); 
    layout->addWidget(priceInput);

    addButton = new QPushButton("Add new products");
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &ProductDialog::onAddProductClicked);
}

void ProductDialog::onAddProductClicked()
{
    QString name = nameInput->text();
    double price = priceInput->value();
}