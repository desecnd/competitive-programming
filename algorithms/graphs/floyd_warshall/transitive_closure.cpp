/*
* author: pavveu
* algorithm: Floyd Warshall transitive closure
* time: O(V^3)
* Using Dynamic Programming, we iterate through every node
* checking for every pair if its possible to get through this node
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;

const int maxV = 1000;

void floydWarshall(vector<bitset<maxV>>& reach, vector<vi>& p, int V) {
	for (int k = 0; k < V; k++) 
	for (int i = 0; i < V; i++)
	for (int j = 0; j < V; j++) 
		if ( reach[i].test(k) && reach[k].test(j) ) 
			reach[i].set(j), p[i][j] = p[k][j];
	
	// distance from node to itself should always be == 0 
	// otherwise we could simply iterate infinitly to shorten distance
}

void go() {		
	cout << "Enter n of verticies , n of edges, and then all edges in form [from, to]\n";
	int V, E;
	cin >> V >> E;

	vector<bitset<maxV>> reachable(V);
	vector<vi> p(V, vi(V, -1));

	for (int i = 0; i < V; i++) reachable[i].set(i);

	for (int e = 0; e < E; e++) {
		int v, u;
		cin >> v >> u;
		v--, u--;

		reachable[v].set(u);
		p[v][u] = v;
	}

	for (int i = 0; i < V; i++) 
	for (int j = 0; j < V; j++) 
		cout << i << " --> " << j << " " << boolalpha << reachable[i][j] << ", parent[" << j << "] = " << p[i][j] << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	go();	
	
	return 0;
}
