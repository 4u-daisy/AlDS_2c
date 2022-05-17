#pragma once
template <class T>
struct Tree {
	T _data;
	int height;

	Tree* _leftBranch;
	Tree* _rightBranch;
};

template <class T>
Tree<T>* CreateNode(Tree<T>* root) {
	root = new Tree<T>();

	root->height = 0;
	root->_leftBranch = NULL;
	root->_rightBranch = NULL;

	return root;
}

template <class T>
int Height(Tree<T>* root) {
	if (root == NULL) return 0;

	int hLeft = Height(root->_leftBranch);
	int hRight = Height(root->_rightBranch);
	if (hLeft > hRight)
		return hLeft + 1;
	return hRight + 1;
}

template <class T>
Tree<T>* SmallLeftRotate(Tree<T>* root) {
	//Tree<T>* tmp = root->_rightBranch;
	//root->_rightBranch = tmp->_leftBranch;
	//tmp->_leftBranch = root;

	Tree<T>* rightSubtree, * rightSubtreeLeftSubtree;
	rightSubtree = root->_rightBranch;
	rightSubtreeLeftSubtree = rightSubtree->_leftBranch;

	rightSubtree->_leftBranch = root;
	root->_rightBranch = rightSubtreeLeftSubtree;
	root = rightSubtree;

	return root;
}

template <class T>
Tree<T>* SmallRightRotate(Tree<T>* root) {
	//Tree<T>* tmp = root->_leftBranch;
	//root->_leftBranch = tmp->_rightBranch;
	//tmp->_rightBranch = root;

	Tree<T>* leftSubtree, * leftSubtreeRightSubtree;
	leftSubtree = root->_leftBranch;
	leftSubtreeRightSubtree = leftSubtree->_rightBranch;

	leftSubtree->_rightBranch = root;
	root->_leftBranch = leftSubtreeRightSubtree;
	root = leftSubtree;

	return root;
}

template <class T>
int BalansFactor(Tree<T>* root)
{
	return Height(root->_rightBranch) - Height(root->_leftBranch);
}

template <class T>
Tree<T>* BalanserTree(Tree<T>* root) {

	int balansFactor = BalansFactor(root);

	if (balansFactor == 2) {
		if (BalansFactor(root->_rightBranch) < 0)
			root->_rightBranch = SmallRightRotate(root->_rightBranch);
		root = SmallLeftRotate(root);
	}
	if (balansFactor == -2) {
		if (BalansFactor(root->_leftBranch) > 0)
			root->_leftBranch = SmallLeftRotate(root->_leftBranch);
		root = SmallRightRotate(root);
	}
	return root;
}

template <class T>
Tree<T>* InsertData(Tree<T>* root, T value) {
	if (root == NULL) {
		root = new Tree<T>();
		root->_data = value;
		root->_leftBranch = NULL;
		root->_rightBranch = NULL;
		return root;
	}

	if (root->_data > value)
		root->_leftBranch = InsertData(root->_leftBranch, value);

	else if (root->_data < value)
		root->_rightBranch = InsertData(root->_rightBranch, value);

	else if (root->_data == value)
		throw std::logic_error("Repeat Data");

	return BalanserTree(root);
}

template <class T>
void PrintData(Tree<T>* root) {
	if (root == NULL)
		return;
	PrintData(root->_leftBranch);
	std::cout << root->_data << "   ";
	PrintData(root->_rightBranch);
}

//template <class T>
//Tree<T>* FindData(Tree<T>*& root, T value) {
//	if (root == NULL)
//		return NULL;
//	if (root->_data > value)
//		FindData(root->_leftBranch, value);
//	else if (root->_data < value)
//		FindData(root->_rightBranch, value);
//	else if (root->_data == value)
//		return root;
//}

template <class T>
Tree<T>* FindData(Tree<T>* root, T value) {
	if (root == NULL)
		return NULL;

	if (root->_data > value)
		return FindData(root->_leftBranch, value);
	else if (root->_data < value)
		return FindData(root->_rightBranch, value);
	else if (root->_data == value)
		return root;
}

template <class T>
bool FindDataBool(Tree<T>* root, T value) {
	return FindData(root, value) == NULL ? false : true;
}

