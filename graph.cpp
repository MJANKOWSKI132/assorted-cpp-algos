#include <iostream>
#include <vector>
#include "ListNode.h"
#include <memory>
#include <queue>
#include "priority-queue.h"
#include <string>

using std::vector;
using std::queue;
using std::pair;

typedef std::unique_ptr<vector<pair<int, int>>> AdjacentWeightVector;

struct EdgeWeightComparator {
    int operator() (const pair<int, int>& p1, const pair<int, int>& p2) {
        return p2.second - p1.second;
    }
};

struct DisplayEdge {
    std::string operator() (const pair<int, int>& p) {
        return "(" + std::to_string(p.first + 1) + ", " + std::to_string(p.second) + ")";
    }
};

class Graph {
private:
    std::unique_ptr<vector<AdjacentWeightVector>> adj;
    bool directed;
    int numVertices;

    void dfsUtil(const int& current, const int& target, vector<bool>& visited, bool& res) const {
        if (current == target) {
            res = true;
            return;
        }
        for (const auto& adjacent : *(*adj)[current]) {
            if (!visited[adjacent.first]) {
                visited[adjacent.first] = true;
                dfsUtil(adjacent.first, target, visited, res);
            }
        }
    }
public:
    Graph(const bool& directed, const int& numVertices) {
        this -> directed = directed;
        this -> adj = std::make_unique<vector<AdjacentWeightVector>>(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            (*adj)[i] = std::make_unique<std::vector<pair<int, int>>>();
        }
        this -> numVertices = numVertices;
    }

    void insertEdge(const int& u, const int& v, const int& weight = 1) {
        (*adj)[u - 1] -> push_back(std::make_pair(v - 1, weight));
        if (!directed)
            (*adj)[v - 1] -> push_back(std::make_pair(u - 1, weight));
    }

    void display() const {
        for (int i = 0; i < numVertices; ++i) {
            std::cout << i + 1 << ":   ";
            for (const auto& v : *(*adj)[i]) {
                std::cout << v.first + 1 << ":" << v.second << " -> ";
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
            queue.pop();
            for (const auto& adjacent : *(*adj)[current]) {
                if (!visited[adjacent.first]) {
                    visited[adjacent.first] = true;
                    queue.push(adjacent.first);
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

    int numEdges() const {
        int res = 0;
        for (const auto& list : *adj) {
            res += list -> size();
        }
        return directed ? res : (res / 2);
    }

    vector<pair<int, int>> prim() const {
        const EdgeWeightComparator edgeWeightComparator;
        auto minHeap = std::make_unique<PriorityQueue<pair<int, int>, EdgeWeightComparator>>(edgeWeightComparator);
        vector<bool> visited(numVertices, false);
        vector<int> dist(numVertices, INT_MAX);
        minHeap -> insert(std::make_pair(0, 0));
        vector<int> prev(numVertices, -1);
        while (!minHeap -> empty()) {
            int u = minHeap -> extractTop().first;
            if (visited[u]) {
                continue;
            }
            visited[u] = true;
            for (const auto& adjacentPair : *(*adj)[u]) {
                int v = adjacentPair.first;
                int weight = adjacentPair.second;
                if (weight < dist[v] && !visited[v]) {
                    dist[v] = weight;
                    minHeap -> insert(adjacentPair);
                    prev[v] = u;
                }
            }
        }
        vector<pair<int, int>> edges;
        for (int i = 0; i < numVertices; ++i) {
            if (prev[i] >= 0)
                edges.push_back(std::make_pair(prev[i], i));
        }
        return edges;
    }
};

int main() {
    Graph g(false, 7);
    g.insertEdge(1, 6, 5);
    g.insertEdge(1, 2, 4);
    g.insertEdge(2, 7, 6);
    g.insertEdge(2, 3, 9);
    g.insertEdge(3, 4, 10);
    g.insertEdge(4, 5, 12);
    g.insertEdge(4, 7, 11);
    g.insertEdge(5, 7, 16);
    g.insertEdge(5, 6, 18);

    g.display();

    auto edges = g.prim();
    for (const auto& edge : edges) {
        std::cout << "(" << edge.first + 1 << ", " << edge.second + 1 << ")\n";
    }
    return 0;
}