#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "sql_parser.h"
#include "database_manager.h"
#include "query_executor.h"
#include "output_formatter.h"
#include "error_reporter.h"

using namespace std;

// 主程序，负责读取SQL文件并执行命令
int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./minidb <input.sql> <output.csv>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    ifstream sqlFile(inputFile);
    if (!sqlFile) {
        cerr << "Error: Unable to open input SQL file." << endl;
        return 1;
    }

    ofstream output(outputFile);
    if (!output) {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    // 初始化模块
    DatabaseManager dbManager;
    QueryExecutor queryExecutor;

    string line;
    int lineNumber = 0;

    // 读取并处理每一行SQL命令
    while (getline(sqlFile, line)) {
        lineNumber++;
        stringstream ss(line);
        string command;
        
        // 跳过空行或注释行
        if (line.empty() || line[0] == '#') {
            continue;
        }

        ss >> command;

        try {
            // 解析并执行SQL命令
            if (command == "CREATE") {
                // 处理 CREATE 命令
                ss >> command;
                if (command == "DATABASE") {
                    string dbName;
                    ss >> dbName;
                    dbManager.createDatabase(dbName);
                    cout << "Database " << dbName << " created." << endl;
                } else if (command == "TABLE") {
                    // 解析 CREATE TABLE 命令
                    CreateTableCommand tableCmd = SQLParser::parseCreateTable(line);
                    dbManager.createTable(tableCmd);
                    cout << "Table " << tableCmd.tableName << " created." << endl;
                } else {
                    throw runtime_error("Invalid CREATE command.");
                }
            } else if (command == "USE") {
                // 处理 USE DATABASE 命令
                string dbName;
                ss >> dbName;
                dbManager.useDatabase(dbName);
                cout << "Using database " << dbName << "." << endl;
            } else if (command == "INSERT") {
                // 解析 INSERT 命令
                InsertCommand insertCmd = SQLParser::parseInsert(line);
                queryExecutor.executeInsert(insertCmd);
                cout << "Data inserted into " << insertCmd.tableName << "." << endl;
            } else if (command == "SELECT") {
                // 解析 SELECT 命令
                SelectCommand selectCmd = SQLParser::parseSelect(line);
                vector<vector<string>> result;
                queryExecutor.executeSelect(selectCmd);
                OutputFormatter::formatOutput(result, output);
                cout << "Query executed: SELECT ..." << endl;
            } else if (command == "UPDATE") {
                // 解析 UPDATE 命令
                string tableName, setClause, whereClause;
                // 解析语法并执行
                queryExecutor.executeUpdate(tableName, setClause, whereClause);
                cout << "Data updated in " << tableName << "." << endl;
            } else if (command == "DELETE") {
                // 解析 DELETE 命令
                string tableName, whereClause;
                queryExecutor.executeDelete(tableName, whereClause);
                cout << "Data deleted from " << tableName << "." << endl;
            } else if (command == "DROP") {
                // 处理 DROP TABLE 命令
                ss >> command;
                if (command == "TABLE") {
                    string tableName;
                    ss >> tableName;
                    dbManager.dropTable(tableName);
                    cout << "Table " << tableName << " dropped." << endl;
                }
            } else {
                throw runtime_error("Invalid SQL command: " + command);
            }

        } catch (const exception& e) {
            // 错误处理
            ErrorReporter::reportError(e.what(), lineNumber);
        }
    }

    sqlFile.close();
    output.close();

    cout << "Execution completed. Results are saved in " << outputFile << endl;
    return 0;
}
