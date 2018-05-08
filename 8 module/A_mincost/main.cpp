#include <stdio.h>
#include <vector>
#include <iostream>
#include <climits>
#include <queue>

long long INF = (long long) 1e18;
int n, m;

struct edge {
    int b, capacity, cost, flow;
    size_t back;
};

std::vector<std::vector<edge>> edges(100);

void add_edge(int a, int b, int capacity, int cost) {
    edge x = {b, capacity, cost, 0, edges[b].size()};
    edge y = {a, 0, -cost, 0, edges[a].size()};
    edges[a].push_back(x);
    edges[b].push_back(y);
}

void prnt() {
    for (int i = 0; i < edges.size(); i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            std::cout << i << " to " << edges[i][j].b << ", can " << edges[i][j].capacity << ", cost " << edges[i][j].cost << ", flow " << edges[i][j].flow << ", back.\n";
        }
    }
}

int main() {
    freopen("mincost.in", "r", stdin);
    freopen("mincost.out", "w", stdout);

    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, capacity, cost;
        std::cin >> a >> b >> capacity >> cost;
        add_edge(a - 1, b - 1, capacity, cost);
    }

    int s = 0, t = n - 1;
    long long flow = 0;
    long long cost = 0;
    while (flow < INF) {
        std::vector<long long> d (n, INF), p (n), used(n);
        std::vector<size_t> p_edge (n);
        std::queue <int> q;
        q.push(s);
        d[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            used[v] = false;

            for (size_t i = 0; i < edges[v].size(); ++i) {
                edge & r = edges[v][i];
                if (r.flow < r.capacity && d[v] + r.cost < d[r.b]) {
                    d[r.b] = d[v] + r.cost;

                    if (!used[r.b]) {
                        used[r.b] = true;
                        q.push(r.b);
                    }

                    p[r.b] = v;
                    p_edge[r.b] = i;
                }
            }
        }
        if (d[t] == INF)
            break;
        long long addflow = INF;
//        int addflow = INF - flow;
        for (int v = t; v != s; v = p[v]) {
            int pv = p[v];
            size_t pr = p_edge[v];
            addflow = std::min(addflow, (long long) edges[pv][pr].capacity - edges[pv][pr].flow);
        }
        for (int v = t; v != s; v = p[v]) {
            int pv = p[v];
            size_t pr = p_edge[v],  r = edges[pv][pr].back;
            edges[pv][pr].flow += addflow;
            edges[v][r].flow -= addflow;
            cost += 1LL * edges[pv][pr].cost * addflow;
        }
        flow += addflow;
    }
//    std::cout << "\n***\n\n";
//    prnt();
    long long final_cost = 0;
    for (int i = 0; i < edges.size(); i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            final_cost += ((long long) edges[i][j].cost) * edges[i][j].flow;
        }
    }
    std::cout << cost << std::endl;
}