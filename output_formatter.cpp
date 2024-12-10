#include "output_formatter.hpp"
#include <iostream>
#include <fstream>

// 格式化并输出查询结果为 CSV 格式
void OutputFormatter::formatOutputToCSV(const std::vector<std::vector<std::string>>& result, const std::string& fileName) {
    // 打开文件输出流
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error: Failed to open file " << fileName << std::endl;
        return;
    }

    // 遍历查询结果，将每行数据输出为 CSV 格式
    for (size_t row = 0; row < result.size(); ++row) {
        bool firstColumn = true;
        for (size_t col = 0; col < result[row].size(); ++col) {
            // 在每一列之间添加逗号，避免在行首多加逗号
            if (!firstColumn) {
                outFile << ",";
            }
            outFile << result[row][col];
            firstColumn = false;
        }
        outFile << "\n";  // 每行数据后添加换行符
    }

    outFile.close();  // 关闭文件
    std::cout << "Data successfully written to " << fileName << std::endl;
}
