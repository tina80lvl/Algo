#include <iostream>
#include <vector>
#include <cstdio>
#include <tuple>

#if 0
using namespace std;

typedef vector <vector<int>> graph;

vector<int> hight, //список высот
        path, //список путей
        first, //хранит первое вхождение вершины в список пути (позиция в нём)
        tree;
vector<char> used;

void dfs (const graph & g, int v, int h = 1)
{
    used[v] = true; //юзаем вершину
    hight[v] = h; //присваиваем высоту
    path.push_back (v);//добавляем в список пути
    for (auto i = g[v].begin(); i != g[v].end(); ++i)
        if (!used[*i])
        {
            dfs (g, *i, h+1);//
            path.push_back (v); //добавляем, когда выходим
        }
}

std::tuple<int, bool, bool> cool_lca (const graph & g, int v, int h = 1, int a = 1, int b = 1)
{
    used[v] = true; //юзаем вершину
    hight[v] = h; //присваиваем высоту
    path.push_back (v);//добавляем в список пути
    bool resa = v == a;
    bool resb = v == b;
    for (auto i = g[v].begin(); i != g[v].end(); ++i)
        if (!used[*i])
        {
            bool cresa, cresb;
            int cres;
            std::tie(cres, cresa, cresb) = cool_lca (g, *i, h+1, a, b);//
            if (cresa && cresb)
                return std::make_tuple(cres, cresa, cresb);

            resa = resa || cresa;
            resb = resb || cresb;

            path.push_back (v); //добавляем, когда выходим
        }

    return std::make_tuple(v, resa, resb);
}


void build (int i, int l, int r)
{
    if (l == r)
        tree[i] = path[l];
    else
    {
        int m = (l + r) >> 1;
        build (i+i, l, m);
        build (i+i+1, m+1, r);
        if (hight[tree[i+i]] < hight[tree[i+i+1]])
            tree[i] = tree[i+i];
        else
            tree[i] = tree[i+i+1];
    }
}

void lca_prepare (const graph & g, int root)
{
    int n = (int) g.size();
    hight.resize (n);
    path.reserve (n * 2);
    used.assign (n + 1, 0);

    dfs (g, root);

    int m = (int) path.size();
    tree.assign (path.size() * 4 + 1, -1);
    build (1, 0, m-1);

    first.assign (n, -1);
    for (int i = 0; i < m; ++i)
    {
        int v = path[i];
        if (first[v] == -1) //хранит !!!первое!!! вхождение
            first[v] = i;
    }
}

int lca_min (int i, int sl, int sr, int l, int r)
{
    if (sl == l && sr == r)
        return tree[i];
    int sm = (sl + sr) >> 1;
    if (r <= sm)
        return lca_min (i+i, sl, sm, l, r);
    if (l > sm)
        return lca_min (i+i+1, sm+1, sr, l, r);
    int ans1 = lca_min (i+i, sl, sm, l, sm);
    int ans2 = lca_min (i+i+1, sm+1, sr, sm+1, r);
    return hight[ans1] < hight[ans2] ? ans1 : ans2;
}

int lca (int a, int b)
{
    int left = first[a],
            right = first[b];
    if (left > right)
        swap (left, right);
    return lca_min (1, 0, (int)path.size()-1, left, right);
}


int main() {
    freopen("ancestor.in", "r", stdin);
    freopen("ancestor.out", "w", stdout);

    int root = 1;
    int n;
    cin >> n;
//    cerr << n << " " << hh << endl;

//    if (n == 1){
//        int m;
//        cin >> m;
////        cerr << m << endl;
//        for (int i = 0; i < m; i++)
//        {
//            int v1, v2; // поступил запрос
//            cin >> v1 >> v2;
//            if  (v1 == v2){
//                cout << 1 << endl;
//            }
//            else{
//                cout << 0 << endl;
//            }
//        }
//        return 0;
//    }

    graph ltree(n + 1, vector <int> ());

    for (int i = 1; i < n+1; i++){ //храним списком смежности
        int x;
        cin >> x;
        if (x == 0) continue;
        ltree[i].push_back(x);
        ltree[x].push_back(i);
    }

//    for (int i = 0; i < n+1; i++){
//        cerr << i << ": ";
//        for (int j = 0; j < tree[i].size(); j++){
//             cerr << tree[i][j] << " ";
//        }
//        cerr << endl;
//    }

    lca_prepare (ltree, root);

    hight.resize (n);
    path.reserve (n * 2);
    used.assign (n, 0);

    int m;
    cin >> m;
//    cerr << m << endl;
    for (int i = 0; i < m; i++)
    {
        int v1, v2; // поступил запрос
        cin >> v1 >> v2;
        if  (v1 == v2){
            cout << 0 << endl;
        }
        else{
            int res = 0;
            bool has_a, has_b;
            //path.clear();
            //used.assign (n + 1, 0);
            //std::tie(res, has_a, has_b) = cool_lca(ltree, 1, 1, v1, v2);
            //cout << res << " " << has_a << " " << has_b << std::endl;
            if (lca(v1, v2) == v1) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
    return 0;
}
#endif

int main() {
    freopen("ancestor.in", "r", stdin);
    freopen("ancestor.out", "w", stdout);

    int root = 1;
    int n;
    std::cin >> n;

    std::vector<int> parents(n);

    for (int i = 0; i < n; i++){ //храним списком смежности
        std::cin >> parents[i];
        --parents[i];
    }

    std::vector<int> dsteps;

    for (int i = 1; i < n; i *= 2) {
        dsteps.push_back(i);
    }



    int m;
    std::cin >> m;
//    cerr << m << endl;
    for (int i = 0; i < m; i++)
    {
        int v1, v2; // поступил запрос
        cin >> v1 >> v2;
        if  (v1 == v2){
            cout << 0 << endl;
        }
        else{
            int res = 0;
            bool has_a, has_b;
            //path.clear();
            //used.assign (n + 1, 0);
            //std::tie(res, has_a, has_b) = cool_lca(ltree, 1, 1, v1, v2);
            //cout << res << " " << has_a << " " << has_b << std::endl;
            if (lca(v1, v2) == v1) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
    return 0;
}