// Assignment 6
// Makoto Emura
// 11/23/2020
// Hash table for UPC and description

#include "twoHashTable.h"
#include <iostream>
#include <cassert>
using namespace std;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "modernize-raw-string-literal"
#pragma ide diagnostic ignored "modernize-use-auto"
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wvla-extension"
//don't change anything in the main function.
int main()
{
    int testSize = 6;
    UPCEntry *items[testSize];
    items[0] = new UPCEntry("753950001954,Doctor's Best Best Curcumin C3 Complex 1000mg Tablets - 120 Ct");
    items[1] = new UPCEntry("025800024117,Weight Watchers Smart Ones Smart Creations");
    items[2] = new UPCEntry("079927020217,\"Unique \"\"splits\"\" Split-open Pretzel Extra Dark\"");
    items[3] = new UPCEntry("1638098830,Weleda Bar Soap Rose - 3.5 Oz");
    items[4] = new UPCEntry("895172001432,Pure Life Body Lotion Coconut And Mango - 15.0 Fl Oz");
    items[5] = new UPCEntry("995172001432,Pure Life Body Lotion Coconut And Mango - 14.9 Fl Oz");

    TwoHashTable *table = new TwoHashTable("test_data.csv", 3);
    cout << "-- sample run start --" << endl;
    assert(abs(table->getStdDev() - 0.471404f) < 1e-6);
    Position pos = table->search(*items[0]);
    assert(pos.indexInTable == 0 && pos.indexInBin == 3);
    pos = table->search(*items[1]);
    assert(pos.indexInTable == -1 && pos.indexInBin == -1);
    pos = table->search(*items[2]);
    assert(pos.indexInTable == 1 && pos.indexInBin == 0);
    cout << "-- sample run pass --" << endl;

    int tableSize[3] = {100000, 1000, 100};
    for (int n = 0; n < 3; n++)
    {
        TwoHashTable *table = new TwoHashTable("grocery_upc_database.csv", tableSize[n]);
        cout << "Table size = " << tableSize[n] << ", stddev = " << table->getStdDev() << endl;
        for (int i = 0; i < testSize; i++)
        {
            Position pos = table->search(*items[i]);
            cout << "      [" << pos.indexInTable << "," << pos.indexInBin << "]" << endl;
        }
    }
    return 0;
}
#pragma clang diagnostic pop