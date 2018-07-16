
//CS 2C Lab 1 code
//This program will display all sublists for certain target
//Copyright © 2018 Hanzhuo Gong. All right reserved.

#include <iostream>
#include <vector>
#include "iTunes.h"
using namespace std;

//-------------------------------class Sublist prototype--------------
template<class T>
class Sublist
{
public:
   Sublist(vector<T> *orig = NULL)
      : sum(0), originalObjects(orig) { }
   Sublist<T> addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; }
   friend ostream& operator<<(ostream& str, const iTunesEntry& s);
   friend int operator+(const int& lhs, const iTunesEntry& rhs);

private:
   int sum;
   vector<T> *originalObjects;
   vector<int> indices;
};

//------------------------------Class Sublist definition----------------
template<class T>
//Add the value and the calculate the total sum of the sublist
Sublist<T> Sublist<T>::addItem(int indexOfItemToAdd) {
   Sublist<T> tempSubList;

   tempSubList = *this;
   tempSubList.indices.push_back(indexOfItemToAdd);
   tempSubList.sum = tempSubList.sum + originalObjects->at(indexOfItemToAdd);
   return tempSubList;
}

//Show all the sublist that within the target
template<class T>
void Sublist<T>::showSublist() const {
   //If there's no sublist
   if (indices.size() == 0) {
      cout << "\nNo subList found.\n" << endl;
   }
   else {
      cout << "\nSublist -------------------------------------------" << '\n'
         << "sum: " << sum << "\n" << endl;

      for (unsigned int i = 0; i < indices.size() - 1; i++) {
         cout << "array[" << indices[i] << "] = " << originalObjects->at(indices[i]) << '\n';
      }
      cout << endl;
   }
}

//Display the list
ostream& operator<<(ostream& str, const iTunesEntry& s) {
   str << s.getTitle() << " by " << s.getArtist() << "("
      << s.getTime() << ")";
   return str;
}

//Combine two number together
int operator+(const int& lhs, const iTunesEntry& rhs) {
   return lhs + rhs.getTime();
}

//------------------------------Global prototype----------------------------
void subSetSumTunes(int TARGET, vector<iTunesEntry> dataSet);
void subSetSumInt(int TARGET, vector<int> dataSet);

template<class T>
void subSetSum(int TARGET, vector<T> dataSet);
//------------------------------Gobal Definition----------------------------
template<class T>
void subSetSum(int TARGET, vector<T> dataSet) {
   vector<Sublist<T>> choices;
   int numSets, max, masterSum;
   numSets = 0;
   max = 0;
   masterSum = 0;
   bool foundPerfect = false;

   choices.clear();

   cout << "Target time: " << TARGET << endl;

   choices.push_back(Sublist<T>(&dataSet));

   typename vector<T>::iterator i;
   for (i = dataSet.begin(); i != dataSet.end(); i++) {
      masterSum = masterSum + *i;
   }
   //If the sum of the master list smaller or equal to the target, copy all the elements
   if (masterSum <= TARGET) {
      Sublist<T> finalSublist = Sublist<T>(&dataSet);

      for (unsigned int i = 0; i < dataSet.size(); i++) {
         finalSublist = finalSublist.addItem(i);
      }
      choices.push_back(finalSublist);
      numSets = choices.size() - 1;
      foundPerfect = true;
   }

   //If the sum of the master list bigger than the target
   Sublist<T> tempSubList;
   int tempSize;

   //If the master set is empty
   if (dataSet.size() == 0) {
      cout << "\nNo empty master set please.\n" << endl;
      foundPerfect = true;
   }
   for (unsigned int i = 0; !foundPerfect && i < dataSet.size(); i++) {
      tempSize = choices.size();

      for (int k = 0; !foundPerfect && k < tempSize; k++) {
         tempSubList = choices[k].addItem(i);

         if (tempSubList.getSum() <= TARGET) {
            choices.push_back(tempSubList);

            if (tempSubList.getSum() == TARGET) {
               numSets = choices.size() - 1;
               foundPerfect = true;
            }

            if (tempSubList.getSum() > max) {
               numSets = choices.size() - 1;
               max = tempSubList.getSum();
            }
         }
      }
   }
   choices[numSets].showSublist();
}

//If the dataset is object
void subSetSumTunes(int TARGET, vector<iTunesEntry> dataSet) {
   subSetSum(TARGET, dataSet);
}
//If the dataset is int
void subSetSumInt(int TARGET, vector<int> dataSet) {
   subSetSum(TARGET, dataSet);
}


int main()
{
   const int TARGET = 1000000;
   //Test for Int
   vector<int> dataSet;

   dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
   dataSet.push_back(15); dataSet.push_back(25);
   dataSet.push_back(19); dataSet.push_back(29);
   dataSet.push_back(18);
   dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);

   subSetSumInt(TARGET, dataSet);

   vector<int> testSet;
   subSetSumInt(TARGET, testSet);

   vector<int> noSubList;
   noSubList.push_back(3700);
   subSetSumInt(TARGET, noSubList);

   //Test for ITunes
   cout << "Test for Itunes:-------------------------------------" << endl;
   int array_size;
   vector<iTunesEntry> dataSetITunes;

   iTunesEntryReader tunes_input("itunes_file.txt");
   if (tunes_input.readError())
   {
      cout << "couldn't open " << tunes_input.getFileName()
         << " for input.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create a vector of objects for our own use:
   array_size = tunes_input.getNumTunes();
   for (int k = 0; k < array_size; k++)
      dataSetITunes.push_back(tunes_input[k]);

   subSetSumTunes(TARGET, dataSetITunes);
   // how we determine the time elapsed -------------------
   stopTime = clock();
   // report algorithm time
   cout << "\nAlgorithm Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   return 0;
} 

/*------------------------------output-------------------------
Target time: 3600

Sublist -------------------------------------------
sum: 201

array[0] = 20
array[1] = 12
array[2] = 22
array[3] = 15
array[4] = 25
array[5] = 19
array[6] = 29
array[7] = 18
array[8] = 11
array[9] = 13

Target time: 3600

No empty master set please.


No subList found.

Target time: 3600

No subList found.

Test for Itunes:-------------------------------------
Target time: 3600

Sublist -------------------------------------------
sum: 3600

array[0] = Cowboy Casanova by Carrie Underwood(236)
array[1] = Quitter by Carrie Underwood(220)
array[2] = Russian Roulette by Rihanna(228)
array[4] = Monkey Wrench by Foo Fighters(230)
array[5] = Pretending by Eric Clapton(283)
array[6] = Bad Love by Eric Clapton(308)
array[7] = Everybody's In The Mood by Howlin' Wolf(178)
array[8] = Well That's All Right by Howlin' Wolf(175)
array[9] = Samson and Delilah by Reverend Gary Davis(216)
array[11] = Hot Cha by Roy Buchanan(208)
array[12] = Green Onions by Roy Buchanan(443)
array[13] = I'm Just a Prisoner by Janiva Magness(230)
array[14] = You Were Never Mine by Janiva Magness(276)
array[15] = Hobo Blues by John Lee Hooker(187)


Algorithm Elapsed Time: 3.994 seconds.

Press any key to continue . . .

Target time: 1

No subList found.

Target time: 1

No empty master set please.


No subList found.

Target time: 1

No subList found.

Test for Itunes:-------------------------------------
Target time: 1

No subList found.


Algorithm Elapsed Time: 0.006 seconds.

Press any key to continue . . .
*/