#include "DoublyLinkedListNode.h"
#include <unordered_map>
#include <iostream>

using std::unordered_map;

template <typename K, typename T>
class LRUCache {
private:
    int capacity;
    unordered_map<K, DoublyLinkedListNode<K, T>*> cache;
    DoublyLinkedListNode<K, T>* head;
    DoublyLinkedListNode<K, T>* tail;
    K defaultKey;
    T defaultVal;

    void removeNode(DoublyLinkedListNode<K, T>* node) {
        node -> next -> prev = node -> prev;
        node -> prev -> next = node -> next;
    }

    void addAtHead(DoublyLinkedListNode<K, T>* node) {
        node -> next = head -> next;
        node -> prev = head;
        head -> next -> prev = node;
        head -> next = node;
    }
public:
    LRUCache(int capacity, K defaultKey, T defaultVal): capacity(capacity), defaultKey(defaultKey), defaultVal(defaultVal) {
        head = new DoublyLinkedListNode(defaultKey, defaultVal);
        tail = new DoublyLinkedListNode(defaultKey, defaultVal);
        head -> next = tail;
        tail -> prev = head;
    }

    ~LRUCache() {
        auto* currNode = head;
        while (currNode) {
            auto* nextNode = currNode -> next;
            delete currNode;
            currNode = nextNode;
        }
    }

    T get(K key) {
        if (cache.count(key) == 0)
            return defaultVal;
        auto* node = cache[key];
        removeNode(node);
        addAtHead(node);
        return node -> val;
    }

    void put(K key, T val) {
        if (cache.count(key) > 0) {
            auto* node = cache[key];
            node -> val = val;
            removeNode(node);
            addAtHead(node);
            cache[key] = node;
        } else {
            if (cache.size() > capacity) {
                auto* nodeToRemove = tail -> prev;
                removeNode(nodeToRemove);
                cache.erase(nodeToRemove -> key);
                delete nodeToRemove;
            }
            auto* newNode = new DoublyLinkedListNode<K, T>(key, val);
            addAtHead(newNode);
            cache[key] = newNode;
        }
    }

    void print() const {
        std::cout << "{";
        auto* currNode = head;
        while (currNode) {
            std::cout << currNode -> key << "=" << currNode -> val << ", ";
            currNode = currNode -> next;
        }
        std::cout << "}\n";
    }
};