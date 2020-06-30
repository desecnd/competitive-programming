/*  Build Suffix Array for any string in O(n log^2 n)
//
//  Suffix Array is data structure that holds suffixes 
//  in lexicographical order, by their indexes 
// 
//  so for string s = ababba 
//
//  suffix array P is:
//  P = [6, 5, 0, 2, 4, 1, 3]
//
//  6: ''
//  5: a 
//  0: ababba
//  2: abba
//  4: ba
//  1: babba
//  3: bba
//
//  credits go to: pashka from codeforces edu suffix array turtorial
//
*/

#include <bits/stdc++.h>
using namespace std;

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

        sort(begin(T), end(T));

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
