ll __d, __x, __y;
void extendedEuclid(ll _A, ll _B) {
    // Gives solutions to Ax + By = __gcd(x, y)
    if(_B == 0LL) {
        __d = _A;
        __x = 1LL;
        __y = 0LL;
    }
    else {
        extendedEuclid(_B, _A % _B);
        int _temp = __x;
        __x = __y;
        __y = _temp - _A / _B * __y;
    }
}

inline ll inv(ll n, ll m) {
    // inv(n) modulo m
    extendedEuclid(n, m);
    if(__d == 1) return (__x % m + m) % m;
    else return -1;
}