#include "models/ProductsManager.h"
ProductManager::ProductManager(ProductRepository& productRepository): productRepository(productRepository){
    products = productRepository.getAll();
    if(!products.empty()){
        nextID = products.back().getId() + 1;
    }
}
void ProductManager::addProduct(const Product& product){
    if(productRepository.create(product)){
        products.push_back(product);
    }
}
const std::vector<Product>& ProductManager::getProducts() const{
    return products;
}
void ProductManager::createProduct(const std::string& name,double price){
    Product newProduct(nextID,name,price);
    if(productRepository.create(newProduct)){
        products.push_back(newProduct);
        nextID++;
    }
}
void ProductManager::removeProduct(int id){
    if(productRepository.remove(id)){
        for(std::size_t index = 0;index < products.size();index++){
            if(products[index].getId() == id){
                products.erase(products.begin() + index);
                return;
            }
        }
    }
}
Product* ProductManager::getProductById(int id){
    for(std::size_t index = 0;index < products.size();index++){
        if(products[index].getId() == id){
            return &products[index];
        }
    }
    return nullptr;
}
void ProductManager::save(){
}
void ProductManager::updateProduct(const Product& product){
    if(productRepository.update(product)){
        for(std::size_t index = 0;index < products.size();index++){
            if(products[index].getId() == product.getId()){
                products[index] = product;
                return;
            }
        }
    }
}