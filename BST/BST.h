#ifndef BST_H
#define BST_H
using namespace std;

class Data {
public:
	int dataInt;
	char dataChar;

	Data() {
		dataInt = NULL;
		dataChar = NULL;
	}

	~Data() {
		dataInt = NULL;
		dataChar = NULL;
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
	
	~Leaf() {
		id = NULL;
		delete leafData;
		leafData = nullptr;
		parent = nullptr;
		left = nullptr;
		right = nullptr;

	}

	bool create(Data data, int counter) {
		bool fail = true;
		bool flag = true;
		while (flag) {
			if (data < *this->leafData) {
				if (this->left) {
					this->left->create(data, counter);
				}
				else {
					this->left = new Leaf(data, counter);
					this->left->parent = this;
				}
				flag = false;
			}
			else if (*this->leafData < data) {
				if (this->right) {
					this->right->create(data, counter);
				}
				else {
					this->right = new Leaf(data, counter);
					this->right->parent = this;
				}
				flag = false;
			}
			else {
				fail = false;
				flag = false;
			};
		}
		return fail;
	}

	void print() {
		cout << this->id << ", " << this->leafData->dataInt << ", " << this->leafData->dataChar << endl;
	}

	void info() {
		cout << "(" << this->id;
		cout << ": [p: ";
		if (this->parent) cout << this->parent->id;
		else cout << "NULL";
		cout << ", l: ";
		if (this->left) cout << this->left->id;
		else cout << "NULL";
		cout << ", r: ";
		if (this->right) cout << this->right->id;
		else cout << "NULL";
		cout << "], data : (" << this->leafData->dataInt << ", " << this->leafData->dataChar << "))" << endl;
	}

};

class Tree {
private:
	Leaf* root;
	int size;
	int idctr;
	int treeHeight;
public:
	
	Tree() {
		root = nullptr;
		size = 0;
		idctr = 0;
		treeHeight = 0;
	}

	void scanPreorder(Leaf& leaf) {
		if (&leaf != nullptr) {
			leaf.print();
			scanPreorder(*leaf.left);
			scanPreorder(*leaf.right);
		}
	}

	void scanInorder(Leaf& leaf) {
		if (&leaf != nullptr) {
			scanInorder(*leaf.left);
			leaf.print();
			scanInorder(*leaf.right);
		}
	}

	void cleanTree(Leaf& leaf) {
		if (&leaf != nullptr) {
			cleanTree(*leaf.left);
			cleanTree(*leaf.right);
			delete &leaf;
			this->size--;
		}
		this->root = nullptr;
	}

	void findHeight(Leaf& leaf, int depth, int &max) {
		if (&leaf != nullptr) {
			depth++;
			findHeight(*leaf.left, depth, max);
			findHeight(*leaf.right, depth, max);
		}
		if (depth > max) {
			max = depth--;
		}
	}

	void printInfo(Leaf& leaf) {
		if (&leaf != nullptr) {
			printInfo(*leaf.left);
			leaf.info();
			printInfo(*leaf.right);
		}
	}

	void add(Data);
	Leaf* search(Data);
	void del();
	void preorder();
	void inorder();
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
		if (root->create(data, idctr) != false) {
			idctr++;
			size++;
		}
	}
}

Leaf* Tree::search(Data data) {
	bool flag = false;
	Leaf start = *root;
	Leaf *current = &start;
	while ((current != nullptr) && flag == false) {
		if (*current->leafData == data) flag = true;
		else if (*current->leafData < data) current = current->right;
		else current = current->left;
	}
	return current;
}

void Tree::del() {

}

void Tree::preorder() {
	this->scanPreorder(*root);
}

void Tree::inorder() {
	this->scanInorder(*root);
}

void Tree::clean() {
	this->cleanTree(*root);
}

void Tree::height() {
	int depth = 0;
	int max = 0;
	int *ctr;
	ctr = &max;

	this->findHeight(*root, depth, *ctr);
	treeHeight = max;
}

void Tree::to_string() {
	cout << "Size: " << size << endl;
	this->height();
	cout << "Height: " << treeHeight << endl;
	cout << "{" << endl;
	this->printInfo(*root);
	cout << "}" << endl;
}
#endif // !BST_H
