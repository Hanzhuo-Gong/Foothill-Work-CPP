// CS2CLab6.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <ctime>
#include "Penguin.hpp"
using namespace std;

//-------------------Global Prototype-----------------------------
int Hash(int key);
int Hash(const string & key);
int Hash(const Penguin & key);
//int getKey(const Penguin &p);
string getKey(const Penguin &p);

#include "FHhashQPwFind.h"
//---------------------Global Definition-----------------------------
int Hash(const string & key)
{
   unsigned int k, retVal = 0;

   for (k = 0; k < key.length(); k++)
      retVal = 37 * retVal + key[k];

   return retVal;
}

int Hash(int key)
{
   return key;
}

// we have to define how to get the number to hash for a Penguin object
int Hash(const Penguin & p)
{
   // TODO: fill this in to get a number for string or int.
   // They will call the Hash functions from above.
   // (write both, but comment out one at a time)

   //For ID
   //return getKey(p);

   //For Name
   unsigned int i, retVal = 0;
   string penguinName = p.getName();

   for (i = 0; i < penguinName.length(); i++)
      retVal = 37 * retVal + penguinName[i];

   return retVal;
}


string getKey(const Penguin &p) {
    return p.getName();
}

//int getKey(const Penguin &p) {
//   return p.getBirdIdNumber();
//}

//--------------------------Main-----------------------
int main()
{
   srand((unsigned)time(NULL));
   //FHhashQPwFind<Penguin, int> hashTable; // for ID equality
   FHhashQPwFind<Penguin, string> hashTable; // for any string equality

   const int NUM_RANDOM_INDICES = 25;
   int randomIndices[NUM_RANDOM_INDICES];
   int k, arraySize, randIndex;
   float randFrac;
   Penguin onePenguin;

   PenguinDataReader penguinInput("penguinData.txt");
   if (penguinInput.readError()) {
      cout << "couldn't open " << penguinInput.getFileName() 
         << " for input.\n";
      exit(1);
   }

   cout << penguinInput.getFileName() << endl;
   cout << penguinInput.getNumPenguins() << endl;

   arraySize = penguinInput.getNumPenguins();
   cout << "arraySize is: " << arraySize << endl;

   //Insert all the penguin to the hash table
   for (int i = 0; i < arraySize; i++)
      hashTable.insert(penguinInput[i]);
   
   cout << "Size of this hash table is " << hashTable.size() << endl;

   //Generate random number
   for (k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      randFrac = rand() / (float)RAND_MAX;
      randIndex = randFrac * arraySize;
      randomIndices[k] = randIndex;
      //cout << randIndex << " ";
   }

   //Display the penguin
   cout << "\n-----------------Display the penguin------------" << endl;
   for (int i = 0; i < NUM_RANDOM_INDICES; i++) {
      cout << "Penguin " << i << " properties:" << endl;
      cout << "Name: " << penguinInput[randomIndices[i]].getName() << endl;
      cout << "ID: " << penguinInput[randomIndices[i]].getBirdIdNumber() 
         << endl;
      cout << endl;
   }
   
   // attempt to find on the selected key
   cout << "The same random penguins from the hash table " << endl;
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
         //for ID
         //onePenguin = hashTable.find(penguinInput[randomIndices[k]].getBirdIdNumber());
         //for name
         onePenguin = hashTable.find(penguinInput[randomIndices[k]].getName());
         cout << "PENGUIN FOUND: " << onePenguin.getName() << " "
            << onePenguin.getBirdIdNumber();
      }
      catch (...)
      {
         cout << "this penguin is not in the hash table, probably lives in a different colony ";
      }
      cout << endl;
   }

   //test known failures exceptions:
   cout << "\n--------------Test for failure of find---------------" << endl;
   try
   {
      //onePenguin = hashTable.find(-3);
      onePenguin = hashTable.find( "albatross" );
      cout << "Penguin Found! " << onePenguin.getName() << endl;
   }
   catch (...)
   {
      cout << "That is not a penguin.  " << endl;
   }

   try
   {
      //onePenguin = hashTable.find(4001);
      onePenguin = hashTable.find( "penguin who know Java" );
      cout << "Penguin Found! " << onePenguin.getName() << endl;
   }
   catch (...)
   {
      cout << "That is not a penguin.  " << endl;
   }

   try
   {
      //onePenguin = hashTable.find(300);
      onePenguin = hashTable.find( "CEOpenguin" );
      cout << "Penguin Found! " << onePenguin.getName() << endl;
   }
   catch (...)
   {
      cout << "That is not a penguin.  " << endl;
   }
   return 0;
}

