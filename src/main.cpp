#include <iostream>
#include <fstream>
#include <random>
#include <dataType.h>
#include <dpp.h>
#include <messageCreator.h>

int main() {

    std::ifstream tokenFile;
    tokenFile.open("data/token.txt");
  
    std::string token;
    getline(tokenFile, token);

    tokenFile.close();

    uint64_t intents = dpp::i_default_intents | dpp::i_message_content;

    dpp::cluster bot(token, intents);

    messageCreator mC;

    bot.on_ready([&bot](const dpp::ready_t & event) {

        std::cout << "Logged in as " << bot.me.username << "." << std::endl; 

    });

    int msgCount = 0;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 35);

    int randomMessageNum = dist(rd);

    bot.on_message_create([&bot, &msgCount, &randomMessageNum, &dist, &mC](const dpp::message_create_t & event){

        if(msgCount == randomMessageNum) {
            bot.message_create(dpp::message(event.msg.channel_id, mC.getMessage()));
            msgCount = 0;
            std::random_device rd1;
            randomMessageNum = dist(rd1);
        }   
        if(event.msg.content.find("<@615210140009889840>") != std::string::npos)  {
            bot.message_create(dpp::message(event.msg.channel_id, mC.getMessage()));
        }
        
        std::cout << event.msg.content << std::endl;
        msgCount++;
    });

    bot.start(false);

    return 0;
}