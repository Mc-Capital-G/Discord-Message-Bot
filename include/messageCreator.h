#pragma once
#include <dataType.h>
#include <cstdio>
#include <iostream>

class messageCreator {

    public:
        std::string getMessage();
        messageCreator();
        ~messageCreator();
    private:
        bool checkCache();
        std::fstream cache;
        std::string generateMessage();
        std::string message;
        int numberOfLines();
        void openCache();


};