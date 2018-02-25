ll fac[N], inv[N];
inline void init(int N) {
	fac[0]=1; rep1(i,N) fac[i]=fac[i-1]*i%mod;
	inv[N]=pwr(fac[N],mod-2);
	for(ll i=N; i>=1; i--) inv[i-1]=inv[i]*i%mod;
}
inline ll ncr(ll n, ll r) {
	if(n<0 or r<0 or n<r) return 0;
	return fac[n]*inv[r]%mod*inv[n-r]%mod;
}
/**************************************************/
ll lucas(ll n, ll r) {
    if(n+r==0) return 1;
    ll ni=n%mod, ri=r%mod;
    if(ri>ni) return 0;
    return lucas(n/mod,r/mod)*ncr(ni,ri)%mod;
}
/**************************************************/
ll eed, eex, eey;
inline void ee(ll a, ll b) { // a,b < 1e18
    // Gives solutions to ax + by = __gcd(a,b)
    if(!b) eed=a, eex=1, eey=0;
    else {
		ee(b, a%b);
        ll t=eex;
		eex=eey;
		eey=t - a/b*eey;
    }
}
inline ll inv(ll n, ll m) { // n,m < 1e18
    ee(n, m); assert(eed==1);
	eex%=m; return (eex<0 ? eex+m:eex);
}
/**************************************************/
ll np, prime[N];
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
inline ll pwr(ll a, ll n, ll m) {
    ll ans=1; a%=m;
    while(n) {
		if(n&1) ans=ans*a%m;
		if(n>>=1) a=a*a%m;
    }
    return ans%m;
}
inline ll pwrp(ll n, ll p) {
    ll ans=0;
    while(n) ans+=n/=p;
    return ans;
}
inline ll inv(ll n, ll p, ll pp) {
	return pwr(n,pp-pp/p-1,pp);
}
inline ll nmodpk(ll n, ll p, ll pp) {
    vector<ll> a(pp+1);
    a[0]=1; rep1(i,pp) a[i]=a[i-1]*(i%p?i:1)%pp;

    ll ans=1;
    while(n) {
		ans=ans*a[n%pp]*pwr(a[pp],n/pp,pp)%pp;
		n/=p;
    }
    return ans%pp;
}
inline ll ncrmodpk(ll n, ll r, ll p, ll pp) {
    ll d = pwrp(n,p)-pwrp(r,p)-pwrp(n-r,p);
    return pwr(p,d,pp)*nmodpk(n,p,pp)%pp*inv(nmodpk(r,p,pp)*nmodpk(n-r,p,pp),p,pp)%pp;
}
inline ll ncr2(ll n, ll r, ll m) {
    ll ans=0, M=m;
	for(int i=1; prime[i]<=m/prime[i]; i++) {
		if(m%prime[i]==0) {
			ll m1=1; while(m%prime[i]==0) m/=prime[i], m1*=prime[i];
			ans += ncrmodpk(n,r,prime[i],m1)*(M/m1)*inv(M/m1,prime[i],m1)%M;
		}
	}
	if(m!=1) ans += ncrmodpk(n,r,m,m)*(M/m)*inv(M/m,m,m)%M;
	return ans % M;
}
