#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QGraphicsOpacityEffect>
#include "ui/ProductItemWidget.h"
#include "models/Products.h"
ProductItemWidget::ProductItemWidget(const Product& product, QWidget* parent): QWidget(parent){
    setObjectName("productItem");
    setMinimumHeight(50);
    setAttribute(Qt::WA_Hover, true);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(18, 8, 18, 8);
    layout->setSpacing(10);
    idLabel = new QLabel(QString("#%1").arg(product.getId()));
    nameLabel = new QLabel(QString::fromStdString(product.getName()));
    priceLabel = new QLabel(QString::number(product.getPrice(), 'f', 2) + " CHF");
    idLabel->setObjectName("productId");
    nameLabel->setObjectName("productName");
    priceLabel->setObjectName("productPrice");
    idLabel->setFixedWidth(80);
    priceLabel->setFixedWidth(125);
    priceLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
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