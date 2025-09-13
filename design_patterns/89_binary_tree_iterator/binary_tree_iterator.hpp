#ifndef _FREDIRC_BINARY_TREE_ITERATOR_HPP_
#define _FREDIRC_BINARY_TREE_ITERATOR_HPP_

template <typename T>
struct BinaryTree;

template <typename T>
struct Node {
    T value {};

    Node<T>* left{nullptr}, *right{nullptr}, *parent{nullptr};

    BinaryTree<T>* tree{nullptr};

    Node(T value_): value(value_) {}

    Node(T value_, Node<T>* left_, Node<T>* right_):
        value(value_), left(left_), right(right_) {
        // 初始化左子节点和右子节点的树为同一棵树
        this->left->tree = this->right->tree = tree;
        // 初始化左子节点和右子节点的父节点为当前节点
        this->left->parent = this->right->parent = this; 
    }

    void setTree(BinaryTree<T>* t) {
        tree = t;
        if(left) left->tree = t;
        if(right) right->tree = t;
    }
    
    ~Node() {
        if(left) delete left;
        if(right) delete right;
    }
};


template <typename T>
struct BinaryTree {
    Node<T>* root {nullptr};

    BinaryTree(Node<T>* root_):
        root(root_) {
            root->setTree(this);
        }
    
    ~BinaryTree() {
        if(root) {
            delete root;
        }
    }

    // 中序遍历迭代器
    template <typename U> 
    struct MidOrderIterator: public std::iterator<std::forward_iterator_tag, Node<U>>{
        Node<U>* current;

        MidOrderIterator(Node<U>* current_): current(current_) {}
        
        bool operator==(MidOrderIterator const& other) {
            return current == other.current;
        }
        // ++ 操作符重载
        MidOrderIterator<U> operator++() {
            // 如果有右子树，就先转到右子树，然后一直寻找他的左子树
            if(current->right) {
                current = current->right;
                while(current->left) {
                    current = current->left;
                }
            } else {
                // 如果往上走，发现当前节点是右子树，
                // 则一直往上走，直到发现当前节点是p的左子树或者根节点为止
                auto p = current->parent;
                while(p && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() {
            return *current;
        }
    };

    using iterator = MidOrderIterator<T>;

    iterator begin() {
        Node<T>* n = root;
        if(n) {
            while(n->left) {
                n = n->left; 
            }
        }

        return iterator{n};
    }

    iterator end() {
        return iterator{nullptr};
    }
    

};
#endif