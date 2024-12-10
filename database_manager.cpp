#include "database_manager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

//创建数据库
void DatabaseManager::createDatabase(const std::string &db_name){
    std::string db_path = getDatabasePath(db_name);
    if (databaseExists(db_name)){
        throw std::runtime_error("Database already exists:"+db_name);
    }
    fs::create_directory(db_path);
    databases.push_back(db_name);
    std::cout << "Database " << db_name << " created successfully." << std::endl;
}

//使用数据库
void DatabaseManager::useDatabase(const std::string &db_name){
    if (!databaseExists(db_name)){
        throw std::runtime_error("Database does not exist:"+db_name);
    }
    current_database = db_name;
    std::cout << "Using database: " << db_name << std::endl;
}

//创建表
void DatabaseManager::createTable(const std::string &table_name, const std::vector<std::pair<std::string, std::string>> &columms){
    if (current_database.empty()){
        throw std::runtime_error("No database selected.");
    }
    std::string table_path = getTablePath(table_name);
    if (tableExists(table_name)){
        throw std::runtime_error("Table already exists:"+table_name);
    }
    std::ofstream table_file(table_path);
    if (!table_file){
        throw std::runtime_error("Failed to create table file:" + table_name);
    }
    table_file << "Table:" << table_name << "\n";
    table_file << "Columns:\n";
    for (const auto &column : columms){
        table_file << column.first << " " << column.second << "\n";
    }
    table_file.close();
    std::cout << "Table: " << table_name << " created successfully in database:" << current_database << std::endl;
}

//删除表
void DatabaseManager::dropTable(const std::string &table_name){
    if (current_database.empty()){
        throw std::runtime_error("No database selected.");
    }
    std::string table_path = getTablePath(table_name);
    if (!tableExists(table_name)){
        throw std::runtime_error("Table does not exist:"+table_name);
    }
    fs::remove(table_path);
    std::cout << "Table: " << table_name << " dropped successfully from database:" << current_database << std::endl;
}

//获取当前数据库
std::string DatabaseManager::getCurrentDatabase() const{
    return current_database;
}

//获取数据库路径
std::string DatabaseManager::getDatabasePath(const std::string &db_name) const{
    return "databases/" + db_name;
}

//获取表路径
std::string DatabaseManager::getTablePath(const std::string &table_name) const{
    if (current_database.empty()){
        throw std::runtime_error("No database selected.");
    }
    return getDatabasePath(current_database) + "/" + table_name + ".csv";
}

//判断数据库是否存在
bool DatabaseManager::databaseExists(const std::string &db_name) const{
    return fs::exists(getDatabasePath(db_name));
}

//判断表是否存在
bool DatabaseManager::tableExists(const std::string &table_name) const{
    return fs::exists(getTablePath(table_name));
}