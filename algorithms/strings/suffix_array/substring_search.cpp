/*  Answering substring queries in O( |p| log n ) time
// 
//  Combination of Suffix Array + Binary Search
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

    auto suffArr { createSuffixArray(s) };
    int n = s.size();

    int q; cin >> q;
    while (q--) {
        string p; cin >> p;

        int l = p.length();  

        int lo = 0, hi = n;
        while ( lo <= hi ) {
            int mid = lo + (hi - lo)/2;
            int x = suffArr[mid];

            string sub = s.substr(x, min(n - x, l));
            // cout << "Mid: " << mid << ", x = " << x << ", sub = " << sub << "\n" ;

            if ( lexicographical_compare(begin(sub), end(sub), begin(p), end(p)) ) {
                lo = mid + 1;
            }
            else  {
                hi = mid - 1;
            }
        }

        if ( lo  <= n ) {
            string sub = s.substr(suffArr[lo], min(n - suffArr[lo], l));
            cout << (( sub == p )? "Yes" : "No") << "\n";
        } 
        else {
            cout << "No\n";
        }

    }

    return 0;
}