#include <messageCreator.h>

#define CACHED_MESSAGE_LIMIT 100

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

int messageCreator::numberOfLines() {
    openCache();

    cache.clear();
    cache.seekg(0, std::ios::beg);
    cache.unsetf(std::ios_base::skipws);
    return count(std::istream_iterator<char>(cache), std::istream_iterator<char>(), '\n');
}

messageCreator::messageCreator() {
    openCache();
}

messageCreator::~messageCreator() {
    if(cache.is_open()) {cache.close();}
}