#include <iostream>
#include <vector>
#include <memory>

using std::vector;

template <typename T, typename Comparator>
class PriorityQueue {
private:
    vector<T>* v;
    Comparator comp;

    void heapify() {
        int largest, left, right;
        for (int i = v -> size() / 2 - 1; i >= 0; --i) {
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
    }

    void heapifyUp() {
        int i = 0;
        int j = 1;
        while (j < v -> size()) {
            if (j + 1 < v -> size() && comp((*v)[j + 1], (*v)[j]) > 0) {
                ++j;
            }
            if (comp((*v)[j], (*v)[i]) > 0) {
                std::swap((*v)[i], (*v)[j]);
                i = j;
                j = 2 * i + 1;
            } else {
                break;
            }
        }
    }
public:
    explicit PriorityQueue(const Comparator& comp) {
        this -> v = new vector<T>();
        this -> comp = comp;
    }

    PriorityQueue(vector<int>*& v, const Comparator& comp) {
        this -> v = v;
        this -> comp = comp;
        heapify();
    }

    ~PriorityQueue() {
        delete v;
    }

    bool empty() const {
        return v -> empty();
    }

    T& top() const {
        return (*v)[0];
    }

    T extractTop() {
        T top = this -> top();
        (*v)[0] = v -> back();
        v -> pop_back();
        heapifyUp();
        return top;
    }

    void display() const {
        for (const auto& x : *v) 
            std::cout << "x: " << x << '\n';
    }
    
    void insert(const T& val) {
        v -> push_back(val);
        std::swap((*v)[0], (*v)[v -> size() - 1]);
        heapifyUp();
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

int main() {
    std::string maxOrMin;
    std::cout << "Enter 'max' or 'min': ";
    std::cin >> maxOrMin;
    if (maxOrMin == "max") {
        const struct GreaterThan greaterThan;
        auto maxHeap = std::make_unique<MaxHeap>(greaterThan);
        for (int i = -20; i <= 20; ++i) 
            maxHeap -> insert(i);
        while (!maxHeap -> empty()) 
            std::cout << "current max: " << maxHeap -> extractTop() << '\n';
    } else if (maxOrMin == "min") {
        const struct LessThan lessThan;
        auto minHeap = std::make_unique<MinHeap>(lessThan);
        for (int i = 20; i >= -20; --i) 
            minHeap -> insert(i);
        while (!minHeap -> empty()) 
            std::cout << "current min: " << minHeap -> extractTop() << '\n';
    } else {
        std::cout << "Using default example\n";
        const struct GreaterThan greaterThan;
        auto v = new vector<int>();
        for (int i = -20; i <= 20; ++i) {
            v -> push_back(i);
        }
        auto maxHeap = std::make_unique<MaxHeap>(v, greaterThan);
        while (!maxHeap -> empty()) 
            std::cout << "current max: " << maxHeap -> extractTop() << '\n';
    }
    return 0;
}