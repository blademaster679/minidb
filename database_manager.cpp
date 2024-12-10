#include "database_manager.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;
DatabaseManager* DatabaseManager::instance = nullptr;

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
void DatabaseManager::createTable(const std::string &table_name, const std::vector<std::pair<std::string, std::string>> &columns){
    if (current_database.empty()){
        throw std::runtime_error("No database selected.");
    }
    std::string table_path = getTablePath(table_name);
    if (tableExists(table_name)){
        throw std::runtime_error("Table already exists:" + table_name);
    }
    std::ofstream table_file(table_path);
    if (!table_file){
        throw std::runtime_error("Failed to create table file:" + table_name);
    }
    table_file << columns.size() << "\n";  // 记录列的数量
    for (const auto &column : columns){
        table_file << column.first << " " << column.second << "\n";
    }
    table_file.close();
    std::cout << "Table: " << table_name << " created successfully in database:" << current_database << std::endl;

    // 将列信息和数量保存到元数据映射中
    TableMetadata metadata;
    metadata.columnCount = columns.size();
    for (const auto &column : columns){
        ColumnInfo colInfo;
        colInfo.name = column.first;
        colInfo.type = column.second;
        metadata.columns.push_back(colInfo);
    }
    tableMetadataMap[table_name] = metadata;
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
    return "../databases/" + db_name;
}

//获取表路径
std::string DatabaseManager::getTablePath(const std::string &table_name) const{
    if (current_database.empty()){
        throw std::runtime_error("No database selected.");
    }
    return getDatabasePath(current_database) + "/" + table_name + ".csv";
}

//读取表数据
std::vector<std::vector<std::string>> DatabaseManager::readFromFile(const std::string& tableName) const{
    std::vector<std::vector<std::string>> data;
    std::ifstream file(getTablePath(tableName));  // 获取表路径

    if (!file) {
        throw std::runtime_error("Failed to open table file: " + tableName);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> row;
        std::string cell;
        while (std::getline(ss, cell, ',')) {  // 根据逗号分隔每列
            row.push_back(cell);
        }
        data.push_back(row);  // 将每行数据存入数据集中
    }

    file.close();
    return data;  // 返回整个表的数据
}

//插入数据
void DatabaseManager::insertData(const InsertCommand& insertCmd) {
    std::cout << "hhhhhhhhhhhhhhhhhhh" << std::endl;
    std::vector<std::vector<std::string>> data = readFromFile(insertCmd.tableName);
    std::cout << "hhhhhhhhhhhhhhhhhhh" << std::endl;
    data.push_back(insertCmd.values);
    std::cout << "hhhhhhhhhhhhhhhhhhh" << std::endl;
    writeToFile(insertCmd.tableName, data);
    std::cout << "hhhhhhhhhhhhhhhhhhh" << std::endl;
    std::cout << "Data inserted into table '" << insertCmd.tableName << "'." << std::endl;
}

//更新数据
void DatabaseManager::updateData(const std::string& tableName, const std::string& setClause, const std::string& whereClause) {
    std::vector<std::vector<std::string>> data = readFromFile(tableName);  // 读取当前数据

    // 解析 SET 子句：SET column1 = value1, column2 = value2, ...
    std::map<std::string, std::string> updates = SQLParser::parseUpdateSet(setClause);

    // 解析 WHERE 子句（简单条件：比如 WHERE Name = 'Jay Chou'）
    std::string columnName, value;
    SQLParser::parseWhereClause(whereClause, columnName, value);

    bool updated = false;

    for (auto& row : data) {
        // 判断当前行是否满足 WHERE 条件
        if (checkCondition(row, columnName, value)) {
            updated = true;

            // 根据 SET 子句的更新条件更新行数据
            for (const auto& update : updates) {
                // 假设我们更新的列在 row 中已经有了对应的索引， 
                // 这里的 columnName 需要和数据表列的顺序匹配
                if (update.first == columnName) {
                    row[std::stoi(update.first)] = update.second;  // 假设列名对应位置的索引
                }
            }
        }
    }

    if (updated) {
        writeToFile(tableName, data);  // 更新数据写回文件
        std::cout << "Data updated in table '" << tableName << "'." << std::endl;
    } else {
        std::cout << "No matching rows found for update in table '" << tableName << "'." << std::endl;
    }
}

//写入数据
void DatabaseManager::writeToFile(const std::string& tableName, const std::vector<std::vector<std::string>>& data) const{
    std::ofstream file(getTablePath(tableName), std::ofstream::trunc);  // 获取表路径

    if (!file) {
        throw std::runtime_error("Failed to open table file for writing: " + tableName);
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            std::cout << row[i] << " ";
            if (i != row.size() - 1) {
                file << ",";  // 添加逗号分隔符
                std::cout << ", ";
                std::cout << "dsfynuhufhhauh";
            }
        }
        file << "\n";
    }
    std::cout << "hsdfbshdnfdnf";

    file.close();
}

//删除数据
void DatabaseManager::deleteData(const std::string& tableName, const std::string& whereClause) {
    std::vector<std::vector<std::string>> data = readFromFile(tableName);
    data.erase(
        std::remove_if(data.begin(), data.end(), [&whereClause](const std::vector<std::string>& row) {
            return row[0] == whereClause;  // 假设条件是 ID 匹配
        }),
        data.end()
    );
    writeToFile(tableName, data);
    std::cout << "Data deleted from table '" << tableName << "'." << std::endl;
}
//判断数据库是否存在
bool DatabaseManager::databaseExists(const std::string &db_name) const{
    return fs::exists(getDatabasePath(db_name));
}

//判断表是否存在
bool DatabaseManager::tableExists(const std::string &table_name) const{
    return fs::exists(getTablePath(table_name));
}

//检查条件
bool DatabaseManager::checkCondition(const std::vector<std::string>& row, const std::string& columnName, const std::string& value) const{
    // 假设我们通过列名来查找相应的列索引
    // 这里我们简化为直接通过列的顺序来做条件判断
    // 实际情况中需要根据列名映射来决定更新哪些列

    // 这个示例假设我们处理的只是一个简单的 WHERE 条件（比如 WHERE Name = 'Jay Chou'）
    for (const auto& rowData : row) {
        if (rowData == value) {
            return true;
        }
    }

    return false;
}