/*
* author: pavveu
* task: find tree diameter
* time: O(n)
* solution: dynamic programming
*
* tree diameter is longest path in a tree
* to find it using dp we can root tree in any node
* next for every node, check whats maximum detpth of its
* child subtrees
* if diameter goes through this node and its subtrees 
* answer would be first max + second max + 2
*
* we dont have to worry about parent nodes, because we will 
* check them after anyways 
* 
* so we simply store every max1 + max2 + 2 in array
* and then select max value from it as our diameter
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

using vi = vector<int>;
using graph = vector<vi>; 
const int inf = 1e9;

#define all(x) begin(x), end(x)
#define mp make_pair

// for every node in rooted tree check if diameter goes through this node
// if so, it will be max depth + second max depth + 2
int depth(graph& G, vi& diam, int v, int a ) {
    int max1 = 0, max2 = 0;
    for (int u : G[v]) {
        if ( u == a ) continue; 

        int maxDepth = depth(G, diam, u, v) + 1;

        if ( maxDepth > max1 ) {
            max2 = max1;
            max1 = maxDepth;
        }
        else if ( maxDepth > max2 ) {
            max2 = maxDepth;
        }
    }

    diam[v] = max1 + max2;
    return max1;
}

void go() {
    int V, E;
    cin >> V; E = V - 1;

    graph T(V);
    for (int e = 0; e < E; e++) {
        int v,u;
        cin >> v >> u;
        v--,u--;

        T[v].push_back(u);
        T[u].push_back(v);
    }

    vi diameter(V, -1);
    depth(T, diameter, 0, -1);
    cout << "Diameter: " << *max_element(all(diameter)) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    go();
     
    return 0;
} 