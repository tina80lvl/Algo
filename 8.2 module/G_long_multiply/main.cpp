#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

int main() {
    std::string as, bs;
    std::cin >> as;
    std::cin >> bs;

    unsigned long long size_a = as.length();
    unsigned long long size_b = bs.length();
    unsigned long long length = size_a + size_b + 1;

    std::vector<int> a(size_a), b(size_b), c(length);
    for (long long i = size_a - 1; i >= 0; i--) {
        a[i] = (int) (as[i] - '0');
    }
    for (long long i = size_b - 1; i >= 0; i--) {
        b[i] = (int) (bs[i] - '0');
    }

    for (long long i = 0; i < size_a; i++) {
        for (int j = 0; j < size_b; j++) {
            c[i + j] += a[i] * b[j];
        }
    }

    for (long long i = 0; i < length; i++) {
        c[i + 1] +=  c[i] / 10;
        c[i] %= 10;
    }

    while (c[length - 1] == 0) {
        length--;
        c.pop_back();
    }

    for (long long i = length - 1; i >= 0; i--) {
        printf("%d", c[i]);
    }

    return 0;
}