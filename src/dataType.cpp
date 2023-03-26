#include <dataType.h>

dataType::dataType(std::string file) {
    filePath = "data/" + file;
}

std::string dataType::getRandomEntry() {

    file.open(filePath);
    file.unsetf(std::ios_base::skipws);
    numberOfLines = count(std::istream_iterator<char>(file), std::istream_iterator<char>(), '\n');
    file.clear();
    file.seekg(0, std::ios::beg);
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, numberOfLines + 1);

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