//PQContest

#include <iostream>
#include <vector>
//#include "PQ.h"
#include "FHlazySearchTree.h"
using namespace std;
//
////Sorted Vector
//template <class Comparable>
//class PQsortedVector : public PQ<Comparable>
//{
//private:
//	vector<int> sortedVector;
//	//vector<Comparable> sortedVector;
//
//public:
//	void insert(const Comparable &x);
//	Comparable & remove();
//};
//
////Unsorted Vector
//template<class Comparable>
//class PQunsortedVector :public PQ<Comparable>
//{
//private:
//	vector<int> unsortedVector;
//	//vector<Comparable> unsortedVector;
//
//public:
//	void insert(const Comparable &x);
//	Comparable & remove();
//};
//
////BST priority queue
//template<class Comparable>
//class PQBST :public PQ<Comparable>
//{
//private:
//	FHlazySearchTree<Comparable> PQTree;
//
//public:
//	void insert(const Comparable &x);
//	Comparable & remove();
//};
//
////--------------------------Definition--------------------------
//template<class Comparable>
//void PQsortedVector<Comparable>::insert(const Comparable &x)
//{
//	typename vector<Comparable>::iterator iter;
//	for (iter = sortedVector.begin(); iter != sortedVector.end(); iter++) {
//		if (x < *iter) {
//			break;
//		}
//	}
//	sortedVector.insert(iter, x);
//}
//
//template <class Comparable>
//Comparable & PQsortedVector<Comparable>::remove() {
//
//	//Empty List
//	if (sortedVector.empty()) {
//		throw EmptyPQException{};
//	}
//
//	static Comparable tempObject;
//	tempObject = sortedVector.front();
//	sortedVector.pop_front();
//
//	return tempObject;
//}