#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "storage/JsonStorage.h"


bool JsonStorage::save(const std::vector<Product>& products, const std::string& filePath){
    QJsonArray jsonProducts;
    QFile jsonFile(QString::fromStdString(filePath));
    for(size_t i = 0; i < products.size(); i++){
        QJsonObject productsToJson;
        productsToJson["id"] = products[i].getId();
        productsToJson["name"] = QString::fromStdString(products[i].getName());
        productsToJson["price"] = products[i].getPrice();
        jsonProducts.append(productsToJson);
    }
    QJsonDocument document(jsonProducts);
    if(jsonFile.open(QIODevice::WriteOnly)){
        jsonFile.write(document.toJson());
        jsonFile.close();
        return true;
    }else{
        return false; 
    }
};
std::vector<Product> JsonStorage::load(const std::string& filePath){
    QFile jsonFile(QString::fromStdString(filePath));
    std::vector<Product> products;
    if(jsonFile.open(QIODevice::ReadOnly)){
        QByteArray data = jsonFile.readAll();
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonArray jsonArray = document.array();
        for(size_t i = 0; i < jsonArray.size(); i ++){
            QJsonObject product = jsonArray[i].toObject();
            int id = product["id"].toInt();
            std::string name = product["name"].toString().toStdString();
            double price = product["price"].toDouble();
            Product newProduct(id, name,price);
            products.push_back(newProduct);
        }
    };
    jsonFile.close();
    return products;
}