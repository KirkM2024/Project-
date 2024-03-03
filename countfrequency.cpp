#include "countfrequency.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <limits>
using namespace std;

// Constructor implementation
CountFrequency::CountFrequency()
{
}

// Prints out the user menu.
void CountFrequency::printMenu()
{
    cout << "*************************************************************" << endl;
    cout << "1) Search For an Item." << endl;
    cout << "2) Print out a List of Numbers With Frequency in Integers." << endl;
    cout << "3) Print out a List of Numbers With Frequency in Histogram." << endl;
    cout << "4) Exit." << endl;
    cout << "*************************************************************" << endl;
}

void CountFrequency::mainMenu()
{
    // Flag for menu input.
    bool finished = false;
    // Variable to store user input.
    int menuInput;
    // Used to return a specific key.
    string item;

    // Call function to read file and store it into a map.
    readFile("items.txt");

    // Calls function to count the duplicate keys in the map.
    countDuplicates();

    // Calls funtion to copy over the map from file to a new map to store.
    transferMap();

    do
    {
        // Calls function to display menu options.
        printMenu();
        cin >> menuInput;

        if (menuInput == 1)
        {
            cout << "Type in the Item you want to look for:\n";
            cin >> item;

            // Creates element to explore map.
            auto element = newMap.find(item);

            // Checks if Item is in the map.
            if (element != newMap.end())
            {
                cout << "Your Item " << element->first << " Times Searched " << element->second.first << "\n"
                    << endl;
            }
            else
            {
                cout << "\n Your Item " << item << " Was Not Found\n";
            }
        }
        else if (menuInput == 2)
        {
            // Calls function to print the list.
            printList();
        }
        else if (menuInput == 3)
        {
            // Calls function to print list as a Histogram.
            printListH();
        }
        else if (menuInput == 4)
        {
            // Create a copy of the List in a dat file before exit.
            createFile();
            cout << "Exiting Program\n";
            break;
        }
        else
        {
            // Resets the flag.
            finished = false;
            cout << "Please enter one of the displayed options.\n";

            // Clears any error flags.
            cin.clear();

            // Discard invalid input.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!finished);
}

multimap<string, pair<int, string>> CountFrequency::readFile(const string& filename)
{
    ifstream myFile(filename);

    // Checks if the file is open.
    if (myFile.is_open())
    {
        // Variable to keep track of key in map.
        string key;

        // Placement variables to help countDuplicates() function.
        string freq2 = "*";
        int freq1 = 0;

        // Get each line from the file and stores it in readLine to be read.
        while (myFile >> key)
        {
            itemMap.insert(make_pair(key, make_pair(freq1, freq2)));
        }

        // Once it is the end of file close it.
    }
    else if (myFile.eof())
    {
        myFile.close();

        // If the file is not found or cannot be opened display error.
    }
    else
    {
        // Display error.
        cerr << "Cannot open file." << endl;
    }
    return itemMap;
}

void CountFrequency::countDuplicates()
{
    // Create map to count number of duplicate keys in integers.
    map<string, int> keyCounts;

    // Create second map to count number of duplicate keys in asterisks.
    map<string, int> keyCounts2;

    // For each loop to itterate through the map.
    for (const auto& entry : itemMap)
    {
        // Creates a key on the first key.
        const string key = entry.first;
        // Keeps track of the count for new map of integers.
        keyCounts[key]++;

        // Keeps track of the count for the 2nd new map of *.
        keyCounts2[key]++;

        // If the key is not zero continue counting.
        if (keyCounts[key] > 1)
        {
            // i stores the * for the 2nd map.
            auto i = itemMap.find(key);
            itemMap.find(key)->second.first = keyCounts[key];
            // If it isnot the end of file or empty add * to the 2nd key.
            if (i != itemMap.end() && !i->second.second.empty())
            {
                i->second.second += "*";
            }
        }
    }
}

// Function to transfer contents from the map made from the file to a new one without duplicates.
void CountFrequency::transferMap()
{
    // Copy over map.
    newMap = itemMap;
    auto i = newMap.begin();
    while (i != newMap.end())
    {
        // Deletes all but the head node to clear duplicates.
        if (i->second.first == 0)
        {
            i = newMap.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

// Function to print numeric list.
void CountFrequency::printList()
{
    cout << "Here is your List of Items." << endl;

    // Iterate through the map and print the Key and the first value.
    for (const auto& pair : newMap)
    {
        cout << "Item: " << pair.first << ", Times Searched: (" << pair.second.first << ")" << endl;
    }
    cout << "\n";
}

// Function to print out Histogram list.
void CountFrequency::printListH()
{
    cout << "Here is your Histogram of Items." << endl;

    // Iterate through the map and print the Key and the second value.
    for (const auto& pair : newMap)
    {
        cout << "Item: " << pair.first << ", Times Searched: (" << pair.second.second << ")" << endl;
    }
    cout << "\n";
}

// Creates a new file from the new map copy.
void CountFrequency::createFile()
{
    ofstream outputFile("items.dat");

    if (outputFile.is_open())
    {
        for (const auto& pair : newMap)
        {
            outputFile << pair.first << " " << pair.second.first << " " << pair.second.second << endl;
        }
    }
    else
    {
        cout << "Failed to create the file." << endl;
    }
}
