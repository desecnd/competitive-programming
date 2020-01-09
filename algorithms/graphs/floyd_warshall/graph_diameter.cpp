#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using graph = vector<vi>;

#define all(x) begin(x), end(x)

const int inf = 1e9;

bool floydWarshall(graph& D, graph& P, int V) {
	for (int k = 0; k < V; k++ ) 
	for (int i = 0; i < V; i++ )
	for (int j = 0; j < V; j++ ) {
		if ( D[i][k] != inf && D[k][j] != inf && D[i][j] > D[i][k] + D[k][j] ) {
			D[i][j] = D[i][k] + D[k][j];
			P[i][j] = P[k][j];
		}
	}
	
	for (int i = 0; i < V; i++ )
		if ( D[i][i] < 0 ) return false;

	return true;
}

void go() {
	int V, E;
	cin >> V >> E;

	graph D(V, vi(V, inf)), P(V, vi(V, -1));
	for (int v = 0; v < V; v++ ) D[v][v] = 0, P[v][v] = v;

	for (int e = 0; e < E; e++) {
		int v, u, w; 
		cin >> v >> u >> w;
		
		v--, u--;
		if ( w < D[v][u] ) {
			D[v][u] = w; 
			P[v][u] = v;
		}
	}

	if ( floydWarshall(D, P, V) ) {
		vi remoteness(V, 0);
		for ( int v = 0; v < V; v++ )
		for ( int u = 0; u < V; u++ ) {
			if ( D[v][u] == inf ) continue;
			remoteness[v] = max(remoteness[v], D[v][u]);
		}

		auto p = minmax_element(all(remoteness));
		int radius = *p.first; 
		int diameter = *p.second; 

		cout << "graph diameter: " << radius << "\n";
		cout << "graph radius: " << diameter << "\n";
		cout << "graph centers: { ";	
		for (int v = 0; v < V; v++)
			if ( remoteness[v] == radius ) cout << v + 1 << " ";
		cout << "}\n";
	}
	else {
		cout << "Negative Cycle detected\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	go();
	return 0;
}
