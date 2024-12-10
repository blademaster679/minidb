#ifndef OUTPUT_FORMATTER_H
#define OUTPUT_FORMATTER_H

#include <vector>
#include <string>
#include <fstream>

class OutputFormatter {
public:
    // 静态方法，格式化并输出数据为 CSV 格式
    static void formatOutputToCSV(const std::vector<std::vector<std::string>>& result, std::ofstream& outFile, bool isFirstWrite);
};

#endif
