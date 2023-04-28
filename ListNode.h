template <typename T>
class ListNode {
public:
    T val;
    ListNode* next;
    explicit ListNode(T val): val(val), next(nullptr) {}
};