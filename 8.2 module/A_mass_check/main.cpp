#include <iostream>
#include <vector>
#include <random>

#define N 300000
#define A 1000000

std::vector<char> prime (A, true);

long long multiply(long long a, long long b, long long m) {
    if (b == 1)
        return a;
    if (b % 2 == 0)
        return (2 * multiply(a, b / 2, m)) % m;
    return (multiply(a, b - 1, m) + a) % m;
}

long long power(long long a, long long b, long long m) {
    if (b == 0)
        return 1;
    if (b % 2 == 0) {
        long long t = power(a, b / 2, m);
        return multiply(t, t, m) % m;
    }
    return (multiply(power(a, b - 1, m), a, m)) % m;
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// O (Log n)
bool check(long long x) {
    if (x == 2)
        return true;
    for (int i = 0; i < 100; i++) {
        long long a = (rand() % (x - 2)) + 2;
        if (gcd(a, x) != 1)
            return false;
        if (power(a, x - 1, x) != 1)
            return false;
    }
    return true;
}

// O (Sqrt n)
long long check2(long long a, long long i)
{
    return i * i <= a ? (a % i) && check2(a, i + 1) : 1;
}

// O (n Log Log n)
long long erat() {
    prime[0] = prime[1] = false;
    for (int i = 2; i <= A; ++i)
        if (prime[i])
            if (i * 1ll * i <= A)
                for (int j = i * i; j <= A; j += i)
                    prime[j] = false;
}

int main() {
    int n;
    std::cin >> n;

    erat();
    for (int i = 0; i < n; i++) {
        long long a;
        scanf("%lld", &a);
        if (prime[a]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}