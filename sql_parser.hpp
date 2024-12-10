#ifndef SQL_PARSER_HPP
#define SQL_PARSER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <map>

struct CreateDatabaseCommand{
    std::string databaseName;
};

struct UseDatabaseCommand{
    std::string databaseName;
};

struct CreateTableCommand{
    std::string tableName;
    std::vector<std::pair<std::string, std::string>> columns;
};

struct InsertCommand{
    std::string tableName;
    std::vector<std::string> values;
};

struct SelectCommand{
    std::string tableName;//主表名
    std::vector<std::string> columns;//要查询的列名
    std::string whereClause;//where子句
    std::vector<std::string> whereConditions;//where子句的条件
    std::string joinTable;//要连接的表名
    std::string onCondition;//连接条件
};

struct Condition{
    std::string column;
    std::string op;
    std::string value;
};

struct Join{
    std::string tableName;
    std::string column1;
    std::string column2;
};

class SQLParser{
public:
    static CreateDatabaseCommand parseCreateDatabase(const std::string& sql_command);
    static UseDatabaseCommand parseUseDatabase(const std::string& sql_command);
    static CreateTableCommand parseCreateTable(const std::string& sql_command);
    static InsertCommand parseInsert(const std::string& sql_command);
    static SelectCommand parseSelect(const std::string& sql_command);
    static std::vector<std::string> parseWhereClause(const std::string& sql_command);
    static Condition parseCondition(const std::string& condition);
    static void parseJoinClause(const std::string& sql_command, SelectCommand& sel_command);
    static std::map<std::string, std::string> parseUpdateSet(const std::string& setClause);
};
#endif