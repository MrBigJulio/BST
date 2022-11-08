#ifndef BST_H
#define BST_H
using namespace std;

class Data {
public:
	int dataI;
	char dataC;

	Data() {

	}

	Data(const Data& d) {
		dataI = d.dataI;
		dataC = d.dataC;
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

	Leaf(Data d, int ctr) {
		id = ctr;
		leafData = new Data(d);
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	
	bool compare(Data a, Data b) {
		if (a.dataI < b.dataI) return true;
		else if (a.dataI == b.dataI) {
			return a.dataC < b.dataC;
		}
		else return false;
	}

	void create(Data d, int ctr) {
		while (true) {
			if (compare(d, *this->leafData)) {
				if (this->left) {
					this->left->create(d, ctr);
					break;
				}
				else {
					this->left = new Leaf(d, ctr);
					this->left->parent = this;
					break;
				}
			}
			else if (compare(*this->leafData, d)) {
				if (this->right) {
					this->right->create(d, ctr);
					break;
				}
				else {
					this->right = new Leaf(d, ctr);
					this->right->parent = this;
					break;
				}
			}
			else break;
		}
	}

};

class Tree {
private:
	Leaf* root;
	int size;
	int idctr;

public:

	Tree() {
		root = nullptr;
		size = 0;
		idctr = 0;
	}

	void add(Data);
	void search();
	void del();
	void pre();
	void in();
	void clean();
	void height();
	void to_string();
};

void Tree::add(Data d) {
	if (!root) {
		root = new Leaf(d, idctr);
		idctr++;
		size++;
	}
	else
	{
		root->create(d, idctr);
		idctr++;
		size++;
	}
}

#endif // !BST_H
