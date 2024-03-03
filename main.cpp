#include <iostream>
#include "countfrequency.h"


// Driver main function.
int main()
{
    // Creates a CountFrequency object.
    CountFrequency* itemList = new CountFrequency();

    // Calls the mainMenu() function to begin program. 
    itemList->mainMenu();

    // Delete object when done.
    delete itemList;

    return 0;
}
