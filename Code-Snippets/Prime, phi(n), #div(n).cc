int np, prime[N];
bool isprime[N];
void primes(int N) {
    memset(isprime, true, sizeof isprime);
    isprime[0] = isprime[1] = false;
	rep(i,N) if(i>1) {
		if(isprime[i]) prime[++np] = i;
		rep1(j,np) {
			if(i * prime[j] > N) break;
			isprime[i * prime[j]] = false;
			if(i % prime[j] == 0) break;
		}
	}
}

ll np, prime[N], q;
bool isp[N];
void sieve(ll N) {
	memset(isp, true, sizeof isp);
	isp[0] = isp[1] = false;
	for(ll i=2; i<N; i++) {
		if(isp[i]) {
			prime[++np]=i;
			for(ll j=2*i; j<N; j+=i) {
				isp[j]=false;
			}
		}
	}
}

int check(int n) {
    for(int i = 3; i <= sqrt(n); i += 2) if(n % i == 0) return 0;
    return 1;
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

ll phi[N];
inline void phis(ll N) {
    phi[1]=1;
    for(ll i=2; i<N; i++) if(!phi[i]) {
        phi[i] = i-1;
        for(ll j=2*i; j<N; j+=i) {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j]/i*(i-1);
        }
    }
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

inline ll add(ll a, ll b, ll m) {
	a%=m; if(a<0) a+=m;
	b%=m; if(b<0) b+=m;
	if(a+b<0 or a+b>=m) return (a-m)+b;
	return a+b;
}
inline ll mul(ll a, ll b, ll m) {
	a%=m; if(a<0) a+=m;
	b%=m; if(b<0) b+=m;
	ll q = ((dbl)a * (dbl)b) / (dbl)m;
	ll r = a*b - q*m;
	return (r<0 ? r+m:r);
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
ull myrand(ll n) {
	return rand()*rand()%n*rand()%n;
}
bool ispmiller(ll p) { // O(30*logp)
	if(p<2) return false;
	if(p==2) return true;
	if(p%2==0) return false;
	ll s=p-1; s>>=__builtin_ctzll(s);
	rep(i,30) {
		ll val=pwr(myrand(p-1)+1,s,p), temp=s;
		while(temp!=p-1 and con(val,2,p-2)) {
			val=mul(val,val,p);
			temp<<=1;
		}
		if(val!=p-1 and temp%2==0) return false;
	}
	return true;
}
inline ll pollardrho(ll n) { // O(n^0.25)
	if(n==1) return 1;
	if(n%2==0) return 2;
	ll c=myrand(n-1)+1, x=myrand(n-2)+2, y=x;
	ll d=1; while(d==1) {
		x=mul(x,x,n)+c; if(x>=n) x-=n;
		y=mul(y,y,n)+c; if(y>=n) y-=n;
		y=mul(y,y,n)+c; if(y>=n) y-=n;
		d=__gcd(abs(x-y),n);
		if(d==n) return (ispmiller(n) ? n:pollardrho(n));
	}
	return d;
}
