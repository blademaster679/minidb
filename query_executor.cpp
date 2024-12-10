#include "query_executor.hpp"
#include "database_manager.hpp"
#include "output_formatter.hpp"
#include <iostream>

// 执行 SELECT 查询
void QueryExecutor::executeSelect(const SelectCommand &cmd)
{
    // 读取数据
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    std::vector<std::vector<std::string>> result = dbManager.readFromFile(cmd.tableName); // 获取表数据

    // 输出查询结果（通过 OutputFormatter 转为 CSV 格式）
    OutputFormatter::formatOutputToCSV(result, "test1.csv");
    std::cout << "SELECT query executed and results saved to test1.csv" << std::endl;
}

// 执行 INSERT 查询
void QueryExecutor::executeInsert(const InsertCommand &insertCmd)
{
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    dbManager.insertData(insertCmd); // 执行插入操作
    std::cout << "INSERT query executed. Data inserted into table '" << insertCmd.tableName << "'." << std::endl;
}

// 执行 UPDATE 查询
void QueryExecutor::executeUpdate(const std::string &tableName, const std::string &setClause, const std::string &whereClause)
{
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    dbManager.updateData(tableName, setClause, whereClause); // 执行更新操作
    std::cout << "UPDATE query executed. Data updated in table '" << tableName << "'." << std::endl;
}

// 执行 DELETE 查询
void QueryExecutor::executeDelete(const std::string &tableName, const std::string &whereClause)
{
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    dbManager.deleteData(tableName, whereClause); // 执行删除操作
    std::cout << "DELETE query executed. Data deleted from table '" << tableName << "'." << std::endl;
}
