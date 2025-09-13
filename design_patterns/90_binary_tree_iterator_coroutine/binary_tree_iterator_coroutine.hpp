#ifndef _FREDIRC_BINARY_TREE_ITERATOR_COROUTINE_HPP_
#define _FREDIRC_BINARY_TREE_ITERATOR_COROUTINE_HPP_

#include <boost/coroutine2/all.hpp>
#include <string>

template <typename T>
using coroutine = boost::coroutines2::coroutine<T>;

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

   
};

template <class T>
void post_order(typename coroutine<Node<T>*>::push_type& sink, Node<T>* node) { 
    if(node->left) {    
        post_order<T>(sink, node->left); 
    }   
    if(node->right) { 
        post_order<T>(sink, node->right); 
    } 
    sink(node); 
} 

using cort_string_node = coroutine<Node<std::string>*>;

#endif