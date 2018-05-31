#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

int inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) {
        return 0;
    }
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }
    return x1;
}

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

int main() {
    unsigned n, e, c;
    unsigned long phi;

    std::cin >> n >> e >> c;
    if (n % 2 == 0) {
        phi = n / 2 - 1;
    } else {
        unsigned p = (unsigned) floor(sqrt(n));
        for (int i = 3; i <= p; i += 2) {
            if (n % i == 0) {
                p = i;
                break;
            }
        }
        unsigned q = n / p;
        phi = (p - 1) * (q - 1);
    }

    int d = inverse(e, (int) phi);
    std::cout << power(c, d, n) << std::endl;
}