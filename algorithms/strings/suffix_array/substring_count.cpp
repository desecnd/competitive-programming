#include <bits/stdc++.h>
using namespace std;

void countingSort(vector<int>& p, vector<int>& c) { 
    int n = p.size();

    vector<int> cnt(n, 0);

    for (int x : c) 
        cnt[x]++;

    vector<int> pos(n);
    vector<int> pNew(n);

    pos[0] = 0;
    for (int i = 1; i < n; i++) 
        pos[i] = pos[i - 1] + cnt[i - 1];

    for(int x : p) {
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

    { // k = 0;
        vector<pair<char,int>> t(n);
        for (int i = 0; i < n; i++) t[i] = { s[i], i };

        sort(begin(t), end(t));

        for (int i = 0; i < n; i++) p[i] = t[i].second;

        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if ( t[i].first == t[i - 1].first ) {
                c[p[i]] = c[p[i - 1]];
            } else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
    }

    int k = 0;
    while ((1<<k) < n) {
        for (auto &i : p) i = (i - (1<<k) + n) % n;

        countingSort(p, c);

        vector<int> cNew(n);
        cNew[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            pair<int,int> now { c[p[i]], c[(p[i] + (1<<k)) % n] };
            pair<int,int> last { c[p[i - 1]], c[(p[i - 1] + (1<<k)) % n] };

            if ( now == last ) {
                cNew[p[i]] = cNew[p[i - 1]];
            } 
            else {
                cNew[p[i]] = cNew[p[i - 1]] + 1;
            }
        }

        c = cNew;
        k++;
    }

    return p;
}

int countSubstring(const vector<int>& suffixArray, const string& s, const string& p) {
    int n = suffixArray.size();
    int len = p.size();
    int r, l;
    {
        int lo = 0, hi = n - 1;
        while ( lo <= hi ) {
            int mid = (lo + hi)/2;
            int x = suffixArray[mid]; 

            string sub { s.substr(x, min(n - x, len) ) };


            // p < sub 
            if (lexicographical_compare(begin(sub), end(sub), begin(p), end(p))) {
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }

        }
        l = lo;
    }
    {
        int lo = 0, hi = n - 1;
        while ( lo <= hi ) {
            int mid = (lo + hi)/2;
            int x = suffixArray[mid]; 

            string sub { s.substr(x, min(n - x, len) ) };

            // p < sub 
            if (lexicographical_compare(begin(p), end(p), begin(sub), end(sub))) {
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }
        r = hi;
    }
    return r - l + 1;
}

int main() {
    ios::sync_with_stdio(false);

    string s; cin >> s;

    auto suffixArray { createSuffixArray(s) };
    
    int q; cin >> q;
    while (q--) {
        string p; cin >> p;
        cout << countSubstring(suffixArray, s, p) << "\n";
    }

    return 0;
}