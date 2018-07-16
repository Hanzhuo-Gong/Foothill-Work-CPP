//CS 2C Lab 3 code
//This program will multiply two matrix
//Copyright © 2018 Hanzhuo Gong. All right reserved.

#ifndef SPARSE_MATRICES
#define SPARSE_MATRICES

#include <iostream>
#include <iomanip>
#include "FHvector.h"
#include "FHlist.h"
using namespace std;

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

//---------------SparseMatWMult class prototype-----------------------
template <class Object>
class SparseMatWMult : public SparseMat<Object>
{
public:
   SparseMatWMult(int numRows, int numCols);
   bool matMult(SparseMatWMult<Object> & a, SparseMatWMult<Object> & b);
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
         cout.precision(2);
         cout << get(row, col) << " ";
      }
      cout << endl;
   }
   cout << "\n" << endl;
}

//---------------SparseMatWMult class Definition-----------------------
template <class Object>
SparseMatWMult<Object>::SparseMatWMult(int numRows, int numCols)
   : SparseMat<Object>(numRows, numCols, Object())
{
}

template <class Object>
bool SparseMatWMult<Object>::matMult(SparseMatWMult<Object> & 
   matA, SparseMatWMult<Object> & matB) {
   Object result;
   int tempRowSize, tempColSize, tempCol, col;
   typename SparseMat<Object>::MatRow::const_iterator iterA, iterB;

   //store the col size from A and row size from B
   tempColSize = matA.getColSize();
   tempRowSize = matB.getRowSize();

   //if not equal, can not do the multiplication
   if (tempRowSize != tempColSize) {
      cout << "The row size of first matrix is not match with "
         << "column size of second matrix, please check back" << endl;
      return false;
   }

   //if the default value is not 0, we need to set to 0
   if ((float)matA.defaultVal != 0 || (float)matB.defaultVal != 0) {
      cout << "Your matrix default value is not 0, I will help you to "
         << "set to 0 in order to continue" << endl;
      this->defaultVal = 0;
   }

   for (int row = 0; row < SparseMat<Object>::rowSize; row++) {
      for (iterA = matA.rows[row].begin(); iterA != matA.rows[row].end(); 
         iterA++) {
         tempCol = (*iterA).getCol();
         result = 0;
         for (iterB = matB.rows[tempCol].begin(); 
            iterB != matB.rows[row].end(); iterB++) {
            col = (*iterB).getCol();
            result += ((*iterA).data * (*iterB).data);
            this->set(row, col, result);
         }
      }
   }
   return true;
}
#endif

//--------------------define value and typedef-----------------------
#define MAT_SIZE 100
typedef float* DynMat[MAT_SIZE];
typedef SparseMatWMult<float> SpMat;

//--------------------global function prototype----------------------
void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size);
void matShowDyn(const DynMat & matA, int start, int size);

//--------------------global function definition---------------------
// Multiply two matrices
void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size) {
   float result;

   for (int row = 0; row < size; row++) {
      for (int col = 0; col < size; col++) {
         result = 0;
         //index to count the row for the second matrix
         for (int i = 0; i < size; i++) {
            result += matA[row][i] * matB[i][col];
         }
         matC[row][col] = result;
      }
   }
}

//Display matrices
void matShowDyn(const DynMat & matA, int start, int size) {
   int maxSize = start + size;

   if (start < 0 || size < 0 || start + size > MAT_SIZE) {
      cout << "Size out of range, please check back." << endl;
      return;
   }

   for (int row = start; row < maxSize; row++) {
      for (int col = start; col < maxSize; col++) {
         cout << setw(5);
         cout.precision(2);
         cout << setiosflags(ios::fixed) << matA[row][col] << " ";
      }
      cout << endl;
   }
   cout << "\n" << endl;
}

int main()
{
   int r, c;
   clock_t startTime, stopTime;
   double randFrac;
   int randRow, randCol, smallPercent;

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;


   // allocate rows and initialize to 0
   for (r = 0; r < MAT_SIZE; r++)
   {
      matDyn[r] = new float[MAT_SIZE];
      matDynAns[r] = new float[MAT_SIZE];
      for (c = 0; c < MAT_SIZE; c++)
      {
         matDyn[r][c] = 0;
         matDynAns[r][c] = 0;
      }
   }

   // generate small% non-default values bet .1 and 1
   smallPercent = int(MAT_SIZE / 20. * MAT_SIZE);  // div by 20. means 5%, of course
   double minRange = 0.1;
   double maxRange = 1;
   double range = (maxRange - minRange);
   for (r = 0; r < smallPercent; r++)
   {
      randRow = int(rand() % MAT_SIZE);
      randCol = int(rand() % MAT_SIZE);
      randFrac = minRange + (range * rand()) / (RAND_MAX + 1.0);
      matDyn[randRow][randCol] = float(randFrac);
   }

   // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);

   startTime = clock();  // ------------------ start
   matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
   stopTime = clock();  // ---------------------- stop

   matShowDyn(matDynAns, MAT_SIZE - 10, 10);
   //cout.precision(4);
   cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   // clean up
   for (r = 0; r < MAT_SIZE; r++) {
      delete[] matDyn[r];
      delete[] matDynAns[r];
   }
   cout << endl;

   ////Test for partB, stack matrix
   //cout << "-------------Test for partB--------------" << endl;
   //SpMat test(MAT_SIZE, MAT_SIZE), testAns(MAT_SIZE, MAT_SIZE);
   //test.set(0, 0, 1);
   //test.set(1, 1, 2);
   //test.set(2, 2, 3);
   //cout << "-----------test matrix-------" << endl;
   //test.showSubSquare(0, 3);
   //testAns.matMult(test, test);
   //cout << "-----------testAns matrix----" << endl;
   //testAns.showSubSquare(0, 3);

   //SpMat MatA(MAT_SIZE, MAT_SIZE), MatAns(MAT_SIZE, MAT_SIZE);

   ////For hard coding
   ////MatA.set(0, 0, 1);
   ////MatA.set(1, 1, 2);
   ////MatA.set(2, 2, 3);

   //int randRow2, randCol2;
   //double randNum;
   //double minRange = 0.1;
   //double maxRange = 1;
   //double range = (maxRange - minRange);
   ////smallPercent = int(MAT_SIZE / 20. * MAT_SIZE);
   //smallPercent = 5;
   //for (r = 0; r < smallPercent; r++)
   //{
   //   randRow2 = int(rand() % MAT_SIZE);
   //   randCol2 = int(rand() % MAT_SIZE);
   //   randNum = minRange + (range * rand()) / (RAND_MAX + 1.0);
   //   MatA.set(randRow2, randCol2, randNum);
   //}

   //// 10x10 submatrix in lower right
   //cout << "-------------MatA matrix------------" << endl;
   //MatA.showSubSquare(MAT_SIZE - 10, 10);
   //startTime = clock();  // ------------------ start
   //MatAns.matMult(MatA, MatA);
   //stopTime = clock();  // ---------------------- stop

   //MatAns.showSubSquare(MAT_SIZE - 10, 10);
   //cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
   //   << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
   //   << " seconds." << endl << endl;

}

/*-----------------------------Ouput--------------------------------
Question to answer:
1.What was the smallest M that gave you a non-zero time?

A: 100

2.What happened when you doubled M , tripled it, quadrupled it, etc?
Give several M values and their times in a table.

Size      Time(Run1)   Time(Run2)
46        0.001        0.00
92        0.006        0.00
100       0.00         0.01
138       0.019        0.02
184       0.020        0.04
200       0.06         0.04
230       0.048        0.06
250       0.07         0.50
276       0.085        0.07
300       0.10         0.12
322       0.120        0.15
400       0.26         0.26
460       0.380        0.40
506       0.600        0.58
552       0.750        0.78
600       1.13         1.14    
800       3.53         3.48
920       6.300        7.19
1000      9.31         9.02
1380      28.00        27.92
2000      93.26        93.46
4600      too long for waiting

When we double the M, the time should be increase time * 8. for 200, If we
double it to 400. 0.04 * 8 = 0.32. 400 time is 0.26, the number is small, so
the time is faster. Tripe it, the increase time should be time * 3^3= 27. 
we got 1.13, 1.13 / 0.04 = 28.25. really close, quadrupled it, time  * 4^3=64.
should be 0.04 * 64 = 2.56, which kind of different compare to 3.53, because
the increase growth rate, so the time is costing longer.

3.How large an M can you use before the program refuses to run
(exception or run-time error due to memory overload) or it takes
so long you can't wait for the run?

A:I put 4600 after I test 460, and I took really long to show the result,
so I didn't wait for that. When the size is 16120, the code won't work by
showing only "Press any key to continue . . .". According to my computer
memory. I have a 8 GB RAM, and a float cost 4 bytes. so my computer can take 
8 +10e9 byte, and 2 + 10e9 float. If I square root the 2+10e9. I get 44721.359.
Therefore, mycomputer can take a maximum 44721 x 44721 matrix. The reason I 
got 16120 for maximum, because my windows only allow visual studio to use that
much memeories.

4.How did the data agree or disagree with your original time complexity estimate?

A:It's disagree with my idea because I miscalculated the time complexity in
the beginning. The time complexity is n^3. With a increase grow rate if the
number getting higher. We can see in 230 testing, I got the time with 0.048.
if I double the time to 460. my time is 0.048 * 8= 0.384, which is really close
to 460 time 0.380. Another example is 250, the time is 0.07. 0.07 * 8 = 0.56. 
which really close to 506 time, 0.58. Another thing we can be sure this is n^3 
because we have 3 for loop together in the matMultDyn function. so that make
the big O to n^3. However, we can also see the grow rate is also increasing
in 276. The time is 0.085. 0.085 * 8 = 0.68. In 552, the time is 0.75. The time
start increasing. In 1000, the time is 9.31. 9.31 *8 = 74.48. but in 2000,
I got the time 93.26. 93.26-74.48 = 18.78. Almost 20 sec more, so that 
concluded the grow rate increase more when the number is bigger.

0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.90  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


0.53  0.84  0.58  1.35  1.22  1.79  0.08  0.00  0.21  1.17
0.74  0.44  0.00  0.45  0.12  0.73  0.75  1.29  0.81  0.65
1.59  0.47  1.52  0.67  0.06  0.17  0.00  0.20  0.58  0.25
0.97  0.41  1.59  2.62  0.25  0.23  0.52  1.15  0.58  1.51
0.35  0.73  0.88  0.06  0.00  0.00  0.35  0.41  0.22  0.52
0.34  0.93  1.11  0.00  1.18  1.23  0.00  0.66  0.96  0.23
1.98  0.34  1.60  1.63  0.34  0.75  1.47  0.16  0.75  0.87
1.66  0.95  0.63  0.53  0.59  0.25  0.13  1.20  0.80  2.30
0.86  0.31  0.29  1.05  0.40  1.26  0.36  0.63  0.48  1.27
0.26  0.71  0.98  0.54  0.24  1.54  1.21  0.03  0.38  0.50



Size = 920 Dyn Array Mult Elapsed Time: 6.22 seconds.


Press any key to continue . . .


PartB Questions to Answer:
1.Are the times longer or shorter than for dynamic matrices?

A. It took longer, I tried to generate random number and put in random spot as
I do in partA. When the code reach to the clock part. I have to wait for a
long time, so I use hard code to set the value.

2 & 3

Size      Time
46        too long to wait
100       too long to wait

4.What was the largest M you could use here, and was the reason the same 
or different than for dynamic arrays?

A: I define 1000000 as the size, dynamic one programming stop running,
but the stack one is running

0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.90  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00
0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


0.53  0.84  0.58  1.35  1.22  1.79  0.08  0.00  0.21  1.17
0.74  0.44  0.00  0.45  0.12  0.73  0.75  1.29  0.81  0.65
1.59  0.47  1.52  0.67  0.06  0.17  0.00  0.20  0.58  0.25
0.97  0.41  1.59  2.62  0.25  0.23  0.52  1.15  0.58  1.51
0.35  0.73  0.88  0.06  0.00  0.00  0.35  0.41  0.22  0.52
0.34  0.93  1.11  0.00  1.18  1.23  0.00  0.66  0.96  0.23
1.98  0.34  1.60  1.63  0.34  0.75  1.47  0.16  0.75  0.87
1.66  0.95  0.63  0.53  0.59  0.25  0.13  1.20  0.80  2.30
0.86  0.31  0.29  1.05  0.40  1.26  0.36  0.63  0.48  1.27
0.26  0.71  0.98  0.54  0.24  1.54  1.21  0.03  0.38  0.50



Size = 920 Dyn Array Mult Elapsed Time: 5.84 seconds.


-------------Test for partB--------------
-----------test matrix-------
1.00 0.00 0.00
0.00 2.00 0.00
0.00 0.00 3.00


-----------testAns matrix----
1.00 0.00 0.00
0.00 4.00 0.00
0.00 0.00 9.00


-------------MatA matrix------------
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
0.00 0.00 1.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.97 0.00 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.15 0.00 0.00 0.00 0.00
0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00

*/