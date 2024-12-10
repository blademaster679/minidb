#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP
#include <iostream>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <string>
#include "sql_parser.hpp"

class DatabaseManager{
public:
    void createDatabase(const std::string &db_name);
    void useDatabase(const std::string &db_name);
    void createTable(const std::string &table_name, const std::vector<std::pair<std::string, std::string>> &columns);
    void dropTable(const std::string &table_name);
    std::string getCurrentDatabase() const;
    // std::vector<std::vector<std::string>> fetchData(const std::string &table_name) const;
    void insertData(const InsertCommand &insert_cmd);
    void updateData(const std::string &table_name, const std::string &set_clause, const std::string &where_clause);
    void deleteData(const std::string &table_name, const std::string &where_clause);
    std::vector<std::vector<std::string>> readFromFile(const std::string& table_name) const;
     // 获取单例实例
    static DatabaseManager& getInstance() {
        if (instance == nullptr) {
            instance = new DatabaseManager();
        }
        return *instance;
    }
private:
    static DatabaseManager* instance;
    std::string current_database;
    DatabaseManager(){
        std::cout << "DatabaseManager created." << std::endl;
    }
     // 私有拷贝构造函数和赋值运算符，确保不能复制实例
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    std::vector<std::string> databases;
    std::string getDatabasePath(const std::string &db_name) const;
    std::string getTablePath(const std::string &table_name) const;
    bool databaseExists(const std::string &db_name) const;
    bool tableExists(const std::string &table_name) const;
    void writeToFile(const std::string& table_name, const std::vector<std::vector<std::string>>& data) const;
    bool checkCondition(const std::vector<std::string> &row, const std::string& column_name, const std::string& value) const;
};
#endif