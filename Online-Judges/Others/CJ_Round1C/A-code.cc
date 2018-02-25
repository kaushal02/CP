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
ifstream fin;
ofstream fout;

//inline void evacuate(map<char,int> my) {
//    if(my.size() == 2) {
//        map<char,int>::iterator it1 = my.begin(), it2 = my.begin(); it2++;
//        while(it1->Y) {
//            fout << it1->X << it2->X << " ";
//            it1->Y -= 1;
//        }
//        fout << "\n";
//        return;
//    }
//    
//    int m = 0; for(auto x: my) m = max(m, x.Y);
//    
//    map<char,int>::iterator it = my.begin();
//    while(it->Y != m) it++;
//    
//    fout << it->X << " ";
//    it->Y -= 1;
//    if(it->Y == 0) my.erase(it);
//    evacuate(my);
//}

inline void evacuate(map<char,int> my) {
    int tot = 0; for(auto x: my) tot += x.Y;
    if(tot == 0) {
        fout << endl;
        return;
    }
    
    int m = 0; for(auto x: my) m = max(m, x.Y);
    map<char,int>::iterator it = my.end(); it--;
    while(it->Y != m) it--;
    
    if(it->Y == tot - it->Y + 2) {
        fout << it->X << it->X << " ";
        it->Y -= 2;
        if(it->Y == 0) my.erase(it);
        evacuate(my);
    }
    else if(it->Y == tot - it->Y + 1) {
        fout << it->X << " ";
        it->Y -= 1;
        if(it->Y == 0) my.erase(it);
        evacuate(my);
    }
    else if(it->Y == tot - it->Y) {
        fout << it->X;
        it->Y -= 1;
        if(it->Y == 0) {
            my.erase(it);
            it = my.begin();
            
            fout << it->X << " ";
            it->Y -= 1;
            if(it->Y == 0) my.erase(it);
            
            evacuate(my);
        }
        else {
            if(it == my.begin()) it++; else it--;
            
            fout << it->X << " ";
            it->Y -= 1;
            if(it->Y == 0) my.erase(it);
            
            evacuate(my);
        }
    }
    else {
        if(it == my.begin()) it++; else it--;
        
        fout << it->X << " ";
        it->Y -= 1;
        if(it->Y == 0) my.erase(it);
        
        evacuate(my);
    }
}

int main() {
    fin.open("A-large.in");
    fout.open("A-large.out");
//    IO("A-small-attempt0.in","A-small-attempt0.txt");
    int t;fin>>t;rep1(_t,1,t){
        int n; fin >> n;
        map<char,int> my;
        rep(i,n) fin >> my['A'+i];
        fout << "Case #" << _t << ": ";
        evacuate(my);
    }
    return 0;
}