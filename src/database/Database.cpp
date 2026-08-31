#include "database/Database.h"
#include <QDir>
#include <QSqlError>
#include <QDebug>
Database::Database(){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("data/ordermanager.db");
}
bool Database::initialize(){
    if(!database.open()){
        qDebug() << "Database connection failed:" << database.lastError().text();
        return false;
    }
    qDebug() << "Database connection successful.";
    return true;
}
QSqlDatabase& Database::getDatabase(){
    return database;
}