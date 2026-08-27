#include "models/ProductsManager.h"

ProductManager::ProductManager(){
    products = jsonStorage.load("data/products.json");
}
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
    jsonStorage.save(products, "data/products.json");
}
void ProductManager::removeProduct(int id)
{
    for(int index = 0;index < products.size(); index++){
        if (products[index].getId() == id)
        {
           products.erase(products.begin() + index); 
           return;
        }
    };
}
Product* ProductManager::getProductById(int id){
    for(int index = 0;index < products.size(); index++){
        if (products[index].getId() == id)
        {
           return &products[index];
        }
    }
    return nullptr;
}
