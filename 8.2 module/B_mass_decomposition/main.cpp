#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

#define N 300000
#define A 1000000

std::vector<unsigned> prime(1000001, 1);

void print_mult(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << " ";
    }
    std::cout << std::endl;

}

void erat() {
    for (unsigned i = 2; i * i < prime.size(); ++i) {
        for (unsigned j = 2 * i; j < prime.size(); j += i) {
            if (prime[j] == 1) {
                prime[j] = i;
            }
        }
    }
}

int main() {
    unsigned n;
    scanf("%u", &n);
    erat();
    for (unsigned i = 0; i < n; ++i) {
        unsigned k;
        scanf("%u", &k);
        while (prime[k] != 1) {
            printf("%u ", prime[k]);
            k /= prime[k];
        };
        if (k != 1) {
            printf("%u ", k);
        }
        printf("\n");
    }
    return 0;
}