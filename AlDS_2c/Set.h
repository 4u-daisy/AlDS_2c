#include "Tree.h"

#pragma once

template <class T>
class Set {
private:
	Tree<T>* _tree;

public:
	Set() {
		_tree = NULL;
	}
	~Set() {
		delete(_tree);
	}

	void Insert(T value) {
		InsertData(_tree, value);
	}

	void prinit(Tree<T>* root) const {
		if (root != NULL) {
			prinit(root->_leftBranch);
			std::cout << root->_data << "	";
			prinit(root->_rightBranch);
		}
	}

	void Print() const {
		prinit(_tree);
	}

	bool Erase(T value) {
		return EraseData(_tree, value);
	}

	Tree<T>* FindData(Tree<T>*& root, T value) const {
		if (root == NULL)
			return NULL;
		if (root->_data > value)
			FindData(root->_leftBranch, value);
		else if (root->_data < value)
			FindData(root->_rightBranch, value);
		else if (root->_data == value)
			return root;
	}

	bool Find(T value) {
		return FindData(_tree, value) == NULL ? false : true;
	}


};