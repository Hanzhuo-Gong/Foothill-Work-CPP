// CS2CLab8.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <ctime>
#include "FHvector.h"
#include "FHsort.h"
using namespace std;

template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int recLimit)
{
   Comparable pivot;
   int i, j;

   if (left + recLimit <= right)
   {
      //Get the median
      pivot = median3(a, left, right);
      for (i = left, j = right - 1; ; ) {
         //travel until i is greater than pivot
         while (a[++i] < pivot) {
            ;
         }
         //travel until j is smaller than pivot
         while (pivot < a[--j]) {
            ;
         }
         if (i < j) {
            mySwapFH(a[i], a[j]);
         }
         else
            break;
      }

      //swap the pivot with the number i and j meet
      swap(a[i], a[right - 1]);

      //recursive call for the left side
      quickSortX(a, left, i - 1, recLimit);
      //recursive call for the right side
      quickSortX(a, i + 1, right, recLimit);
   }
   else {
      // use insertion instead of quicksort
      insertionSort(a, left, right);
   }
}

template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int recLimit)
{
   //If the recLimit smaller than two, make it two
   if (recLimit < 2)
      recLimit = 2;
   quickSortX(a, 0, a.size() - 1, recLimit);
}


int main()
{
   srand((unsigned)time(NULL));
   int i, k, recLimit;
   clock_t startTime, stopTime;
   const int maxLimited = 100;
   FHvector<int> fhVectorOfInts;
   ofstream outputFile, compareFile;
   vector<double> timeData;
   bool gapOutput = false;
   int arraySize[] = { 40000, 80000, 120000, 160000 };
   int numSizesToTest = sizeof(arraySize) / sizeof(arraySize[0]);

   //Create the file
   outputFile.open("QuickSortX.csv");

   outputFile << "gap, 40000, 80000, 120000, 160000 \n";

   for (i = 0; i < numSizesToTest; i++) {
      vector<int> randNumbersToInsert;
      int numNumbers = arraySize[i];

      cout << "size is:" << numNumbers << endl;
      // fullfill the vector
      for (k = 0; k < numNumbers; k++) {
         int r = rand() / (double)RAND_MAX * numNumbers * 5;
         randNumbersToInsert.push_back(r);
      }

      // Push back the number
      for (recLimit = 2; recLimit <= maxLimited; recLimit += 2) {
         fhVectorOfInts.clear();
         for (k = 0; k < numNumbers; k++)
            fhVectorOfInts.push_back(randNumbersToInsert[k]);

         //Output the gap only one time
         if (!gapOutput) {
            timeData.push_back(recLimit);
            if (recLimit == maxLimited) {
               gapOutput = true;
            }
         }

         //Time the select algorithm
         startTime = clock();
         quickSortX(fhVectorOfInts, recLimit);
         stopTime = clock();

         double time = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
         timeData.push_back(time);

         cout << "Elapsed Time with rec limit = " << recLimit << ": "
            << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
            << " seconds." << endl;
      }
   }

   //Write the data to the csv file
   int gap, time1, time2, time3, time4;
   gap = 0;
   time1 = 1;
   time2 = 100;
   time3 = 150;
   time4 = 200;

   for (gap, time1, time2, time3, time4; time4 < 250;
      gap += 2, time1 += 2, time2++, time3++, time4++) {
      outputFile << timeData.at(gap) << "," << timeData.at(time1) << ","
         << timeData.at(time2) << "," << timeData.at(time3) << ","
         << timeData.at(time4) << "\n";
   }
   outputFile.close();

   //----------------------------part 2----------------------------------
   FHvector<int> fhQuickSort;
   FHvector<int> fhInsertionSort;
   FHvector<int> fhMergeSort;
   FHvector<int> fhHeapSort;
   FHvector<double> dataComparation;
   double quickSortTime, heapSortTime, insertionSortTime, mergeSortTime;

   compareFile.open("CompareAlgorithm.csv");
   compareFile << ", 40000, 80000, 120000, 160000" << "\n";

   for (int i = 0; i < numSizesToTest; i++) {
      int numNumbers = arraySize[i];

      cout << "size is:" << numNumbers << endl;
      // fullfill the vector
      for (int k = 0; k < numNumbers; k++) {
         int r = rand() / (double)RAND_MAX * numNumbers * 5;
         fhQuickSort.push_back(r);
         fhInsertionSort.push_back(r);
         fhMergeSort.push_back(r);
         fhHeapSort.push_back(r);
      }

      //Quick sort
      startTime = clock();
      quickSort(fhQuickSort);
      stopTime = clock();

      quickSortTime = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
      cout << "quick: " << quickSortTime << endl;
      dataComparation.push_back(quickSortTime);

      //Merge sort
      startTime = clock();
      mergeSort(fhMergeSort);
      stopTime = clock();

      mergeSortTime = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
      cout << "merge: " << mergeSortTime << endl;
      dataComparation.push_back(mergeSortTime);

      //Heap sort
      startTime = clock();
      heapSort(fhHeapSort);
      stopTime = clock();

      heapSortTime = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
      cout << "heap: " << heapSortTime << endl;
      dataComparation.push_back(heapSortTime);

      //Insertion sort
      startTime = clock();
      insertionSort(fhInsertionSort);
      stopTime = clock();

      insertionSortTime = (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC;
      cout << "Insertion: " << insertionSortTime << endl;
      dataComparation.push_back(insertionSortTime);
   }

   //Write the file out
   compareFile << "Quick Sort:" << ",";
   int count = 0;
   for (int i = 0; count < 4; count++, i += 4) {
      compareFile << dataComparation.at(i) << ",";
   }

   compareFile << "\n" << "Merge Sort:" << ",";
   count = 0;
   for (int k = 1; count < 4; count++, k += 4) {
      compareFile << dataComparation.at(k) << ",";
   }

   compareFile << "\n" << "Heap Sort:" << ",";
   count = 0;
   for (int j = 2; count < 4; count++, j += 4) {
      compareFile << dataComparation.at(j) << ",";
   }

   compareFile << "\n" << "Insertion Sort:" << ",";
   count = 0;
   for (int l = 3; count < 4; count++, l += 4) {
      compareFile << dataComparation.at(l) << ",";
   }

   return 0;
}

