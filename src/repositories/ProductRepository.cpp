#include "repositories/ProductRepository.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <iostream>
ProductRepository::ProductRepository(Database& database): database(database){
}
bool ProductRepository::create(const Product& product){
    QSqlQuery query(database.getDatabase());
    query.prepare("INSERT INTO products(id,name,price) VALUES(:id,:name,:price)");
    query.bindValue(":id",product.getId());
    query.bindValue(":name",QString::fromStdString(product.getName()));
    query.bindValue(":price",product.getPrice());
    if(!query.exec()){
        std::cerr << "Failed to create product: " << query.lastError().text().toStdString() << std::endl;
        return false;
    }
    return true;
}
std::vector<Product> ProductRepository::getAll(){
    std::vector<Product> products;
    QSqlQuery query(database.getDatabase());
    if(!query.exec("SELECT id,name,price FROM products ORDER BY id")){
        std::cerr << "Failed to get products: " << query.lastError().text().toStdString() << std::endl;
        return products;
    }
    while(query.next()){
        int id = query.value("id").toInt();
        std::string name = query.value("name").toString().toStdString();
        double price = query.value("price").toDouble();
        products.emplace_back(id,name,price);
    }
    return products;
}
std::optional<Product> ProductRepository::getById(int id){
    QSqlQuery query(database.getDatabase());
    query.prepare("SELECT id,name,price FROM products WHERE id = :id");
    query.bindValue(":id",id);
    if(!query.exec()){
        std::cerr << "Failed to get product: " << query.lastError().text().toStdString() << std::endl;
        return std::nullopt;
    }
    if(!query.next()){
        return std::nullopt;
    }
    int productId = query.value("id").toInt();
    std::string name = query.value("name").toString().toStdString();
    double price = query.value("price").toDouble();
    return Product(productId,name,price);
}
bool ProductRepository::update(const Product& product){
    QSqlQuery query(database.getDatabase());
    query.prepare("UPDATE products SET name = :name,price = :price,updated_at = CURRENT_TIMESTAMP WHERE id = :id");
    query.bindValue(":id",product.getId());
    query.bindValue(":name",QString::fromStdString(product.getName()));
    query.bindValue(":price",product.getPrice());
    if(!query.exec()){
        std::cerr << "Failed to update product: " << query.lastError().text().toStdString() << std::endl;
        return false;
    }
    return query.numRowsAffected() > 0;
}
bool ProductRepository::remove(int id){
    QSqlQuery query(database.getDatabase());
    query.prepare("DELETE FROM products WHERE id = :id");
    query.bindValue(":id",id);
    if(!query.exec()){
        std::cerr << "Failed to remove product: " << query.lastError().text().toStdString() << std::endl;
        return false;
    }
    return query.numRowsAffected() > 0;
}