#include "models/Products.h"

Product::Product(int id, const std::string& name, double price)
: id(id), name(name), price(price){}
//NOTE: const methods can't change object value!
int Product::getId() const{
    return id;
}
const std::string Product::getName() const{
    return name;
}
double Product::getPrice() const{
    return price;
}
void Product::setPrice(double price){
    this->price = price;
}
void Product::setName(const std::string& name){
    this->name = name;
}
