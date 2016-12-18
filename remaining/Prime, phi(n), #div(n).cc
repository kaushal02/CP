int np(0), prime[N];
bool isprime[N];
void primes(int N) {
    memset(isprime, true, sizeof isprime);
    isprime[0] = isprime[1] = false;
	rep1(i,2,N-1) {
		if(isprime[i]) prime[++np] = i;
		rep1(j,1,np) {
			if(i * prime[j] > N) break;
			isprime[i * prime[j]] = false;
			if(i % prime[j] == 0) break;
		}
	}
}

int np(0), prime[N];
bool isprime[N];
void sieve(int N) {
    memset(isprime, true, sizeof isprime);
    isprime[0] = isprime[1] = false;
    rep1(i,2,N-1) if(isprime[i]) {
        rep1(j,i,N/i) isprime[i * j] = false;
        prime[++np] = i;
    }
}

inline ll phi(ll n) {
    // Calculates Totient(n). Needs prime[]. O(sqrt(n))
    ll ans = n;
    for(int i = 1; prime[i] <= n / prime[i]; ++i)
        if(n % prime[i] == 0) {
            ans -= ans/prime[i];
            while(n % prime[i] == 0)
                n /= prime[i];
        }
    if(n != 1)
        ans -= ans / n;
    return ans;
}

inline ll divnum(ll n) {
    // Counts number of divisors of n. Needs prime[]. O(sqrt(n))
    if(n < 1) return 0;
    ll ans(1), temp;
    for(int i = 1; prime[i] <= n / prime[i]; ++i)
        if(n % prime[i] == 0) {
            temp = 1;
            while(n % prime[i] == 0)
                temp++, n /= prime[i];
            ans *= temp;
        }
    ans <<= (n != 1);
    return ans;
}

inline ll divsum(ll n) {
    // Sum of divisors of n. Needs prime[]. O(sqrt(n))
    if(n < 1) return 0;
    ll ans(1), temp, cur;
    for(int i = 1; prime[i] <= n / prime[i]; ++i)
        if(n % prime[i] == 0) {
            temp = 1, cur = 1;
            while(n % prime[i] == 0)
                cur *= prime[i], temp += cur, n /= prime[i];
            ans *= temp;
        }
    ans *= (n != 1) + n;
    return ans;
}

inline ll mul(ll a, ll b, ll m) {
    long double temp = a;
    temp *= b;
    a *= b;
    b = temp / m;
    a -= b * m;
    return ((a % m) + m) % m;
}
inline ll pwr(ll a, ll n, ll m) {
    ll ans(1);
    while(n) {
        if(n & 1) ans = mul(ans, a, m);
        n >>= 1;
        a = mul(a, a, m);
    }
    return ans;
}
bool isp_miller(ll p) {
    // Checks whether p is prime. Needs pwr() and mul(). O(times * log p)
    if(p < 2) return false;
    if(p == 2) return true;
    if(p%2 == 0) return false;
    // write p-1 = s * 2 * 2 * .. * 2
    ll s = p - 1;
    while(s%2 == 0) s >>= 1;
    
    int times = 20;
    rep(i, times) {
        ll a = rand() % (p-1) + 1, temp = s;
        ll val = pwr(a, temp, p);
        while(temp != p-1 and val != 1 and val != p-1) {
            val = mul(val, val, p);
            temp <<= 1;
        }
        if(val != p-1 and temp % 2 == 0)
            return false;
    }
    return true;
}