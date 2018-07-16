//CS 2C Lab 2 code
//This program will display the Sparse Matrices
//Copyright © 2018 Hanzhuo Gong. All right reserved.

#ifndef SPARSE_MATRICES
#define SPARSE_MATRICES

#include <iostream>
#include <iomanip>
#include "FHvector.h"
#include "FHlist.h"
using namespace std;

//----------------------MatNode class--------------------------
template <class Object>
class MatNode
{
protected:
   int col;

public:
   Object data;
   // we need a default constructor for lists
   MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
   int getCol() const { return col; }

   // not optimized yet for set() = defaultVal;  refer to forums
   const Object & operator=(const Object &x) { return (data = x); }
};

//---------------------------------SparseMat class prototype------------
template <class Object>
class SparseMat {
protected:

   typedef FHlist<MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MatCol;

   MatCol rows;
   Object defaultVal;
   int rowSize, colSize;

public:
   static const int MIN_SIZE = 1;

   SparseMat(int r, int c, const Object & defaultVal);
   const Object & get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear();
   void showSubSquare(int start, int size);
   class OutOfBoundsException { };

   int getRowSize() { return rowSize; }
   int getColSize() { return colSize; }

private:
   bool isValid(int r, int c) const;

};

// -----------------------------SparseMat class definition--------------
// Constructor
template <class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & defaultVal) {
   // If the value is invalid, change the value to minimum
   if (r < MIN_SIZE)
      r = MIN_SIZE;
   if (c < MIN_SIZE)
      c = MIN_SIZE;
   rowSize = r;
   colSize = c;
   rows.resize(r);
   this->defaultVal = defaultVal;
}

// Mutator
template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x) {
   MatRow::iterator iter;
   MatRow *curRow;

   if (!isValid(r, c))
      return false;

   curRow = &rows[r];
   for (iter = curRow->begin(); iter != curRow->end(); iter++)
      if ((*iter).getCol() == c)
      {
         if (x != defaultVal)
            (*iter).data = x;
         else
            curRow->erase(iter);
         return true;
      }

   if (x != defaultVal) {
      MatNode<Object> tempNode(c, x);
      curRow->push_back(tempNode);
   }
   return true;
}

// Private helper method to check validation
template <class Object>
bool SparseMat<Object>::isValid(int r, int c) const {
   if (r < 0 || r >= rowSize || c < 0 || c >= colSize)
      return false;
   return true;
}

// Get the value for certain position
template <class Object>
const Object &SparseMat<Object>::get(int r, int c) const {
   MatRow::const_iterator iter;
   const MatRow *curRow;

   if (!isValid(r, c))
      throw OutOfBoundsException();

   curRow = &rows[r];

   for (iter = curRow->begin(); iter != curRow->end(); iter++) {
      if ((*iter).getCol() == c) {
         return (*iter).data;
      }
   }
   // if not found, return default value
   return defaultVal;
}

// Clear all rows
template <class Object>
void SparseMat<Object>::clear() {
   int tempSize = rows.size();
   rows.clear();
   rows.resize(tempSize);
}

// Display method to the console
template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size) {
   int maxSize = start + size;

   if (start < 0 || size < 0 || start + size > rowSize ||
      start + size > colSize) {
      cout << "Out of range, can not display" << endl;
      return;
   }

   for (int row = start; row < maxSize; row++) {
      for (int col = start; col < maxSize; col++) {
         //set field width
         cout << setw(3);
         cout << get(row, col) << " ";
      }
      cout << endl;
   }
   cout << "\n" << endl;
}
#endif

#define MAT_SIZE 100000
typedef SparseMat<float> SpMat;

// --------------- main ---------------
/*
int main()
{
   SpMat mat(MAT_SIZE, MAT_SIZE, 0); // 100000 x 100000 filled with 0

                                     // test mutators
   mat.set(2, 5, 10);
   mat.set(2, 5, 35);   // should overwrite the 10
   mat.set(3, 9, 21);
   mat.set(MAT_SIZE, 1, 5);  // should fail silently
   mat.set(9, 9, mat.get(3, 9));  // should copy the 21 here
   mat.set(4, 4, -9);
   mat.set(4, 4, 0);   // should remove the -9 node entirely
   mat.set(MAT_SIZE - 1, MAT_SIZE - 1, 99);

   //check for size


   // test accessors and exceptions
   try
   {
      cout << mat.get(7, 8) << endl;
      cout << mat.get(2, 5) << endl;
      cout << mat.get(9, 9) << endl;
      cout << mat.get(-4, 7) << endl;  // should throw an exception
   }
   catch (...)
   {
      cout << "oops" << endl;
   }

   // show top left 15x15
   mat.showSubSquare(0, 15);

   // show bottom right 15x15
   mat.showSubSquare(MAT_SIZE - 15, 15);

   cout << "----------------Self test-------------" << endl;
   SpMat testMat(20, 20, 0), testMat2(-1, -1, 0);
   testMat.set(1, 1, 30);
   testMat.set(3, 7, 10);
   if (testMat.set(-1, -1, 15))
      cout << "Set Row -1, Col -1 to 15 succeed." << endl;
   else
      cout << "Set Row -1, Col -1 to 15 failed." << endl;

   cout << "Row size is:" << testMat.getRowSize() << endl;
   cout << "Col size is:" << testMat.getColSize() << endl;
   cout << "Row 1 Col 1 should be 30: " << testMat.get(1, 1) << endl;
   cout << "Row 3 Col 7 should be 10: " << testMat.get(3, 7) << endl;
   testMat.showSubSquare(0, 20);

   cout << "Row size for negative size, should back to 1: "
      << testMat2.getRowSize() << endl;
   cout << "Col size for negative size, should back to 1: "
      << testMat2.getColSize() << endl;

   //Test for clear
   cout << "\n-------------Test for clear function----------------" << endl;
   testMat.clear();
   cout << "After clear the Row size is: " << testMat.getRowSize() << endl;
   cout << "After clear the Col size is: " << testMat.getColSize() << endl;
   testMat.showSubSquare(0, 20);
}
*/

/*--------------------------output---------------------------------
0
35
21
oops
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0  35   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0  21   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0  21   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0


0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0  99


----------------Self test-------------
Set Row -1, Col -1 to 15 failed.
Row size is:20
Col size is:20
Row 1 Col 1 should be 30: 30
Row 3 Col 7 should be 10: 10
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0  30   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0  10   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0


Row size for negative size, should back to 1: 1
Col size for negative size, should back to 1: 1

-------------Test for clear function----------------
After clear the Row size is: 20
After clear the Col size is: 20
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0


Press any key to continue . . .*/