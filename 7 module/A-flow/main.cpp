#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000005
const int MAXN = 100;

struct Edge{
    int i, c, f;
    int v, to;

    Edge(int i, int c, int v, int to): i(i), c(c), f(0), v(v), to(to) {}
};

int prevv[MAXN], used[MAXN];
std::vector<int> nums[MAXN];
std::vector<Edge> g;
int n, m;

int bfs(){
    memset(used, 0, sizeof(int) * n);
    memset(prevv, -1, sizeof(int) * n);

    int s = 0, t = n - 1;

    std::queue<int> q;
    q.push(s);
    int flow = INF;

    used[s] = 1;
    while(!q.empty()){
        int v = q.front(); q.pop();
        for (int i = 0; i < nums[v].size(); i++) {
            int j = nums[v][i];
            int u = g[j].to, delta = g[j].c - g[j].f;

            if (!used[u] && delta > 0){
                flow = std::min(delta, flow);
                q.push(u);
                prevv[u] = j;
                used[u] = 1;
            }
        }
    }

    if (used[t]) return flow;
    else return 0;
}

int dfs(int v, int flow){
    if (v == n - 1) return flow;

    for (int i = 0; i < nums[v].size(); i++){
        int j = nums[v][i], u = g[j].to, f = g[j].f;
        if (f > 0){
            f = dfs(u, std::min(flow, f));
            g[j].f -= f;
            return f;
        }
    }
    return 0;
}

void maxFlow(){
    int s = 0, t = n - 1;
    int v, u, j, f;

    while((f = bfs())){
        for (v = t; v != s; v = g[prevv[v]].v){
            j = prevv[v];
            g[j].f += f;
            g[j ^ 1].f -= f;
        }
    }

    std::vector<int> fl;
    for(int i = 0; i < 2 * m; i+= 2){
        fl.push_back(g[i].f);
    }

    int ans = 0, tmp;
    while((tmp = dfs(0, INF))){
        ans += tmp;
    }

    std::cout << ans << '\n';
    for (int i = 0; i < m; i++) {
        std::cout << fl[i] << std::endl;
    }

}

int main(){
    freopen("flow.in", "r", stdin);
    freopen("flow.out", "w", stdout);

    std::cin >> n >> m;

    int v, u, c, j = 0;
    for (int i = 0; i < m; i++) {
        std::cin >> v >> u >> c;
        v--, u--;
        g.push_back(Edge(i + 1, c, v, u));
        g.push_back(Edge(-1, c, u, v));
        nums[v].push_back(j);
        nums[u].push_back(j + 1);
        j += 2;
    }

    maxFlow();

    return 0;
}