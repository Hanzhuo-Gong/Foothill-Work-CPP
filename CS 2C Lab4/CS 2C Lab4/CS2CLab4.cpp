// CS 2C Lab4.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <stack>
#include "FHlazySearchTree.h"
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

int main()
{
   int k;
   FHlazySearchTree<int> searchTree, testTree;
   PrintObject<int> intPrinter;

   //searchTree.traverse(intPrinter);
   //testTree.traverse(intPrinter);

   ////Test for find the min and max and find in a empty tree
   //cout << "-------------------Test for empty tree----------------" << endl;
   //try { cout << "Min is:" << testTree.findMin() << endl; }
   //catch (FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "can't find the min in this tree" << endl;
   //}

   //try { cout << "Min is:" << testTree.findMax() << endl; }
   //catch (FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "can't find the max in this tree" << endl;
   //}

   //try { cout << "found:" << testTree.find(30) << endl; }
   //catch (FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "Node 30 is not found" << endl;
   //}

   //cout << "-----------------Test for remove in empty tree---------" << endl;
   //if (testTree.remove(60))
   //	cout << "60 has been removed from the tree" << endl;
   //else
   //	cout << "60 is not in the tree, unable to remove, please check back" << endl;
   //testTree.remove(3);
   //cout << "testTree size: " << testTree.size() << endl;
   //cout << "testTree hard size: " << testTree.sizeHard() << endl;
   //testTree.traverse(intPrinter);

   //cout << "--------------Test for insert in empty tree---------------" << endl;
   //testTree.insert(40);
   //testTree.insert(50);
   //cout << "testTree size: " << testTree.size() << endl;
   //cout << "testTree hard size: " << testTree.sizeHard() << endl;
   //testTree.traverse(intPrinter);

   //cout << "\n--------------Test for remove in empty tree-------------" << endl;
   //testTree.remove(40);
   //testTree.remove(40);
   //testTree.remove(50);
   //cout << "testTree size: " << testTree.size() << endl;
   //cout << "testTree hard size: " << testTree.sizeHard() << endl;
   //try { cout << "Min is:" << testTree.findMin() << endl; }
   //catch (FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "can't find the min in this tree" << endl;
   //}

   //try { cout << "Min is:" << testTree.findMax() << endl; }
   //catch (FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "can't find the max in this tree" << endl;
   //}
   //testTree.traverse(intPrinter);

   //testTree.collectGarbage();
   //cout << "testTree size: " << testTree.size() << endl;
   //cout << "testTree hard size: " << testTree.sizeHard() << endl;


   //cout << "\ninitial size: " << searchTree.size() << endl;
   //searchTree.insert(50);
   //searchTree.insert(20);
   //searchTree.insert(30);
   //searchTree.insert(70);
   //searchTree.insert(10);
   //searchTree.insert(60);

   //cout << "After populating -- traversal and sizes: \n";
   //searchTree.traverse(intPrinter);
   //cout << "\ntree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //try { cout << "Min is:" << searchTree.findMin() << endl; }
   //catch(FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "can't find the min in this tree" << endl;
   //}
   //cout << "Max is:" << searchTree.findMax() << endl;

   //try { cout << "found:" << searchTree.find(30) << endl;}
   //catch(FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "Node 30 is not found" << endl;
   //}

   //try { cout << "found:" << searchTree.find(120) << endl; }
   //catch (FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "Node 120 is not found" << endl;
   //}

   //cout << "Collecting garbage on new tree - should be no garbage." << endl;
   //searchTree.collectGarbage();
   //cout << "tree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //// test assignment operator
   //FHlazySearchTree<int> searchTree2 = searchTree;

   //cout << "\n\nAttempting 1 removal: \n";
   //if (searchTree.remove(20))
   //	cout << "removed " << 20 << endl;
   //cout << "tree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //cout << "Collecting Garbage - should clean 1 item. " << endl;
   //searchTree.collectGarbage();
   //cout << "tree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //cout << "Collecting Garbage again - no change expected. " << endl;
   //searchTree.collectGarbage();
   //cout << "tree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //// test soft insertion and deletion:

   //cout << "Adding 'hard' 22 - should see new sizes. " << endl;
   //searchTree.insert(22);
   //searchTree.traverse(intPrinter);
   //cout << "\ntree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //cout << "\nAfter soft removal. " << endl;
   //searchTree.remove(22);
   //searchTree.traverse(intPrinter);
   //cout << "\ntree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //cout << "Repeating soft removal. Should see no change. " << endl;
   //searchTree.remove(22);
   //searchTree.traverse(intPrinter);
   //cout << "\ntree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //cout << "Soft insertion. Hard size should not change. " << endl;
   //searchTree.insert(22);
   //searchTree.traverse(intPrinter);
   //cout << "\ntree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //cout << "\n\nAttempting 100 removals: \n";
   //for (k = 100; k > 0; k--)
   //{
   //	if (searchTree.remove(k))
   //		cout << "removed " << k << endl;
   //}
   //searchTree.collectGarbage();

   //cout << "\nsearchTree now:\n";
   //searchTree.traverse(intPrinter);
   //cout << "\ntree 1 size: " << searchTree.size()
   //	<< "  Hard size: " << searchTree.sizeHard() << endl;

   //searchTree2.insert(500);
   //searchTree2.insert(200);
   //searchTree2.insert(300);
   //searchTree2.insert(700);
   //searchTree2.insert(100);
   //searchTree2.insert(600);
   //cout << "\nsearchTree2:\n";
   //searchTree2.traverse(intPrinter);
   //cout << "\ntree 2 size: " << searchTree2.size()
   //	<< "  Hard size: " << searchTree2.sizeHard() << endl;


   cout << "------------------self testing------------------------" << endl;
   FHlazySearchTree<int> test2, test3;
   test2.insert(50);
   test2.insert(20);
   test2.insert(30);
   test2.insert(70);
   test2.insert(10);
   test2.insert(60);
   test2.insert(80);

   cout << "Before do anything to the tree:" << endl;
   test2.traverse(intPrinter);
   cout << "\ntest2 size: " << test2.size() << endl;
   cout << "test2 hard size: " << test2.sizeHard() << endl;
   cout << "test2 min: " << test2.findMin() << endl;
   cout << "test2 max: " << test2.findMax() << endl;

   cout << "\nAfter do something to the tree:" << endl;
   ////-------------Test for remove two times------------------
   //test2.remove(10);
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);
   //test2.remove(10);

   //cout << "\n\nNothing change, size and hard size should be the same" << endl;
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);

   //cout << "\n\ncall collectGarbage, hard size should be the same with size" 
   //	<< endl;
   //test2.collectGarbage();
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //test2.traverse(intPrinter);

   ////------------------Test for insert two times-----------------
   //test2.insert(45);
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);

   //cout << "\n\nInsert again, nothing should happened" << endl;
   //test2.insert(45);
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);

   ////-----------------Test for find min after deleting all left child--------
   //test2.remove(10);
   //test2.remove(20);
   //test2.remove(30);
   //test2.remove(50);
   //test2.collectGarbage();
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);

   ////----------------Test for find max after deleting all right child---------
   //test2.remove(80);
   //test2.remove(70);
   //test2.remove(60);
   //test2.remove(50);
   //test2.collectGarbage();
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);

   ////-----------------Test for remove unexist node-------------------
   //if (test2.remove(1))
   //	cout << "1 has been removed from test2." << endl;
   //else
   //	cout << "1 is not found in test2, unable to remove," 
   //	<<" please check back."<< endl;
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.collectGarbage();
   //test2.traverse(intPrinter);
   //cout << "\n" <<endl;

   //if (test2.remove(20))
   //	cout << "20 has been removed from test2." << endl;
   //else
   //	cout << "20 is not found in test2, unable to remove,"
   //	<< " please check back." << endl;
   //test2.collectGarbage();
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);

   ////-------------------Test for operator =-------------------
   //test2.remove(30);
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);

   //cout << "\n\nAssign test3 equal to test2:" << endl;
   //test3 = test2;
   //cout << "test3 size: " << test3.size() << endl;
   //cout << "test3 hard size: " << test3.sizeHard() << endl;
   //cout << "test3 min: " << test3.findMin() << endl;
   //cout << "test3 max: " << test3.findMax() << endl;
   //test3.traverse(intPrinter);

   //cout << "\n\nAfter calling collectGarbage for test2:" << endl;
   //test2.collectGarbage();
   //cout << "test2 size: " << test2.size() << endl;
   //cout << "test2 hard size: " << test2.sizeHard() << endl;
   //cout << "test2 min: " << test2.findMin() << endl;
   //cout << "test2 max: " << test2.findMax() << endl;
   //test2.traverse(intPrinter);

   //cout << "\n\nAssign test3 equal to test2 again:" << endl;
   //test3 = test2;
   //cout << "test3 size: " << test3.size() << endl;
   //cout << "test3 hard size: " << test3.sizeHard() << endl;
   //cout << "test3 min: " << test3.findMin() << endl;
   //cout << "test3 max: " << test3.findMax() << endl;
   //test3.traverse(intPrinter);

   ////Test for remove and insert the same node before calling collectGarbage
   test2.remove(20);
   cout << "test2 size: " << test2.size() << endl;
   cout << "test2 hard size: " << test2.sizeHard() << endl;
   cout << "test2 min: " << test2.findMin() << endl;
   cout << "test2 max: " << test2.findMax() << endl;
   test2.traverse(intPrinter);

   cout << "\n\n---------Insert back the node--------------" << endl;
   test2.insert(20);
   cout << "test2 size: " << test2.size() << endl;
   cout << "test2 hard size: " << test2.sizeHard() << endl;
   cout << "test2 min: " << test2.findMin() << endl;
   cout << "test2 max: " << test2.findMax() << endl;
   test2.traverse(intPrinter);

   cout << "\n\nCalling collectGarbabge, nothing should change." << endl;
   test2.collectGarbage();
   cout << "test2 size: " << test2.size() << endl;
   cout << "test2 hard size: " << test2.sizeHard() << endl;
   cout << "test2 min: " << test2.findMin() << endl;
   cout << "test2 max: " << test2.findMax() << endl;
   test2.traverse(intPrinter);

   ////Test for One Node remove
   //test3.insert(5);
   //cout << "test3 size: " << test3.size() << endl;
   //cout << "test3 hard size: " << test3.sizeHard() << endl;
   //cout << "test3 min: " << test3.findMin() << endl;
   //cout << "test3 max: " << test3.findMax() << endl;
   //test3.traverse(intPrinter);

   //cout << "\n\nDelete the same node which insert" << endl;
   //test3.remove(5);
   //test3.collectGarbage();
   //cout << "test3 size: " << test3.size() << endl;
   //cout << "test3 hard size: " << test3.sizeHard() << endl;
   //try { cout << "Min is:" << test3.findMin() << endl; }
   //catch(FHlazySearchTree<int>::NotFoundException)
   //{
   //	cout << "can't find the min in this tree" << endl;
   //}
   //try { cout << "Max is:" << test3.findMax() << endl; }
   //catch (FHlazySearchTree<int>::NotFoundException)
   //{
   //   cout << "can't find the max in this tree" << endl;
   //}
   //test3.traverse(intPrinter);

}

/*-------------------------------output-------------------------------
-------------------Test for empty tree----------------
can't find the min in this tree
can't find the max in this tree
Node 30 is not found
-----------------Test for remove in empty tree---------
60 is not in the tree, unable to remove, please check back
testTree size: 0
testTree hard size: 0
--------------Test for insert in empty tree---------------
testTree size: 2
testTree hard size: 2
40 50
--------------Test for remove in empty tree-------------
testTree size: 0
testTree hard size: 2
can't find the min in this tree
can't find the max in this tree
testTree size: 0
testTree hard size: 0
Press any key to continue . . .


initial size: 0
After populating -- traversal and sizes:
10 20 30 50 60 70
tree 1 size: 6  Hard size: 6
Min is:10
Max is:70
found:30
Node 120 is not found
Collecting garbage on new tree - should be no garbage.
tree 1 size: 6  Hard size: 6


Attempting 1 removal:
removed 20
tree 1 size: 5  Hard size: 6
Collecting Garbage - should clean 1 item.
tree 1 size: 5  Hard size: 5
Collecting Garbage again - no change expected.
tree 1 size: 5  Hard size: 5
Adding 'hard' 22 - should see new sizes.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6

After soft removal.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Repeating soft removal. Should see no change.
10 30 50 60 70
tree 1 size: 5  Hard size: 6
Soft insertion. Hard size should not change.
10 22 30 50 60 70
tree 1 size: 6  Hard size: 6


Attempting 100 removals:
removed 70
removed 60
removed 50
removed 30
removed 22
removed 10

searchTree now:

tree 1 size: 0  Hard size: 0

searchTree2:
10 20 30 50 60 70 100 200 300 500 600 700
tree 2 size: 12  Hard size: 12
Press any key to continue . . .

------------------self testing------------------------
Before do anything to the tree:
10 20 30 50 60 70 80
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80

After do something to the tree:
test2 size: 6
test2 hard size: 7
test2 min: 20
test2 max: 80
20 30 50 60 70 80

Nothing change, size and hard size should be the same
test2 size: 6
test2 hard size: 7
test2 min: 20
test2 max: 80
20 30 50 60 70 80

call collectGarbage, hard size should be the same with size
test2 size: 6
test2 hard size: 6
20 30 50 60 70 80 Press any key to continue . . .

------------------self testing------------------------
Before do anything to the tree:
10 20 30 50 60 70 80
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80

After do something to the tree:
test2 size: 8
test2 hard size: 8
test2 min: 10
test2 max: 80
10 20 30 45 50 60 70 80

Insert again, nothing should happened
test2 size: 8
test2 hard size: 8
test2 min: 10
test2 max: 80
10 20 30 45 50 60 70 80 Press any key to continue . . .

------------------self testing------------------------
Before do anything to the tree:
10 20 30 50 60 70 80
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80

After do something to the tree:
test2 size: 3
test2 hard size: 3
test2 min: 60
test2 max: 80
60 70 80 Press any key to continue . . .

------------------self testing------------------------
Before do anything to the tree:
10 20 30 50 60 70 80
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80

After do something to the tree:
test2 size: 3
test2 hard size: 3
test2 min: 10
test2 max: 30
10 20 30 Press any key to continue . . .

------------------self testing------------------------
Before do anything to the tree:
10 20 30 50 60 70 80
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80

After do something to the tree:
1 is not found in test2, unable to remove, please check back.
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80
10 20 30 50 60 70 80

20 has been removed from test2.
test2 size: 6
test2 hard size: 6
test2 min: 10
test2 max: 80
10 30 50 60 70 80 Press any key to continue . . .

------------------self testing------------------------
Before do anything to the tree:
10 20 30 50 60 70 80
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80

After do something to the tree:
test2 size: 6
test2 hard size: 7
test2 min: 10
test2 max: 80
10 20 50 60 70 80

Assign test3 equal to test2:
test3 size: 6
test3 hard size: 7
test3 min: 10
test3 max: 80
10 20 50 60 70 80

After calling collectGarbage for test2:
test2 size: 6
test2 hard size: 6
test2 min: 10
test2 max: 80
10 20 50 60 70 80

Assign test3 equal to test2 again:
test3 size: 6
test3 hard size: 6
test3 min: 10
test3 max: 80
10 20 50 60 70 80 Press any key to continue . . .

------------------self testing------------------------
Before do anything to the tree:
10 20 30 50 60 70 80
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80

After do something to the tree:
test2 size: 6
test2 hard size: 7
test2 min: 10
test2 max: 80
10 30 50 60 70 80

---------Insert back the node--------------
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80
10 20 30 50 60 70 80

Calling collectGarbabge, nothing should change.
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80
10 20 30 50 60 70 80 Press any key to continue . . .

------------------self testing------------------------
Before do anything to the tree:
10 20 30 50 60 70 80
test2 size: 7
test2 hard size: 7
test2 min: 10
test2 max: 80

After do something to the tree:
test3 size: 1
test3 hard size: 1
test3 min: 5
test3 max: 5
5

Delete the same node which insert
test3 size: 0
test3 hard size: 0
can't find the min in this tree
can't find the max in this tree
Press any key to continue . . .
*/