#pragma once
#include <dataType.h>
#include <cstdio>
#include <iostream>

class messageCreator {

    public:
        string getMessage();
        messageCreator();
        ~messageCreator();
    private:
        bool checkCache();
        fstream cache;
        string generateMessage();
        string message;
        int numberOfLines();
        void openCache();


};