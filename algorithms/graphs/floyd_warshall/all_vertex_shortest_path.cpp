/*
* author: pavveu
* algorithm: Floyd Warshall all pairs shortest paths
* time: O(V^3)
* Using Dynamic Programming, we iterate through every node
* checking for every pair if its better to go through this node
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;


const ll inf = (1ll<<62);

bool floydWarshall(vector<vll>& dist, vector<vi>& p, int V) {
	for (int k = 0; k < V; k++) 
	for (int i = 0; i < V; i++)
	for (int j = 0; j < V; j++) 
		if ( dist[i][k] != inf && dist[k][j] != inf && dist[i][j] > dist[i][k] + dist[k][j] ) 
			dist[i][j] = dist[i][k] + dist[k][j], p[i][j] = p[k][j];
	
	// distance from node to itself should always be == 0 
	// otherwise we could simply iterate infinitly to shorten distance
	for (int i = 0; i < V; i++) 
		if ( dist[i][i] < 0 ) return false;

	return true;
}

void go() {		
	cout << "Enter n of verticies , n of edges, and then all edges in form [from, to, weight]\n";
	int V, E;
	cin >> V >> E;

	vector<vll> dist(V, vll(V, inf));
	vector<vi> p(V, vi(V, -1));

	for (int i = 0; i < V; i++) dist[i][i] = 0;

	for (int e = 0; e < E; e++) {
		int v, u; ll w;
		cin >> v >> u >> w;
		v--, u--;

		if ( dist[v][u] > w ) {
			dist[v][u] = w;	
			p[v][u] = v;
		}
	}


	if( !floydWarshall(dist, p, V) ) cout << "Graph contains negative cycle\n";
	else {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				cout << i << " --> " << j << " (dist = ";

				if ( dist[i][j] != inf ) cout << dist[i][j] << ", ";
				else cout << "inf, ";

				cout << "parent[" << j << "] = " << p[i][j] << "\n";
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	go();	
	
	return 0;
}
