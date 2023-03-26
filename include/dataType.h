#pragma once
#include <fstream>
#include <random>

class dataType {
    public:
        std::string getRandomEntry();
        dataType(std::string file);
        ~dataType();
    private:
        std::ifstream file;
        std::string filePath;
        int numberOfLines;
        std::string currentLine;

};