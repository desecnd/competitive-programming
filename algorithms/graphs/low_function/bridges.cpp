#include <bits/stdc++.h>
using namespace std;

// low(v) = function that represent minimum preorder number of vertex
// we can get to, not through edge {parent(v), v} in dfs-preorder traversal
//
// low = min(preorder(v), low( sons_of(v) ), preorder( backward_adj(v) ))
//
// Edge {u, v} is called a bridge when after deleting this edge, there is
// no path between u and v
//
// Can know that if low(v) == preorder(v) there is no other way to v,
// from parent(v) so

const int maxN = 1e5 + 10;
vector<int> G[maxN]; 
int pre[maxN];

int findBridges(int v, int parent = -1, int time = 1) {
	int low = pre[v] = time; 
	
	for (int u : G[v]) { 
		if (u == parent) continue; // ignore the same edge we came here

		if (pre[u] == 0) {
			// tree edge
			int son_low = findBridges(u, v, time + 1);
			low = min(low, son_low);
		} else { 
			// backward edge
			low = min(low, pre[u]);
		}
	}

	if (low == pre[v] && parent != -1) {
		cout << "{" << parent << " " << v << "}" << '\n';
	}
	
	return low;
}

void go() {
	int V,E;
	cin >> V >> E;

	for (int e = 1; e <= E; e++) {
		int v,u;
		cin >> v >> u;	
		G[v].push_back(u);
		G[u].push_back(v);
	}

	cout << "Bridges:\n";
	findBridges(1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);	

	go();

	return 0;
}
