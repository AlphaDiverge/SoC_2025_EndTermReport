#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// 1. Dijkstra's Algorithm - Shortest Path (No Negative Weights)
vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int S) {
    vector<int> dist(V, INT_MAX);
    dist[S] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, S});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}



// 2. Bellman-Ford Algorithm (Handles Negative Weights)
vector<int> bellmanFord(int V, vector<vector<int>>& edges, int S) {
    vector<int> dist(V, INT_MAX);
    dist[S] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
            return {-1};
        }
    }
    return dist;
}



// 3. Floyd-Warshall (All-Pairs Shortest Path)
void floydWarshall(vector<vector<int>>& matrix) {
    int V = matrix.size();
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (matrix[i][k] != -1 && matrix[k][j] != -1) {
                    if (matrix[i][j] == -1 || matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                }
            }
        }
    }
}



// 4. Prim's Algorithm (Minimum Spanning Tree)
int primMST(int V, vector<vector<pair<int, int>>>& adj) {
    int sum = 0;
    vector<bool> inMST(V, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        int w = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        sum += w;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!inMST[v]) {
                pq.push({weight, v});
            }
        }
    }
    return sum;
}



// 5. Path With Minimum Effort (Dijkstra's Variant)
int minimumEffortPath(vector<vector<int>>& heights) {
    int rows = heights.size(), cols = heights[0].size();
    vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
    effort[0][0] = 0;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({0, 0, 0});

    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int e = cur[0], x = cur[1], y = cur[2];

        if (x == rows-1 && y == cols-1) return e;

        for (auto& d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                int ne = max(e, abs(heights[x][y] - heights[nx][ny]));
                if (ne < effort[nx][ny]) {
                    effort[nx][ny] = ne;
                    pq.push({ne, nx, ny});
                }
            }
        }
    }
    return -1;
}



// 6. City With Smallest Number of Neighbors (Floyd-Warshall Application)
int findCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; ++i) dist[i][i] = 0;
    for (auto& e : edges) {
        dist[e[0]][e[1]] = e[2];
        dist[e[1]][e[0]] = e[2];
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    int minCities = n, result = -1;
    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (i != j && dist[i][j] <= distanceThreshold) count++;
        }
        if (count <= minCities) {
            minCities = count;
            result = i;
        }
    }
    return result;
}
