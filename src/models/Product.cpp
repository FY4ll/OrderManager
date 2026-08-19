#include "models/Products.h"

Product::Product(int id, const std::string& name, double price)
{
    this->id = id;
    this->name = name;
    this->price = price;
}