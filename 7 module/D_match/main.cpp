#include <iostream>
#include <vector>
#include <queue>
#include <map>

const int MAXN = 100500;

std::vector <std::vector<int>> g;
std::vector <int> match;
std::vector <bool> used;
int n, m, ans = 0;

void print_match () {
    for (int i = 0; i < m; i++) {
        std::cout << "from " << match[i] << " to " << i << std::endl;
    }
    std::cout << "EOM\n";
}

bool kuhn (int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (match[to] == -1 || kuhn(match[to])) {
            if (match[to] == -1)
                ++ans;
            match[to] = v;
//            print_match();
            return true;
        }
    }
    return false;
}


int main() {
    std::cin >> n >> m;

    g.resize(n);
    for (int i = 0; i < n; i++) {
        int a;
        while (std::cin >> a) {
            if (a == 0)
                break;
            --a;
            g[i].push_back(a);
        }
    }

    match.assign(m, -1);
    for (int i = 0; i < n; i++) {
        used.assign(n, false);
        kuhn(i);
    }

//    for (int i = 0; i < g.size(); i++) {
//        for (int j = 0; j < g[i].size(); j++) {
//            std::cout << g[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

    std::cout << ans << std::endl;
    for (int i = 0; i < m; i++) {
        if (match[i] != -1) {
            printf("%d %d\n", match[i] + 1, i + 1);
        }
    }

    return 0;
}