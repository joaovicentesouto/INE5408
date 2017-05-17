//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "array_list.h"

namespace structures {

//! Classe Árvore binária
/*! Implementação de uma árvore binária de busca.
 *  \author João Vicente Souto.
 *  \since 13/05/17
 *  \version 1.0
 */
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
    struct Node {
        //! Construtor padrão
        /*! Inicializado com o dado.
         *  \param data dado que será armazenado.
         *  \sa ~Node()
         */
        explicit Node(const T& data) :
        data_{data}
        {}

        //! Destrutor
        /*! Destruindo os filhos, deve ser recursivo.
         *  \sa Node(const T& data)
         */
        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;  //! Dado
        Node* left_{nullptr};  //! Filho da esquerda
        Node* right_{nullptr};  //! Filho da direita

        //! Inserir
        /*! Insere o dado na árvore seguindo ordem de grandeza
         *  \param data Dado à ser inserido.
         */
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

        //! Remover padrão
        /*! Comportamento inicial de remoção, uso auxiliar de outra função.
         *  \param data Dado à ser removido.
         *  \return bool verdadeiro se foi removido com sucesso.
         *  \sa remove(const T& data, Node* arv, bool deleted)
         */
        bool remove(const T& data) {
            bool deleted = false;
            if (data < data_ && left_ != nullptr) {
                left_ = remove(data, left_, deleted);
            } else if (data > data_ && right_ != nullptr) {
                right_ = remove(data, right_, deleted);
            } else {
                if (right_ != nullptr && left_ != nullptr) {
                    Node* temp = right_->minimum();
                    data_ = temp->data_;
                    right_ = remove(data_, right_, deleted);
                } else if (right_ != nullptr) {
                    Node* temp = right_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                    deleted = true;
                } else if (left_ != nullptr) {
                    Node* temp = left_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                    deleted = true;
                }
            }
            return deleted;
        }

        //! Contém dado
        /*! Verifica se contém algum dado
         *  \param data Dado à ser procurado.
         *  \return bool verdadeiro se encontrou o dado.
         */
        bool contains(const T& data) const {
            if (data < data_)
                return left_ == nullptr? false : left_->contains(data);
            else if (data > data_)
                return right_ == nullptr? false : right_->contains(data);
            else
                return true;
        }

        //! Pré-ordem
        /*! Busca os dados em pré-ordem
         *  \param v ArrayList<T> para inserção dos dados.
         *  \sa in_order(), post_order()
         */
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        //! Em-ordem
        /*! Busca os dados em em-ordem
         *  \param v ArrayList<T> para inserção dos dados.
         *  \sa pre_order(), post_order()
         */
        void in_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->in_order(v);
            v.push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        //! Pós-ordem
        /*! Busca os dados em pós-ordem
         *  \param v ArrayList<T> para inserção dos dados.
         *  \sa in_order(), pre_order()
         */
        void post_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v.push_back(data_);
        }

     private:
        //! Complemento da funcão remover
        /*! Comportamento complementar ao remover
         *  \param data Dado à ser removido.
         *  \return Node* Node que vai ocupar lugar do antigo.
         *  \sa remove()
         */
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

            arv->right_ = arv->left_ = nullptr;
            delete arv;
            deleted = true;
            return temp;
        }

        //! Encontra o menor node
        /*! Encontra o node com menor valor em data
         *  \return Node* Node com menor valor em data
         */
        Node* minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }
    };

    Node* root_{nullptr};  //!< Raiz
    std::size_t size_{0};  //!< Tamanho
};

//! Construtor
/*! Construtor padrão
 *  \sa ~BinaryTree()
 */
template<typename T>
BinaryTree<T>::BinaryTree()
{}

//! Destrutor
/*! Destruindo a raiz, e por recursividade, os filhos;
 *  \sa BinaryTree()
 */
template<typename T>
BinaryTree<T>::~BinaryTree() {
    delete root_;
}

//! Inserir
/*! Insere o dado na árvore seguindo ordem de grandeza
 *  \param data Dado à ser inserido.
 */
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

//! Remove
/*! Remove um dado da árvore
 *  \param data Dado à ser removido.
 */
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

//! Contém dado
/*! Verifica se contém algum dado
 *  \param data Dado à ser procurado.
 *  \return bool verdadeiro se encontrou o dado.
 */
template<typename T>
bool BinaryTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Árvore vazia
/*! Verifica se a árvore esta vazia
 *  \return bool verdadeiro se estiver vazia
 */
template<typename T>
bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho da Árvore
/*! Retorna a quantidade de dados na árvore
 *  \return size_t quantidade de dados.
 */
template<typename T>
std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré-ordem
/*! Busca os dados em pré-ordem
 *  \return ArrayList<T> dados em pré-ordem
 *  \sa in_order(), post_order()
*/
template<typename T>
ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size()};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! Em-ordem
/*! Busca os dados em em-ordem
 *  \return ArrayList<T> dados em-ordem
 *  \sa pre_order(), post_order()
 */
template<typename T>
ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! Pós-ordem
/*! Busca os dados em pós-ordem
 *  \return ArrayList<T> dados em pós-ordem
 *  \sa in_order(), pre_order()
 */
template<typename T>
ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  // namespace structures

#endif
