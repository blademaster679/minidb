#ifndef QUERY_EXECUTOR_H
#define QUERY_EXECUTOR_H

#include <string>
#include <vector>
#include "sql_parser.h"  // 用于 SQL 解析

class QueryExecutor {
public:
    // 执行 SELECT 查询
    void executeSelect(const SelectCommand& cmd);

    // 执行 INSERT 查询
    void executeInsert(const InsertCommand& insertCmd);

    // 执行 UPDATE 查询
    void executeUpdate(const std::string& tableName, const std::string& setClause, const std::string& whereClause);

    // 执行 DELETE 查询
    void executeDelete(const std::string& tableName, const std::string& whereClause);
};

#endif // QUERY_EXECUTOR_H
