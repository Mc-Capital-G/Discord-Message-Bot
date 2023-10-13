/**
 * messageCreator.h:
 * 
 * Declaration of the messageCreator class
 * 
 * The messageCreator class is a class designed to be the controller for the program, in which it handles most
 * of what the program will be doing with the associated class, dataType. The controller is responsible for 
 * putting together the messages the bot will spit out and is the "brain" of our bot.
 * 
 * @author Declan McGrellis
*/

#pragma once
#include "dataType.h"
#include <cstdio>
#include <iostream>
#include <string>

class messageCreator {

    public:
        std::string getMessage(std::string usrMessage);
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