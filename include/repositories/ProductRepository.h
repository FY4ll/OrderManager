#pragma once
#include <optional>
#include <vector>
#include "models/Products.h"
#include "database/Database.h"
class ProductRepository{
public:
    explicit ProductRepository(Database& database);
    bool create(const Product& product);
    std::vector<Product> getAll();
    std::optional<Product> getById(int id);
    bool update(const Product& product);
    bool remove(int id);
private:
    Database& database;
};