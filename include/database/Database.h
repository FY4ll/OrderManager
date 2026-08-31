#pragma once
#include <QSqlDatabase>
class Database{
public:
    Database();
    bool initialize();
    QSqlDatabase& getDatabase();
private:
    QSqlDatabase database;
};