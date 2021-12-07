#ifndef BST_CLION_BST_H
#define BST_CLION_BST_H
using namespace std;
class Node{
public:
    int value;
    //int sign;
    Node* parent;
    Node* left;
    Node* right;

    Node(int data, Node* parentPtr){
        value = data;
        parent = parentPtr;
        left = nullptr;
        right = nullptr;
    }
};

class Tree{
private:
    int size;
    Node* root;
public:
    Tree(){
        size = 0;
        root = nullptr;
    }
    ~Tree(){
    }

    void add(int);
    Node* search(int);
    void deleteSearched(Node*);
    void pre_order();
    void in_order();
    int height();
};

void Tree::add(int data) {
    if (root == nullptr){
        Node* newNode = new Node(data, nullptr);
        root = newNode;
        size++;
    }
    else{
        Node* ptr = root;
        bool flag = false;
        while (!flag){
            if (data < ptr->value && ptr->left == nullptr){
                Node* newNode = new Node(data, ptr);
                ptr->left = newNode;
                flag = true;
                size++;
            }else if (data >= ptr->value && ptr->right == nullptr){
                Node* newNode = new Node(data, ptr);
                ptr->right = newNode;
                flag = true;
                size++;
            }else if (data < ptr->value){
                ptr = ptr->left;
            }else if (data >= ptr->value){
                ptr = ptr->right;
            }
        }
    }
}
Node* Tree::search(int data) {
    if (root == nullptr){
        return nullptr;
    }else{
        Node* ptr = root;
        while (true){
            if (data == ptr->value){
                return ptr;
            }else if ((data < ptr->value && ptr->left == nullptr)||(data > ptr->value && ptr->right == nullptr)){
                return nullptr;
            }else if (data < ptr->value){
                ptr = ptr->left;
            }else if (data > ptr->value){
                ptr = ptr->right;
            }
        }
    }
}
void Tree::deleteSearched(Node* nodePtr) {
    if (nodePtr == nullptr){}
    else{
        Node* node = nodePtr;
        if (node->left == nullptr && node->right == nullptr && node == root){
            root = nullptr;
        }else if (node->left == nullptr && node->right == nullptr){
            if (node == node->parent->left) node->parent->left = nullptr;
            else if (node == node->parent->right) node->parent->right = nullptr;
        }else if (node->left == nullptr){
            if (node == node->parent->left){
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }else if (node == node->parent->right){
                node->parent->right = node->right;
                node->right->parent = node->parent;
            }
        }else if (node->right == nullptr){
            if (node == node->parent->left){
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }else if (node == node->parent->right){
                node->parent->right = node->left;
                node->left->parent = node->parent;
            }
        }else{
            if (node == node->parent->left){
                Node* deletedNode = node;
                node = node->left;
                while (node->right != nullptr) node = node->right;
                node->parent->right = node->left;
                node->left->parent = node->parent;
                deletedNode->parent->left = node;
                node->parent = deletedNode->parent;


            }
        }
        delete node;
        size--;
    }
}
#endif //BST_CLION_BST_H
