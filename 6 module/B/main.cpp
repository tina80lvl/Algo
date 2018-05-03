#include <iostream>
#include <stdio.h>
#include <vector>
#include <assert.h>

using namespace std;

const int N = (int) 7e5;
const int LG = 20;
int tin[N], tout[N], timer;
vector <int> g[N];
int up[N][LG];

void dfs(int v, int p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < LG; i++) {
        up[v][i] = up[up[v][i-1]][i-1];
    }
    for (int to : g[v]) if (to != p) {
            dfs(to, v);
        }
    tout[v] = timer++;
}

bool is_pred(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int v, int u) {
    if (is_pred(v, u)) return v;
    if (is_pred(u, v)) return u;
    int a = v;
    for (int i = LG - 1; i >= 0; i--) {
        if (!is_pred(up[a][i], u)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int main() {
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    int q;
    cin >> q;
    int n = 1;
    vector < pair<int, int> > queries;
    while (q--) {
        string type;
        int a, b;
        cin >> type >> a >> b;
        a--, b--;
        if (type == "ADD") {
            g[a].push_back(b);
            n++;
        } else if (type == "GET") {
            queries.push_back(make_pair(a, b));
        } else {
            assert(0);
        }
    }
    dfs(0, 0);
    for (auto p : queries) {
        cout << lca(p.first, p.second) + 1 << "\n";
    }

    return 0;
}