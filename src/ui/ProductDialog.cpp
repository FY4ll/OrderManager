#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "ui/ProductDialog.h"
ProductDialog::ProductDialog(ProductManager& productManager,Product* product): productManager(productManager),product(product){
    setWindowTitle(product == nullptr ? "New Product" : "Update Product");
    resize(400,250);
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* nameLabel = new QLabel("Name");
    layout->addWidget(nameLabel);
    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter product name");
    layout->addWidget(nameInput);
    QLabel* priceLabel = new QLabel("Price");
    layout->addWidget(priceLabel);
    priceInput = new QDoubleSpinBox();
    priceInput->setDecimals(2);
    priceInput->setMaximum(999999.99);
    priceInput->setButtonSymbols(QAbstractSpinBox::NoButtons);
    priceInput->setSuffix(" CHF");
    layout->addWidget(priceInput);
    if(product != nullptr){
        nameInput->setText(QString::fromStdString(product->getName()));
        priceInput->setValue(product->getPrice());
    }
    addButton = new QPushButton(product == nullptr ? "Create Product" : "Save Changes");
    layout->addWidget(addButton);
    connect(addButton,&QPushButton::clicked,this,&ProductDialog::onAddProductClicked);
}
void ProductDialog::onAddProductClicked(){
    QString name = nameInput->text().trimmed();
    if(name.isEmpty()){
        return;
    }
    double price = priceInput->value();
    if(product == nullptr){
        productManager.createProduct(name.toStdString(),price);
    }
    else{
        Product updated(product->getId(),name.toStdString(),price);
        productManager.updateProduct(updated);
    }
    accept();
}