#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Define max-min distance and some global variables and vectors
// to store input and use in order to solve the problem.
#define max_min_d 10005
int n, d = max_min_d;
unsigned long q, temp;
vector<unsigned long> distances, queries(max_min_d, -1);
set<pair<unsigned long, int>> pool;

void update_queries() {
    while(!pool.empty()) {
        pair<unsigned long, int> head = *pool.begin();
        int sum = head.first;
        unsigned long current = head.second;
        pool.erase(head);

        for(auto i : distances) {
            int node = (current + i) % d;
            int distance = sum + i;

            if(distance < queries[node] || queries[node] == -1) {
                pool.erase(make_pair(queries[node], node));
                queries[node] = distance;
                pool.insert(make_pair(queries[node], node));
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    // Read input and update the max-min distance.
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> temp;
        distances.push_back(temp);
        if(temp < d) {
            d = temp;
        }
    }

    // Initialize the queries vector with 0 and add the initial
    // (0, 0) pair to the pool.
    queries[0] = 0;
    pool.insert(make_pair(queries[0], 0));
    update_queries();

    // Read all the questions for the stations and output NO or
    // YES based on if the train can reach that station.
    for (int i = 0; i < q; i++) {
        cin >> temp;
        if(queries[temp % d] > temp) {
            cout << "NO" << endl;
        }
        else {
            cout << "YES" << endl;
        }
    }

    return 0;
}