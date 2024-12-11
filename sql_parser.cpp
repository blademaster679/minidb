#include "sql_parser.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iterator>


// 去除字符串中的空格和制表符
static std::string DeleteSpaces(const std::string &str) {
    std::string result = str;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    result.erase(std::remove(result.begin(), result.end(), '\t'), result.end());
    return result;
}


std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos_start = 0, pos_end;
    std::string token;
    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        DeleteSpaces(token);
        tokens.push_back(token);
        pos_start = pos_end + delimiter.length();
    }
    token = s.substr(pos_start);
    DeleteSpaces(token);
    tokens.push_back(token);
    return tokens;
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

// 实现 parseWhereConditions 函数
std::vector<Condition> SQLParser::parseWhereConditions(const std::string& whereClause) {
    std::vector<Condition> conditions;

    // 按照 "AND" 分割条件
    std::vector<std::string> conditionStrings = split(whereClause, "AND");
    for (const auto& condition : conditionStrings) {
        std::cout << "Condition string: " << condition << std::endl;
    }

    for (const auto& condStr : conditionStrings) {
        Condition cond = parseCondition(condStr);
        cond.column = DeleteSpaces(cond.column);
        cond.value = DeleteSpaces(cond.value);
        conditions.push_back(cond);
    }
    for (const auto& condition : conditions) {
        std::cout << "Column: " << condition.column << ", Operator: " << condition.op << ", Value: " << condition.value << std::endl;
    }
    return conditions;
}
// 解析查询命令
SelectCommand SQLParser::parseSelect(const std::string& sql_command) {
    SelectCommand selectCmd;
    std::stringstream ss(sql_command);
    std::string token;

    ss >> token; // 跳过 "SELECT"
    // 解析列名
    std::getline(ss, token, 'F'); // 读取到 "FROM" 为止
    DeleteSpaces(token);
    selectCmd.columns = split(token, ",");

    // 解析 FROM
    ss >> token; // 应该是 "ROM" 的剩余部分
    ss >> selectCmd.tableName;
    std::cout << "Table name: " << selectCmd.tableName << std::endl; // 调试输出
    if (!selectCmd.tableName.empty() && selectCmd.tableName.back() == ';') {
        selectCmd.tableName.pop_back();  // 删除最后一个字符
    }
    std::cout << "Table name: " << selectCmd.tableName << std::endl; // 调试输出
    // 检查是否有 WHERE 子句
    ss >> token;
    std::cout << "Token: " << token << std::endl; // 调试输出
    if (token == "WHERE") {
        std::string whereClause;
        std::getline(ss, whereClause, ';'); // 读取 WHERE 子句直到分号
        DeleteSpaces(whereClause);
        std::cout << "Where clause: " << whereClause << std::endl; // 调试输出

        // 将 WHERE 子句解析为条件对象列表
        selectCmd.whereConditions = parseWhereConditions(whereClause);
    } else {
        // 如果没有 WHERE，将读取的 token 回退
        ss.putback(' ');
        for (int i = token.length() - 1; i >= 0; --i) {
            ss.putback(token[i]);
        }
    }

    return selectCmd;
}

//     std::vector<Condition> SQLParser::parseWhereConditions(const std::string& whereClause) {
//     std::vector<Condition> conditions;
//     std::vector<std::string> conditionStrings = split(whereClause, "AND");

//     for (const auto& condStr : conditionStrings) {
//         Condition cond = parseCondition(condStr);
//         conditions.push_back(cond);
//     }

//     return conditions;
// }

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
    Condition SQLParser::parseCondition(const std::string& conditionStr) {
    Condition condition;
    std::string str = DeleteSpaces(conditionStr);
    std::cout << "Condition stringhhhhhh: " << str << std::endl; // 调试输出
    std::vector<std::string> operators = {">", "<", "=", "!="};
    for (const auto& op : operators) {
        size_t pos = str.find(op);
        if (pos != std::string::npos) {
            condition.op = op;
            condition.column = str.substr(0, pos);
            condition.value = str.substr(pos + op.length());
            break;
        }
    }
    // std::stringstream ss(str);
    // ss >> condition.column >> condition.op >> condition.value;

    // 去除可能的引号
    condition.value.erase(remove(condition.value.begin(), condition.value.end(), '\''), condition.value.end());

    return condition;
}
// Condition SQLParser::parseCondition(const std::string &condition)
// {
//     Condition condition_group;
//     std::string no_space_condition = DeleteSpaces(condition);
//     if (no_space_condition.find(">") != std::string::npos)
//     {
//         size_t pos = no_space_condition.find(">");
//         condition_group.op = ">";
//         condition_group.column = no_space_condition.substr(0, pos);
//         condition_group.value = no_space_condition.substr(pos + 1);
//     }
//     else if (no_space_condition.find("<") != std::string::npos)
//     {
//         size_t pos = no_space_condition.find("<");
//         condition_group.op = "<";
//         condition_group.column = no_space_condition.substr(0, pos);
//         condition_group.value = no_space_condition.substr(pos + 1);
//     }
//     else if (no_space_condition.find("=") != std::string::npos)
//     {
//         size_t pos = no_space_condition.find("=");
//         condition_group.op = "=";
//         condition_group.column = no_space_condition.substr(0, pos);
//         condition_group.value = no_space_condition.substr(pos + 1);
//     }
//     else if (no_space_condition.find("!=") != std::string::npos)
//     {
//         size_t pos = no_space_condition.find("!=");
//         condition_group.op = "!=";
//         condition_group.column = no_space_condition.substr(0, pos);
//         condition_group.value = no_space_condition.substr(pos + 2);
//     }
//     condition_group.column = DeleteSpaces(condition_group.column);
//     condition_group.value = DeleteSpaces(condition_group.value);
//     return condition_group;
// }

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