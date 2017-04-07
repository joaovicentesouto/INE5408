namespace structures {

template<typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList()
    ~DoublyLinkedList()
    void clear()

    void push_back(const T& data) // insere no fim
    void push_front(const T& data) // insere no início
    void insert(const T& data, std::size_t index) // insere na posição
    void insert_sorted(const T& data) // insere em ordem

    T pop(std::size_t index) // retira da posição
    T pop_back() // retira do fim
    T pop_front() // retira do início
    void remove(const T& data) // retira específico

    bool empty() const // lista vazia
    bool contains(const T& data) const // contém

    T& at(std::size_t index) // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const // getter constante a um elemento

    std::size_t find(const T& data) const // posição de um dado
    std::size_t size() const // tamanho
private:
    class Node {
    public:
        Node(const T& data)
        Node(const T& data, Node* next)
        Node(const T& data, Node* prev, Node* next)

        T& data()
        const T& data() const

        Node* prev()
        const Node* prev() const

        void prev(Node* node)

        Node* next()
        const Node* next() const

        void next(Node* node)
    private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}