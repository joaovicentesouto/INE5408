//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>
#include "array_list.h"

namespace structures {

//! Classe Árvore AVL
/*! Implementação de uma árvore AVL.
 *  \author João Vicente Souto.
 *  \since 17/05/17
 *  \version 1.0
 */
template<typename T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

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

        T data_;  //!< Dado
        std::size_t height_{0};  //!< Altura
        Node* left_{nullptr};  //!< Filho da esquerda
        Node* right_{nullptr};  //!< Filho da direita

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
            } else if (data == data_) {
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

        //! Atualiza altura de todos e rotaciona
        /*! Verifica e modifica a altura recursivamente e se necessário
         *  rotaciona a sub-árvore.
         */
        void updateHeight() {
            int h_left, h_right;
            if (left_ == nullptr && right_ == nullptr) {
                height_ = 0;
            } else {
                // Balança o filho da esquerda
                if (left_ != nullptr) {
                    left_->updateHeight();
                    switch (left_->type_balance()) {
                        case 0:  // balanceado
                            h_left = height(left_->left_);
                            h_right = height(left_->right_);
                            left_->height_ = std::max(h_left, h_right) + 1;
                            break;
                        case 1:  // Esquerda-esquerda
                            left_ = left_->simpleLeft();
                            break;
                        case 2:  // Esquerda-direita
                            left_ = left_->doubleLeft();
                            break;
                        case 3:  // Direita-direita
                            left_ = left_->simpleRight();
                            break;
                        case 4:  // Direita-direita
                            left_ = left_->doubleRight();
                            break;
                        default :
                            break;
                    }
                }
                if (right_ != nullptr) {
                    right_->updateHeight();
                    switch (right_->type_balance()) {
                        case 0:  // balanceado
                            h_left = height(right_->left_);
                            h_right = height(right_->right_);
                            right_->height_ = std::max(h_left, h_right) + 1;
                            break;
                        case 1:  // Esquerda-esquerda
                            right_ = right_->simpleLeft();
                            break;
                        case 2:  // Esquerda-direita
                            right_ = right_->doubleLeft();
                            break;
                        case 3:  // Direita-direita
                            right_ = right_->simpleRight();
                            break;
                        case 4:  // Direita-esquerda
                            right_ = right_->doubleRight();
                            break;
                        default :
                            break;
                    }
                }
            }
        }

        //! Tipo de balanceamento
        /*! Verifica a condição em que o node se encontra.
         *  0 : Está balanceado
         *  1 : Esquerda-esquerda
         *  2 : Esquerda-direita
         *  3 : Direita-direita
         *  4 : Direita-esquerda
         *  \return size_t tipo de balanceamento.
         */
        std::size_t type_balance() {
            if (height(left_) - height(right_) > 1) {
                if (height(left_->left_) > height(left_->right_))
                    return 1;  // esq-esq
                else
                    return 2;  // esq-dir
            } else if (height(right_) - height(left_) > 1) {
                if (height(right_->right_) > height(right_->left_))
                    return 3;  // dir-dir
                else
                    return 4;  // dir-esq
            }
            return 0;
        }

        //! Altura do node
        /*! Retorna a altura se ele não for nulo
         *  \param tnode Node* para buscar a altura
         *  \return int altura
         */
        int height(Node* tnode) {
            if (tnode == nullptr)
                return -1;
            else
                return tnode->height_;
        }

        //! Rotação simples à esquerda
        /*! Álvore desbalanceada esquerda-esquerda
         *  \return Node* nova raiz da sub-matriz
         */
        Node* simpleLeft() {
            Node* temp = left_;
            left_ = temp->right_;
            temp->right_ = this;

            height_ = std::max(height(left_), height(right_) + 1);
            temp->height_ = std::max(height(temp->left_), height(this)) + 1;

            return temp;
        }

        //! Rotação dupla à esquerda
        /*! Álvore desbalanceada esquerda-direita
         *  \return Node* nova raiz da sub-matriz
         */
        Node* simpleRight() {
            Node* temp = right_;
            right_ = temp->left_;
            temp->left_ = this;

            height_ = std::max(height(right_), height(left_) + 1);
            temp->height_ = std::max(height(temp->right_), height(this)) + 1;

            return temp;
        }

        //! Rotação simples à direita
        /*! Álvore desbalanceada direita-direita
         *  \return Node* nova raiz da sub-matriz
         */
        Node* doubleLeft() {
            left_ = left_->simpleRight();
            return this->simpleLeft();
        }

        //! Rotação dupla à direita
        /*! Álvore desbalanceada direita-esquerda
         *  \return Node* nova raiz da sub-matriz
         */
        Node* doubleRight() {
            right_ = right_->simpleLeft();
            return this->simpleRight();
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

    Node* root_{nullptr};
    std::size_t size_{0u};
};

//! Construtor
/*! Construtor padrão
 *  \sa ~AVLTree()
 */
template<typename T>
AVLTree<T>::AVLTree()
{}

//! Destrutor
/*! Destruindo a raiz, e por recursividade, os filhos;
 *  \sa AVLTree()
 */
template<typename T>
AVLTree<T>::~AVLTree() {
    delete root_;
}

//! Inserir
/*! Insere o dado na árvore seguindo ordem de grandeza
 *  \param data Dado à ser inserido.
 */
template<typename T>
void AVLTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("Full tree!");
    } else {
        root_->insert(data);
    }
    ++size_;

    int h_left, h_right;
    root_->updateHeight();
    switch (root_->type_balance()) {
        case 0:  // balanceado
            h_left = root_->height(root_->left_);
            h_right = root_->height(root_->right_);
            root_->height_ = std::max(h_left, h_right) + 1;
            break;
        case 1:  // Esquerda-esquerda
            root_ = root_->simpleLeft();
            break;
        case 2:  // Esquerda-direita
            root_ = root_->doubleLeft();
            break;
        case 3:  // Direita-direita
            root_ = root_->simpleRight();
            break;
        case 4:  // Direita-esquerda
            root_ = root_->doubleRight();
            break;
        default :
            break;
    }
}

//! Remove
/*! Remove um dado da árvore
 *  \param data Dado à ser removido.
 */
template<typename T>
void AVLTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree!");

    if (size() != 1u) {
        if (root_->remove(data)) {
            --size_;
            int h_left, h_right;
            root_->updateHeight();
            switch (root_->type_balance()) {
                case 0:  // balanceado
                    h_left = root_->height(root_->left_);
                    h_right = root_->height(root_->right_);
                    root_->height_ = std::max(h_left, h_right) + 1;
                    break;
                case 1:  // Esquerda-esquerda
                    root_ = root_->simpleLeft();
                    break;
                case 2:  // Esquerda-direita
                    root_ = root_->doubleLeft();
                    break;
                case 3:  // Direita-direita
                    root_ = root_->simpleRight();
                    break;
                case 4:  // Direita-esquerda
                    root_ = root_->doubleRight();
                    break;
                default :
                    break;
            }
        }
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
bool AVLTree<T>::contains(const T& data) const {
    return empty()? false : root_->contains(data);
}

//! Árvore vazia
/*! Verifica se a árvore esta vazia
 *  \return bool verdadeiro se estiver vazia
 */
template<typename T>
bool AVLTree<T>::empty() const {
    return size_ == 0u;
}

//! Tamanho da Árvore
/*! Retorna a quantidade de dados na árvore
 *  \return size_t quantidade de dados.
 */
template<typename T>
std::size_t AVLTree<T>::size() const {
    return size_;
}

//! Pré-ordem
/*! Busca os dados em pré-ordem
 *  \return ArrayList<T> dados em pré-ordem
 *  \sa in_order(), post_order()
 */
template<typename T>
ArrayList<T> AVLTree<T>::pre_order() const {
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
ArrayList<T> AVLTree<T>::in_order() const {
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
ArrayList<T> AVLTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  //  namespace structures

#endif
