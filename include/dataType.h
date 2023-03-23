#include <fstream>
#include <random>

using namespace std;

string generateMessage();

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