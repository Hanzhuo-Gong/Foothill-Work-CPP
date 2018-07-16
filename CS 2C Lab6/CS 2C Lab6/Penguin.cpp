//
//  Penguin.cpp

#include "Penguin.hpp"

Penguin::Penguin(string name, int birdIdNumber){
    if (!setName(name))
        name = "generic_penguin";
    if (!setBirdIdNumber(birdIdNumber))
        birdIdNumber = -1;
}
string Penguin::toString() const {
    string output = "Penguin with name " + this->name;
    output += " and ID number " + to_string(birdIdNumber);
    return output;
}

string Penguin::getName() const {
    return name;
}
int Penguin::getBirdIdNumber() const {
    return birdIdNumber;
}
bool Penguin::setName(string name) {
    if (name=="")
        return false;
    this->name = name;
    return true;
}
bool Penguin::setBirdIdNumber(int idNumber) {
    if (idNumber<0)
        return false;
    birdIdNumber = idNumber;
    return true;
}

bool Penguin::operator==(const Penguin &other) const
{
    return (other.name==this->name && other.birdIdNumber==this->birdIdNumber);
}

bool Penguin::operator!=(const Penguin &other) const
{
    return !(other == *this);
}

PenguinDataReader::PenguinDataReader(string fileName) {
    string name;
    string line, entryString;
    Penguin penguin("",0);
    
    numPenguins = 0;
    fileOpenError = false;
    penguinFile = "NO FILE NAME PROVIDED";
    
    if (fileName.length() == 0)
    {
        fileOpenError = true;
        return;
    }
    penguinFile = fileName;
    // open file for reading
    ifstream infile(fileName.c_str());
    if (!infile)
    {
        fileOpenError = true;
        return;
    }
    // for each line that starts #. read and add to vector
    while ( !infile.eof() )
    {
        getline (infile, line);
        penguin = readOneLine(line);
        penguins.push_back(penguin);
        numPenguins++;
    }
    infile.close();
    
}


Penguin & PenguinDataReader::operator[](int k)
{

    if (k < 0 || k >= numPenguins)
        throw PenguinIndexNotFoundException();
    return penguins[k];
}

Penguin PenguinDataReader::readOneLine(string line) {
    // split on delimiter
    string penguinName;
    string penguinIdAsString;
    int penguinId;
    char delim = ',';
    stringstream ss(line);
    std::getline(ss,penguinName,delim);
    std::getline(ss,penguinIdAsString,delim);
    
    // convert penguin ID to integer
    penguinId = stoi(penguinIdAsString);
    
    // create and return a penguin
    Penguin thisPenguin(penguinName,penguinId);
    return thisPenguin;
}


