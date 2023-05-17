#include <iostream>
#include "LRUCache.h"

int main() {
    auto* lruCache = new LRUCache<int, int>(2, -1, -1);
    lruCache -> put(1, 1);
    lruCache -> print();
    lruCache -> put(2, 2);
    lruCache -> print();
    std::cout << lruCache -> get(1) << '\n';
    lruCache -> print();
    lruCache -> put(3, 3);
    std::cout << lruCache -> get(2) << '\n';
    lruCache -> print();
    lruCache -> put(4, 4);
    lruCache -> print();
    std::cout << lruCache -> get(1) << '\n';
    lruCache -> print();
    std::cout << lruCache -> get(3) << '\n';
    lruCache -> print();
    std::cout << lruCache -> get(4) << '\n';
    lruCache -> print();
    delete lruCache;
    return -1;
}