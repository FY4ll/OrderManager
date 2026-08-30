#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "ui/ProductDialog.h"

ProductDialog::ProductDialog(ProductManager& productManager, Product* product): productManager(productManager), product(product){
    //Window size
    setWindowTitle("Add New Product");
    resize(400, 300);
    //Window layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* nameLabel = new QLabel("Name:");
    layout->addWidget(nameLabel);
    //Name input
    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter product Name");
    layout->addWidget(nameInput);
    //Price input
    QLabel* priceLabel = new QLabel("Price:");
    layout->addWidget(priceLabel);
    priceInput = new QDoubleSpinBox();
    priceInput->setDecimals(2);
    priceInput->setMinimum(0.00);
    priceInput->setSuffix(" CHF");
    layout->addWidget(priceInput);
    //Load product information when editing
    if(product != nullptr){
        nameInput->setText(QString::fromStdString(product->getName()));
        priceInput->setValue(product->getPrice());
    }
    addButton = new QPushButton("Add Product");
    layout->addWidget(addButton);
    connect(addButton,&QPushButton::clicked,this,&ProductDialog::onAddProductClicked);
}
void ProductDialog::onAddProductClicked(){
    QString name = nameInput->text();
    double price = priceInput->value();
    if(name.trimmed().isEmpty()){
        return;
    }
    std::string productName = name.toStdString();
    if(product != nullptr){
        product->setName(productName);
        product->setPrice(price);
    }
    else{
        productManager.createProduct(productName, price);
    }
    accept();
}
