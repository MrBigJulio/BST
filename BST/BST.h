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

	void delNoKids() {

	}

	void delSingleKid() {

	}


	void add(Data);
	Leaf* search(Data);
	void del(Leaf*);
	void preorder();
	void inorder();
	void clean();
	void height();
	void to_string();
};

void Tree::add(Data data) {
	if (!this->root) {
		this->root = new Leaf(data, idctr++);
		size++;
	}
	else {
		Leaf *start = this->root;
		bool flag = true;
		while (flag) {
			if (data < *start->leafData) {
				if (start->left) {
					start = start->left;
				}
				else {
					start->left = new Leaf(data, idctr++);
					start->left->parent = start;
					flag = false;
					size++;
				}
			}
			else if (*start->leafData < data) {
				if (start->right) {
					start = start->right;
				}
				else {
					start->right = new Leaf(data, idctr++);
					start->right->parent = start;
					flag = false;
					size++;
				}
			}
			else {
				flag = false;
			};
		}
	}
}

Leaf* Tree::search(Data data) {
	if (*root->leafData == data) return root;
	else {
		bool flag = false;
		Leaf start = *this->root;
		Leaf* current = &start;
		while ((current != nullptr) && flag == false) {
			if (*current->leafData == data) flag = true;
			else if (*current->leafData < data) current = current->right;
			else current = current->left;
		}
		return current;
	}
}

void Tree::del(Leaf *deleted) {
	if (deleted) {
		if (deleted == root) {
			if (deleted->left == nullptr && deleted->right == nullptr) {
				root = nullptr;
				delete deleted;
				size--;
			}
			else if (deleted->right == nullptr) {
				deleted->left->parent = nullptr;
				root = deleted->left;
				delete deleted;
				size--;
			}
			else if (deleted->left == nullptr) {
				deleted->right->parent = nullptr;
				root = deleted->right;
				delete deleted;
				size--;
			}
			else {
				if (deleted->left->right == nullptr) {
					deleted->left->parent = nullptr;
					deleted->left->right = deleted->right;
					if (deleted->right) deleted->right->parent = deleted->left;
					root = deleted->left;
					delete deleted;
					size--;
				}
				else {
					Leaf* current = deleted->left;
					while(current->right != nullptr) {
						current = current->right;
					}
					current->parent->right = current->left;
					current->left->parent = current->parent;
					deleted->leafData = current->leafData;
					deleted->id = current->id;
					delete current;
					size--;
				}
			}
			
		}
		else {
			if (deleted->left == nullptr && deleted->right == nullptr) {
				if (deleted == deleted->parent->left) {
					deleted->parent->left = nullptr;
				}
				else if(deleted == deleted->parent->right) {
					deleted->parent->right = nullptr;
				}
				delete deleted;
				size--;
			}
			else if (deleted->right == nullptr) {
				if (deleted == deleted->parent->left) {
					deleted->parent->left = deleted->left;
				}
				else if (deleted == deleted->parent->right) {
					deleted->parent->right = deleted->left;
				}
				deleted->left->parent = deleted->parent;
				delete deleted;
				size--;
			}
			else if (deleted->left == nullptr) {
				if (deleted == deleted->parent->left) {
					deleted->parent->left = deleted->right;
				}
				else if (deleted == deleted->parent->right) {
					deleted->parent->right = deleted->right;
				}
				deleted->right->parent = deleted->parent;
				delete deleted;
				size--;
			}
			else {
				if (deleted == deleted->parent->left) {
					if (deleted->left->right == nullptr) {
						deleted->left->parent = deleted->parent;
						deleted->left->right = deleted->right;
						if(deleted->right) deleted->right->parent = deleted->left;
						delete deleted;
						size--;
					}
					else {
						Leaf* current = deleted->left;
						while (current->right != nullptr) {
							current = current->right;
						}
						current->parent->right = current->left;
						current->left->parent = current->parent;
						deleted->leafData = current->leafData;
						deleted->id = current->id;
						delete current;
						size--;
					}
				}
				else if (deleted == deleted->parent->right) {
					if (deleted->right->left == nullptr) {
						deleted->right->parent = deleted->parent;
						deleted->right->left = deleted->left;
						if (deleted->left) deleted->left->parent = deleted->right;
						delete deleted;
						size--;
					}
					else {
						Leaf* current = deleted->right;
						while (current->left != nullptr) {
							current = current->left;
						}
						current->parent->left = current->right;
						current->right->parent = current->parent;
						deleted->leafData = current->leafData;
						deleted->id = current->id;
						delete current;
						size--;
					}
				}
			}
		}
	}
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
