/**
 * dataType.h:
 * 
 * Declaration of the dataType class
 * 
 * The dataType class stores data related to a specific given file, and the class can get random entries from
 * the given file to give to the program
 * 
 * @author Declan McGrellis
*/

#pragma once
#include <fstream>
#include <random>
#include <string>

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