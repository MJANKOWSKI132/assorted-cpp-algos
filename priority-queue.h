#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <vector>
#include <memory>

using std::vector;

template <typename T, typename Comparator>
class PriorityQueue {
private:
    vector<T>* v;
    Comparator comp;

    void siftDown(int i) {
        int largest, left, right;
        while ((2 * i + 1) < v -> size()) {
            largest = i;
            left = 2 * i + 1;
            right = 2 * i + 2;
            if (left < v -> size() && comp((*v)[left], (*v)[largest]) > 0) {
                largest = left;
            }
            if (right < v -> size() && comp((*v)[right], (*v)[largest]) > 0) {
                largest = right;
            }
            if (largest == i) break;
            std::swap((*v)[i], (*v)[largest]);
            i = largest;
        }
    }

    void heapify() {
        for (int i = v -> size() / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    void siftUp() {
        int i = v -> size() - 1;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (comp((*v)[parent], (*v)[i]) > 0)
                break;
            std::swap((*v)[parent], (*v)[i]);
            i = parent;
        }
    }
public:
    explicit PriorityQueue(const Comparator& comp): v(new vector<T>()), comp(comp) {}

    PriorityQueue(vector<int>*& v, const Comparator& comp): v(v), comp(comp) {
        heapify();
    }

    ~PriorityQueue() {
        delete v;
    }

    bool empty() const {
        return v -> empty();
    }

    T top() const {
        return (*v)[0];
    }

    T extractTop() {
        T top = (*v)[0];
        (*v)[0] = v -> back();
        v -> pop_back();
        siftDown(0);
        return top;
    }

    template <typename Display>
    void display(Display display) const {
        for (const auto& x : *v) 
            std::cout << "x: " << display(x) << '\n';
    }
    
    void insert(const T val) {
        v -> push_back(val);
        siftUp();
    } 

    int size() const {
        return v -> size();
    }
};

struct GreaterThan {
    int operator() (const int& x1, const int& x2) {
        return x1 - x2;
    }
};

struct LessThan {
    int operator() (const int& x1, const int& x2) {
        return x2 - x1;
    }
};

typedef PriorityQueue<int, LessThan> MinHeap;
typedef PriorityQueue<int, GreaterThan> MaxHeap;

#endif // PRIORITY_QUEUE_H