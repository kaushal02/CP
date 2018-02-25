/*
_offline _policy_tree

Using ordered_set to get the rank of an element in a multiset
O(n*sqrt(n)*log(n))
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define rep(i,n) for(int i = 0, _n = (n); i < _n; i++)
const int N = 5e4 + 10, k = 225;
 
struct point {
    int x, y, z, id, yid;
} p[N];
ordered_set<pair<int,int>> s[k];
set<pair<int,int>> ss[k];
int n, ans[N];
 
int main() {
    cin >> n;
    rep(i,n) cin >> p[i].x >> p[i].y >> p[i].z, p[i].id = i;
    
    sort(p, p + n, [](point a, point b){return a.y < b.y;});
    rep(i,n) p[i].yid = i / k;
    
    sort(p, p + n, [](point a, point b){return a.x < b.x;});
    rep(i,n) {        
        rep(j,p[i].yid) ans[p[i].id] += s[j].order_of_key({p[i].z,i});
        s[p[i].yid].insert({p[i].z,i});
        for(auto ele: ss[p[i].yid]) if(ele.first <= p[i].y and ele.second <= p[i].z) ans[p[i].id]++;
        ss[p[i].yid].insert({p[i].y,p[i].z});
    }
    rep(i,n) cout << ans[i] << ' ';
}
