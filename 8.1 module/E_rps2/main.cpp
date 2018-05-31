#include <iostream>
#include <cmath>


int main() {
    freopen("rps2.in", "r", stdin);
    freopen("rps2.out", "w", stdout);

    long long r1, s1, p1, r2, s2, p2, r, p, s, ans;

    std::cin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;

    r = r1 - r2 - p2;
    s = s1 - s2 - r2;
    p = p1 - p2 - s2;

    ans = 0;
    if (r > ans) {
       ans = r;
    }
    if (s > ans) {
        ans = s;
    }
    if (p > ans) {
        ans = p;
    }


//    ans = r1 + s1 + p1;
//
//    r = std::min(r2, s1);
//    r2 -= r;
//    s1 -= r;
//    ans -= r;
//    p = std::min(p2, r1);
//    p2 -= p;
//    r1 -= p;
//    ans -= p;
//    s = std::min(s2, p1);
//    s2 -= s;
//    p1 -= s;
//    ans -= s;
//    if (r2 > 0) {
//        if (r1 >= 0) {
//            ans -= std::min(r1, r2);
//        }
//    }
//    if (s2 > 0) {
//        if (s1 >= 0) {
//            ans -= std::min(s1, s2);
//        }
//    }
//    if (p2 > 0) {
//        if (p1 >= 0) {
//            ans -= std::min(p1, p2);
//        }
//    }

    std::cout << ans << std::endl;

    return 0;
}