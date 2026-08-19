#include "models/Products.h"

Product::Product(int id, const std::string& name, double price)
{
    this->id = id;
    this->name = name;
    this->price = price;
}
//NOTE: const methods can't change object value!
int Product::getId()const
{
    return this->id; 
}

std::string Product::getName() const
{
    return this->name;
}

double Product::getPrice() const{
    return this->price;
}

void Product::setPrice(double price){
    this->price = price;
}