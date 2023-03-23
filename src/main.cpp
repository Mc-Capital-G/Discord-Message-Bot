#include <iostream>
#include <fstream>
#include <random>
#include <dataType.h>
#include <dpp.h>

using namespace std;

int main() {

    uint64_t intents = dpp::i_default_intents | dpp::i_message_content;

    dpp::cluster bot("NjE1MjEwMTQwMDA5ODg5ODQw.GINdAm.jfCL4j9jRpVcfqsWa5GNsbt7gQrD1UFFcBCgPA", intents);

    bot.on_ready([&bot](const dpp::ready_t & event) {

        std::cout << "Logged in as " << bot.me.username << "." << endl; 

    });

    bot.on_message_create([&bot](const dpp::message_create_t & event){

        if(event.msg.content == "!msg") {
            bot.message_create(dpp::message(event.msg.channel_id, generateMessage()));
            cout << "I can read and interpret the message!" << endl;
        }
        //bot.message_create(dpp::message(event.msg.channel_id, generateMessage()));
        cout << event.msg.content << endl;
        cout << "I can see the message!" << endl;
    });

    bot.start(false);

    return 0;
}