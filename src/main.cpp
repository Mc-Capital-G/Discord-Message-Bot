/**
 * main.cpp:
 * 
 * Discord Message Bot - 
 * A very vulgar bot written to have some fun and make some wacky statements
 * 
 * @author Declan McGrellis
*/

#include <iostream>
#include <fstream>
#include <random>
#include "dataType.h"
#include <dpp.h>
#include "messageCreator.h"
#include <vector>

/**
 * Function main runs at program start
 * Turns the bot on and calls functions on events from Discord's API
 * 
 * @return The result of execution
*/
int main() {

    // get the token out of the token.txt file to give to the bot to access discords api. 
    // The program WILL crash and throw an error if the token is invalid.
    std::ifstream tokenFile("data/token.txt");
    if(!tokenFile) std::cerr << "Could not open data/token.txt!" << std::endl;
    std::string token;
    tokenFile >> token;
    tokenFile.close();

    // flags to pass to the bot api to control what the bot should and should not be able to do
    uint64_t intents = dpp::i_default_intents | dpp::i_message_content;

    // initializing the bot object
    dpp::cluster bot(token, intents);

    //initializing our messageCreator controller object
    messageCreator mC;

    // When the bot successfully connects to Discord, print to the terminal that we are logged in as the bot
    bot.on_ready([&bot](const dpp::ready_t & event) {

        std::cout << "Logged in as " << bot.me.username << "." << std::endl; 

    });

    // initialize variables for the random message counter
    // The bot will randomly speak after a random amount of messages have been sent, which is configured here
    int msgCount = 0;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 35);
    int randomMessageNum = dist(rd);

    // tracker for what channels are paused for the bot
    std::vector<dpp::snowflake> pausedChannels;
    pausedChannels.clear();

    // When a message is created in any channel the bot can see, it will run this code
    bot.on_message_create([&bot, &msgCount, &randomMessageNum, &dist, &mC, &pausedChannels](const dpp::message_create_t & event){
        
        // check to see if the channel the message was generated in was a paused channel or not
        bool pauseBot = false;
        for(int i = 0; i < pausedChannels.size(); i++) {
            if(pausedChannels[i] == event.msg.channel_id) pauseBot = true;
        }

        if(!pauseBot) {
            // create a message and reset the random message counter if the message hits the previous generated limit
            if(msgCount == randomMessageNum) {

                bot.message_create(dpp::message(event.msg.channel_id, mC.getMessage(event.msg.content)));
                msgCount = 0;
                std::random_device rd1;
                randomMessageNum = dist(rd1);

            }   

            // create a message if the bot is mentioned in any channel it can see
            if(event.msg.content.find("<@615210140009889840>") != std::string::npos)  {

                bot.message_create(dpp::message(event.msg.channel_id, mC.getMessage(event.msg.content)));

            }
            
            std::cout << event.msg.content << std::endl;
            msgCount++;
        }

        // pause the bot if the user says goodbye to it, while checking to see if the channel is already paused
        if(event.msg.content == "Goodbye <@615210140009889840>") {

            bool isInVector = false;
            for(int i = 0; i < pausedChannels.size(); i++) {
                if(pausedChannels[i] == event.msg.channel_id) isInVector = true;
            }
            if(!isInVector) {
                pausedChannels.emplace_back(event.msg.channel_id);
                bot.message_create(dpp::message(event.msg.channel_id, "See you later nerd."));
            }

        }

        // unpause the bot
        if(event.msg.content == "Wakey wakey <@615210140009889840>") {

            for(int i = 0; i < pausedChannels.size(); i++) {
                if(pausedChannels[i] == event.msg.channel_id) { 
                    pausedChannels.erase(pausedChannels.begin()+i);
                    bot.message_create(dpp::message(event.msg.channel_id, "I have returned."));
                }
            }

        }

    });

    // i don't remember what this does so don't touch it.
    bot.start(false);

    return 0;
}