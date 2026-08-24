#pragma once
#include <vector>
#include "models/Products.h"

class ProductManager{
    public:
        void createProduct(const std::string& name, double price);
        //setter
        void addProduct(const Product& product);
        // getter
        const std::vector<Product>& getProducts() const;
    private:
        std::vector<Product> products;
        int nextID = 1;
};