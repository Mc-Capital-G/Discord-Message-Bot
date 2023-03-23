#include <iostream>
#include <fstream>
#include <random>
#include <dataType.h>
#include <dpp.h>

using namespace std;

int main() {

    ifstream tokenFile;
    tokenFile.open("../data/token.txt");
  
    string token;
    getline(tokenFile, token);

    tokenFile.close();

    uint64_t intents = dpp::i_default_intents | dpp::i_message_content;

    dpp::cluster bot(token, intents);

    bot.on_ready([&bot](const dpp::ready_t & event) {

        std::cout << "Logged in as " << bot.me.username << "." << endl; 

    });

    int msgCount = 0;
    random_device rd;
    uniform_int_distribution<int> dist(1, 100);

    int randomMessageNum = dist(rd);

    bot.on_message_create([&bot, &msgCount, &randomMessageNum](const dpp::message_create_t & event){

        if(msgCount == randomMessageNum) {
            bot.message_create(dpp::message(event.msg.channel_id, generateMessage()));
            msgCount = 0;
        }   
        if(event.msg.content.find("<@615210140009889840>") != string::npos)  {
            bot.message_create(dpp::message(event.msg.channel_id, generateMessage()));
            
        }
        
        cout << event.msg.content << endl;
        msgCount++;
    });

    bot.start(false);

    return 0;
}