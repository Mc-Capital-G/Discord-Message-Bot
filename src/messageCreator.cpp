/**
 * messageCreator.cpp:
 * Definitions of the members of the messageCreator controller class
 * 
 * @author Declan McGrellis
*/
#include <messageCreator.h>

#define CACHED_MESSAGE_LIMIT 100

/**
 * Generate a random message from the given datatypes by picking a random template and replacing the 
 * "blanks" in the template with other data types.
 * 
 * @return the generated random message
*/
std::string messageCreator::generateMessage() {

    dataType templates("templates.txt");
    dataType noun("nouns.txt");
    dataType verb("verbs.txt");
    dataType adjective("adjectives.txt");
    
    std::string output;

    output = templates.getRandomEntry();
    
    while (output.find("{VERB}")!= std::string::npos) {
        int i = output.find("{VERB}");
        output.erase(i, 6);
        output.insert(i, verb.getRandomEntry());

    }

     while (output.find("{NOUN}")!= std::string::npos) {
        int i = output.find("{NOUN}");
        output.erase(i, 6);
        output.insert(i, noun.getRandomEntry());

    }
    while (output.find("{ADJ}")!= std::string::npos) {
        int i = output.find("{ADJ}");
        output.erase(i, 5);
        output.insert(i, adjective.getRandomEntry());

    }
    while(output.find("{STATEMENT}") != std::string::npos) {
        int i = output.find("{STATEMENT}");
        output.erase(i, 11);
        output.insert(i, generateMessage());
    }

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
 * 
 * @return the valid message
*/
std::string messageCreator::getMessage() {
    openCache();
    
    do { message = generateMessage(); } while (checkCache());

    cache.clear();
    cache << message << std::endl;

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