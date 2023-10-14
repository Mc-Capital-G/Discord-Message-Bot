/**
 * messageCreator.cpp:
 * Definitions of the members of the messageCreator controller class
 * 
 * @author Declan McGrellis
*/
#include "messageCreator.h"

#define CACHED_MESSAGE_LIMIT 100

/**
 * Generate a random message from the given datatypes by picking a random template and replacing the 
 * "blanks" in the template with other data types.
 * 
 * @return the generated random message
*/
std::string messageCreator::generateMessage() {

    std::vector<dataType*> types;
    
    // templates.txt MUST be the file for the first member of the types vector, 
    // otherwise messages will not be generated properly

    types.emplace_back(new dataType("templates.txt", "{STATEMENT}"));
    types.emplace_back(new dataType("nouns.txt", "{NOUN}"));
    types.emplace_back(new dataType("verbs.txt", "{VERB}"));
    types.emplace_back(new dataType("adjectives.txt", "{ADJ}"));
    types.emplace_back(new dataType("gifs.txt", "{GIF}"));

    // generate a template for the message from the first dataType in the types vector

    std::string output = types[0]->getRandomEntry();
    
    // for each dataType object, find any placeholder elements and 
    // replace it with a generated output from the dataType

    for(int i = 0; i < types.size(); i++) {

        while(output.find(types[i]->getPlaceHolder()) != std::string::npos) {
        
            int j = output.find(types[i]->getPlaceHolder());
            output.erase(j, types[i]->getPlaceHolderSize());
            output.insert(j, types[i]->getRandomEntry());

        }

    }

    for(int i = 0; i < types.size(); i++) delete types[i];

    return output;
}

/**
 * Open the bot's message cache
*/
void messageCreator::openCache() {
    if(!cache.is_open()) {
        std::cout << "Opening cache..." << std::endl;
        cache.open("data/cache.txt");
        if (cache.is_open()) {
            std::cout << "Cache opened successfully" << std::endl;
        }
        else { std::cout << "Cache could not be opened!" << std::endl;}
        
    }
}

/**
 * Check to see if the current message has already been generated recently by comparing it to the cache
 * 
 * @return if the current generated message is in the cache or not
*/
bool messageCreator::checkCache() {
    openCache();

    int j = numberOfLines();

    cache.clear();
    cache.seekg(0, std::ios::beg);
    
    for(int i = 0; i < j; i++) {
        std::string cachedMessage;
        getline(cache, cachedMessage);
        if(message == cachedMessage) {
            std::cout << "Generated message is in cache, generating new message..." << std::endl;
            return true;
        }
    }

    return false;
}

/**
 * Generate random messages until a new valid* message has been generated, and update the cache with the new message
 * Valid means not being in the cache
 * If the generated message calls to repeat the users message, 
 * remove mentions of the bot from the string to not have them in the output
 * 
 * @return the valid message
*/
std::string messageCreator::getMessage(std::string usrMessage) {
    openCache();

    bool addToCache = true;
    
    do { message = generateMessage(); } while (checkCache());

    // if the bot rolls a {REPEAT}, we are going to repeat the users message
    if(message.find("{REPEAT}") != std::string::npos) {

        addToCache = false;

        while(message.find("{REPEAT}") != std::string::npos) {
            
            // create a new string to manipulate the input user message to not fuck with the given value
            std::string editUsrMsg = usrMessage;

            // remove the @PunkinBot from the message so the bot does not @ himself and loop for eternity
            // only replace the @PunkinBot with ... if it is the only thing that is non-whitespace
            while(editUsrMsg.find("<@615210140009889840>") != std::string::npos) {
                int x = editUsrMsg.find("<@615210140009889840>");
                editUsrMsg.erase(x, 21);
                if(editUsrMsg.find_first_not_of(" ") == std::string::npos) editUsrMsg.insert(x, "...");
            }

            int i = message.find("{REPEAT}");
            message.erase(i, 8);
            message.insert(i, editUsrMsg);

            
            for(int j = i; j < i + editUsrMsg.size(); j++) {
                if(j % 2 == 0) message[j] = std::toupper(message[j]);
                else message[j] = std::tolower(message[j]);
            }
            
        }

    }

    cache.clear();
    if(addToCache) cache << message << std::endl;

    if(numberOfLines() > CACHED_MESSAGE_LIMIT) {
        int j = numberOfLines();

        cache.clear();
        cache.seekg(0, std::ios::beg); //numberOfLines() edits file positioning, these reset it

        std::ofstream ofs;
        ofs.open("data/tempCache.txt");

        std::string cachedMessage;
        getline(cache, cachedMessage);

        for(int i = 0; i < j - 1; i++) {
            
            getline(cache, cachedMessage);
            ofs << cachedMessage + '\n';

        }

        ofs.close();
        cache.close();

        remove("data/cache.txt");
        rename("data/tempCache.txt", "data/cache.txt");
        
    }

    return message;
}

/**
 * Get the number of lines in the cache
*/
int messageCreator::numberOfLines() {
    openCache();

    cache.clear();
    cache.seekg(0, std::ios::beg);
    cache.unsetf(std::ios_base::skipws);
    
    return count(std::istream_iterator<char>(cache), std::istream_iterator<char>(), '\n');
}

/**
 * Open the cache when the controller is initialized
*/
messageCreator::messageCreator() {
    openCache();
}

/**
 * Close the cache when the controller is destroyed
*/
messageCreator::~messageCreator() {
    if(cache.is_open()) cache.close();
}