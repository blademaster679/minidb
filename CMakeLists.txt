cmake_minimum_required(VERSION 3.10)

# Set the project name
project(minidb)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    database_manager.cpp
    error_reporter.cpp
    output_formatter.cpp
    sql_parser.cpp
    query_executor.cpp
    )

include_directories(${CMAKE_SOURCE_DIR})
add_executable(minidb ${SOURCES})