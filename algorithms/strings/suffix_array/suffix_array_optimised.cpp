/*  Build Suffix Array for any string in O(n log n) time
// 
//  Instead of using Radix Sort for sorting pairs
//  We can take advantage of the fact that 1 number is already in sorted order
//  So instead of Radix Sort we can use just 1 Counting Sort 
//
//  credits go to: pashka from codeforces edu suffix array turtorial
*/

#include <bits/stdc++.h>
using namespace std;

void countingSort(vector<int>& p, vector<int>& c) {
    int n = p.size();

    vector<int> cnt(n, 0);
    for (auto x : c) cnt[x]++;

    vector<int> pos(n);
    vector<int> pNew(n);

    pos[0] = 0;
    for (int i = 1; i < n; i++)
        pos[i] = pos[i - 1] + cnt[i - 1];

    for (int x : p) {
        int i = c[x];
        pNew[pos[i]] = x;
        pos[i]++;
    }

    p = pNew;
} 

vector<int> createSuffixArray(string s) {
    s += "$";
    int n = s.size();

    vector<int> p(n), c(n);
    {
        vector<pair<char, int>> t(n);

        for (int i = 0; i < n; i++) 
            t[i] = { s[i], i };
        sort(begin(t), end(t));

        for (int i = 0; i < n; i++) p[i] = t[i].second;

        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if ( t[i].first == t[i - 1].first ) 
                c[p[i]] = c[p[i - 1]];
            else 
                c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    int k = 0; 
    while ((1<<k) < n) {
        for (int i = 0; i < n; i++)
            p[i] = (p[i] - (1<<k) + n) % n;

        countingSort(p, c);

        vector<int> cNew(n);
        cNew[p[0]] = 0;

        for (int i = 1; i < n; i++) {
            pair<int,int> last = {c[p[i - 1]], c[(p[i - 1] + (1<<k)) % n]};
            pair<int,int> now = {c[p[i]], c[(p[i] + (1<<k)) % n] };

            if ( now == last ) cNew[p[i]] = cNew[p[i - 1]];
            else cNew[p[i]] = cNew[p[i - 1]] + 1;
        }
        c = cNew;

        k++;
    }

    return p;
}

int main() {
    string s;
    cin >> s;

    auto p { createSuffixArray(s) };

    for (int i : p) cout << i << " ";
    cout << endl;

    return 0;
}