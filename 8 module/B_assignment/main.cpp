#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> g;
const int INF = 2000000000;

int main() {
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
    int n = 0, m, c;

    std::cin >> n;
    m = n;

    g.resize(n + 1);
    g[0] = std::vector<int>(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        g[i].push_back(0);
        for (int j = 1; j <= m; j++) {
            std::cin >> c;
            g[i].push_back(c);
        }
    }

    std::vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        std::vector<int> minv(m + 1, INF);
        std::vector<char> used(m + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;
            for (int j = 1; j <= m; ++j)
                if(!used[j]) {
                    int cur = g[i0][j] - u[i0] - v[j];
                    if(cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if(minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if(used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    std::vector<std::pair<int, int>> answer;
    long sum = 0;
    for (int j = 1; j <= m; ++j) {
        answer.push_back(std::make_pair(p[j], j));
        sum += g[p[j]][j];
    }

    std::cout << sum << std::endl;
    for (int i = 0; i < answer.size(); i++) {
        std::cout << answer[i].first << " " << answer[i].second << std::endl;
    }

    return 0;
}