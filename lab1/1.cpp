#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct portal {
    int first;
    int second;
    int width;
    portal(int x, int y, int z) : first(x), second(y), width(z) {}
};

bool compareByWidth(const portal &a, const portal &b)
{
    return a.width < b.width;
}

#define N 1000000
int parent[N], size[N];

void make_set(int v) {
    parent[v] = v;
    size[v] = 0;
}

int find_set(int v) {
    if (v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        if (size[a] == size[b]) {
            size[a]++;
        }
    }
}

bool mortify(int x) {
    return true;
}

int binary_search(int low, int high) {
    while(low < high) {
        // int mid = low + (high - low) / 2;
        int mid = low + (high - low + 1) / 2;
        if(mortify(mid)) {
            low = mid;
        }
        else {
            high = mid - 1;
        }
    }
    return low;
}

vector<int> mortys;
vector<portal> portals;               

int main() {
    ios_base::sync_with_stdio(false);

    int n, m, t, temp[3];
    cin >> n >> m;

    for(int i = 0; i < n; i++) {
        cin >> t;
        mortys.push_back(t);
    }

    for(int i = 0; i < m; i++) {
        cin >> temp[0] >> temp[1] >> temp[2];
        portal p(temp[0], temp[1], temp[2]);
        portals.push_back(p);
    }

    // Check that portals are initiliazed correctly.

    // for(int i = 0; i < m; i++) {
    //     cout << portals[i].first << " " << portals[i].second << " "  << portals[i].width << endl;
    // }

    sort(portals.begin(), portals.end(), compareByWidth);

    // Check that portals are sorted correctly.

    // for(int i = 0; i < m; i++) {
    //     cout << portals[i].first << " " << portals[i].second << " "  << portals[i].width << endl;
    // }

    cout << binary_search(0, m - 1) << endl;

    return 0;
}