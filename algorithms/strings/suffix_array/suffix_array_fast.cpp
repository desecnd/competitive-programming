/*  Build Suffix Array for any string in O(n log n) time
// 
//  Last time we used sorting every time which took O(n log n) every iteration
//
//  Instead we can use Radix Sort for pairs, which runs in O(n) time
//
//  credits go to: pashka from codeforces edu suffix array turtorial
//
*/
#include <bits/stdc++.h>
using namespace std;


void radixSort(vector<pair<pair<int,int>, int>>& T) {
    int n = T.size();

    {
        vector<int> cnt(n, 0);
        for (auto x : T) 
            cnt[x.first.second]++;

        vector<int> pos(n);

        pos[0] = 0;
        for (int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + cnt[i - 1];

        vector<pair<pair<int,int>, int>> newT(n);

        for (auto x : T) {
            int i = x.first.second;
            newT[pos[i]] = x;
            pos[i]++;
        }

        T = newT;
    }
    {
        vector<int> cnt(n, 0);
        for (auto x : T) 
            cnt[x.first.first]++;

        vector<int> pos(n);

        pos[0] = 0;
        for (int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + cnt[i - 1];

        vector<pair<pair<int,int>, int>> newT(n);

        for (auto x : T) {
            int i = x.first.first;
            newT[pos[i]] = x;
            pos[i]++;
        }

        T = newT;
    }
} 

vector<int> createSuffixArray(string s) {
    s += "$";
    int n = s.size();

    vector<int> P(n), C(n);

    {
        vector<pair<char, int>> T(n);

        for (int i = 0; i < n; i++) 
            T[i] = { s[i], i };
        sort(begin(T), end(T));

        for (int i = 0; i < n; i++) P[i] = T[i].second;

        C[P[0]] = 0;
        for (int i = 1; i < n; i++) {
            if ( T[i].first == T[i - 1].first ) 
                C[P[i]] = C[P[i - 1]];
            else 
                C[P[i]] = C[P[i - 1]] + 1;
        }
    }

    int k = 0; 
    while ((1<<k) < n) {
        vector<pair<pair<int,int>, int>> T(n);

        for (int i = 0; i < n; i++)
            T[i] = {{C[i], C[(i + (1<<k)) % n] }, i};

        radixSort(T);

        for (int i = 0; i < n; i++)
            P[i] = T[i].second;

        C[P[0]] = 0;
        for (int i = 1; i < n; i++) {
            if ( T[i].first  == T[i - 1].first ) C[P[i]] = C[P[i - 1]];
            else C[P[i]] = C[P[i - 1]] + 1;
        }
        k++;
    }

    return P;
}

int main() {
    string s;
    cin >> s;

    auto P { createSuffixArray(s) };

    for (int i : P) cout << i << " ";
    cout << endl;

    return 0;
}