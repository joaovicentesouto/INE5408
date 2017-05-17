#include "array_list.h"


namespace structures {

class AVLTree {
public:
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
        Node(const T& data);

        T data;
        std::size_t height;
        Node* left;
        Node* right;

        void insert(const T& data_);

        bool remove(const T& data_);

        bool contains(const T& data_) const;
        
        void updateHeight() ;

        Node* simpleLeft() ;

        Node* simpleRight() ;

        Node* doubleLeft() ;
        
        Node* doubleRight() ;

        void pre_order(ArrayList<T>& v) const;

        void in_order(ArrayList<T>& v) const;

        void post_order(ArrayList<T>& v) const;
    };

    Node* root;
    std::size_t size_;
};

}