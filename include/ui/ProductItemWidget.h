#pragma once

#include <QWidget>

class Product;

class QLabel;

class ProductItemWidget : public QWidget
{
public:
    explicit ProductItemWidget(const Product& product, QWidget* parent = nullptr);

private:
    QLabel* idLabel;
    QLabel* nameLabel;
    QLabel* priceLabel;
};