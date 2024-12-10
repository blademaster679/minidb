#include "sql_parser.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iterator>

// 去除字符串中的空格和制表符
static std::string DeleteSpaces(const std::string &str)
{
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");

    if (first == std::string::npos)
        return "";                              // 如果没有找到非空字符
    return str.substr(first, last - first + 1); // 返回去除空格后的字符串
}

// static std::string DeleteSpaces(const std::string &str)
// {
//     size_t start = str.find_first_not_of(" \t");
//     size_t end = str.find_last_not_of(" \t");
//     if (start == std::string::npos || end == std::string::npos)
//     {
//         return "";
//     }
//     else
//     {
//         return str.substr(start, end - start + 1);
//     }
// }

// 解析创建数据库命令
CreateDatabaseCommand SQLParser::parseCreateDatabase(const std::string &sql_command)
{
    std::istringstream stream(sql_command);
    std::string command, database_name;
    stream >> command >> command >> database_name;
    return CreateDatabaseCommand{DeleteSpaces(database_name)};
}

// 解析使用数据库命令
UseDatabaseCommand SQLParser::parseUseDatabase(const std::string &sql_command)
{
    std::istringstream stream(sql_command);
    std::string command, database_name;
    stream >> command >> command >> database_name;
    return UseDatabaseCommand{DeleteSpaces(database_name)};
}

// 解析创建表命令
CreateTableCommand SQLParser::parseCreateTable(const std::string &sql_command)
{
    std::istringstream stream(sql_command);
    std::string command, table_name, column_name, column_type;
    char c;
    std::vector<std::pair<std::string, std::string>> columns;

    // 读取 CREATE TABLE 和表名
    stream >> command >> command >> table_name;
    if (table_name.empty())
    {
        throw std::runtime_error("Error: Invalid SQL command: missing table name.");
    }
    std::cout << "Parsing CREATE TABLE for table: " << table_name << std::endl; // 调试输出
    stream >> c;                                                                // 跳过左括号 '('

    // 解析列定义
    while (stream >> column_name)
    {
        // 删除列名两端的空格
        column_name = DeleteSpaces(column_name);

        // 如果列名解析完毕，接着读取列类型
        if (stream >> column_type)
        {
            column_type = DeleteSpaces(column_type);
            std::cout << "Column: " << column_name << ", Type: " << column_type << std::endl; // 调试输出
            columns.push_back({column_name, column_type});
        }
        char nextChar = stream.peek(); // 查看下一个字符
        if (nextChar == ')')
        {
            break;
        }
        // 读取逗号或右括号
        // stream >> c;
        // std::cout << "Next character: " << c << std::endl;  // 调试输出
        // if (c == ')') {
        //     break;  // 如果遇到右括号，则结束循环
        // }
    }

    // 返回包含表名和列信息的创建表命令
    return CreateTableCommand{DeleteSpaces(table_name), columns};
}

// CreateTableCommand SQLParser::parseCreateTable(const std::string& sql_command){
//     std::istringstream stream(sql_command);
//     std::string command , table_name , column_name , column_type;
//     char c;
//     stream >> command >> command >> table_name;
//     stream >> c; //跳过左括号
//     std::vector<std::pair<std::string, std::string>> columns;
//     while(stream >> column_name >> column_type){
//         columns.push_back({DeleteSpaces(column_name), DeleteSpaces(column_type)});
//         stream >> c; //跳过逗号和右括号
//         if(c == ')'){
//             break;
//         }
//     }
//     return CreateTableCommand{DeleteSpaces(table_name), columns};
// }

// 解析插入命令
InsertCommand SQLParser::parseInsert(const std::string &sql_command)
{
    std::istringstream stream(sql_command);
    std::string command, table_name, value;
    char c;
    stream >> command >> command >> table_name;
    stream >> c; // 跳过左括号
    std::getline(stream, value);
    value = value.substr(value.find('(') + 1, value.find(')') - value.find('(') - 1);
    std::istringstream value_stream(value);
    std::vector<std::string> values;
    while (std::getline(value_stream, value, ','))
    {
        values.push_back(DeleteSpaces(value));
    }
    std::cout << table_name << "  " << value << std::endl; // 调试输出
    return InsertCommand{DeleteSpaces(table_name), values};
}

// 解析查询命令
SelectCommand SQLParser::parseSelect(const std::string &sql_command)
{
    std::istringstream stream(sql_command);
    std::string command, column_name, table_name, joinTable, onCondition, whereClause, fromKeyword;
    char c;
    std::vector<std::string> columns;

    // 读取 SELECT 关键字
    stream >> command;
    if (command != "SELECT")
    {
        throw std::runtime_error("Error: Invalid SQL command. Expected 'SELECT'.");
    }

    // 解析列名，直到遇到 FROM 关键字
    while (stream >> column_name)
    {
        if (column_name == "FROM")
        {
            break; // 跳出循环，准备解析表名
        }
        column_name = DeleteSpaces(column_name); // 去除列名两端的空格
        columns.push_back(column_name);

        // 读取逗号或空格，确保正确处理多个列名
        while (stream.peek() == ' ' || stream.peek() == ',')
        {
            stream.ignore(); // 跳过空格或逗号
        }
    }

    if (column_name != "FROM")
    {
        throw std::runtime_error("Error: Expected 'FROM' after columns.");
    }

    // 读取表名
    stream >> table_name;
    if (!table_name.empty() && table_name[table_name.size() - 1] == ';')
    {
        table_name.erase(table_name.size() - 1); // 删除最后一个字符
    }
    table_name = DeleteSpaces(table_name); // 去除表名两端的空格

    // std::string columns;                        // 解析所有列名
    // std::getline(stream, columns, ',');         // 以逗号分隔
    // std::istringstream columns_stream(columns); // 对于所有列名进行处理，将其分为一个个列名
    // std::vector<std::string> columns_vector;
    // std::string column;
    // while (std::getline(columns_stream, column, ','))
    // {
    //     columns_vector.push_back(DeleteSpaces(column)); // 将一个个列名存入vector
    // }
    // stream >> command;
    // stream >> table_name;
    SelectCommand cmd{DeleteSpaces(table_name), columns, ""};
    parseJoinClause(sql_command, cmd); // 解析join子句
    // std::vector<Join> joins = parseJoinClause(sql_command);//解析join子句

    std::getline(stream, whereClause); // 解析where子句
    whereClause = DeleteSpaces(whereClause);
    if (whereClause.find("WHERE") == std::string::npos)
    {
        whereClause = ""; // 如果没有where子句，将其置为空
    }
    if (whereClause.find("WHERE") != std::string::npos)
    {
        cmd.whereClause = whereClause;
        cmd.whereConditions = parseWhereClause(whereClause);
    }
    return SelectCommand{DeleteSpaces(table_name), columns, whereClause, cmd.whereConditions, joinTable, onCondition};
}

// 解析where子句
std::vector<std::string> SQLParser::parseWhereClause(const std::string &sql_command)
{
    std::string whereClause = DeleteSpaces(sql_command);
    std::vector<std::string> conditions;
    if (whereClause.find("WHERE") != std::string::npos)
    {
        whereClause = whereClause.substr(whereClause.find("WHERE") + 5);
        std::istringstream stream(whereClause);
        std::string condition;
        while (std::getline(stream, condition, ' '))
        {
            condition = DeleteSpaces(condition);
            conditions.push_back(condition);
        }
    }
    return conditions;
}

// 解析where子句(update)
void SQLParser::parseWhereClause(const std::string &whereClause, std::string &columnName, std::string &value)
{
    // 假设我们处理一个简单的条件：WHERE column = value
    std::stringstream ss(whereClause);
    std::string column, eq, val;
    ss >> column >> eq >> val;

    columnName = column;
    value = val;
}

// 解析join子句
void SQLParser::parseJoinClause(const std::string &sql_command, SelectCommand &table_name)
{
    std::istringstream stream(sql_command);
    std::string command, joinType, joinTable, onCondition;
    if (sql_command.find("INNER JOIN") != std::string::npos)
    {
        stream >> command;                 // 读取select
        stream >> command;                 // 跳过表名
        stream >> command;                 // 跳过from
        stream >> command;                 // 跳过主表名
        stream >> joinType;                // 读取join类型INNER
        stream >> joinType;                // 读取join类型JOIN
        stream >> joinTable;               // 读取连接表名
        std::getline(stream, onCondition); // 读取连接条件
        onCondition = DeleteSpaces(onCondition);
        if (onCondition.find("ON") != std::string::npos)
        {
            onCondition = onCondition.substr(onCondition.find("ON") + 2);
        }
        table_name.joinTable = DeleteSpaces(joinTable);
        table_name.onCondition = DeleteSpaces(onCondition);
    }
}

// 解析条件
Condition SQLParser::parseCondition(const std::string &condition)
{
    Condition condition_group;
    std::string no_space_condition = DeleteSpaces(condition);
    if (no_space_condition.find(">") != std::string::npos)
    {
        size_t pos = no_space_condition.find(">");
        condition_group.op = ">";
        condition_group.column = no_space_condition.substr(0, pos);
        condition_group.value = no_space_condition.substr(pos + 1);
    }
    else if (no_space_condition.find("<") != std::string::npos)
    {
        size_t pos = no_space_condition.find("<");
        condition_group.op = "<";
        condition_group.column = no_space_condition.substr(0, pos);
        condition_group.value = no_space_condition.substr(pos + 1);
    }
    else if (no_space_condition.find("=") != std::string::npos)
    {
        size_t pos = no_space_condition.find("=");
        condition_group.op = "=";
        condition_group.column = no_space_condition.substr(0, pos);
        condition_group.value = no_space_condition.substr(pos + 1);
    }
    else if (no_space_condition.find("!=") != std::string::npos)
    {
        size_t pos = no_space_condition.find("!=");
        condition_group.op = "!=";
        condition_group.column = no_space_condition.substr(0, pos);
        condition_group.value = no_space_condition.substr(pos + 2);
    }
    condition_group.column = DeleteSpaces(condition_group.column);
    condition_group.value = DeleteSpaces(condition_group.value);
    return condition_group;
}

// 解析更新命令
std::map<std::string, std::string> SQLParser::parseUpdateSet(const std::string &setClause)
{
    std::map<std::string, std::string> updates;
    std::stringstream ss(setClause);
    std::string part;

    // 格式：SET column1 = value1, column2 = value2, ...
    while (std::getline(ss, part, ','))
    {
        std::stringstream partStream(part);
        std::string column, value;
        std::getline(partStream, column, '=');
        std::getline(partStream, value);

        // 去除两端的空白字符
        column = DeleteSpaces(column);
        value = DeleteSpaces(value);

        updates[column] = value;
    }

    return updates;
}