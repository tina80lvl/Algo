#include <iostream>
#include <vector>
#include <cstdio>

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
    used.assign (n, 0);

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
        return tree[I];
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
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);

    int root = 1;
    int n;
    cin >> n;
//    cout << n;
    graph tree(n + 1, vector <int> ());

    for (int i = 2; i < n + 1; i++){ //храним списком смежности
        int x;
        cin >> x;
        tree[i].push_back(x);
        tree[x].push_back(i);
    }

//    for (int i = 0; i < tree.size(); i++){
//        cout << i << ": ";
//        for (int j = 0; j < tree[i].size(); j++){
//            cout << tree[i][j] << " ";
//        }
//        cout << endl;
//    }

    lca_prepare (tree, root);

    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int v1, v2; // поступил запрос
        cin >> v1 >> v2;
        cout << lca (v1, v2) << endl; // ответ на запрос
    }
    return 0;
}