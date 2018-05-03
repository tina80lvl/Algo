#include <stdio.h>
#include <vector>
#include <iostream>
#include <climits>

int INF = 1000001;
int n, m;

struct edge {
    int a, b, capacity, flow, cost;
    edge(int a, int b, int capacity, int flow, int cost) : a(a), b(b), capacity(capacity), flow(flow), cost(cost) {}
};

std::vector<edge> edges;

void add_edge(int a, int b, int cap, int cost) {
    edge e1(a, b, cap, 0, cost);
    edge e2(b, a, 0, 0, -cost);
    edges.push_back(e1);
    edges.push_back(e2);
}

int ford_bellman() {
    std::vector<long long> depth(n, LLONG_MAX);
    depth[0] = 0;
    std::vector<int> p(n, -1);
    for (;;) {
        bool any = false;
        for (int j = 0; j < edges.size(); ++j) {
            if (depth[edges[j].a] < LLONG_MAX) {
                if (edges[j].flow < edges[j].capacity && depth[edges[j].b] > depth[edges[j].a] + edges[j].cost) {
                    depth[edges[j].b] = depth[edges[j].a] + edges[j].cost;
                    p[edges[j].b] = j;
                    any = true;
                }
            }
        }
        if (!any) break;
    }
    int min_flow = INF;
    if (depth[n - 1] != LLONG_MAX) {
        int e = p[n - 1];
        while (e != -1) {
            min_flow = std::min(min_flow, (edges[e].capacity - edges[e].flow));
            e = p[edges[e].a];
        }
        e = p[n - 1];
        while (e != -1) {
            edges[e].flow += min_flow;
            edges[e ^ 1].flow -= min_flow;
            e = p[edges[e].a];
        }
    } else {
        min_flow = 0;
    }
    return min_flow;
}

int main(int argc, char *args[]) {
    freopen("mincost.in", "r", stdin);
    freopen("mincost.out", "w", stdout);

    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, capacity, cost;
        std::cin >> a >> b >> capacity >> cost;
        add_edge(a - 1, b - 1, capacity, cost);
    }
    int k, s = 0, t = n - 1;

    int flow = 0,  cost = 0;
    while (flow < k) {
        std::vector<int> id (n, 0);
        std::vector<int> d (n, INF);
        std::vector<int> q (n);
        std::vector<int> p (n);
        std::vector<size_t> p_rib (n);
        int qh=0, qt=0;
        q[qt++] = s;
        d[s] = 0;
        while (qh != qt) {
            int v = q[qh++];
            id[v] = 2;
            if (qh == n)  qh = 0;
            for (size_t i=0; i<g[v].size(); ++i) {
                rib & r = g[v][i];
                if (r.f < r.u && d[v] + r.c < d[r.b]) {
                    d[r.b] = d[v] + r.c;
                    if (id[r.b] == 0) {
                        q[qt++] = r.b;
                        if (qt == n)  qt = 0;
                    }
                    else if (id[r.b] == 2) {
                        if (--qh == -1)  qh = n-1;
                        q[qh] = r.b;
                    }
                    id[r.b] = 1;
                    p[r.b] = v;
                    p_rib[r.b] = i;
                }
            }
        }
        if (d[t] == INF)  break;
        int addflow = k - flow;
        for (int v=t; v!=s; v=p[v]) {
            int pv = p[v];  size_t pr = p_rib[v];
            addflow = std::min (addflow, g[pv][pr].u - g[pv][pr].f);
        }
        for (int v=t; v!=s; v=p[v]) {
            int pv = p[v];  size_t pr = p_rib[v],  r = g[pv][pr].back;
            g[pv][pr].f += addflow;
            g[v][r].f -= addflow;
            cost += g[pv][pr].c * addflow;
        }
        flow += addflow;
    }


    long long final_cost = 0;
    for (int i = 0; i < edges.size(); i += 2) {
        final_cost += ((long long) edges[i].cost) * edges[i].flow;
    }
    std::cout << final_cost << std::endl;
}