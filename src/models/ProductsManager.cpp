#include "models/ProductsManager.h"

ProductManager::ProductManager(){
    JsonStorage::LoadResult result = jsonStorage.load("data/products.json");
    products = result.products;
    nextID = result.nextID;
}
void ProductManager::addProduct(const Product& product){
    //Add product to the end of the vector
    products.push_back(product);
}
const std::vector<Product>& ProductManager::getProducts() const{
return products;
}
void ProductManager::createProduct(const std::string& name, double price){
    //Create a new product
    Product newProduct(nextID, name, price);
    addProduct(newProduct);
    nextID += 1;
    save();
}
void ProductManager::removeProduct(int id){
for(std::size_t index = 0; index < products.size(); index++){
        if(products[index].getId() == id){
            products.erase(products.begin() + index);
            save();
            return;
        }
    }
}
Product* ProductManager::getProductById(int id){
    for(std::size_t index = 0; index < products.size(); index++){
            if(products[index].getId() == id){
                    return &products[index];
                }
        }
    return nullptr;
}
void ProductManager::save(){
    jsonStorage.save(products, nextID, "data/products.json");
}
