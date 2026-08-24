#include "models/ProductsManager.h"

void ProductManager::addProduct(const Product& product)
{
    //adding an elements to the end of the vector with push_back() methods from <vector> 
    products.push_back(product);
};
const std::vector<Product>& ProductManager::getProducts() const
{
    return this->products;
}
void ProductManager::createProduct(const std::string& name, double price)
{
    //Create every info we need to use addProduct methods
    Product newProduct(nextID, name, price);
    addProduct(newProduct);
    nextID += 1;
}