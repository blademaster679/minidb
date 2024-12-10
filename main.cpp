#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "sql_parser.hpp"
#include "database_manager.hpp"
#include "query_executor.hpp"
#include "output_formatter.hpp"
#include "error_reporter.hpp"

using namespace std;

// 主程序，负责读取SQL文件并执行命令
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: ./minidb <input.sql> <output.csv>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    ifstream sqlFile(inputFile);
    if (!sqlFile)
    {
        cerr << "Error: Unable to open input SQL file." << endl;
        return 1;
    }

    ofstream output(outputFile);
    if (!output)
    {
        cerr << "Error: Unable to open output file." << endl;
        return 1;
    }

    // 初始化模块
    DatabaseManager &dbManager = DatabaseManager::getInstance();
    QueryExecutor queryExecutor;

    string line;
    int lineNumber = 0;
    bool insideCreateTable = false;
    string createTableCommand;

    // 读取并处理每一行SQL命令
    while (getline(sqlFile, line))
    {
        lineNumber++;
        std::cout << lineNumber << std::endl;
        stringstream ss(line);
        string command;
        cout << "Line " << lineNumber << ": " << line << endl;
        // 跳过空行或注释行
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        ss >> command;
        std::cout << "Command: " << command << std::endl;//调试输出
        try
        {
            // 解析并执行SQL命令
            if (command == "CREATE")
            {
                ss >> command;
                if (command == "DATABASE")
                {
                    string dbName;
                    ss >> dbName;
                    if (!dbName.empty() && dbName[dbName.size() - 1] == ';')
                    {
                        dbName.erase(dbName.size() - 1); // 删除最后一个字符
                    }
                    dbManager.createDatabase(dbName);
                    cout << "Database " << dbName << " created." << endl;
                }
                else if (command == "TABLE")
                {
                    string tableCommand;
                    // 开始解析 CREATE TABLE 命令
                    insideCreateTable = true;
                    createTableCommand = line; // 将当前行加入 CREATE TABLE 命令

                    // 继续读取接下来的行直到括号结束
                    while (getline(sqlFile, line) && insideCreateTable)
                    {
                        createTableCommand += "\n" + line;  // 追加当前行到 CREATE TABLE 命令
                        if (line.find(')') != string::npos) // 如果遇到右括号，则结束
                        {
                            insideCreateTable = false;
                            break;
                        }
                    }

                    cout << "Parsed CREATE TABLE statement: " << createTableCommand << endl;       // 调试输出
                    CreateTableCommand tableCmd = SQLParser::parseCreateTable(createTableCommand); // 传递整个表创建命令
                    dbManager.createTable(tableCmd.tableName, tableCmd.columns);
                    cout << "Table " << tableCmd.tableName << " created." << endl;
                }
                else
                {
                    throw runtime_error("Invalid CREATE command.");
                }
            }
            else if (command == "USE")
            {
                ss >> command; // 跳过 DATABASE 关键字
                if (command != "DATABASE")
                {
                    cerr << "Error: Invalid USE command. Expected 'USE DATABASE'." << endl;
                    return 1;
                }

                string dbName;
                ss >> dbName; // 提取数据库名称
                if (!dbName.empty() && dbName[dbName.size() - 1] == ';')
                {
                    dbName.erase(dbName.size() - 1); // 删除最后一个字符
                }
                dbManager.useDatabase(dbName); // 设置当前数据库
                cout << "Using database " << dbName << "." << endl;
            }

            else if (command == "INSERT")
            {
                // 解析 INSERT 命令
                InsertCommand insertCmd = SQLParser::parseInsert(line);
                queryExecutor.executeInsert(insertCmd);
                cout << "Insert command processed." << endl;
            }
            else if (command == "SELECT")
            {
                // 解析 SELECT 命令
                SelectCommand selectCmd = SQLParser::parseSelect(line);
                // 执行查询并将结果写入 CSV 文件
                queryExecutor.executeSelect(selectCmd,outputFile);
                cout << "Select command processed." << endl;
            }

            else
            {
                throw runtime_error("Invalid SQL command: " + command);
            }
        }
        catch (const exception &e)
        {
            // 错误处理
            cerr << "Error at line " << lineNumber << ": " << e.what() << endl;
        }
    }

    sqlFile.close();
    output.close();

    cout << "Execution completed. Results are saved in " << outputFile << endl;
    return 0;
}
