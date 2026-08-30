#pragma once
#include <vector>
#include "models/Products.h"
#include "storage/JsonStorage.h"

class ProductManager{
    public:
        ProductManager();
        void createProduct(const std::string& name, double price);
        void addProduct(const Product& product);
        void save();
        const std::vector<Product>& getProducts() const;
        void removeProduct(int id);
        Product* getProductById(int id);
    private:
        std::vector<Product> products;
        int nextID = 1;
        JsonStorage jsonStorage; 
};