#pragma once

template <class T>
struct Tree {
	T _data;

	Tree* _leftBranch;
	Tree* _rightBranch;
};

template <class T>
void CreateNode(Tree<T>*& root) {
	root = new Tree<T>();

	root->_leftBranch = NULL;
	root->_rightBranch = NULL;
}

template <class T>
void InsertData(Tree<T>*& root, T value) {
	if (root == NULL) {
		CreateNode(root);
		root->_data = value;
		return;
	}

	if (root->_data > value)
		InsertData(root->_leftBranch, value);
	else if (root->_data < value)
		InsertData(root->_rightBranch, value);
	else if (root->_data == value)
		std::cout << "\nRepeat\n";
}

template <class T>
void PrintData(Tree<T>*& root) {
	if (root == NULL)
		return;
	PrintData(root->_leftBranch);
	std::cout << root->_data << "   ";
	PrintData(root->_rightBranch);
}

template <class T>
Tree<T>* FindData(Tree<T>*& root, T value) {
	if (root == NULL)
		return NULL;
	if (root->_data > value)
		FindData(root->_leftBranch, value);
	else if (root->_data < value)
		FindData(root->_rightBranch, value);
	else if (root->_data == value)
		return root;
}

template <class T>
bool FindDataBool(Tree<T>*& root, T value) {
	return FindData(root, value) == NULL ? false : true;
}

template <class T>
bool EraseData(Tree<T>*& root, T value) {
	if (root == NULL)
		return false;
	if (root->_data > value)
		return EraseData(root->_leftBranch, value);
	else if (root->_data < value)
		return EraseData(root->_rightBranch, value);

	if (root == NULL)
		return false;

	if (root->_leftBranch == NULL && root->_rightBranch == NULL) {
		root = NULL;
	}
	else if (root->_leftBranch == NULL && root->_rightBranch != NULL) {
		auto tmp = root;
		root = root->_rightBranch;
		delete(tmp);
	}
	else if (root->_leftBranch != NULL && root->_rightBranch == NULL) {
		auto tmp = root;
		root = root->_leftBranch;
		delete(tmp);
	}
	else {
		Tree<T>* tmp = root->_leftBranch;

		if (tmp->_leftBranch == NULL && tmp->_rightBranch == NULL) {
			root->_data = tmp->_data;
			delete(tmp);
			root->_leftBranch = NULL;
		}
		else {
			while (tmp->_rightBranch->_rightBranch != NULL) {
				tmp = tmp->_rightBranch;
			}
			root->_data = tmp->_rightBranch->_data;
			delete(tmp->_rightBranch);
			tmp->_rightBranch = NULL;
		}
	}

	return true;
}

template <class T>
bool ComprareTree(Tree<T>*& lhs, Tree<T>*& rhs) {
	if (lhs == NULL || rhs == NULL)
		return false;

	return lhs->_data == rhs->_data && ComprareTree(lhs->_leftBranch, rhs->_leftBranch) &&
									   ComprareTree(lhs->_rightBranch, rhs->_rightBranch);
}

// descending 
template <class T>
void RootLeftRight(Tree<T>*& root) {
	if (root == NULL)
		return;

	std::cout << root->_data << "   ";

	PrintData(root->_leftBranch);
	PrintData(root->_rightBranch);
}

// ascending
template <class T>
void LeftRightRoot(Tree<T>*& root) {
	if (root == NULL)
		return;

	PrintData(root->_leftBranch);
	PrintData(root->_rightBranch);
	std::cout << root->_data << "   ";

}
template <class T>
void Mix(Tree<T>*& root) {
	if (root == NULL)
		return;
	PrintData(root->_leftBranch);
	std::cout << root->_data << "   ";
	PrintData(root->_rightBranch);
}

template <class T>
Tree<T>* Search(Tree<T>*& root, T key) {

	if (!root || root->_data == key) {
		return root;
	}
	if (root->_data > key)
		return Search(root->_leftBranch, key);
	return Search(root->_rightBranch, key);

}