#pragma once 
#include <string>

class Product
{
    private:
        int id; //the product's unique identifier
        std::string name; //the product's name
        double price; //the product's price
    public:
        Product(int id, const std::string& name, double price); //constructor that initializes the product's id, name, and price
        //Getter
        int getId() const; //getter for the product's id
        const std::string getName() const; //getter for the product's name
        double getPrice() const; //getter for the product's price   
        
        //Setter
        void setPrice(double price); //Setter for the price
        void setName(const std::string& name);
};