#include <dataType.h>

using namespace std;

string generateMessage() {

    dataType templates("templates.txt");
    dataType noun("nouns.txt");
    dataType verb("verbs.txt");
    dataType adjective("adjectives.txt");
    
    string output;

    output = templates.getRandomEntry();
    
    while (output.find("{VERB}")!= string::npos) {
        int i = output.find("{VERB}");
        output.erase(i, 6);
        output.insert(i, verb.getRandomEntry());

    }

     while (output.find("{NOUN}")!= string::npos) {
        int i = output.find("{NOUN}");
        output.erase(i, 6);
        output.insert(i, noun.getRandomEntry());

    }
    while (output.find("{ADJ}")!= string::npos) {
        int i = output.find("{ADJ}");
        output.erase(i, 5);
        output.insert(i, adjective.getRandomEntry());

    }
    while(output.find("{STATEMENT}") != string::npos) {
        int i = output.find("{STATEMENT}");
        output.erase(i, 11);
        output.insert(i, generateMessage());
    }

    return output;
}

dataType::dataType(string file) {
    filePath = "data/" + file;
}

string dataType::getRandomEntry() {

    file.open(filePath);
    file.unsetf(ios_base::skipws);
    numberOfLines = count(istream_iterator<char>(file), istream_iterator<char>(), '\n');
    file.clear();
    file.seekg(0, ios::beg);
    random_device rd;
    uniform_int_distribution<int> dist(1, numberOfLines + 1);

    int randomLineNumber = dist(rd);

    for(int i = 0; i < randomLineNumber; i++) {
        getline(file, currentLine);
    }

    file.close();
    return currentLine;
}

dataType::~dataType() {
    if(file.is_open()) {file.close();}
}