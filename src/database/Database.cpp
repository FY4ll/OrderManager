#include "database/Database.h"
#include <QDebug>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <iostream>
Database::Database() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    const QString dataDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDirectory);
    database.setDatabaseName(QDir(dataDirectory).filePath("ordermanager.db"));
}
bool Database::initialize() {
    if (!database.open()) {
        qDebug() << "Database connection failed:" << database.lastError().text();
        return false;
    }
    qDebug() << "Database connection successful.";
    if (!createTables()) {
        return false;
    }
    qDebug() << "Database tables initialized.";
    return true;
}
QSqlDatabase& Database::getDatabase() {
    return database;
}
bool Database::createTables() {
    QSqlQuery query(database);
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS products(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            price REAL NOT NULL,
            created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
            updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
        )
    )";
    if (!query.exec(sql)) {
        qDebug() << "Failed to create products table:" << query.lastError().text();
        return false;
    }
    qDebug() << "Products table ready.";
    return true;
}