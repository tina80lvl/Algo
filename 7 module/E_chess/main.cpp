#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

const int N = 1000;

char a[N][N];
int n, m;
int lused[N], rused[N];
std::vector <int> g[N], revg[N];
int used[N], p[N];

bool dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (p[to] == -1 || (!used[p[to]] && dfs(p[to]))) {
            p[to] = v;
            return true;
        }
    }
    return false;
}

int tp1(int i, int j) {
    return i + j;
}

int tp2(int i, int j) {
    return m - 1 + i - j;
}

struct painting {
    int tp, x, y;
    char color;

    painting(int tp, int x, int y, char color) :
            tp(tp), x(x), y(y), color(color) {}
};

void go(int v) {
    lused[v] = true;
    for (int to : g[v]) {
        rused[to] = true;
        if (p[to] != -1 && !lused[p[to]]) {
            go(p[to]);
        }
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    int sz = n + m - 1;

    std::vector <std::pair<int, int>> kors1(sz);
    std::vector <std::pair<int, int>> kors2(sz);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            kors1[tp1(i, j)] = std::make_pair(i, j);
            kors2[tp2(i, j)] = std::make_pair(i, j);
        }
    }

    int ans = n * m + 200;
    std::vector <painting> ret;

    for (int odd = 0; odd < 2; odd++) {
        for (int i = 0; i < sz; i++) {
            g[i].clear();
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (odd == 0) {
                    if ((i + j) % 2 == 0 && a[i][j] == 'B') {
                        g[tp1(i, j)].push_back(tp2(i, j));
                        revg[tp2(i, j)].push_back(tp1(i, j));
                    }
                    if ((i + j) % 2 == 1 && a[i][j] == 'W') {
                        g[tp1(i, j)].push_back(tp2(i, j));
                        revg[tp2(i, j)].push_back(tp1(i, j));
                    }
                } else {
                    if ((i + j) % 2 == 0 && a[i][j] == 'W') {
                        g[tp1(i, j)].push_back(tp2(i, j));
                        revg[tp2(i, j)].push_back(tp1(i, j));
                    }
                    if ((i + j) % 2 == 1 && a[i][j] == 'B') {
                        g[tp1(i, j)].push_back(tp2(i, j));
                        revg[tp2(i, j)].push_back(tp1(i, j));
                    }
                }
            }
        }
        int cans = 0;
        std::fill(used, used + sz, 0);
        for (int i = 0; i < sz; i++) {
            p[i] = -1;
        }
        for (int i = 0; i < sz; i++) {
            std::fill(used, used + sz, 0);
            if (dfs(i)) {
                cans++;
            }
        }
        if (cans < ans) {
            ans = cans;
            std::vector <int> x(sz);
            for (int i = 0; i < sz; i++) {
                if (p[i] != -1) {
                    int from = p[i];
                    g[from].erase(find(g[from].begin(), g[from].end(), i));
                    x[from] = true;
                }
            }
            std::fill(lused, lused + sz, 0);
            std::fill(rused, rused + sz, 0);

            for (int i = 0; i < sz; i++) {
                if (!x[i] && !lused[i]) {
                    go(i);
                }
            }
            ret.clear();

            for (int i = 0; i < sz; i++) {
                if (!lused[i]) {
                    int x = kors1[i].first;
                    int y = kors1[i].second;
                    ret.push_back(painting(1, x, y, (x + y) % 2 == odd ? 'W' : 'B'));
                }
            }
            for (int i = 0; i < sz; i++) {
                if (rused[i]) {
                    int x = kors2[i].first;
                    int y = kors2[i].second;
                    ret.push_back(painting(2, x, y, (x + y) % 2 == odd ? 'W' : 'B'));
                }
            }
        }
    }

    std::cout << ans << std::endl;
    for (auto p : ret) {
        std::cout << p.tp << " " << p.x + 1 << " " << p.y + 1 << " " << p.color << "\n";
    }

    return 0;
}