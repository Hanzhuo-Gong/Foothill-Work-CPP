// File FHsplayTree.h
// Template definitions for FHsplayTree.

#ifndef SPLAYTREE_H
#define SPLAYTREE_H
#include "FHsearch_tree.h"

// ---------------------- SplayTreeNode --------------------------
template <class Comparable>
class SplayTreeNode : public FHs_treeNode<Comparable>
{
public:
	SplayTreeNode(const Comparable &d, SplayTreeNode *lftChild, 
		SplayTreeNode *rtChild, int ht = 0)
		: FHs_treeNode<Comparable>(d, lftChild, rtChild), height(ht)
	{ }

	int height;

	int getHeight() const { return height; }
	bool setHeight(int height);
};

template <class Comparable>
bool SplayTreeNode<Comparable>::setHeight(int height)
{
	if (height < -1)
		return false;
	this->height = height;
	return true;
}

//--------------------------Splay Tree Prototype-----------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable>
{
public:
	bool insert(const Comparable &x);
	bool remove(const Comparable &x);
	bool contains(const Comparable &x);
	const Comparable &find(const Comparable &x);
	const Comparable &showRoot();

protected:
	void splay(FHs_treeNode<Comparable> *& root, const Comparable &x);
	void rotateWithLeftChild(FHs_treeNode<Comparable> * & k2);
	void rotateWithRightChild(FHs_treeNode<Comparable> * & k2);
};

//------------------------Splay Tree Definition------------------------
//Insert Node into the splay tree
template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable &x) {

	//If the tree empty
	if (this->mRoot == NULL) {
		this->mRoot = new FHs_treeNode<Comparable>(x, NULL, NULL);
		this->mSize++;
		return true;
	}

	//Bring x to the top
	splay(this->mRoot, x);

	FHs_treeNode<Comparable> *newNode;

	if (x < this->mRoot->data) {
		newNode = new FHs_treeNode<Comparable>(x, this->mRoot->lftChild,
			this->mRoot);
		this->mRoot->lftChild = NULL;
		this->mRoot = newNode;
		this->mSize++;
	}

	else if (this->mRoot->data < x) {
		newNode = new FHs_treeNode<Comparable>(x, this->mRoot, 
			this->mRoot->rtChild);
		this->mRoot->rtChild = NULL;
		this->mRoot = newNode;
		this->mSize++;
	}
	else
		return false;

	return true;
}

//Remove node from the splay tree
template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable & x) {
	FHs_treeNode<Comparable> *newRoot;

	//If the tree is empty
	if (this->mRoot == NULL)
		return false;

	//Bring x to the top
	splay(this->mRoot, x);

	//If the remove node not equal to root, x node not exist in tree
	if (this->mRoot->data < x || x < this->mRoot->data)
		return false;

	//find the maximum of the left child to become the new root
	if (this->mRoot->lftChild != NULL) {
		newRoot = this->mRoot->lftChild;
		splay(newRoot, x);
		newRoot->rtChild = this->mRoot->rtChild;
	}
	//If there's no left child, right child become the new root
	else {
		newRoot = this->mRoot->rtChild;
	}

	delete this->mRoot;
	this->mRoot = newRoot;
	this->mSize--;
	return true;
}

//Check if the tree contain certain node
template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable &x) {
	try
	{
		find(x);
		return true;
	}
	catch (typename FHsearch_tree<Comparable>::NotFoundException())
	{
		return false;
	}
}

//Find certain node in the tree
template <class Comparable>
const Comparable &FHsplayTree<Comparable>::find(const Comparable &x) {

	//If the tree is empty
	if (this->mRoot == NULL)
		throw typename FHsearch_tree<Comparable>::NotFoundException();

	//Bring x to the top
	splay(this->mRoot, x);

	//If the node value doesn't match with new root x, node not found in tree
	if (this->mRoot->data < x || x < this->mRoot->data)
		throw typename FHsearch_tree<Comparable>::NotFoundException();

	return this->mRoot->data;
}

//Show the root of the splay tree
template <class Comparable>
const Comparable &FHsplayTree<Comparable>::showRoot() {
	if (this->mRoot == NULL) {	
		return Comparable();
	}
	else {
		return this->mRoot->data;
	}
}

//Method to splay the x to become the new root
template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root,
	const Comparable &x) {

	FHs_treeNode<Comparable> *leftRoot = NULL;
	FHs_treeNode<Comparable> *rightRoot = NULL;
	FHs_treeNode<Comparable> *leftTreeMax = NULL;
	FHs_treeNode<Comparable> *rightTreeMin = NULL;

	while (root != NULL) {

		//If x less than root data
		if (x < root->data) {
			if (root->lftChild == NULL) {
				break;
			}

			//zig-zig
			if (x < root->lftChild->data) {
				rotateWithLeftChild(root);
				if (root->lftChild == NULL) {
					break;
				}
			}

			if (rightRoot == NULL)
				rightRoot = root;
			else
				rightTreeMin->lftChild = root;
			rightTreeMin = root;

			root = root->lftChild;
		}
		else if (root->data < x) {
			if (root->rtChild == NULL)
				break;

			//zig-zig
			if (root->rtChild->data < x) {
				rotateWithRightChild(root);
				if (root->rtChild == NULL)
					break;
			}

			if (leftRoot == NULL)
				leftRoot = root;
			else
				leftTreeMax->rtChild = root;
			leftTreeMax = root;

			root = root->rtChild;
		}
		else
			break;
	}

	//If x has child, insert the left to leftMax and right to rightMin
	if (leftRoot != NULL) {
		leftTreeMax->rtChild = root->lftChild;
		root->lftChild = leftRoot;
	}
	if (rightRoot != NULL) {
		rightTreeMin->lftChild = root->rtChild;
		root->rtChild = rightRoot;
	}

	return;
}

//Rotate to the left
template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(
	FHs_treeNode<Comparable> * & k2) {
	FHs_treeNode<Comparable> *k1 = k2->lftChild;
	k2->lftChild = k1->rtChild;
	k1->rtChild = k2;
	k2 = k1;
}

//Rotate to the right
template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(
	FHs_treeNode<Comparable> * & k2) {
	FHs_treeNode<Comparable> *k1 = k2->rtChild;
	k2->rtChild = k1->lftChild;
	k1->lftChild = k2;
	k2 = k1;
}


#endif // !SPLAYTREE_H