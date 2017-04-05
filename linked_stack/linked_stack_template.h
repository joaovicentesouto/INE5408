namespace structures {

template<typename T>
class LinkedStack {
public:
    LinkedStack();

    ~LinkedStack();

    void clear(); // limpa pilha

    void push(const T& data); // empilha

    T pop(); // desempilha

    T& top() const; // dado no topo

    bool empty() const; // pilha vazia

    std::size_t size() const; // tamanho da pilha

private:
    class Node {
    public:
        Node(const T& data);
        Node(const T& data, Node* next);

        T& data(); // getter: info
        const T& data() const; // getter-constante: info

        Node* next(); // getter: próximo
        const Node* next() const; // getter-constante: próximo

        void next(Node* next); // setter: próximo
    private:
        T data_;
        Node* next_;
    };

    Node* top_; // nodo-topo
    std::size_t size_; // tamanho
};

}
