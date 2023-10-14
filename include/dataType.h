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
        std::string getPlaceHolder();
        int getPlaceHolderSize();
        dataType(std::string file, std::string holder);
        ~dataType();
    private:
        std::ifstream file;
        std::string filePath;
        std::string placeHolder;
        int numberOfLines;
        std::string currentLine;

};