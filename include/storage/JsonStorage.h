#pragma once
#include <vector>
#include <string>
#include "models/Products.h"

class JsonStorage
{
public:
    bool save(const std::vector<Product>& products,
              const std::string& filePath);

    std::vector<Product> load(const std::string& filePath);
};