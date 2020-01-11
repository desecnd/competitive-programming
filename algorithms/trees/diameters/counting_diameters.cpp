#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using graph = vector<vi>;
#define all(x) begin(x), end(x)

pair<int,int> findCenters(graph& G, int V, int& diameter) {
    vi level(V, -1);
    vi deg(V, -1);
    queue<int> Q;

    for (int i = 0; i < V; i++) {
        deg[i] = G[i].size();
        if ( deg[i] == 1 ) {
            level[i] = 0; Q.push(i);
        }
    }

    while ( Q.size() ) {
        int v = Q.front(); Q.pop();
        for (int u : G[v]) {
            deg[u]--;

            if ( deg[u] == 1 ) {
                Q.push(u);
                level[u] = level[v] + 1;
            }
        }
    } 

    int maxLevel = *max_element(all(level));
    pair<int,int> p { -1, -1 };

    for (int v = 0; v < V; v++) {
        if ( level[v] == maxLevel ) {
            if ( p.first == -1 ) p.first = v;
            else p.second = v;
        }
    }

    if ( p.second == -1 ) diameter = 2 * maxLevel;
    else diameter = 2 * maxLevel + 1;

    return p;
}

int depthCnt(graph& G, int v, int a, int level, int target) {
    int cnt = 0;
    if ( level == target ) cnt++;

    for (int u : G[v]) {
        if ( a == u ) continue;

        cnt += depthCnt(G, u, v, level + 1, target);
    }

    return cnt;
}

ll countOneCenter(graph& G, int V, int c, int derimeter) {
    ll ans = 0;
    ll vSum = 0;

    for ( int u : G[c] ) {
        int cnt = depthCnt(G, u, c, 1, derimeter/2);
        ans += cnt * vSum;
        vSum += cnt;
    }

    return ans;
}

ll countTwoCenters(graph& G, int V, int c1, int c2, int derimeter ) {
    ll cnt1 = depthCnt(G, c1, c2, 0, (derimeter - 1)/2);
    ll cnt2 = depthCnt(G, c2, c1, 0, (derimeter - 1)/2);
    ll ans = cnt1 * cnt2;
    return ans;
}

void go() {
    int V, E;
    cin >> V; E = V - 1;

    graph T(V);
    for (int e = 0; e < E; e++) {
        int v,u; cin >> v >> u;
        v--, u--;

        T[v].push_back(u);
        T[u].push_back(v);
    }

    int diameter = 0;
    auto p = findCenters(T, V, diameter);

    if ( p.second == -1 ) 
        cout << countOneCenter(T, V, p.first, diameter) << "\n";
    else 
        cout << countTwoCenters(T, V, p.first, p.second, diameter) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    go();
    return 0;
}