#include <iostream>
#include <vector>
#include "ListNode.h"
#include <memory>
#include <queue>

using std::vector;
using std::queue;

typedef std::unique_ptr<vector<int>> IntVector;

class Graph {
private:
    std::unique_ptr<vector<IntVector>> adj;
    bool directed;
    int numVertices;

    void dfsUtil(const int& current, const int& target, vector<bool>& visited, bool& res) const {
        if (current == target) {
            res = true;
            return;
        }
        for (const auto& adjacent : *(*adj)[current]) {
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                dfsUtil(adjacent, target, visited, res);
            }
        }
    }
public:
    Graph(const bool& directed, const int& numVertices) {
        this -> directed = directed;
        this -> adj = std::make_unique<vector<IntVector>>(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            (*adj)[i] = std::make_unique<std::vector<int>>();
        }
        this -> numVertices = numVertices;
    }

    void insertEdge(const int& u, const int& v) {
        (*adj)[u] -> push_back(v);
        if (!directed)
            (*adj)[v] -> push_back(u);
    }

    void display() const {
        for (int i = 0; i < numVertices; ++i) {
            std::cout << i << ": ";
            for (const auto& v : *(*adj)[i]) {
                std::cout << v << " -> ";
            }
            std::cout << '\n';
        }
    }

    bool bfs(const int& start, const int& target) const {
        vector<bool> visited(numVertices, false);
        queue<int> queue;
        queue.push(start);
        visited[start] = true;
        while (!queue.empty()) {
            int current = queue.front();
            if (current == target)
                return true;
            std::cout << "current: " << current << '\n';
            queue.pop();
            for (const auto& adjacent : *(*adj)[current]) {
                if (!visited[adjacent]) {
                    visited[adjacent] = true;
                    queue.push(adjacent);
                }
            }
        }
        return false;
    }

    bool dfs(const int& start, const int& target) const {
        bool res = false;
        vector<bool> visited(numVertices, false);
        visited[start] = true;
        dfsUtil(start, target, visited, res);
        return res;
    }
};

int main() {
    Graph g(false, 7);
    g.insertEdge(0, 1);
    g.insertEdge(0, 3);
    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);
    g.insertEdge(2, 5);
    g.insertEdge(3, 4);
    g.insertEdge(4, 5);
    g.insertEdge(4, 6);

    g.display();

    std::cout << (g.dfs(0, 6) ? "true" : "false") << '\n';
    return 0;
}