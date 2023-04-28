#include "priority-queue.h"

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