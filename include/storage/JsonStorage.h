#pragma once

#include <vector>
#include <string>

#include "models/Products.h"

class JsonStorage
{
public:
    struct LoadResult
    {
        std::vector<Product> products;
        int nextID;
    };
    bool save(const std::vector<Product>& products,int nextID,const std::string& filePath);
    LoadResult load(const std::string& filePath);
};