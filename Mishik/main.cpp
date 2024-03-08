#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    
    std::ifstream fileExists("abc.txt");
    if (!fileExists.good()) {
        std::cerr << "Error!" << std::endl;
        return 1;
    }

    const std::string Path = "abc.txt";

    std::ofstream inputFile(Path, std::ios::out | std::ios::trunc);
    
    if (inputFile.is_open()) {
        std::cout << "opened " << Path << "\n";
    }

    std::ostringstream fileContentStream;
    fileContentStream << inputFile.rdbuf();
    std::string fileContent = fileContentStream.str();

    inputFile.close();

    std::ofstream outputFile(Path);
    for (int i = 0; i < 5; i++) {
        // adding content
        std::string content = "??????????????????????????????????????????????????";
        outputFile << content << "\n"; 
        
        // removeing
        outputFile.seekp(0, std::ios_base::end);
        outputFile.seekp(-(content.length() + 1), std::ios_base::cur);
        outputFile << std::string(content.length(), ' ');
        outputFile.close();
        std::cout << "adding and removing" << "\n";
    }
    // Delete the file after the loop
    if (std::remove("abc.txt") != 0) {
        std::cerr << "Error " << std::endl;
        return 1;
    }

    return 0;
};

