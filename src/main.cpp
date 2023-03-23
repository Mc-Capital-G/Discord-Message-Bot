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

    uint64_t intents = dpp::i_default_intents | dpp::i_message_content;

    dpp::cluster bot(token, intents);

    bot.on_ready([&bot](const dpp::ready_t & event) {

        std::cout << "Logged in as " << bot.me.username << "." << endl; 

    });

    bot.on_message_create([&bot](const dpp::message_create_t & event){

        if(event.msg.content == "!msg") {
            bot.message_create(dpp::message(event.msg.channel_id, generateMessage()));
            
        }
        
        cout << event.msg.content << endl;

    });

    bot.start(false);

    return 0;
}