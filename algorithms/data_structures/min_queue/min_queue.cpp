#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <limits>

using namespace std;
using ll = long long;

#define mp make_pair

template <typename T>
struct MinQueue {
    /// Data Structure LIFO queue that returns current minimum in O(1)
    /// O(n) for amorthized cost of all operations

    deque<pair<T,int>> Q;
    int size;

    MinQueue() : Q(), size(0) {}

    // Push x into queue
    void Push(const T& x) {
        size++;

        int cnt = 0;
        while ( Q.size() && Q.back().first >= x ) {
            cnt += Q.back().second + 1;
            Q.pop_back();
        }
        Q.push_back(mp(x, cnt));
    }

    // Pop front element from Queue
    void Pop() {
        if ( size == 0 ) return;
        size--;

        if ( Q.front().second > 0 ) Q.front().second--;
        else Q.pop_front();
    }

    // return Minimum element in Queue
    T Min() {
        if ( size == 0 ) return numeric_limits<T>::max();
        else return Q.front().first;
    }
};

void go() {
    MinQueue<int> Q;

    int q = 0, temp;
    while ( cin >> q ) {
        switch( q ) {
            case 0: { cin >> temp; Q.Push(temp); } break;
            case 1: { Q.Pop(); } break;
            case 2: { cout << Q.Min() << "\n"; } break;
            default: cout << "Uknown query.\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    go();
    return 0;
}