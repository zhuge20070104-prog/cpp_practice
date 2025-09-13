#ifndef _FREDIRC_BOOST_ITERATOR_FACADE_HPP_
#define _FREDIRC_BOOST_ITERATOR_FACADE_HPP_

#include <string>
#include <iostream>
#include <boost/iterator/iterator_facade.hpp>

// 单链表及其迭代器类实现

template <typename T>
struct Node {
    T value;
    Node<T>* next {nullptr};
    Node(T const& value_): value(value_) {}
};

template <typename T> 
struct List{
    Node<T>* head{nullptr};

    Node<T>* current{nullptr};

    void add(T value) {
        if(!head) {
            head =new Node<T>(value);
            current = head;
        } else {
            Node<T>* tmp = new Node<T>(value);
            current->next = tmp;
            current = current->next;
        }
    } 

    ~List() {
        std::cout << "Release list...\n";
        current = head;
        while(current) {
            delete current;
            current = current->next;
        } 
    }

    struct Iterator: public boost::iterator_facade<Iterator, Node<T>, boost::forward_traversal_tag> {
   
        Node<T>* current {nullptr};
        Iterator() {}
        Iterator(Node<T>* current_): current(current_) {}

        friend class boost::iterator_core_access;

        void increment() {
            current = current->next;
        }

        bool equal(Iterator const& other) const {
            return current == other.current;
        }

        Node<T>& dereference() const {
            return *current;
        }
    };

    Iterator end()  const {
        return Iterator();
    }

    Iterator begin() const {
        return Iterator(head);
    }        
};

using string_list = List<std::string>;
using string_list_iterator =  List<std::string>::Iterator;
#endif