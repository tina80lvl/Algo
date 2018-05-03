#include <iostream>
#include <assert.h>
#include <vector>
#include <queue>

const int N = 5010, INF = 1000000001;

char a[N][N];
int n, m, s, t, d[N], ptr[N];
std::vector<int> g[N];

int num(int i, int j) {
    return i * m + j + 1;
}

struct edge {
    int a, b, cap, flow;
};

std::vector<edge> e;

void add_edge (int a, int b, int cap) {
    edge x = { a, b, cap, 0 };
    edge y = { b, a, 0, 0 };
    g[a].push_back ((int) e.size());
    e.push_back (x);
    g[b].push_back ((int) e.size());
    e.push_back (y);
}

int dfs (int v, int flow) {
    if (v == t || flow == 0)
        return flow;

    for (; ptr[v] < (int) g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]],
                to = e[id].b;
        if (d[to] == d[v] + 1) {
            int pushed = dfs(to, std::min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
    }
    return 0;
}

bool bfs() {
    std::queue <int> q;
    q.push(s);
    for (int i = s; i <= t; i++) {
        d[i] = INF;
    }
    d[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < g[v].size(); ++i) {
            int id = g[v][i], to = e[id].b;
            if (d[to] == INF && e[id].flow < e[id].cap) {
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != INF;
}

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool good(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m && a[x][y] != '#';
}

int main() {
//    freopen("input.txt", "r", stdin);
    std::cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    s = 0;
    t = num(n - 1, m - 1) * 2 + 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '#')
                continue;
            int x = num(i, j) * 2 - 1;
            int y = num(i, j) * 2;
            if (a[i][j] == 'A') {
                add_edge(s, x, INF);
            }
            if (a[i][j] == 'B') {
                add_edge(y, t, INF);
            }

            if (a[i][j] == '.') {
                add_edge(x, y, 1);
            } else {
                add_edge(x, y, INF);
            }

            for (int it = 0; it < 4; it++) {
                int ni = i + dx[it];
                int nj = j + dy[it];
                if (good(ni, nj)) {
                    int nx = num(ni, nj) * 2 - 1;
                    int ny = num(ni, nj) * 2;
                    add_edge(y, nx, INF);
                }
            }
        }
    }

    int mxflow = 0;

    while (bfs()) {
        memset (ptr, 0, (t + 1) * sizeof ptr[0]);
        while (int f = dfs(s, INF)) {
            mxflow += f;
        }
    }

    int wall = 0;
    for (int v = s; v <= t; v++) {
        if (d[v] != INF) {
            int u = (v - 1) / 2;
            int x = u / m;
            int y = u % m;
            bool take = false;
            for (int i = 0; i < (int) g[v].size(); i++) {
                int id = g[v][i];
                int to = e[id].b;
                if (d[to] == INF && e[id].cap && e[id].flow == e[id].cap)
                    take = true;
            }
            if (a[x][y] == '.' && take) {
                a[x][y] = '+';
                wall++;
            }
        }
    }

    if (mxflow > N) {
        std::cout << -1 << std::endl;
        return 0;
    }

    assert(wall == mxflow);

    std::cout << mxflow << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}