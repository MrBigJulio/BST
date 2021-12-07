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
void Tree::deleteSearched(Node* node) {
    if (node == nullptr){}
    else{
        if (node->left == nullptr && node->right == nullptr && node == root){
            root = nullptr;
            delete node;
        }else if (node->left == nullptr && node->right == nullptr){
            if (node == node->parent->left) node->parent->left = nullptr;
            else if (node == node->parent->right) node->parent->right = nullptr;
            delete node;
        }else if (node->left == nullptr){
            if (node == node->parent->left){
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }else if (node == node->parent->right){
                node->parent->right = node->right;
                node->right->parent = node->parent;
            }
            delete node;
        }else if (node->right == nullptr){
            if (node == node->parent->left){
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }else if (node == node->parent->right){
                node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            delete node;
        }else{
            if (node == node->parent->left){
                Node* deletedNode = node;
                node = node->left;
                if(node->right == nullptr){
                    deletedNode->parent->left = node;
                    node->parent = deletedNode->parent;
                    deletedNode->right->parent = node;
                    node->right = deletedNode->left;
                }else{
                    while (node->right != nullptr) node = node->right;
                    node->parent->right = node->left;
                    node->left->parent = node->parent;
                    deletedNode->parent->left = node;
                    node->parent = deletedNode->parent;
                    deletedNode->left->parent = node;
                    node->left = deletedNode->left;
                    deletedNode->right->parent = node;
                    node->right = deletedNode->right;
                }
                delete deletedNode;
            }else if(node == node->parent->right){
                Node* deletedNode = node;
                node = node->right;
                if(node->left == nullptr){
                    deletedNode->parent->right = node;
                    node->parent = deletedNode->parent;
                    deletedNode->left->parent = node;
                    node->left = deletedNode->left;
                }else{
                    while (node->left != nullptr) node = node->left;
                    node->parent->left = node->right;
                    node->right->parent = node->parent;
                    deletedNode->parent->right = node;
                    node->parent = deletedNode->parent;
                    deletedNode->right->parent = node;
                    node->right = deletedNode->right;
                    deletedNode->left->parent = node;
                    node->left = deletedNode->left;
                }
                delete deletedNode;
            }else if(node == root){
                Node* deletedNode = node;
                node = node->right;
                if(node->left == nullptr){
                    deletedNode->left->parent = node;
                    node->left = deletedNode->left;
                }else {
                    while (node->left != nullptr) node = node->left;
                    node->parent->left = node->right;
                    node->right->parent = node->parent;
                    deletedNode->right->parent = node;
                    node->right = deletedNode->right;
                    deletedNode->left->parent = node;
                    node->left = deletedNode->left;
                }
                delete deletedNode;
            }
        }
        size--;
    }
}
#endif //BST_CLION_BST_H
