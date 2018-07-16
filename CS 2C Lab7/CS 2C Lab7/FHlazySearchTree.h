// File FHlazySearchTree.h
// Template definitions for FHsearchTrees, which are general trees
#ifndef FHSEARCHTREE_H
#define FHSEARCHTREE_H

// ---------------------- FHlazySearchTreeNode Prototype --------------------------
template <class Comparable>
class FHlazySearchTreeNode
{
public:
	FHlazySearchTreeNode(const Comparable & d = Comparable(),
		FHlazySearchTreeNode *lt = NULL,
		FHlazySearchTreeNode *rt = NULL, bool deleted = false)
		: lftChild(lt), rtChild(rt), data(d)
	{ }

	FHlazySearchTreeNode *lftChild, *rtChild;
	Comparable data;
	bool deleted;

	// for use only with AVL Trees
	virtual int getHeight() const { return 0; }
	virtual bool setHeight(int height) { return true; }
};

// ---------------------- FHlazySearchTree Prototype --------------------------
template <class Comparable>
class FHlazySearchTree
{
protected:
	int mSize;
	int mSizeHard;
	FHlazySearchTreeNode<Comparable> *mRoot;

public:
	FHlazySearchTree() { mSize = 0; mRoot = NULL; }
	FHlazySearchTree(const FHlazySearchTree &rhs)
	{
		mRoot = NULL; mSize = 0; *this = rhs;
	}
	~FHlazySearchTree() { clear(); }

	const Comparable &findMin() const;
	const Comparable &findMax() const;
	const Comparable &find(const Comparable &x) const;

	bool empty() const { return (mSize == 0); }
	int size() const { return mSize; }
	int sizeHard() const { return mSizeHard; }
	void clear() { makeEmpty(mRoot); }
	const FHlazySearchTree & operator=(const FHlazySearchTree &rhs);

	bool insert(const Comparable &x);
	bool remove(const Comparable &x);
	bool contains(const Comparable &x) const { return find(mRoot, x) != NULL; }
	void collectGarbage() { collectGarbage(mRoot); }

	template <class Processor>
	void traverse(Processor func) const { traverse(mRoot, func); }
	int showHeight() const { return findHeight(mRoot); }

protected:
	FHlazySearchTreeNode<Comparable> *clone(FHlazySearchTreeNode<Comparable> *root) const;
	FHlazySearchTreeNode<Comparable> *findMin(FHlazySearchTreeNode<Comparable> *root) const;
	FHlazySearchTreeNode<Comparable> *findMax(FHlazySearchTreeNode<Comparable> *root) const;
	FHlazySearchTreeNode<Comparable> *find(FHlazySearchTreeNode<Comparable> *root,
		const Comparable &x) const;
	FHlazySearchTreeNode<Comparable> *findMinHard(FHlazySearchTreeNode<Comparable> *root) const;
	FHlazySearchTreeNode<Comparable> *findMaxHard(FHlazySearchTreeNode<Comparable> *root) const;
	bool insert(FHlazySearchTreeNode<Comparable> * &root,
		const Comparable &x);
	bool remove(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x);
	bool removeHard(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x);;
	
	void makeEmpty(FHlazySearchTreeNode<Comparable> * &subtreeToDelete);
	template <class Processor>
	void traverse(FHlazySearchTreeNode<Comparable> *treeNode,
		Processor func, int level = -1) const;
	int findHeight(FHlazySearchTreeNode<Comparable> *treeNode, int height = -1) const;
	void collectGarbage(FHlazySearchTreeNode<Comparable> * &root);

public:
	// for exception throwing
	class EmptyTreeException {};
	class NotFoundException {};
};

// FHlazySearchTree public method definitions -----------------------------
//Find the minimum value of the tree
template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMin() const
{
	FHlazySearchTreeNode<Comparable> *minNode = findMin(mRoot);
	//If not found the minimum, throw exception
	if (minNode == NULL)
		throw NotFoundException();

	return minNode->data;
}

//Find the maximum value of the tree
template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMax() const
{
	FHlazySearchTreeNode<Comparable> *maxNode = findMax(mRoot);
	//If not found the maximum, throw exception
	if (maxNode == NULL)
		throw NotFoundException();

	return maxNode->data;
}

template <class Comparable>
const Comparable &FHlazySearchTree<Comparable>::find(
	const Comparable &x) const
{
	FHlazySearchTreeNode<Comparable> *result = find(mRoot, x);
	//If not found the node, throw exception
	if (result == NULL)
		throw NotFoundException();
	return result->data;
}

template <class Comparable>
const FHlazySearchTree<Comparable> &FHlazySearchTree<Comparable>::operator=
(const FHlazySearchTree &rhs)
{
	if (&rhs != this)
	{
		clear();
		mRoot = clone(rhs.mRoot);
		mSize = rhs.size();
		mSizeHard = rhs.sizeHard();
	}
	return *this;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(const Comparable &x)
{
	if (insert(mRoot, x))
	{
		mSize++;
		return true;
	}
	return false;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(const Comparable &x)
{
	if (remove(mRoot, x))
	{
		mSize--;
		return true;
	}
	return false;
}

template <class Comparable>
template <class Processor>
void FHlazySearchTree<Comparable>::traverse(FHlazySearchTreeNode<Comparable>
	*treeNode, Processor func, int level) const
{
	if (treeNode == NULL)
		return;
	// we're not doing anything with level but its there in case we want it
	traverse(treeNode->lftChild, func, level + 1);
	if (!treeNode->deleted) {
		func(treeNode->data);
	}
	traverse(treeNode->rtChild, func, level + 1);
}

//remove all nodes that marked delete
template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage
(FHlazySearchTreeNode<Comparable> * &treeNode) {
	if (mRoot == NULL)
		return;
	if (treeNode == NULL)
		return;

	collectGarbage(treeNode->lftChild);
	collectGarbage(treeNode->rtChild);
	if (treeNode->deleted) {
		removeHard(treeNode, treeNode->data);
	}
}

// FHlazySearchTree private method definitions -----------------------------
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::clone(
	FHlazySearchTreeNode<Comparable> *root) const
{
	FHlazySearchTreeNode<Comparable> *newNode;
	if (root == NULL)
		return NULL;

	newNode = new FHlazySearchTreeNode<Comparable>(
		root->data,
		clone(root->lftChild), clone(root->rtChild));
	newNode->deleted = root->deleted;
	return newNode;
}

//Find the minimum that not mark as deleted
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMin(
	FHlazySearchTreeNode<Comparable> *root) const
{
	//If empty tree, return
	if (root == NULL)
		return NULL;

	FHlazySearchTreeNode<Comparable> *minNode = findMin(root->lftChild);
	//If the left child is not mark as delete, return the child node
	if (minNode != NULL)
		return minNode;

	//If all the left child marked as delete, return min of the right
	if (root->deleted)
		return findMin(root->rtChild);
	else
		return root;
}

//Find the min which includes the deleted one
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMinHard(
	FHlazySearchTreeNode<Comparable> *root) const {
	if (root == NULL)
		return NULL;
	if (root->lftChild == NULL)
		return root;
	return findMinHard(root->lftChild);
}

//Find the maximum that not mark as deleted
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMax(
	FHlazySearchTreeNode<Comparable> *root) const
{
	//If empty tree, return
	if (root == NULL)
		return NULL;

	FHlazySearchTreeNode<Comparable> *maxNode = findMax(root->rtChild);
	//If the right child is not mark as delete, return the child node
	if (maxNode != NULL)
		return maxNode;

	//If all the right child marked as delete, return max of the left
	if (root->deleted)
		return findMax(root->lftChild);
	else
		return root;
}

//Find the max which includes the deleted one
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMaxHard(
	FHlazySearchTreeNode<Comparable> *root) const {
	if (root == NULL)
		return NULL;
	if (root->rtChild == NULL)
		return root;
	return findMaxHard(root->rtChild);
}

//Find the number what we assign for
template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::find(
	FHlazySearchTreeNode<Comparable> *root, const Comparable &x) const
{
	//empty tree
	if (root == NULL)
		return NULL;

	if (x < root->data)
		return find(root->lftChild, x);
	if (root->data < x)
		return find(root->rtChild, x);

	if (!root->deleted)
		return root;
	else
		return NULL;
}

//Insert Data
template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(
	FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
	//If empty tree
	if (root == NULL) 
	{
		root = new FHlazySearchTreeNode<Comparable>(x, NULL, NULL);
		mSizeHard++;
		return true;
	}
	else if (x < root->data)
		return insert(root->lftChild, x);
	else if (root->data < x)
		return insert(root->rtChild, x);
	else if (root->deleted)
	{
		root->deleted = false;
		return true;
	}
	
	return false; // duplicate
}

//Helper method for the collectGarbage
template <class Comparable>
bool FHlazySearchTree<Comparable>::removeHard(
	FHlazySearchTreeNode<Comparable> * &root, const Comparable &x) {
	//empty tree
	if (root == NULL)
		return false;

	//x is small than root, go to the left
	if (x < root->data)
		return removeHard(root->lftChild, x);

	//x is greater than root, go to the right
	if (root->data < x)
		return removeHard(root->rtChild, x);

	//node found
	if (root->lftChild != NULL && root->rtChild != NULL) {
		FHlazySearchTreeNode<Comparable> *minNode = findMinHard(root->rtChild);
		root->data = minNode->data;
		root->deleted = minNode->deleted;
		minNode->deleted = true;
		removeHard(root->rtChild, minNode->data);
	}
	else {
		FHlazySearchTreeNode<Comparable> *nodeToRemove = root;
		if (root->lftChild != NULL) {
			root = root->lftChild;
		}
		else {
			root = root->rtChild;
		}
		delete nodeToRemove;
		mSizeHard--;
	}
	return true;
}

//remove for lazy delete
template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(
	FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
	if (root == NULL)
		return false;

	if (x < root->data)
		return remove(root->lftChild, x);
	if (root->data < x)
		return remove(root->rtChild, x);

	if (!root->deleted) {
		root->deleted = true;
		return true;
	}
	else
		return false;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::makeEmpty(
	FHlazySearchTreeNode<Comparable> * &subtreeToDelete)
{
	if (subtreeToDelete == NULL)
		return;

	// remove children
	makeEmpty(subtreeToDelete->lftChild);
	makeEmpty(subtreeToDelete->rtChild);

	// clear client's pointer
	if (!subtreeToDelete->deleted) {
		mSize--;
	}
	delete subtreeToDelete;
	subtreeToDelete = NULL;
}

template <class Comparable>
int FHlazySearchTree<Comparable>::findHeight(FHlazySearchTreeNode<Comparable>
	*treeNode, int height) const
{
	int leftHeight, rightHeight;

	if (treeNode == NULL)
		return height;
	height++;
	leftHeight = findHeight(treeNode->lftChild, height);
	rightHeight = findHeight(treeNode->rtChild, height);
	return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}
#endif

