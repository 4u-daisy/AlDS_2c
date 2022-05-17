#include <vector>
#include <string>
#include <thread>

#pragma once

template <class T>
class Set {
private:

	struct Tree {
		T _data;
		int height;

		Tree* _leftBranch;
		Tree* _rightBranch;
	};

	Tree* _tree;

	int Height(Tree* root) const {
		if (root == NULL)
			return 0;

		int hLeft = Height(root->_leftBranch);
		int hRight = Height(root->_rightBranch);
		if (hLeft > hRight)
			return hLeft + 1;
		return hRight + 1;
	}

	Tree* SmallLeftRotate(Tree* root) {
		Tree* rightSubtree, * rightSubtreeLeftSubtree;
		rightSubtree = root->_rightBranch;
		rightSubtreeLeftSubtree = rightSubtree->_leftBranch;

		rightSubtree->_leftBranch = root;
		root->_rightBranch = rightSubtreeLeftSubtree;
		root = rightSubtree;

		return root;
	}
	Tree* SmallRightRotate(Tree* root) {
		Tree* leftSubtree, * leftSubtreeRightSubtree;
		leftSubtree = root->_leftBranch;
		leftSubtreeRightSubtree = leftSubtree->_rightBranch;

		leftSubtree->_rightBranch = root;
		root->_leftBranch = leftSubtreeRightSubtree;
		root = leftSubtree;

		return root;
	}

	int BalansFactor(Tree* root) const
	{
		return Height(root->_rightBranch) - Height(root->_leftBranch);
	}

	Tree* BalanserTree(Tree* root) {
		if (root == NULL)
			return NULL;
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

	Tree* InsertRecursion(Tree* root, T value) {
		if (root == NULL) {
			root = new Tree;
			root->_data = value;
			root->height = 0;
			root->_leftBranch = NULL;
			root->_rightBranch = NULL;
			return root;
		}

		if (root->_data > value)
			root->_leftBranch = InsertRecursion(root->_leftBranch, value);

		else if (root->_data < value)
			root->_rightBranch = InsertRecursion(root->_rightBranch, value);

		else if (root->_data == value)
			throw std::logic_error("Repeat Data");

		return BalanserTree(root);
	}

	void PrintRecursion(Tree* root) const {
		if (root == NULL)
			return;
		PrintRecursion(root->_leftBranch);
		std::cout << root->_data << "   ";
		PrintRecursion(root->_rightBranch);
	}
	Tree* FindDataRecursion(Tree* root, T value) const {
		if (root == NULL)
			return NULL;
		if (root->_data > value) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			return FindDataRecursion(root->_leftBranch, value);
		}
		else if (root->_data < value) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			return FindDataRecursion(root->_rightBranch, value);
		}
		else if (root->_data == value) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			return root;
		}
	}
	bool FindDataBoolRecursion(Tree* root, T value) const {
		return FindDataRecursion(root, value) == NULL ? false : true;
	}

	bool EraseData(Tree*& root, T value) {
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
			Tree* tmp = root->_leftBranch;

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

		root = BalanserTree(root);
		return true;
	}

	void f(Tree* tree, std::vector<std::vector<std::string>>& v, int i, int max) const {
		if (i == max)
			return;

		if (tree == NULL) {
			v[i].push_back("NULL");
			return;
		}

		std::string y = std::to_string(tree->_data);

		v[i].push_back(y);

		f(tree->_leftBranch, v, i + 1, max);
		f(tree->_rightBranch, v, i + 1, max);

		i--;
	}
	void print(int i, std::vector<std::vector<std::string>>& v) const {
		for (size_t j = 0; j < v[i].size(); j++) {
			std::cout << v[i][j] << "	";
		}
		std::cout << '\n';
	}

	void DeleteRecursion(Tree* root) {
		if (root == NULL)
			return;
		if (root->_leftBranch)
			DeleteRecursion(root->_leftBranch);
		if (root->_rightBranch)
			DeleteRecursion(root->_rightBranch);
		delete(root);
	}

	void Copy(Tree* lhs, Tree*& rhs) {
		if (lhs == NULL)
			return;
		rhs = new Tree(*lhs);
		rhs->_leftBranch = NULL;
		rhs->_rightBranch = NULL;

		Copy(lhs->_leftBranch, rhs->_leftBranch);
		Copy(lhs->_rightBranch, rhs->_rightBranch);
	}

public:

	Set() {
		_tree = NULL;
	}
	Set(const Set& rhs) {
		this->operator=(rhs);
	}

	~Set() {
		Delete();
	}

	void Insert(T value) {
		_tree = InsertRecursion(_tree, value);
	}

	void Print() const {
		PrintRecursion(_tree);
	}

	bool Find(T value) const {
		return FindDataBoolRecursion(_tree, value);
	}

	bool Erase(T value) {
		return EraseData(_tree, value);
	}

	void BeautifulPrint() const {
		int height = Height(_tree);
		std::vector<std::vector<std::string>> v;
		v.resize(height);
		f(_tree, v, 0, height);
		for (int i = 0; i < height; i++) {
			print(i, v);
		}

		std::cout << "\n";
	}

	void Delete() {
		DeleteRecursion(_tree);
		_tree = NULL;
	}

	void operator=(const Set& rhs) {
		Copy(rhs._tree, _tree);
	}
	void operator+(T value) {
		Insert(value);
	}
	void operator-(T value) {
		Erase(value);
	}

};

template<typename T>
std::ostream& operator<< (std::ostream& out, const Set<T>& lhs) {
	out << "meow";
	return out;
}