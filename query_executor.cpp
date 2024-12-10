#include "query_executor.hpp"
#include "database_manager.hpp"
#include "output_formatter.hpp"
#include <iostream>

// 执行 SELECT 查询
void QueryExecutor::executeSelect(const SelectCommand& cmd, const std::string& outputFile) {
    // 获取 DatabaseManager 单例
    DatabaseManager& dbManager = DatabaseManager::getInstance();

    // 确保当前数据库已经选择
    if (dbManager.getCurrentDatabase().empty()) {
        throw std::runtime_error("No database selected.");
    }

    // 假设读取的数据已经是不包含数据类型的信息
    std::vector<std::vector<std::string>> result = dbManager.readFromFile(cmd.tableName);

    // 执行查询的逻辑（例如查找数据库中的表、执行查询）
    std::cout << "Executing SELECT on database: " << dbManager.getCurrentDatabase() << std::endl;

    // 打开指定的输出文件
    std::ofstream outFile(outputFile, std::ios::app);  // 以追加模式打开文件

    if (!outFile) {
        throw std::runtime_error("Error: Unable to open output file: " + outputFile);
    }

    // 判断是否是第一次写入（文件是否为空）
    bool isFirstWrite = (outFile.tellp() == 0);

    // 使用 OutputFormatter 进行格式化输出
    OutputFormatter::formatOutputToCSV(result, outFile, isFirstWrite);

    // 输出到控制台
    std::cout << "SELECT query executed and results saved to " << outputFile << std::endl;
}

// void QueryExecutor::executeSelect(const SelectCommand &cmd)
// {
//     // 读取数据
//     DatabaseManager& dbManager = DatabaseManager::getInstance();
//     std::vector<std::vector<std::string>> result = dbManager.readFromFile(cmd.tableName); // 获取表数据

//     // 输出查询结果（通过 OutputFormatter 转为 CSV 格式）
//     std::string filePath = dbManager.getDatabasePath(dbManager.getCurrentDatabase()) + "/" + cmd.tableName + ".csv";
//     OutputFormatter::formatOutputToCSV(result, filePath);
//     std::cout << "SELECT query executed and results saved to test1.csv" << std::endl;
// }



// 执行 INSERT 查询
void QueryExecutor::executeInsert(const InsertCommand& cmd) {
    // 获取 DatabaseManager 单例
    DatabaseManager& dbManager = DatabaseManager::getInstance();

    // 确保当前数据库已经选择
    if (dbManager.getCurrentDatabase().empty()) {
        throw std::runtime_error("No database selected.");
    }

    // 获取表文件路径
    std::string filePath = dbManager.getDatabasePath(dbManager.getCurrentDatabase()) + "/" + cmd.tableName + ".csv";

    // 打开文件进行写入
    std::ofstream outFile(filePath, std::ios::app);  // 以追加模式打开文件

    if (!outFile) {
        throw std::runtime_error("Error: Unable to open file for writing: " + filePath);
    }

    // 写入数据到文件
    for (size_t i = 0; i < cmd.values.size(); ++i) {
        outFile << cmd.values[i];
        if (i != cmd.values.size() - 1) {
            outFile << ",";  // 用逗号分隔列值
        }
    }
    outFile << "\n";  // 写入换行符

    std::cout << "Data inserted into " << cmd.tableName << " in file " << filePath << std::endl;
}

// void QueryExecutor::executeInsert(const InsertCommand &insertCmd)
// {
//     DatabaseManager& dbManager = DatabaseManager::getInstance();
//     dbManager.insertData(insertCmd); // 执行插入操作
//     std::cout << "INSERT query executed. Data inserted into table '" << insertCmd.tableName << "'." << std::endl;
// }

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
