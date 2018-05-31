#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define BLOCK_SIZE 16384

int main() {

    int32_t n, x, h = 0;
    std::cin >> n >> x;

    unsigned nsqrt = (unsigned) floor(sqrt(n)) + 1;
    std::vector<bool> is_prime(nsqrt, true);
    is_prime[0] = false;
    is_prime[1] = false;
    std::vector<unsigned> primes;
    for (unsigned i = 2; i < nsqrt; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (unsigned j = i * i; j < nsqrt; j += i) {
                is_prime[j] = false;
            }
        }
    }

    std::vector<bool> block;
    for (unsigned k = 0; k <= n / BLOCK_SIZE; ++k) {
        block.assign(BLOCK_SIZE, false);
        int start = k * BLOCK_SIZE;
        for (unsigned i = 0; i < primes.size(); ++i) {
            int start_idx = (start + primes[i] - 1) / primes[i];
            for (int j = std::max(start_idx, 2) * primes[i] - start; j < BLOCK_SIZE; j += primes[i])
                block[j] = true;
        }
        if (k == 0)
            block[0] = block[1] = true;
        for (unsigned i = 0; (i < BLOCK_SIZE) && (start + i <= n); ++i)
            if (!block[i])
                h = (long) h * (long) x + (long) start + i;
    }

    std::cout << h << std::endl;

    return 0;
}