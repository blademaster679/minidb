# MiniDB: A Simple SQL Database

## 项目简介

MiniDB 是一个简单的 SQL 数据库系统，支持基本的 SQL 查询操作，如 `CREATE DATABASE`、`CREATE TABLE`、`INSERT`、`SELECT` 和 `WHERE` 子句。该项目的目标是实现一个简单的数据库引擎，允许用户通过 SQL 命令操作数据库中的数据。MiniDB 解析和执行 SQL 查询，并将查询结果以 CSV 格式输出。

## 项目结构

- **sql_parser**: 解析 SQL 查询语句，将其转化为程序内部的数据结构（如 `SelectCommand`、`InsertCommand` 等）。
- **database_manager**: 管理数据库的创建、使用和删除，并处理与磁盘上的数据文件的交互。
- **query_executor**: 执行 SQL 查询，处理 `SELECT` 和 `WHERE` 子句，并将结果返回给用户。
- **output_formatter**: 格式化查询结果并将其输出为 CSV 格式文件。
- **error_reporter**: 负责错误报告和异常处理。

## 项目原理

### 1. **SQL 解析**

用户输入的 SQL 语句通过 **`sql_parser`** 模块进行解析。解析的过程将 SQL 查询语句转化为内部数据结构（如 `SelectCommand`、`InsertCommand`），其中包含查询所需的所有信息（如列名、表名、条件等）。其中的 **`WHERE`** 子句也会被解析成独立的条件对象，以便后续用于过滤数据。

**`parseSelect`** 方法解析 `SELECT` 查询，并通过 `whereClause` 提取条件。如果查询包含 `WHERE` 子句，它会将条件表达式解析为 `Condition` 对象，然后传递给 **`query_executor`** 模块，用于数据的筛选。

### 2. **数据存储与管理**

**`database_manager`** 模块负责管理数据库和数据表。用户通过 `CREATE DATABASE` 和 `USE DATABASE` 命令来创建和切换数据库。数据库的表数据存储在文件系统中，每个表有一个对应的文件，数据以简单的文本格式存储。

- **创建数据库**：数据库目录和文件会在文件系统中创建。
- **使用数据库**：切换当前正在使用的数据库。
- **创建表**：定义表的列和数据类型。
- **插入数据**：通过 `INSERT` 命令将数据添加到表中。

### 3. **查询执行**

**`query_executor`** 模块负责执行 SQL 查询，支持 `SELECT` 查询和 `WHERE` 条件的筛选。根据用户的查询条件，模块会从指定的表中读取数据，并应用 **`WHERE`** 子句过滤数据。

- **SELECT 查询**：读取表中的所有数据，并根据 **`WHERE`** 子句（如果有）筛选数据。
- **WHERE 子句解析**：根据条件（如 `GPA > 3.0` 或 `Name = 'Taylor Swift'`）过滤数据。每个条件会被解析为 `Condition` 对象，并通过比较表的相应列值来筛选数据。

### 4. **输出结果**

查询结果会通过 **`output_formatter`** 模块格式化为 CSV 文件输出。结果按列名和数据行格式化，并以逗号分隔的形式保存到文件中。

### 5. **错误报告**

**`error_reporter`** 模块负责捕获运行时错误并提供友好的错误消息，帮助用户调试和解决问题。例如，若用户尝试查询一个不存在的数据库或表，系统会抛出适当的错误，并输出详细的错误信息。


