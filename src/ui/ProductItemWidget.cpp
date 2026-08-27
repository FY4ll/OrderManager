#include "ui/ProductItemWidget.h"
#include "models/Products.h"
#include <QHBoxLayout>
#include <QLabel>

ProductItemWidget::ProductItemWidget(const Product& product, QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    idLabel = new QLabel(QString::number(product.getId()));
    nameLabel = new QLabel(QString::fromStdString(product.getName()));
    priceLabel = new QLabel(QString::number(product.getPrice(), 'f', 2) + " CHF");

    layout->addWidget(idLabel);
    layout->addWidget(nameLabel);
    layout->addStretch();
    layout->addWidget(priceLabel);
}