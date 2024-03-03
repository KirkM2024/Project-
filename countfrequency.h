#ifndef COUNT_FREQUENCY_H
#define COUNT_FREQUENCY_H
#include <string>
#include <map>
#include <fstream>

using namespace std;

class CountFrequency
{

private:
    multimap<string, pair<int, string>> readFile(const string& filename);
    multimap<string, pair<int, string>> itemMap;
    multimap<string, pair<int, string>> newMap;

public:
    // Initialize functions
    CountFrequency();
    void mainMenu();
    void countDuplicates();
    void transferMap();
    void printMenu();
    void printList();
    void printListH();
    void createFile();

};

#endif
