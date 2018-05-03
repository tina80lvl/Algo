#include <iostream>
#include <vector>
#include <queue>
#include <map>
#define INF 100000000

const int MAXN = 100;

int g[MAXN][MAXN], parent[MAXN], used[MAXN];
std::map<std::pair<int, int>, std::pair<int, int>> edge;
int n, m;

int bfs(int s, int t){
    memset(used, 0, sizeof(int) * n);
    std::queue<int> q;
    q.push(s);

    used[s] = 1;
    parent[s] = -1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++){
            if (!used[v] && g[u][v] > 0){
                q.push(v);
                parent[v] = u;
                used[v] = 1;
            }
        }
    }

    return used[t];
}

void dfs(int v){
    used[v] = 1;
    for (int i = 0; i < n; i++){
        if (g[v][i] && !used[i]) dfs(i);
    }
}

void minCut(int s, int t){
    int v, u;

    while(bfs(s, t)){
        int flow = INF;
        for (v = t; v != s; v = parent[v]){
            u = parent[v];
            flow = std::min(flow, g[u][v]);
        }

        for (v = t; v != s; v = parent[v]){
            u = parent[v];
            g[u][v] -= flow;
            g[v][u] += flow;
        }
    }

    memset(used, 0, sizeof(int) * n);
    dfs(s);

    int ansc = 0;
    std::vector <int> ans;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            std::pair<int, int> tmp = edge[std::make_pair(i, j)];
            if (used[i] && !used[j] && tmp.second){
                ansc += tmp.second;
                ans.push_back(tmp.first);
            }
        }
    }

    std::cout << ans.size() << ' ' << ansc << std::endl;
    for (int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << std::endl;
}

int main(){
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);

    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        memset(g[i], 0, sizeof(int) * n);
    }

    int v, u, c;
    for (int i = 0; i < m; i++){
        std::cin >> v >> u >> c;
        v--, u--;
        edge[std::make_pair(v, u)] = std::make_pair(i + 1, c);
        edge[std::make_pair(u, v)] = std::make_pair(i + 1, c);
        g[v][u] = c;
        g[u][v] = c;
    }

    minCut(0, n - 1);

    return 0;
}