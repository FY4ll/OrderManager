#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include "ui/ProductItemWidget.h"
#include "models/Products.h"

ProductItemWidget::ProductItemWidget(const Product& product, QWidget* parent): QWidget(parent){
    setObjectName("productItem");
    setMinimumHeight(50);
    QHBoxLayout* layout = new QHBoxLayout(this);
    idLabel = new QLabel(QString::number(product.getId()));
    nameLabel = new QLabel(QString::fromStdString(product.getName()));
    priceLabel = new QLabel(QString::number(product.getPrice(), 'f', 2) + " CHF");
    idLabel->setObjectName("productId");
    nameLabel->setObjectName("productName");
    priceLabel->setObjectName("productPrice");
    layout->addWidget(idLabel);
    layout->addWidget(nameLabel);
    layout->addStretch();
    layout->addWidget(priceLabel);
}
void ProductItemWidget::setSelected(bool selected){
    setProperty("selected", selected);
    style()->unpolish(this);
    style()->polish(this);
    update();
}
