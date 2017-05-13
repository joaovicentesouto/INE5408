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
        Node* left_{nullptr};
        Node* right_{nullptr};

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

        /*! Sem o uso de uma segunda função
        bool remove(const T& data) {
            // Go to left
            if (data < data_) {
                if (left_ != nullptr)
                    return left_->remove(data);
                return false;
            }
            // Go to right
            if (data > data_) {
                if (right_ != nullptr)
                    return right_->remove(data);
                return false;
            }
            // I found
            // Two sons
            if (right_ != nullptr && left_ != nullptr) {
                data_ = right_->minimum()->data_;
                return right_->remove(data_);
            }
            // One son or leaf
            if (right_ != nullptr) {
                data_ = right_->data_;
                if (right_->right_ != nullptr || right_->left_ != nullptr)
                    return right_->remove(data_);
                // Son is a leaf
                delete right_;
                right_ = nullptr;
                return true;
            } else {
                data_ = left_->data_;
                if (left_->right_ != nullptr || left_->left_ != nullptr)
                    return left_->remove(data_);
                // Son is a leaf
                delete left_;
                left_ = nullptr;
                return true;
            }
            // PROBLEMA SE FOR FOLHA, NÃO CONSEGUE DELETAR A SI MESMA
        } */

        //! uso dos slides
        bool remove(const T& data) {
            bool deleted = false;
            if (data < data_ && left_ != nullptr)
                left_ = remove(data, left_, deleted);
            else if (data > data_ && right_ != nullptr)
                right_ = remove(data, right_, deleted);
            return deleted;
        }

        //! metodo removeção dos slides
        Node* remove(const T& data, Node* arv, bool& deleted) {
            deleted = false;
            if (arv == nullptr)
                return arv;

            // Go to left
            if (data < arv->data_) {
                arv->left_ = remove(data, arv->left_, deleted);
                return arv;
            }
            // Go to right
            if (data > arv->data_) {
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            // I found
            // Two sons
            if (arv->right_ != nullptr && arv->left_ != nullptr) {
                Node* temp = arv->right_->minimum();
                arv->data_ = temp->data_;
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            // One son or leaf
            Node* temp = nullptr;
            if (arv->right_ != nullptr)
                temp = arv->right_;
            else
                temp = arv->left_;

            delete arv;
            deleted = true;
            return temp;
        }

        //! Doc
        bool contains(const T& data) const {
            if (data < data_)
                return left_ == nullptr? false : left_->contains(data);
            else if (data > data_)
                return right_ == nullptr? false : right_->contains(data);
            else
                return true;
        }

        //! Doc
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            left_->pre_order(v);
            right_->pre_order(v);
        }

        //! Doc
        void in_order(ArrayList<T>& v) const {
            left_->in_order(v);
            v.push_back(data_);
            right_->in_order(v);
        }

        //! Doc
        void post_order(ArrayList<T>& v) const {
            left_->post_order(v);
            right_->post_order(v);
            v.push_back(data_);
        }

     private:
        //! Doc
        Node* minimum() {
            if (right_ == nullptr)
                return this;
            return right_->minimum();
        }
    };

    //! Doc
    //  Node* minimum(Node* arv);

    Node* root_{nullptr};
    std::size_t size_{0};
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
    if (empty()) {
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
void BinaryTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree!");

    if (size() != 1u) {
        if (root_->remove(data))
            --size_;
    } else {
        // If the root to delete and no sons
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            --size_;
        }
    }
}

//! Doc
template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Doc
template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Doc
template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Doc
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size()};
    if (empty())
        return v;
    root_->pre_order(v);
    return v;
}

//! Doc
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size()};
    if (empty())
        return v;
    root_->in_order(v);
    return v;
}

//! Doc
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size()};
    if (empty())
        return v;
    root_->post_order(v);
    return v;
}

/* metodo removeção dos slides
        Node* remove(const T& data, Node* arv) {
            if (arv == nullptr)
                return arv;
            // Go to left
            if (data < arv->data_) {
                arv->left_ = remove(data, arv->left_);
                return arv;
            }
            // Go to right
            if (data > arv->data_) {
                arv->right_ = remove(data, arv->right_);
                return arv;
            }
            // I found
            // Two sons
            if (arv->right_ != nullptr && arv->left_ != nullptr) {
                Node* temp = arv->right_->minimum();
                arv->data_ = temp->data_;
                arv->right_ = remove(data, arv->right_);
                return arv;
            }
            // One son or leaf
            Node* temp = nullptr;
            if (arv->right_ != nullptr)
                temp = arv->right_;
            else
                temp = arv->left_;

            delete arv;
            return temp;
        }
*/
}  // namespace structures

#endif
