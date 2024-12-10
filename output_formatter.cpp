#include "output_formatter.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>  

void OutputFormatter::formatOutputToCSV(const std::vector<std::vector<std::string>>& result, std::ofstream& outFile, bool isFirstWrite) {
    if (result.empty()) {
        return; // 如果结果为空，直接返回
    }
    std::stringstream ss = std::stringstream(result[0][0]); 
    size_t startIndex = 0; 
    ss >> startIndex;
    std::cout << startIndex << std::endl;
    for(size_t i = 1; i <= startIndex; i++){
        std::string cell = result[i][0];
        size_t pos = cell.find_last_not_of(' ');
        while (pos == cell.size() - 1) {
            cell = cell.substr(0, pos);
            pos = cell.find_last_not_of(' ');
        }
        if (pos != std::string::npos) {
            cell = cell.substr(0, pos + 1);
        }
        outFile << cell;
        if (i != startIndex) {
            outFile << ",";
        }
    }
    outFile << "\n";
    for (size_t i = startIndex + 1; i < result.size(); ++i) {
        const auto& row = result[i];
        for (size_t j = 0; j < row.size(); ++j) {
            outFile << row[j];
            if (j != row.size() - 1) {
                outFile << ",";
            }
        }
        outFile << "\n";
    }

    
    outFile << "---" << "\n";
}



// // 格式化并输出查询结果为 CSV 格式
// #include <fstream>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <filesystem>  

// void OutputFormatter::formatOutputToCSV(const std::vector<std::vector<std::string>>& result, const std::string& filePath) {
//     // 确保文件路径有效
//     std::filesystem::path outputPath(filePath);
//     if (!std::filesystem::exists(outputPath.parent_path())) {
//         std::cerr << "Error: The directory does not exist: " << outputPath.parent_path() << std::endl;
//         return;
//     }

//     // 打开文件输出流
//     std::ofstream outFile(filePath,std::ios::app);
//     if (!outFile) {
//         std::cerr << "Error: Failed to open file " << filePath << std::endl;
//         return;
//     }

//     // 遍历查询结果，将每行数据输出为 CSV 格式
//     for (size_t row = 0; row < result.size(); ++row) {
//         bool firstColumn = true;
//         for (size_t col = 0; col < result[row].size(); ++col) {
//             // 在每一列之间添加逗号，避免在行首多加逗号
//             if (!firstColumn) {
//                 outFile << ",";
//             }
//             outFile << result[row][col];
//             firstColumn = false;
//         }
//         outFile << "\n";  // 每行数据后添加换行符
//     }

//     outFile.close();  // 关闭文件
//     std::cout << "Data successfully written to " << filePath << std::endl;
// }

// void OutputFormatter::formatOutputToCSV(const std::vector<std::vector<std::string>>& result, const std::string& fileName) {
//     // 打开文件输出流
//     std::ofstream outFile(fileName);
//     if (!outFile) {
//         std::cerr << "Error: Failed to open file " << fileName << std::endl;
//         return;
//     }

//     // 遍历查询结果，将每行数据输出为 CSV 格式
//     for (size_t row = 0; row < result.size(); ++row) {
//         bool firstColumn = true;
//         for (size_t col = 0; col < result[row].size(); ++col) {
//             // 在每一列之间添加逗号，避免在行首多加逗号
//             if (!firstColumn) {
//                 outFile << ",";
//                 std::cout << result[row][col] << " ";
//             }
//             outFile << result[row][col];
//             firstColumn = false;
//         }
//         outFile << "\n";  // 每行数据后添加换行符
//     }

//     outFile.close();  // 关闭文件
//     std::cout << "Data successfully written to " << fileName << std::endl;
// }
