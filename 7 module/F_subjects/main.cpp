#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <assert.h>
#include <stdio.h>

const int N = 500;
bool g[N][N];
int n, used[N], par[N];
const double EPS = 0.0000000001;

struct point {
    int x, y;
} p[N];

struct sbj {
    point pos;
    int v;
} b[N];

bool dfs(int v) {
    used[v] = true;
    for (int to = 0; to < n; to++) {
        if (!g[v][to]) continue;
        if (par[to] == -1 || (!used[par[to]] && dfs(par[to]))) {
            par[to] = v;
            return true;
        }
    }
    return false;
}

int matches() {
    for (int i = 0; i < n; i++) {
        par[i] = -1;
    }
    std::vector <bool> used2(n);
    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int from = 0; from < n; from++) {
            if (!used2[from] && g[from][i]) {
//                std::cerr << from << " ";
                par[i] = from;
                used2[from] = true;
                ret++;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!used2[i]) {
            std::fill(used, used + n, false);
            if (dfs(i)) {
                ret++;
            }
        }
    }
    return ret;
}

bool achieve(sbj b, point p, double time) {
    int dx = b.pos.x - p.x;
    int dy = b.pos.y - p.y;
    double loc = sqrt(dx * dx + dy * dy) / b.v;
    return loc < time + EPS;
}

bool proof(double time) {
    for (int v = 0; v < n; v++) {
        for (int to = 0; to < n; to++) {
            if (achieve(b[v], p[to], time)) {
                g[v][to] = true;
            } else {
                g[v][to] = false;
            }
        }
    }

    return matches() == n;
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> b[i].pos.x >> b[i].pos.y >> b[i].v;
        assert(b[i].v > EPS);
    }
    for (int i = 0; i < n; i++) {
        std::cin >> p[i].x >> p[i].y;
    }

    // cout << "Proof(1.5) = " << (proof(1.5) ? "True" : "False") << "\n";

    double l = 0, r = (double) 100000000;
    for (int it = 0; it < 200; it++) {
        double m = (l + r) / 2.0;
        if (proof(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    std::cout << std::fixed << std::setprecision(4) << r << std::endl;
    return 0;
}