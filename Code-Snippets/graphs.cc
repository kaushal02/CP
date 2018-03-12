vi t[N];
int n, vis[N];
stack<int> cycle;
inline int cycledfs(int v) {
    vis[v]++;
    for(int ch: t[v]) {
        if(vis[ch] == 0) {
            int vf = cycledfs(ch);
            if(vf == 0) continue;
            if(vf > 0) cycle.push(v);
            if(vf == v) vf = -1;
            return vf;
        }
        else if(vis[ch] == 1) {
            cycle.push(v);
            return ch;
        }
    }
    vis[v]++;
    return 0;
}
inline void cyclefind() {
    // For undirected graph, change cycledfs(v) to cycledfs(v,p)
    rep1(i,n) vis[i]=0;
    while(!cycle.empty()) cycle.pop();
    rep1(i,n)for(int ch: t[i]) if(ch==i) { cycle.push(i); return;} // handling loops
    rep1(i,n) sort(all(t[i])), uni(t[i]); // handling multi-edges
    rep1(i,n) if(!vis[i]) if(cycledfs(i)==-1) return;
}
//----------------------------------------------------------------------------//
vector<pll> t[N];
ll n, dis[N];
inline void bellmanford(int s) {
    rep1(i,n) dis[i] = inf; dis[s] = 0;
    queue<int> q;
    rep1(k,n) {
        rep1(i,n) for(auto x: t[i]) {
            if(dis[i] < inf and dis[i] + x.Y < dis[x.X]) {
                if(k < n) {
                    dis[x.X] = dis[i] + x.Y;
                    if(dis[x.X] > inf) dis[x.X] = inf;
                    if(dis[x.X] < -inf) dis[x.X] = -inf;
                }
                else q.push(x.X);
            }
        }
    }
    while(!q.empty()) {
        int v = q.front(); q.pop();
        if(dis[v] == -inf) continue;
        dis[v] = -inf;
        for(auto x: t[v]) q.push(x.X);
    }
}