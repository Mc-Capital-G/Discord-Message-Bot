#pragma once
#include <fstream>
#include <random>

using namespace std;

class dataType {
    public:
        string getRandomEntry();
        dataType(string file);
        ~dataType();
    private:
        ifstream file;
        string filePath;
        int numberOfLines;
        string currentLine;

};