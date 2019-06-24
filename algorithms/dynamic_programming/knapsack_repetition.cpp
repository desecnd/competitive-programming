#include <bits/stdc++.h>
using namespace std;

const int maxW = 1e5 + 10;
const int maxN = 100 + 10;

// max possible value of knapsack for weight w-th
long long DP[maxW];

// items parameters
int weight[maxN];
int value[maxN];


void go() {

	// number of items (n) and knapsack max capacity (W) 
	int n, W;
	cin >> n >> W;

	// next n pairs in form (value, weight) for i-th item
	for(int i = 0; i < n; i++) {
		cin >> value[i] >> weight[i];
	}

	for(int i = 0; i < n; i++) {
		for(int w = 0; w <= W; w++) {

			// can we get better result for weight w with item i ? 
			if(w - weight[i] >= 0) 
				DP[w] = max(DP[w], DP[w - weight[i]] + value[i]);
		}
	}	

	// answer is max knapsack value for every weight <= W
	cout << *max_element(DP, DP+W+1) << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	go();
	
	return 0;
}
