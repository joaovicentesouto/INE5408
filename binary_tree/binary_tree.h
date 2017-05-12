//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "array_list.h"

namespace structures {

//! Doc
template<typename T>
class BinaryTree {
 public:
    BinaryTree();
    ~BinaryTree();

    void insert(const T& data);
    void remove(const T& data);
    bool contains(const T& data) const;

    bool empty() const;
    std::size_t size() const;

    ArrayList<T> pre_order() const;
    ArrayList<T> in_order() const;
    ArrayList<T> post_order() const;

 private:
    //! Doc
    struct Node {
        explicit Node(const T& data) :
        data_{data}
        {}

        T data_;
        Node* left_;
        Node* right_;

        //! Doc
        void insert(const T& data) {
            if (data < data_) {
                if (left_ == nullptr) {
                    left_ = new Node(data);
                    if (left_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    left_->insert(data);
                }
            } else {
                if (right_ == nullptr) {
                    right_ = new Node(data);
                    if (right_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    right_->insert(data);
                }
            }
        }

        //! Doc
        bool remove(const T& data_);

        //! Doc
        bool contains(const T& data_) const;

        //! Doc
        void pre_order(ArrayList<T>& v) const;

        //! Doc
        void in_order(ArrayList<T>& v) const;

        //! Doc
        void post_order(ArrayList<T>& v) const;
    };

    Node* root_;
    std::size_t size_;
};

//! Doc
template<typename T>
BinaryTree<T>::BinaryTree()
{}

//! Doc
template<typename T>
BinaryTree<T>::~BinaryTree()
{}

//! Doc
template<typename T>
void BinaryTree<T>::insert(const T& data) {
    if (root_ == nullptr) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("Full tree!");
    } else {
        root_->insert(data);
    }
    ++size_;
}

//! Doc
template<typename T>
void BinaryTree<T>::remove(const T& data);

//! Doc
template<typename T>
bool BinaryTree<T>::contains(const T& data) const;

//! Doc
template<typename T>
bool BinaryTree<T>::empty() const;

//! Doc
template<typename T>
std::size_t BinaryTree<T>::size() const;

//! Doc
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const;

//! Doc
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const;

//! Doc
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const;

}  // namespace structures

#endif
