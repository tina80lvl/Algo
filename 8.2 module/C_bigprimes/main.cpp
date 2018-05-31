#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>


long long multiply(long long a, long long b, long long m) {
    long long res = 0;
    while (b > 0) {
        if (b % 2 == 1) {
            b--;
            res = (res + a) % m;
        }
        a = (a + a) % m;
        b /= 2;
    }
    return res;

}

long long power(long long a, long long b, long long m) {
    long long ans = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            b--;
            ans = multiply(ans, a, m);
        }
        b /= 2;
        a = multiply(a, a, m);

    }
    return ans;
}

bool check(long long n) {
    if (n == 0 || n == 1)
        return false;
    if (n == 2 || n == 3)
        return true;

    long long s = 0, t = n - 1;
    while (t % 2 == 0) {
        t /= 2;
        s++;
    }

    for (int i = 0; i < 10; i++) {
        long long a = rand() % (n - 3) + 2;
        long long x = power(a, t, n);
        bool next_iteration = (x == 1) || (x == n - 1);
        if (next_iteration) continue;
        for (long long j = 0; j < s; j++) {
            x = power(x, 2, n);
            if (x == 1) return false;
            if (x == n - 1) {
                next_iteration = true;
                break;
            }
        }
        if (next_iteration) continue;
        return false;
    }
    return true;
}

int main() {
    srand(100500);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        long long k;
        scanf("%lld", &k);
        printf(check(k) ? "YES\n" : "NO\n");
    }
}
