// http://acm.timus.ru/problem.aspx?space=1&num=1846
// _augmented_tree

// g++ -std=c++11 -O2 -DLOCAL a.cc -o a
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define sz(c) (ll)c.size()
#define rep(i,n) for(ll i = 0, _n = (n); i < _n; i++)
#define rep1(i,a,b) for(ll i = a, _b = (b); i <= _b; i++)
#define rep2(i,b,a) for(ll i = b, _a = (a); i >= _a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define eb emplace_back // tie, ignore, get<i>(a)
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define case(ans) "Case #" << _t << ": " << ans << "\n"
#define cout(d) cout << fixed << setprecision(d)
#define err(x) cerr << #x << " = " << x << '\n'
const ll mod = 1e9 + 7, inf = 1e16, N = 2e6 + 10;
const double eps = 1e-16;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
template<class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct my_node_update {
    typedef int metadata_type; // change
    virtual Node_CItr node_begin() const=0;
    virtual Node_CItr node_end() const=0;
    virtual ~my_node_update() {}

    void init(metadata_type &a) {
    	// update
    	a = 0;
    }
    int gcd() {
		auto it = node_begin();
        if(it == node_end()) return 1;
        return it.get_metadata();
    }

    void operator()(Node_Itr it, Node_CItr it_end) {
        auto l = it.get_l_child();
        auto r = it.get_r_child();
        metadata_type lt, rt;
        init(lt), init(rt);
        if(l != it_end) lt = l.get_metadata();
        if(r != it_end) rt = r.get_metadata();
        const_cast<metadata_type&>(it.get_metadata()) =
        	__gcd((*it)->X, __gcd(lt, rt)); // change
    }
};
template <typename T> using TREE =  tree<T, T, less<T>, rb_tree_tag, my_node_update>;

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    clock_t _start = clock();
    fprintf(stderr, "Execution started\n");
#endif
    ios::sync_with_stdio(0); cin.tie(0);

    TREE<int> tr;
    int t, n; cin >> t;
    char c;
    while(t--) {
    	cin >> c >> n;
    	if(c == '+') {
    		tr[n]++;
    	}
    	else if(c == '-') {
    		tr[n]--;
    	}
    	else assert(0);

    	if(!tr[n]) tr.erase(n);
    	cout << tr.gcd() << '\n';
    }

#ifdef LOCAL
    clock_t _end = clock();
	double _time = (double) (_end - _start) / CLOCKS_PER_SEC;
	fprintf(stderr, "Total running time: %.3lf s\n", _time);
#endif
    return 0;
}
