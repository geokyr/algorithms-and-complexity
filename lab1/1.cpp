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

#define N 1000005
int n, m, parent[N], size[N];
vector<int> mortys;
vector<portal> portals;

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

void reset_sets() {
    for(int i = 0 ; i < n; i++) {
        make_set(i + 1);
    }
}

bool mortify(int x) {
    for(int i = m - 1; i >= 0; i--) {
        portal current = portals[i];

        if(x <= current.width) {
            union_sets(current.first, current.second);
        }
        else {
            break;
        }
    }

    for(int i = 0; i < n; i++) {
        if((i + 1) != mortys[i]) {
            if(find_set(i + 1) != find_set(mortys[i])) {
                return false;
            }
        }
    }

    reset_sets();
    return true;
}

int binary_search(int low, int high) {
    while(low < high) {
        int mid = low + (high - low + 1) / 2;

        if(mortify(portals[mid].width)) {
            low = mid;
        }
        else {
            high = mid - 1;
        }
    }
    return low;
}

int main() {
    ios_base::sync_with_stdio(false);

    int t, temp[3];
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

    if(n <= 100000 and m <= 100000) {
        sort(portals.begin(), portals.end(), compareByWidth);
    }

    reset_sets();

    cout << portals[binary_search(0, m - 1)].width << endl;

    return 0;
}