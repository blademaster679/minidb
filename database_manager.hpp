#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP
#include <iostream>
#include <vector>
#include <stdexcept>
#include "sql_parser.h"

class DatabaseManager{
public:
    void createDatabase(const std::string &db_name);
    void useDatabase(const std::string &db_name);
    void createTable(const std::string &table_name, const std::vector<std::pair<std::string, std::string>> &columns);
    void dropTable(const std::string &table_name);
    std::string getCurrentDatabase() const;
    std::vector<std::vector<std::string>> fetchData(const std::string &table_name) const;
    void insertData(const InsertCommand &insert_cmd);
    void updateData(const std::string &table_name, const std::string &set_clause, const std::string &where_clause);
    void deleteData(const std::string &table_name, const std::string &where_clause);
private:
    std::string current_database;
    std::vector<std::string> databases;
    std::string getDatabasePath(const std::string &db_name) const;
    std::string getTablePath(const std::string &table_name) const;
    bool databaseExists(const std::string &db_name) const;
    bool tableExists(const std::string &table_name) const;
};
#endif