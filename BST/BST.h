#ifndef BST_H
#define BST_H
using namespace std;

class Data {
public:
	int dataI;
	char dataC;
};

class Leaf {
public:
	Data* data;
	Leaf* parent;
	Leaf* left;
	Leaf* right;

	Leaf() {
		data = nullptr;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

};

class Tree {
	Leaf* start;
	int size;
	int idctr;

	Tree() {
		start = nullptr;
		size = 0;
		idctr = 0;
	}
};




#endif // !BST_H
