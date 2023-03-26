#include <dataType.h>

using namespace std;

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