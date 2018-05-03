#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <map>

const int MAXN = 100500;
struct Edge{
    int i, c, f;
    int v, to;
    ////index, left, flow, from, to
    Edge(int i, int c, int v, int to): i(i), c(c), f(0), v(v), to(to) {}
};

int prevv[MAXN], used[MAXN];
std::vector<int> nums[MAXN];
std::vector<int> decomp[2];
std::vector<Edge> g;
int n, m, st, fin;

int bfs(int s, int t){
    memset(used, 0, sizeof(int) * n);
    memset(prevv, -1, sizeof(int) * n);

    std::queue<int> q;
    q.push(s);

    used[s] = 1;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for (int i = 0; i < nums[v].size(); i++) {
            int j = nums[v][i];
            int u = g[j].to, delta = g[j].c - g[j].f;

            if (!used[u] && delta > 0){
                q.push(u);
                prevv[u] = j;
                used[u] = 1;
            }
        }
    }

    return used[t];
}

int dfs(int v, int t, int k){
    decomp[k].push_back(v + 1);
    if (v == t)
        return 1;

    for (int i = 0; i < nums[v].size(); i++) {
        int j = nums[v][i], u = g[j].to, f = g[j].f;
        if (f > 0){
            dfs(u, t, k);
            g[j].f -= 1;
            return 1;
        }
    }
    return 0;
}

void maxFlow(int s, int t){
    int v, u, j, flow = 0;

    while(bfs(s, t)){
        int flag = 0;
        for (v = t; v != s; v = g[prevv[v]].v){
            j = prevv[v];
            flag |= j % 2;
            g[j].f += 1;
            g[j ^ 1].f -= 1;
        }
        if (flag) flow -= 1;
        else flow += 1;

        if (flow == 2){
            break;
        }
    }

    int i = 0;

    while(dfs(s, t, i)){
        i++;
        if (i == 2) break;
    }
    if (i < 2){
        std::cout << "NO" << std::endl;
        return;
    } else
        std::cout << "YES" << std::endl;

    for (int j = 0; j < 2; j++){
        for (int y = 0; y < decomp[j].size(); y++) {
            v = decomp[j][y];
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    }

}

int main() {
    freopen("snails.in", "r", stdin);
    freopen("snails.out", "w", stdout);

    int s, t;
    std::cin >> n >> m >> st >> fin;

    int v, u, j = 0;
    for (int i = 0; i < m; i++){
        std::cin >> v >> u;
        v--, u--;
        if (v == u)
            continue;
        g.push_back(Edge(i + 1, 1, v, u));
        g.push_back(Edge(-1, 0, u, v));
        nums[v].push_back(j);
        nums[u].push_back(j + 1);
        j += 2;
    }

    maxFlow(st - 1, fin - 1);

    return 0;
}