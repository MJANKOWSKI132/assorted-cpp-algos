#include <iostream>
#include <vector>
#include <memory>
#include "ListNode.h"

using std::vector;

class HashTable {
protected:
    ListNode<int>* hashTable[10];

    void init(const std::initializer_list<int>& list) {
        for (const auto& x : list) put(x);
    }
public:
    virtual ~HashTable() {
        std::cout << "Now deleting HashTable\n";
        for (auto*& head : hashTable) {
            auto* currNode = head;
            ListNode<int>* nextNode = nullptr;
            while (currNode) {
                nextNode = currNode -> next;
                delete currNode;
                currNode = nextNode;
            }
        }
    }

    virtual int get(int x) const = 0;

    virtual void put(int x) = 0;

    void display() const {
        for (int i = 0; i < 10; ++i) {
            std::cout << "index " << i << ": ";
            auto* currNode = hashTable[i];
            while (currNode) {
                std::cout << currNode -> val << " -> ";
                currNode = currNode -> next;
            }
            std::cout << '\n';
        }
    }
};

class HashTableChaining : public HashTable {
public:
    void put(int x) override {
        int idx = x % 10;
        auto* currNode = hashTable[idx];
        if (!currNode) {
            hashTable[idx] = new ListNode<int>(x);
        } else {
            while (currNode -> next) currNode = currNode -> next;
            currNode -> next = new ListNode<int>(x);
        }
    }

    int get(int x) const override {
        int idx = x % 10;
        auto* currNode = hashTable[idx];
        while (currNode && currNode -> val != x) {
            currNode = currNode -> next;
        }
        if (!currNode || (currNode -> val != x)) {
            std::cout << "Could not find key: " << x << '\n';
            return -1;
        }
        return currNode -> val;
    }

    HashTableChaining(const std::initializer_list<int>& list): HashTable() {
        init(list);
    }
};

class HashTableLinearProbing : public HashTable {
public:
    void put(int x) override {
        int i = 0;
        while (i < 10) {
            int idx = ((x % 10) + i) % 10;
            if (hashTable[idx]) {
                ++i;
            } else {
                hashTable[idx] = new ListNode<int>(x);
                return;
            }
        }
        if (i == 10) {
            std::cout << "No space available to insert key: " << x << '\n';
        }
    }

    int get(int x) const override {
        int i = 0;
        while (i < 10) {
            int idx = ((x % 10) + i) % 10;
            auto* head = hashTable[idx];
            if (head && head -> val == x) {
                return head -> val;
            } else {
                ++i;
            }
        }
        if (i == 10) {
            std::cout << "Could not find key: " << x << '\n';
        }
        return -1;
    }

    HashTableLinearProbing(const std::initializer_list<int>& list): HashTable() {
        init(list);
    }
};

int main () {
    std::unique_ptr<HashTable> table(new HashTableChaining({16, 12, 25, 39, 6, 122, 5, 68, 75, 76, 77, 61, 62}));
    table -> put(16);
    table -> display();
    return 0;
}