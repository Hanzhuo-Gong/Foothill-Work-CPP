// PQ.h

#include <iostream>
#include <vector>
#include <ctime>
#include "FHlist.h"

// ------------- base class -----------------

template <class Comparable>
class PQ {
protected:
	int mSize;

public:
	virtual void insert(const Comparable & x) = 0;
	virtual Comparable & remove() = 0;
	bool empty() const { return mSize == 0; }
};

// ------------- exception class -----------------

class EmptyPQException {};

// ------------- derived class prototypes -----------------

// sorted list
template <class Comparable>
class PQsortedList : public PQ<Comparable>
{
private:
	FHlist<Comparable> sortedList;

public:
	void insert(const Comparable &x);
	Comparable & remove();
};

// unsorted list
template <class Comparable>
class PQunsortedList : public PQ<Comparable>
{
private:
	FHlist<Comparable> unsortedList;

public:
	void insert(const Comparable &x);
	Comparable & remove();
};

//Sorted Vector
template <class Comparable>
class PQsortedVector : public PQ<Comparable>
{
private:
	vector<Comparable> sortedVector;

public:
	void insert(const Comparable &x);
	Comparable & remove();
};

//Unsorted Vector
template<class Comparable>
class PQunsortedVector :public PQ<Comparable>
{
private:
	vector<Comparable> unsortedVector;

public:
	void insert(const Comparable &x);
	Comparable & remove();
};

// ------------- derived class implementations -----------------
template <class Comparable>
void PQsortedList<Comparable>::insert(const Comparable &x) {
	typename FHlist<Comparable>::iterator iter;
	for (iter = sortedList.begin(); iter != sortedList.end(); iter++) {
		if (x < *iter) {
			break;
		}
	}
	sortedList.insert(iter, x);
}

template <class Comparable>
Comparable & PQsortedList<Comparable>::remove() {

	//Empty List
	if (sortedList.empty()) {
		throw EmptyPQException{};
	}

	static Comparable tempObject;
	tempObject = sortedList.front();
	sortedList.pop_front();

	return tempObject;
}

// Unsorted List
template <class Comparable>
void PQunsortedList<Comparable>::insert(const Comparable &x) {
	unsortedList.push_front(x);
}

template <class Comparable>
Comparable & PQunsortedList<Comparable>::remove() {
	//If the list is empty
	if (unsortedList.empty()) {
		throw EmptyPQException{};
	}
	//Remove the minimum node from the list
	else {
		typename FHlist<Comparable>::iterator iter = unsortedList.begin();
		typename FHlist<Comparable>::iterator iter2 = iter;

		for (iter; iter != unsortedList.end(); iter++) {
			if (*iter2 > *iter) {
				iter2 = iter;
			}
		}

		static Comparable tempObject;
		tempObject = *iter2;
		unsortedList.erase(iter2);

		return tempObject;
	}
}

//Sorted vector
template<class Comparable>
void PQsortedVector<Comparable>::insert(const Comparable &x) {
	typename vector<Comparable>::iterator iter;
	for (iter = sortedVector.begin(); iter != sortedVector.end(); iter++) {
		if (x < *iter) {
			break;
		}
	}
	sortedVector.insert(iter, x);
}

template <class Comparable>
Comparable & PQsortedVector<Comparable>::remove() {

	//Empty List
	if (sortedVector.empty()) {
		throw EmptyPQException{};
	}

	static Comparable tempObject;
	tempObject = sortedVector.front();
	sortedVector.erase(sortedVector.begin());

	return tempObject;
}

//unsorted vector
template<class Comparable>
void PQunsortedVector<Comparable>::insert(const Comparable &x) {
	unsortedVector.push_back(x);
}

template<class Comparable>
Comparable & PQunsortedVector<Comparable>::remove() {
	//If the list is empty
	if (unsortedVector.empty()) {
		throw EmptyPQException{};
	}
	//Remove the minimum node from the list
	else {
		typename vector<Comparable>::iterator iter = unsortedVector.begin();
		typename vector<Comparable>::iterator iter2 = iter;

		for (iter; iter != unsortedVector.end(); iter++) {
			if (*iter2 > *iter) {
				iter2 = iter;
			}
		}

		static Comparable tempObject;
		tempObject = *iter2;
		unsortedVector.erase(iter2);

		return tempObject;
	}
}
