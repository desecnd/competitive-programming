#include <bits/stdc++.h>
using namespace std;

void countSort(vector<int>& order, const vector<int>& keys)  {
    int n = order.size();

    vector<int> cnt(n, 0);
    for (auto x : keys) {
        cnt[x]++;
    }
    vector<int> pos(n); // position in bucket

    pos[0] = 0;
    for (int i = 1; i < n; i++) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }

    vector<int> newOrder(n);
    for (auto i : order) {
        int key = keys[i];
        newOrder[pos[key]] = i;
        pos[key]++;
    }
    order = newOrder;
}

vector<int> createSuffixArray(const string& s) {
    int n = s.size();
    vector<int> p(n), c(n);

    // k = 0;
    {

        iota(begin(p), end(p), 0);
        sort(begin(p), end(p), [&](int a, int b){
            if ( s[a] != s[b] ) return s[a] < s[b];
            else return a < b;
        });

        c[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            if ( s[p[i]] == s[p[i - 1]] ) {
                c[p[i]] = c[p[i - 1]];
            }
            else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
    }

    int k = 0;
    while ( (1<<k) < n ) {
        for (auto &i : p) i = (i - (1<<k) + n) % n;

        countSort(p, c);

        vector<int> cNew(n);
        cNew[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            pair<int, int> last { c[p[i - 1]], c[(p[i - 1] + (1<<k)) % n]};
            pair<int, int> now { c[p[i]], c[(p[i] + (1<<k)) % n]};

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

vector<int> createLCPArray(const string& s, vector<int>& p) {
    int n = p.size();
    vector<int> pInv(n);
    for (int i = 0; i < n; i++)
        pInv[p[i]] = i;

    vector<int> lcp(n);

    int k = 0;
    // we have to be careful, normaly empty suffix is first 
    // entry in the suffix array, but we can have delimeter character '#'
    // etc, so its not always truth, we should guarantee it
    for (int i = 0; i < n; i++) {
        if ( pInv[i] == 0 ) continue;

        int pi = pInv[i];
        int j = p[pi - 1];

        while ( s[i + k] == s[j + k] ) k++;

        lcp[pi] = k;
        k = max(k - 1, 0);
    }

    return lcp;
}

int main() {
    ios::sync_with_stdio(0);
    string a, b; 
    cin >> a >> b;
    string s = a + "#" + b + "$";

    auto p { createSuffixArray(s) };
    auto lcp { createLCPArray(s, p) };

    int n = s.size();
    int an = a.size();

    int maxLen = 0;
    int ans = 0;

    for (int i = 1; i < n; i++) {
        bool nowSuffA = bool(p[i] < an);
        bool lastSuffA = bool(p[i - 1] < an);

        // both suffixes are from a or both from b
        if ( nowSuffA == lastSuffA ) {
            continue;
        }
        // 2 suffixes are from different strings
        else if ( lcp[i] > maxLen ) {
            maxLen = lcp[i];
            ans = p[i]; 
        }
    }

    std::cout << s.substr(ans, maxLen) << "\n";

    return 0;
}