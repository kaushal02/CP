// Time erodes gratitude more quickly than it does beauty!
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define X first
#define Y second
#define rep(i,n) for(int i=0, _n=(n); i<_n; i++)
#define rep1(i,a,b) for(int i=a,_b=(b); i<=_b; i++)
#define rep2(i,b,a) for(int i=b,_a=(a); i>=_a; i--)
#define mem(a,val) memset(a, (val), sizeof a)
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define all(c) (c).begin(), (c).end()
#define uni(c) c.resize(distance(c.begin(), unique(all(c))))
#define fix(c,sz_val...) c.clear();c.resize(sz_val);
#define tr(c,it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define cases int t;cin>>t;rep1(_t,1,t)
#define case(ans) "Case #"<<_t<<": "<<ans<<"\n"
#define cout(d) cout<<fixed<<setprecision(d)
#define IO(i, o) ifstream cin(i);ofstream fout(o)
#define io ios_base::sync_with_stdio(false);cin.tie(NULL);
#define err(x) cerr << #x << " = " << x << '\n'
const int mod = 1e9 + 7;

#define show(aa,bb,cc) rep1(a,1,aa)rep1(b,1,bb)rep1(c,1,cc) fout << a << " " << b << " " << c << "\n";

int main() {
    IO("C-small-practice.in","C-small-practice.txt");
    int j,p,s,k;
    cases {
        cin >> j >> p >> s >> k;
        if(s == 1) {
            fout << case(1);
            show(1,1,1);
        }
        if(s == 2 and p == 1) {
            if(k == 1) {
                fout << case(1);
                show(1,1,1);
            }
            else {
                fout << case(2);
                show(1,1,2);
            }
        }
        if(s == 2 and p == 2 and j == 1) {
            if(k == 1) {
                fout << case(2);
                fout << "1 1 1\n1 2 2\n";
            }
            else {
                fout << case(4);
                show(1,2,2);
            }
        }
        if(s == 2 and p == 2 and j == 2) {
            if(k == 1) {
                fout << case(4);
                fout << "1 1 1\n1 2 2\n2 1 2\n2 2 1\n";
            }
            else {
                fout << case(8);
                show(2,2,2);
            }
        }
        if(s == 3 and p == 1) {
            if(k == 1) {
                fout << case(1);
                show(1,1,1);
            }
            else if(k == 2) {
                fout << case(2);
                show(1,1,2);
            }
            else {
                fout << case(3);
                show(1,1,3);
            }
        }
        if(s == 3 and p == 2 and j == 1) {
            if(k == 1) {
                fout << case(2);
                fout << "1 1 1\n1 2 2\n";
            }
            else if(k == 2) {
                fout << case(4);
                show(1,2,2);
            }
            else {
                fout << case(6);
                show(1,2,3);
            }
        }
        if(s == 3 and p == 2 and j == 2) {
            if(k == 1) {
                fout << case(4);
                fout << "1 1 1\n1 2 2\n2 1 2\n2 2 3\n";
            }
            else if(k == 2) {
                fout << case(8);
                show(2,2,2);
            }
            else {
                fout << case(12);
                show(2,2,3);
            }
        }
        if(s == 3 and p == 3 and j == 1) {
            if(k == 1) {
                fout << case(3);
                fout << "1 1 1\n1 2 2\n1 3 3\n";
            }
            else if(k == 2) {
                fout << case(6);
                fout << "1 1 1\n1 1 2\n1 2 1\n1 2 3\n1 3 2\n1 3 3\n";
            }
            else {
                fout << case(9);
                show(1,3,3);
            }
        }
        if(s == 3 and p == 3 and j == 2) {
            if(k == 1) {
                fout << case(6);
                fout << "1 1 1\n1 2 2\n1 3 3\n2 1 3\n2 2 1\n2 3 2\n";
            }
            else if(k == 2) {
                fout << case(12);
                rep1(a,1,2)rep1(b,1,3)rep1(c,1,3)if(b!=c)fout << a << " " << b << " " << c << "\n";
            }
            else {
                fout << case(18);
                show(2,3,3);
            }
        }
        if(s == 3 and p == 3 and j == 3) {
            if(k == 1) {
                fout << case(9);
                fout << "1 1 1\n1 2 2\n1 3 3\n2 1 2\n2 2 3\n2 3 1\n3 1 3\n3 2 1\n3 3 2\n";
            }
            else if(k == 2) {
                fout << case(18);
                rep1(a,1,3)rep1(b,1,3)rep1(c,1,3)if(c%3 != (a+b+1)%3)fout << a << " " << b << " " << c << "\n";
            }
            else {
                fout << case(27);
                show(3,3,3);
            }
        }
    }
    return 0;
}