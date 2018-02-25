/*
_dfs

DFS traversal without using inbuilt stack. Example where you need to do something before visiting child and undo it after the visit.
The same tree can be stored in stacks rather than vectors but it gives MLE on this judge.

Problem link:
https://courses.edx.org/courses/course-v1:ITMOx+I2CPx+3T2016/courseware/823f3cd014574b93afb5520087401895/03881171b78d4bb7b9e5ceb19df11461/
from the course "ITMOx: I2CPx How to win coding competitions: secrets of champions" on edX

O(m + n)
*/
#include <cstdio>
#include <vector>
inline void in(int &p) {
    p=0;register bool negative=false; register char ch=0;
    while(ch<0x30 or ch>0x39) {if(ch=='-') negative=true; ch=getchar();}
    while(ch>=0x30 and ch<=0x39) {p=(p<<1)+(p<<3)+(ch&15); ch=getchar();}
    if(negative) p=-p;
}

const int N = 1e6 + 10;
std::vector<int> t[N], wei, lost;
int par[N], w[N];
long long mass;
inline void release() {
    mass -= wei.back();
    wei.pop_back();
}
inline void receive(int tw) {
    mass += tw;
    wei.push_back(tw);
}
inline void reject() {
    mass -= wei.back();
    lost.push_back(wei.back());
    wei.pop_back();
}
inline void retrieve() {
    mass += lost.back();
    wei.push_back(lost.back());
    lost.pop_back();
}
inline void dfs(int V) {
    int v(V);
    long long ans(0);
    while(true) {
        if(t[v].empty()) {
            if(v == V) {
                printf("%I64d\n", ans);
                return;
            }
            ans += mass;
            if(w[v]) release();
            else retrieve();
            v = par[v];
        }
        else {
            int x = t[v].back(); t[v].pop_back();
            v = x;
            if(w[v]) receive(w[v]);
            else reject();
        }
    }
}

int main() {
    freopen("snowmen.in","r",stdin);
    freopen("snowmen.out","w",stdout);
    
    int n; in(n);
    for(int i = 1; i <= n; i++) {
        in(par[i]), in(w[i]);
        t[par[i]].push_back(i);
    }
    dfs(0);
    return 0;
}
