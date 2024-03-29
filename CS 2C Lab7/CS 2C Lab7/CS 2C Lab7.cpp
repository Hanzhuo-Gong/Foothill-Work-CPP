//CS 2C Lab 7 code
//This program compare the time complexity of different data structure
//Copyright © 2018 Hanzhuo Gong. All right reserved.

#include <iostream>
#include <vector>
#include <ctime>
#include <queue>
#include "FHsearch_tree.h"
#include "FHbinHeap.h"
#include "PQ.h"
using namespace std;

template <typename Object>
class PrintObject
{
public:
	void operator()(Object obj)
	{
		cout << obj << " ";
	}
};

int main(int argc, const char * argv[])
{
	srand((unsigned)time(NULL));
	clock_t startTime, stopTime;
	PrintObject<int> intPrinter;

	PQsortedList<int> myList;
	myList.insert(20);
	myList.insert(4);
	myList.insert(80);

	cout << myList.remove() << endl;
	cout << myList.remove() << endl;
	cout << myList.remove() << endl;

	PQunsortedList<int> myList2;
	myList2.insert(20);
	myList2.insert(4);
	myList2.insert(80);

	cout << myList2.remove() << endl;
	cout << myList2.remove() << endl;
	cout << myList2.remove() << endl;

	////Test for already-sorted values
	//int numNumbers = 40000;
	//vector<int> inorderInsert;
	//for (int i = 0; i < numNumbers; i++) {
	//	inorderInsert.push_back(i);
	//}

	////Test for inverse values
	//int numNumbers = 40000;
	//vector<int> reverseOrderInsert;
	//for (int i = numNumbers; i > 0; i--) {
	//	reverseOrderInsert.push_back(i);
	//}

	// Timing on random list of numbers
	int sizes[] = { 5000, 10000, 20000, 40000 };
	int numSizesToTest = sizeof(sizes) / sizeof(sizes[0]);

	for (int i = 0; i < numSizesToTest; i++) {
		vector<int> randNumbersToInsert;
		int numNumbers = sizes[i];
		for (int j = 0; j < numNumbers; j++) {
			// arbitrary - make random numbers up to 5 times the size of the vector, to spread them out
			int r = rand() / (double)RAND_MAX * numNumbers * 5;
			randNumbersToInsert.push_back(r);
		}

		PQsortedList<int> sortedListPQ;
		PQunsortedList<int> unsortedListPQ;
		FHbinHeap<int> heapPQ;
		priority_queue<int> PQList;
		PQsortedVector<int> sortedVectorPQ;
		PQunsortedVector<int> unsortedVectorPQ;
		FHsearch_tree<int> BSTreePQ;

		// put your tests here:
		cout << "\n----------------unsorted list----------------" << endl;
		startTime = clock();
		for (int k = 0; k < numNumbers; k++) {
			unsortedListPQ.insert(randNumbersToInsert[k]);

			//For in order and reverse order
			//unsortedListPQ.insert(inorderInsert[k]);
			//unsortedListPQ.insert(reverseOrderInsert[k]);
		}
		stopTime = clock();


		cout << "\nSize = " << numNumbers << " inserted into unsortedListPQ.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		//Test remove time for the sorted list
		startTime = clock();
		for (int i = 0; i < numNumbers; i++) {
			unsortedListPQ.remove();
		}
		stopTime = clock();

		//Check the list is empty
		try
		{
			unsortedListPQ.remove();
		}
		catch (...)
		{
			cout << "List is empty, can't remove" << endl;
		}

		cout << "\nSize = " << numNumbers << " remove from unsortedListPQ.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		cout << "\n---------------sorted list--------------------" << endl;
		startTime = clock();
		for (int i = 0; i < numNumbers; i++) {
			sortedListPQ.insert(randNumbersToInsert[i]);

			//For inorder and reverse order only
			//sortedListPQ.insert(inorderInsert[i]);
			//sortedListPQ.insert(reverseOrderInsert[i]);
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " inserted into sortedListPQ.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		startTime = clock();
		for (int k = 0; k < numNumbers; k++) {
			sortedListPQ.remove();
		}
		stopTime = clock();

		try
		{
			sortedListPQ.remove();
		}
		catch (...)
		{
			cout << "can't remove from a empty list" << endl;
		}

		cout << "\nSize = " << numNumbers << " remove from sortedListPQ.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		cout << "\n------------------------heapPQ------------------" << endl;
		startTime = clock();
		for (int i = 0; i < numNumbers; i++) {
			heapPQ.insert(randNumbersToInsert[i]);

			//For in order and reverse order
			//heapPQ.insert(inorderInsert[i]);
			//heapPQ.insert(reverseOrderInsert[i]);
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " insert from heapPQ.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		startTime = clock();
		for (int k = 0; k < numNumbers; k++) {
			heapPQ.remove();
		}
		stopTime = clock();

		try
		{
			heapPQ.remove();
		}
		catch (...)
		{
			cout << "empty in heapPQ, can't remove" << endl;
		}

		cout << "\nSize = " << numNumbers << " remove from heapPQ.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		cout << "-----------------test for priority queue--------------" << endl;
		startTime = clock();
		for (int i = 0; i < numNumbers; i++) {
			PQList.push(randNumbersToInsert[i]);
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " insert to priority queue.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		startTime = clock();
		for (int k = 0; k < numNumbers; k++) {
			PQList.pop();
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " remove from priority queue.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		cout << "----------------Test for Sorted Vector--------------" << endl;
		startTime = clock();
		for (int i = 0; i < numNumbers; i++) {
			sortedVectorPQ.insert(randNumbersToInsert[i]);
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " insert to sorted vector.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		startTime = clock();
		for (int k = 0; k < numNumbers; k++) {
			sortedVectorPQ.remove();
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " remove from sorted vector.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		cout << "--------------Test for Unsorted Vector---------------" << endl;
		startTime = clock();
		for (int i = 0; i < numNumbers; i++) {
			unsortedVectorPQ.insert(randNumbersToInsert[i]);
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " insert to unsorted vector.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		startTime = clock();
		for (int k = 0; k < numNumbers; k++) {
			unsortedVectorPQ.remove();
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " remove from unsorted vector.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		cout << "--------------------Test for BSTPQ--------------------" << endl;
		int minNode;
		startTime = clock();
		for (int i = 0; i < numNumbers; i++) {
			BSTreePQ.insert(randNumbersToInsert[i]);
		}
		stopTime = clock();

		cout << "\nSize = " << numNumbers << " insert to BSTPQ.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

		startTime = clock();
		for (int i = 0; i < numNumbers; i++) {
			//Need to set up try out statement just in case the randNumber generate
			//same number and the tree don't take duplicate number, so the size will
			//be less than remove time, it will break the code
			try
			{
				minNode = BSTreePQ.findMin();
				BSTreePQ.remove(minNode);
			}
			catch (...)
			{
				//intentionally blank
			}
		}
		stopTime = clock();

		//Check the tree is empty
		BSTreePQ.traverse(intPrinter);

		cout << "\nSize = " << numNumbers << " remove from BSTPQ.";
		cout << "Elapsed Time: "
			<< (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
			<< " seconds." << endl << endl;

	}

	// put your tests here:
	cout << "\n--------------------Self Test-----------------" << endl;
	PQunsortedList<int> tempList;
	//tempList.insert(30);
	//tempList.insert(50);
	tempList.insert(70);
	tempList.insert(40);
	tempList.insert(90);
	tempList.insert(110);
	tempList.insert(90);
	//tempList.insert(1);

	cout << "1:" << tempList.remove() << endl;
	cout << "2:" << tempList.remove() << endl;
	cout << "3:" << tempList.remove() << endl;
	cout << "4:" << tempList.remove() << endl;
	cout << "5:" << tempList.remove() << endl;

	try
	{
		cout << tempList.remove();
	}
	catch (...)
	{
		cout << "The list is empty, nothing to remove" << endl;
	}

	cout << "\n---------------------Test for Sorted List-------------" << endl;
	PQsortedList<int> testList;
	testList.insert(40);
	testList.insert(20);
	testList.insert(20);
	testList.insert(10);
	testList.insert(30);
	testList.insert(80);

	cout << "1:" << testList.remove() << endl;
	cout << "2:" << testList.remove() << endl;
	cout << "3:" << testList.remove() << endl;
	cout << "4:" << testList.remove() << endl;
	cout << "5:" << testList.remove() << endl;
	cout << "6:" << testList.remove() << endl;

	try
	{
		testList.remove();
	}
	catch (...)
	{
		cout << "The list is empty, nothing to remove" << endl;
	}

	FHsearch_tree<int> testTree;
	int min;
	testTree.insert(30);
	testTree.insert(50);
	testTree.insert(1);
	testTree.insert(80);

	min = testTree.findMin();
	testTree.remove(min);

	testTree.traverse(intPrinter);

	return 0;

}

/*-----------------------------------output-------------------------
4
20
80
4
20
80

----------------unsorted list----------------

Size = 5000 inserted into unsortedListPQ.Elapsed Time: 0.003 seconds.

List is empty, can't remove

Size = 5000 remove from unsortedListPQ.Elapsed Time: 2.733 seconds.


---------------sorted list--------------------

Size = 5000 inserted into sortedListPQ.Elapsed Time: 1.192 seconds.

can't remove from a empty list

Size = 5000 remove from sortedListPQ.Elapsed Time: 0.001 seconds.


------------------------heapPQ------------------

Size = 5000 insert from heapPQ.Elapsed Time: 0.003 seconds.

empty in heapPQ, can't remove

Size = 5000 remove from heapPQ.Elapsed Time: 0.014 seconds.


----------------unsorted list----------------

Size = 10000 inserted into unsortedListPQ.Elapsed Time: 0.006 seconds.

List is empty, can't remove

Size = 10000 remove from unsortedListPQ.Elapsed Time: 10.804 seconds.


---------------sorted list--------------------

Size = 10000 inserted into sortedListPQ.Elapsed Time: 4.808 seconds.

can't remove from a empty list

Size = 10000 remove from sortedListPQ.Elapsed Time: 0.003 seconds.


------------------------heapPQ------------------

Size = 10000 insert from heapPQ.Elapsed Time: 0.005 seconds.

empty in heapPQ, can't remove

Size = 10000 remove from heapPQ.Elapsed Time: 0.018 seconds.


----------------unsorted list----------------

Size = 20000 inserted into unsortedListPQ.Elapsed Time: 0.012 seconds.

List is empty, can't remove

Size = 20000 remove from unsortedListPQ.Elapsed Time: 43.547 seconds.


---------------sorted list--------------------

Size = 20000 inserted into sortedListPQ.Elapsed Time: 19.202 seconds.

can't remove from a empty list

Size = 20000 remove from sortedListPQ.Elapsed Time: 0.007 seconds.


------------------------heapPQ------------------

Size = 20000 insert from heapPQ.Elapsed Time: 0.011 seconds.

empty in heapPQ, can't remove

Size = 20000 remove from heapPQ.Elapsed Time: 0.058 seconds.


----------------unsorted list----------------

Size = 40000 inserted into unsortedListPQ.Elapsed Time: 0.023 seconds.

List is empty, can't remove

Size = 40000 remove from unsortedListPQ.Elapsed Time: 175.034 seconds.


---------------sorted list--------------------

Size = 40000 inserted into sortedListPQ.Elapsed Time: 77.767 seconds.

can't remove from a empty list

Size = 40000 remove from sortedListPQ.Elapsed Time: 0.013 seconds.


------------------------heapPQ------------------

Size = 40000 insert from heapPQ.Elapsed Time: 0.02 seconds.

empty in heapPQ, can't remove

Size = 40000 remove from heapPQ.Elapsed Time: 0.085 seconds.

Press any key to continue . . .

//--------------------------In order number---------------------------

----------------unsorted list----------------

Size = 40000 inserted into unsortedListPQ.Elapsed Time: 0.022 seconds.

List is empty, can't remove

Size = 40000 remove from unsortedListPQ.Elapsed Time: 174.657 seconds.


---------------sorted list--------------------

Size = 40000 inserted into sortedListPQ.Elapsed Time: 153.712 seconds.

can't remove from a empty list

Size = 40000 remove from sortedListPQ.Elapsed Time: 0.012 seconds.


------------------------heapPQ------------------

Size = 40000 insert from heapPQ.Elapsed Time: 0.015 seconds.

empty in heapPQ, can't remove

Size = 40000 remove from heapPQ.Elapsed Time: 0.102 seconds.

Press any key to continue . . .

//--------------------------Reverse order number----------------------

----------------unsorted list----------------

Size = 40000 inserted into unsortedListPQ.Elapsed Time: 0.023 seconds.

List is empty, can't remove

Size = 40000 remove from unsortedListPQ.Elapsed Time: 174.162 seconds.


---------------sorted list--------------------

Size = 40000 inserted into sortedListPQ.Elapsed Time: 0.041 seconds.

can't remove from a empty list

Size = 40000 remove from sortedListPQ.Elapsed Time: 0.011 seconds.


------------------------heapPQ------------------

Size = 40000 insert from heapPQ.Elapsed Time: 0.061 seconds.

empty in heapPQ, can't remove

Size = 40000 remove from heapPQ.Elapsed Time: 0.082 seconds.

Press any key to continue . . .

Question 2: 

Sorted List: Insert will take a n time, because It need to iterate the
whole numNumber to do the insertion. I got some weired time in my computer,
when I changed desktop to do the same test, the time is cut in half. Remove
is constant, because we only remove the first minimum node from the list.
When the size is double, the time is also double.

Unsorted List: Will be the opposite of sorted list, insert takes constant time
because we only insert the back of the list. Remove will take n time, because
we need to iterate the whole list to find the minimum since the list is unsorted.
I got the time for unsorted list is 175.034 seconds, but for sorted list time for
insert is 77.767 for size 40000. We see a big time difference in here. I believe
because when sorted list doing insert, when it find the node greater than the node
to insert. It can break the loop and do the next insertion. Which is average case.
However, unsorted list remove need to find the minimum, we don't know where is the
minimum, so we need to travel the whole list to find the minimum. Worst case.

heap sort: insert will take n log n time, when we insert a node, It will compare with
its parent and get to the right position. log n time for one, since we need to iterate
the whole list, the time is n log n. Remove is the same log n, when we try to remove a
node, it will search the child which have the minimum value and return it.

Question 4:
//-----------------------------In order-------------------------------
Sorted List: 
Insert I got the time 152.572 seconds. time should be n, because when we insert
the number 2, we need to compare 1, insert 2. then we insert 3, we need to compare
1, 2, then insert 3. If we want to insert 40000, we need to compare 1,2,3....39999.
Which the worst case. Remove won't change, because the list is sorted, remove the first
node, time is constant.

Unsorted List:
Insert shouldn't change, I got the time 0.023. constant, just push_back. Remove doesn't
change too, because we don't know where the minimum, so we need to travel the whole list
to get mimum, n times. I got 174.646.

Heap sorted:
Nothing affect, I got the insert time 0.015, and remove time 0.083. But this is the best case
for max heap sort tree, because we are insert the in order, so the large number will be always
in the root, not many swtich will needed. n log n for both insert and remove.

//---------------------------Reverse order-------------------------------
Sorted List:
insert is contants, this is best case for insert, when we insert 39999, we compare only 40000.
39998, only compare 39999. When you insert 1, only compare 2, so we only compare one number when
doing insertion. Remove no change, still the first number out, constant. I got 0.04 for insert,
and 0.011 for remove

Unsorted List:
Nothing change, insert will still push_back, constant. Remove we still need to travel the whole list
to find the minimum. N times. I got 0.023 for insert, 174.468 for remove.

heap sorted:
Insertion I got the time longer than in order one, 0.061. Time still n log n, this is the worst
case for max heap tree. because we are insert the number smaller than then one we inserted before,
so the tree need to swap everytime we do the insertion. Remove, nothing change, 0.081 time, n log n
time.

//--------------------------Extra Credit PQ---------------------------
-----------------test for priority queue--------------

Size = 5000 insert to priority queue.Elapsed Time: 0.042 seconds.


Size = 5000 remove from priority queue.Elapsed Time: 0.762 seconds.

-----------------test for priority queue--------------

Size = 10000 insert to priority queue.Elapsed Time: 0.07 seconds.


Size = 10000 remove from priority queue.Elapsed Time: 2.752 seconds.

-----------------test for priority queue--------------

Size = 20000 insert to priority queue.Elapsed Time: 0.085 seconds.


Size = 20000 remove from priority queue.Elapsed Time: 10.853 seconds.

-----------------test for priority queue--------------

Size = 40000 insert to priority queue.Elapsed Time: 0.169 seconds.


Size = 40000 remove from priority queue.Elapsed Time: 43.304 seconds.

Press any key to continue . . .

//-------------------------Extra Credit part C-----------------------
----------------Test for Sorted Vector--------------

Size = 5000 insert to sorted vector.Elapsed Time: 5.3 seconds.


Size = 5000 remove from sorted vector.Elapsed Time: 0.008 seconds.

----------------Test for Sorted Vector--------------

Size = 10000 insert to sorted vector.Elapsed Time: 20.935 seconds.


Size = 10000 remove from sorted vector.Elapsed Time: 0.018 seconds.

----------------Test for Sorted Vector--------------

Size = 20000 insert to sorted vector.Elapsed Time: 83.202 seconds.


Size = 20000 remove from sorted vector.Elapsed Time: 0.04 seconds.

----------------Test for Sorted Vector--------------

Size = 40000 insert to sorted vector.Elapsed Time: 332.645 seconds.


Size = 40000 remove from sorted vector.Elapsed Time: 0.104 seconds.

Press any key to continue . . .

--------------Test for Unsorted Vector---------------

Size = 5000 insert to unsorted vector.Elapsed Time: 0.003 seconds.


Size = 5000 remove from unsorted vector.Elapsed Time: 10.921 seconds.

--------------Test for Unsorted Vector---------------

Size = 10000 insert to unsorted vector.Elapsed Time: 0.007 seconds.


Size = 10000 remove from unsorted vector.Elapsed Time: 43.803 seconds.

--------------Test for Unsorted Vector---------------

Size = 20000 insert to unsorted vector.Elapsed Time: 0.013 seconds.


Size = 20000 remove from unsorted vector.Elapsed Time: 174.524 seconds.

--------------Test for Unsorted Vector---------------

Size = 40000 insert to unsorted vector.Elapsed Time: 0.024 seconds.


Size = 40000 remove from unsorted vector.Elapsed Time: 695.273 seconds.

Press any key to continue . . .

--------------------Test for BSTPQ--------------------

Size = 5000 insert to BSTPQ.Elapsed Time: 0.004 seconds.


Size = 5000 remove from BSTPQ.Elapsed Time: 0.005 seconds.

--------------------Test for BSTPQ--------------------

Size = 10000 insert to BSTPQ.Elapsed Time: 0.007 seconds.


Size = 10000 remove from BSTPQ.Elapsed Time: 0.011 seconds.

--------------------Test for BSTPQ--------------------

Size = 20000 insert to BSTPQ.Elapsed Time: 0.015 seconds.


Size = 20000 remove from BSTPQ.Elapsed Time: 0.034 seconds.

--------------------Test for BSTPQ--------------------

Size = 40000 insert to BSTPQ.Elapsed Time: 0.034 seconds.


Size = 40000 remove from BSTPQ.Elapsed Time: 0.11 seconds.

Press any key to continue . . .
*/