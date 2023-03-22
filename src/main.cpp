#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ofstream nounList;
    nounList.open("../data/nouns.txt");
    nounList << "write test";
    nounList.close();

    return 0;
}