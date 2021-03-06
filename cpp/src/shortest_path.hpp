#ifndef __SHORTEST_PATH_H__
#define __SHORTEST_PATH_H__

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

struct Node {
    int v;
    int len;
    Node(int v, int len)
        : v(v)
        , len(len)
    {
    }

    bool operator>(const Node &rhs) const { return len > rhs.len; }

    bool operator<(const Node &rhs) const { return len < rhs.len; }
};

class Graph {
private:
    int v;
    int e;
    std::vector<std::vector<Node>> adj;

public:
    Graph(std::string filename)
        : v(0)
        , e(0)
    {
        std::ifstream in;
        in.open(filename);
        in >> v >> e;
        adj = std::vector(v, std::vector<Node>());
        int x, y, len;
        while (in >> x >> y >> len) {
            adj[x].push_back(Node(y, len));
            adj[y].push_back(Node(x, len));
        }
    }

    std::vector<int> dijkstra(int srcouce);
    int shortest_path();
};

inline int Graph::shortest_path()
{
    std::vector<int> memo = std::vector(v, INT32_MAX);
    memo[0] = 0;

    for (int i = 1; i < v; ++i) {
        for (const auto &adje : adj[i]) {
            if (adje.v < i) {
                memo[i] = std::min(memo[i], memo[adje.v] + adje.len);
            }
        }
    }

    return memo[v - 1];
}

inline std::vector<int> Graph::dijkstra(int s)
{
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push(Node(s, 0));

    std::vector<int> dis = std::vector(v, INT32_MAX);
    dis[s] = 0;

    std::vector<bool> visited = std::vector(v, false);
    std::vector<int> parent = std::vector(v, 0);
    parent[s] = s;

    while (!pq.empty()) {
        auto e = pq.top();
        pq.pop();
        if (visited[e.v]) {
            continue;
        }

        visited[e.v] = true;
        for (auto w : adj[e.v]) {
            if (dis[e.v] + w.len < dis[w.v]) {
                dis[w.v] = dis[e.v] + w.len;
                pq.push(Node(w.v, dis[w.v]));
                parent[w.v] = e.v;
            }
        }
    }

    std::cout << "source is: " << s << std::endl;
    for (int i = 0; i < v; ++i) {
        if (i == s)
            continue;

        std::stack<int> stack;
        stack.push(i);
        int pre = parent[i];
        while (pre != s) {
            stack.push(pre);
            pre = parent[pre];
        }
        stack.push(s);

        std::cout << "path[" << i << "]: ";
        while (!stack.empty()) {
            int point = stack.top();
            stack.pop();
            std::cout << point;
            if (!stack.empty())
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }

    return dis;
}

#endif
