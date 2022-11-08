#ifndef BST_H
#define BST_H
using namespace std;

class Data {
public:
	int dataInt;
	char dataChar;

	Data() {

	}

	Data(const Data& data) {
		dataInt = data.dataInt;
		dataChar = data.dataChar;
	}

	bool operator < (const Data& compare) {
		if (dataInt < compare.dataInt) return true;
		else if (dataInt == compare.dataInt && dataChar < compare.dataChar) return true;
		else return false;
	};

	bool operator == (const Data& compare) {
		if (dataInt == compare.dataInt && dataChar == compare.dataChar) return true;
		else return false;
	}

	bool operator > (const Data& compare) {
		if (dataInt > compare.dataInt) return true;
		else if (dataInt == compare.dataInt && dataChar > compare.dataChar) return true;
		else return false;
	}
};

class Leaf {
public:
	int id;
	Data* leafData;
	Leaf* parent;
	Leaf* left;
	Leaf* right;

	Leaf() {
		id = NULL;
		leafData = nullptr;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	Leaf(Data data, int counter) {
		id = counter;
		leafData = new Data(data);
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	Leaf(const Leaf& leaf) {
		id = leaf.id;
		leafData = leaf.leafData;
		parent = leaf.parent;
		left = leaf.left;
		right = leaf.right;
	}


	bool addCompare(Data a, Data b) {
		if (a.dataInt < b.dataInt) return true;
		else if (a.dataInt == b.dataInt) {
			return a.dataChar < b.dataChar;
		}
		else return false;
	}

	

	bool createLeaf(Data data, int counter) {
		while (true) {
			if (addCompare(data, *this->leafData)) {
				if (this->left) {
					this->left->createLeaf(data, counter);
					break;
				}
				else {
					this->left = new Leaf(data, counter);
					this->left->parent = this;
					break;
				}
			}
			else if (addCompare(*this->leafData, data)) {
				if (this->right) {
					this->right->createLeaf(data, counter);
					break;
				}
				else {
					this->right = new Leaf(data, counter);
					this->right->parent = this;
					break;
				}
			}
			else {
				return true;
			};
		}
	}

};

class Tree {
private:
	Leaf* root;
	int size;
	int idctr;
	
public:
	Leaf* memory;
	Tree() {
		root = nullptr;
		size = 0;
		idctr = 0;
		memory = nullptr;
	}

	bool create(Leaf& root, Data data, int counter) {
		return root.createLeaf(data, counter);
	}

	void add(Data);
	void search(Data);
	void del();
	void pre();
	void in();
	void clean();
	void height();
	void to_string();
};

void Tree::add(Data data) {
	if (!root) {
		root = new Leaf(data, idctr);
		idctr++;
		size++;
	}
	else
	{
		if (create(*root, data, idctr) != true) {
			idctr++;
			size++;
		}
	}
}

void Tree::search(Data data) {
	bool flag = false;
	Leaf curent = *root;
	while ((&curent != nullptr) && flag == false) {

		if (*curent.leafData == data) flag = true;
		else if (*curent.leafData < data) curent = *curent.right;
		else curent = *curent.left;
	}
	memory = new Leaf(curent);
};

#endif // !BST_H
