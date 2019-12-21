#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

int Merge(vector<ll>& A, vector<ll>& temp, int l, int q, int r) {
    for (int i = l; i <= r; i++)
        temp[i] = A[i];

    int i = l;
    int j = q + 1;
    int invs = 0;

    for (int k = l; k <= r; k++ ) {
        if ( i <= q && (j > r || temp[i] <= temp[j]))
            A[k] = temp[i++];  
        else {
            A[k] = temp[j++];
            invs += q + 1 - i; 
        }
    }

    return invs;
}

int MergeSort(vector<ll>& A, vector<ll>& temp, int l, int r) {
    /// closed interval [l, r] as parameters
    /// returns n of inversions in A 
    int inversions = 0;

    if ( l < r ) {
        int q = (l + r) / 2; 
        inversions += MergeSort(A, temp, l, q);
        inversions += MergeSort(A, temp, q + 1, r);
        inversions += Merge(A, temp, l, q, r);
    }
    return inversions;
}

void go() {
    int n; cin >> n;
    vector<ll> A(n), temp(n, 0);
    for (ll &i : A) cin >> i;

    int inversions = MergeSort(A, temp, 0, n-1);
    
    cout << "Sorted array: ";
    for (ll i : A) cout << i << " ";
    cout << "\nwith " << inversions << " inversions\n";
}

int main() {
    ios::sync_with_stdio(0);
    go();

    return 0;
}
