#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "storage/JsonStorage.h"



bool JsonStorage::save(
    const std::vector<Product>& products,
    int nextID,
    const std::string& filePath)
{
    QJsonArray jsonProducts;
    QJsonObject root;
    QFile jsonFile(QString::fromStdString(filePath));

    // Loop through all products to convert them into JSON objects
    for(size_t i = 0; i < products.size(); i++)
    {
        QJsonObject productsToJson;
        productsToJson["id"] = products[i].getId();
        productsToJson["name"] =
            QString::fromStdString(products[i].getName());
        productsToJson["price"] = products[i].getPrice();
        jsonProducts.append(productsToJson);
    }

    // Put the products and the next ID inside the main JSON object
    root["nextID"] = nextID;
    root["products"] = jsonProducts;

    QJsonDocument document(root);

    // Open the JSON file for writing
    if(jsonFile.open(QIODevice::WriteOnly)){
        jsonFile.write(document.toJson());
        jsonFile.close();
        return true;
    }else{
        return false;
    }
}
JsonStorage::LoadResult JsonStorage::load(const std::string& filePath)
{
    QFile jsonFile(QString::fromStdString(filePath));
    LoadResult result;
    result.nextID = 1;
    // Open the JSON file for reading
    if(jsonFile.open(QIODevice::ReadOnly)){
        QByteArray data = jsonFile.readAll();
        jsonFile.close();
        QJsonDocument document = QJsonDocument::fromJson(data);
        // Check if the JSON is an object
        if(!document.isObject()){
            return result;
        }

        QJsonObject root = document.object();
        result.nextID = root["nextID"].toInt(1);
        QJsonArray jsonArray = root["products"].toArray();
        // Loop through all JSON products
        for(size_t i = 0; i < jsonArray.size(); i++){
            QJsonObject productJson = jsonArray[i].toObject();
            int id = productJson["id"].toInt();
            std::string name =
                productJson["name"].toString().toStdString();
            double price =
                productJson["price"].toDouble();

            Product product(id, name, price);
            result.products.push_back(product);
        }
    }

    return result;
}