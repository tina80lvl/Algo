#include <iostream>
#include <map>
#include <assert.h>
#include <vector>
#include <queue>

const int N = 50000;
const int INF = (int) 1e9;

char a[120][120];
int n, p[N], s, t, d[N], ptr[N];

struct edge {
    int a, b, cap, flow;
};

std::vector<edge> e;
std::vector<int> g[N];

void add_edge (int a, int b, int cap) {
    edge x = { a, b, cap, 0 };
    edge y = { b, a, 0, 0 };
    g[a].push_back ((int) e.size());
    e.push_back (x);
    g[b].push_back ((int) e.size());
    e.push_back (y);
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

int dfs(int v, int flow) {
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

int main() {
   std::cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    std::vector <int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }

    s = 0;
    int game = n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 'w')
                p[i] -= 2;
            if (a[i][j] == 'W')
                p[i] -= 3;
            if (a[i][j] == 'l')
                p[i] -= 1;
            if (a[i][j] == '.' && i < j) {
                add_edge(s, game, 3);
                add_edge(game, i + 1, INF);
                add_edge(game, j + 1, INF);
                game++;
            }
        }
    }


    t = game;
    for (int i = 0; i < n; i++) {
        add_edge(i + 1, t, std::max(p[i], 0));
    }

    int mxflow = 0;
    while (bfs()) {
        std::fill(ptr, ptr + t + 1, 0);
        while (int f = dfs(s, INF)) {
            mxflow += f;
        }
    }

    std::map <int, char> def;
    def[0] = 'L';
    def[1] = 'l';
    def[2] = 'w';
    def[3] = 'W';

    for (int v = n + 1; v < t; v++) {
        std::vector <int> players;
        for (int id : g[v]) {
            int to = e[id].b;
            if (to != s) {
                players.push_back(id);
            }
        }
        assert(players.size() == 2);
        int x = e[players[0]].b - 1;
        int x_pts = e[players[0]].flow;
        int y = e[players[1]].b - 1;
        int y_pts = e[players[1]].flow;

        while (x_pts + y_pts < 3) {
            x_pts++;
        }
        a[x][y] = def[x_pts];
        a[y][x] = def[y_pts];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << a[i][j];
        }
        std::cout << std::endl;
    }


    return 0;
}