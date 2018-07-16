//
//  Penguin.hpp
//  Copyright © 2018 Joanna Lankester. All rights reserved.
//

#ifndef Penguin_hpp
#define Penguin_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Penguin {
private:
    string name;
    int birdIdNumber;
    
public:
    Penguin(string name = "generic_penguin", int birdIdNumber = -1);
    string toString() const;
    
    string getName() const;
    int getBirdIdNumber() const;
    bool setName(string name);
    bool setBirdIdNumber(int idNumber);
    bool operator==(const Penguin &other) const;
    bool operator!=(const Penguin &other) const;
    class InvalidSeaBirdException{};

    
private:
    static int sortKey;
};

class PenguinDataReader {
private:
    vector<Penguin> penguins;
    int numPenguins;
    bool fileOpenError;
    string penguinFile;
    Penguin readOneLine(string line);
public:
    PenguinDataReader(string fileName);
    Penguin & operator[](int k);
    string getFileName() { return penguinFile; }
    bool readError() { return fileOpenError; }
    int getNumPenguins() { return numPenguins; }
    class PenguinIndexNotFoundException{};
};



#endif /* Penguin_hpp */
