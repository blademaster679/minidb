#include "query_executor.hpp"
#include "database_manager.hpp"
#include "output_formatter.hpp"
#include <iostream>
#include <algorithm>

static std::string DeleteSpaces(const std::string &str) {
    std::string result = str;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    result.erase(std::remove(result.begin(), result.end(), '\t'), result.end());
    return result;
}


bool QueryExecutor::evaluateWhereConditions(const std::vector<Condition>& conditions, const std::vector<std::string>& row, const std::unordered_map<std::string, size_t>& columnIndexMap) {
    for (const auto& condition : conditions) {
        auto it = columnIndexMap.find(condition.column);
        if (it == columnIndexMap.end()) {
            throw std::runtime_error("Column not found in WHERE clause: " + condition.column);
        }
        size_t idx = it->second;
        std::string cellValue = row[idx];
        cellValue.erase(std::remove(cellValue.begin(), cellValue.end(), '\''), cellValue.end());

        // 比较操作，目前支持 '=', '<', '>'
        if (condition.op == "=") {
            if (cellValue != condition.value) {
                return false;
            }
        } else if (condition.op == "<") {
            if (!(cellValue < condition.value)) {
                return false;
            }
        } else if (condition.op == ">") {
            if (!(cellValue > condition.value)) {
                return false;
            }
        } else {
            throw std::runtime_error("Unsupported operator in WHERE clause: " + condition.op);
        }
    }
    return true; // 所有条件都满足
}

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
    // //如果有where子句，进行筛选
    // if(!cmd.whereClause.empty()){
    //     std::vector<std::vector<std::string>> filteredResult;
    //     for (const auto& row : result) {
    //         if (dbManager.checkCondition(row, cmd.whereConditions[0], cmd.whereConditions[2])) {
    //             filteredResult.push_back(row);
    //         }
    //     }
    //     result = filteredResult;
    // }

    // 执行查询的逻辑（例如查找数据库中的表、执行查询）
    std::cout << "Executing SELECT on database: " << dbManager.getCurrentDatabase() << std::endl;
    // 输出 cmd.columns 里的内容
    std::cout << "Columns to be selected: ";
    for (const auto& col : cmd.columns) {
        std::cout << col << " ";
    }
    std::cout << std::endl;
   // 构建列名到索引的映射
    std::unordered_map<std::string, size_t> columnIndexMap;
    for (size_t i = 0; i < cmd.columns.size(); ++i) {
        std::string column = cmd.columns[i];
        column = DeleteSpaces(column);
        columnIndexMap[column] = i;
    }
    // 输出 columnIndexMap 的内容
    std::cout << "Column Index Map: " << std::endl;
    for (const auto& pair : columnIndexMap) {
        std::cout << "Column: " << pair.first << ", Index: " << pair.second << std::endl;
    }
    // 过滤数据
    std::vector<std::vector<std::string>> filteredData;
    filteredData.push_back(cmd.columns); // 添加要查询的列名
    

    for (size_t i = 1; i < result.size(); ++i) {
        auto& row = result[i];
        // // 输出 row 的内容
        // std::cout << "Row: ";
        // for (const auto& cell : row) {
        //     std::cout << cell << " ";
        // }
        // std::cout << std::endl;
        for (auto& cell : row) {
            size_t pos = cell.find(' ');
            if (pos != std::string::npos) {
                cell = cell.substr(0, pos);
            }
        }
        // 输出 row 的内容
        std::cout << "Row: ";
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
        if (evaluateWhereConditions(cmd.whereConditions, row, columnIndexMap)) {
            // 选择需要的列
            std::vector<std::string> selectedRow;
            for (const auto& col : cmd.columns) {
                size_t idx = columnIndexMap[DeleteSpaces(col)];
                std::cout << idx << std::endl;
                std::cout << "Selected column: " << col << ", Value: " << row[idx] << std::endl;
                selectedRow.push_back(row[idx]);
            }
            filteredData.push_back(selectedRow);
        }
    }

    // 输出结果到文件
    std::ofstream outFile(outputFile, std::ios::app);
    bool isFirstWrite = (outFile.tellp() == 0);
    OutputFormatter::formatOutputToCSV(filteredData, outFile, isFirstWrite);

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
