template <typename K, typename T>
class DoublyLinkedListNode {
public:
    K key;
    T val;
    DoublyLinkedListNode<K, T>* prev;
    DoublyLinkedListNode<K, T>* next;

    DoublyLinkedListNode(K key, T val): val(val), key(key), prev(nullptr), next(nullptr) {}

    ~DoublyLinkedListNode() = default;
};