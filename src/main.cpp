#include <iostream>
#include <fstream>
#include <random>
#include <string.h>

using namespace std;

class dataType {
    public:
        string getRandomEntry();
        dataType(string file);
        ~dataType();
    private:
        ifstream file;
        string filePath;
        int numberOfLines;
        string currentLine;

};

int main() {

    dataType templates("templates.txt");
    dataType noun("nouns.txt");
    dataType adjective("adjective.txt");
    
    string output;

    output = templates.getRandomEntry();

    cout << noun.getRandomEntry() << endl;

    return 0;
}

dataType::dataType(string file) {
    filePath = "../data/" + file;
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