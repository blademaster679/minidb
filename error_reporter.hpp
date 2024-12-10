#ifndef ERROR_REPORTER_HPP
#define ERROR_REPORTER_HPP
#include <iostream>
#include <stdexcept>
#include <string>

class ErrorReporter{
public:
    static void reportError(const std::string& error_message, int line_number);
};
#endif