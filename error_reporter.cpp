#include "error_reporter.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

void ErrorReporter::reportError(const std::string& error_message, int line_number){
    std::cerr << "Error at line " << line_number << ": " << error_message << std::endl;
    throw std::runtime_error("Error at line " + std::to_string(line_number) + ": " + error_message);
}