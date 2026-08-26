#include "ui/ProductDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

ProductDialog::ProductDialog(ProductManager& productManager, Product* product) : productManager(productManager), product(product)
{
    //window size
    setWindowTitle("Add New Product");
    resize(400, 300);
    //window layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *nameLabel = new QLabel("Name:");
    layout->addWidget(nameLabel);
    // Name input for new product
    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter product Name");
    layout->addWidget(nameInput);

    //Price input only for double value no string
    QLabel *priceLabel = new QLabel("Price:");
    layout->addWidget(priceLabel);
    priceInput = new QDoubleSpinBox(); 
    priceInput->setDecimals(2);
    priceInput->setMinimum(0.00);
    priceInput->setSuffix(" CHF");
    layout->addWidget(priceInput);
    if (product != nullptr)
    {
        nameInput->setText(QString::fromStdString(product->getName()));
        priceInput->setValue(product->getPrice());
    }

    addButton = new QPushButton("Add new products");
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &ProductDialog::onAddProductClicked);
}

void ProductDialog::onAddProductClicked()
{
    if (product != nullptr){
        QString name = nameInput->text();
        double price = priceInput->value();
        std::string productName = name.toStdString();
        product->setName(productName);
        product->setPrice(price);
        accept();
    }else{
         QString name = nameInput->text();
        double price = priceInput->value();
        //convert Qstring to normal string
        std::string productName = name.toStdString();
        productManager.createProduct(productName,price);
        accept();  
    }
    
}