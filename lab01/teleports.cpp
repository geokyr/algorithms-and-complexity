#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Struct for portal that connects first universe to second and backwards
// and has a certain width.
struct portal {
    int first;
    int second;
    int width;
    portal(int x, int y, int z) : first(x), second(y), width(z) {}
};

// Used to sort the portals vector, from smallest to largest width.
bool compareByWidth(const portal &a, const portal &b)
{
    return a.width < b.width;
}

// Define max N and some global variables to store input and union-find.
#define N 1000005
int n, m, parent[N], size[N], limit;
vector<int> mortys;
vector<portal> portals;

// Initialize a set with its self as parent and rank equal to 0.
void make_set(int v) {
    parent[v] = v;
    size[v] = 0;
}

// Perform the find operation and return the parent of selected set
// (using path compression). Iterative implementation is commented out.
// int find_set(int v) {
//     while (parent[v] != v) {
//         parent[v] = parent[parent[v]];
//         v = parent[v];
//     }
//     return v;
// }
int find_set(int v) {
    if (v == parent[v]) {
        return v;
    }
    else {
        return parent[v] = find_set(parent[v]);
    }
}

// Perform the union operation (using union by rank).
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

// Reset all sets and limit to largest width portal index.
void reset_sets() {
    for(int i = 0 ; i < n; i++) {
        make_set(i + 1);
    }
    limit = m - 1;
}

// Function to perform union-find algorithm on portals
// and search if all Mortys can return to their home universe
// using portals that have at least x width.
bool mortify(int x) {
    // Unify all universes that are connected through a portal by
    // iterating from limit width until x width (either from the end
    // of portals vector or continue from limit index towards the
    // beginning, since it is sorted from smallest to largest width).
    for(int i = limit; i >= 0; i--) {
        portal current = portals[i];

        // If current.width is greater than or equal to x then we need
        // to consider this portal to our solution.
        if(x <= current.width) {
            union_sets(current.first, current.second);
        }
        // The first time that current.width isn't greater than or equal
        // to x is when it is smaller than x, so we need to stop considering
        // those portals to our solution and update our limit index to our
        // current index, since that's the first portal we need to check
        // on our next search.
        else {
            limit = i;
            break;
        }
    }

    // Now, with our universe connections established through our portals
    // we iterate the Mortys positions and if a Morty is not in his home 
    // universe, we check if there is a connection between his current universe
    // and his home one by checking if these two belong on the same union.
    // If at least one of them can't return to his home universe through one or
    // more portals, then we return false, as x width portals are not enough
    // to solve the problem.
    for(int i = 0; i < n; i++) {
        if((i + 1) != mortys[i]) {
            if(find_set(i + 1) != find_set(mortys[i])) {
                // If x width fails, then we don't need to reset our union-find, 
                // since we are going to add more portals of smaller width on 
                // our next search to check if they are enough to solve the problem.
                return false;
            }
        }
    }

    // If x width succeeds, we will try to remove some of the smaller width 
    // portals on our next search and check if the solution still holds. 
    // So we need to reset the union-find and limit index.
    reset_sets();
    return true;
}

// Binary search function that finds the largest width of the smallest
// portal that will be used to solve the problem.
int binary_search(int low, int high) {
    while(low < high) {
        // Using this mid version that rounds up, to avoid infinite loops.
        int mid = low + (high - low + 1) / 2;

        // If this width is successful then we remove the left half
        // from our solution search space, since we are looking for the
        // largest width of the smallest portal.
        if(mortify(portals[mid].width)) {
            low = mid;
        }
        // If this width fails then we remove the right half from our
        // solution search space, since we know that if we don't
        // have a solution with that as our smallest portal, we won't
        // have a solution with a larger smallest portal.
        else {
            high = mid - 1;
        }
    }
    // When the binary search is done, our solution will be pointed at by low.
    return low;
}

int main() {
    ios_base::sync_with_stdio(false);

    // Initialize some variables to read input and read the universes
    // and portals sizes, then Mortys' positions and the portals.
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

    // If we are not on the bonus cases, we need to sort our portals
    // vector, so that we can binary search the width. Else, the input
    // is already sorted from smallest to largest width.
    if(n <= 100000 and m <= 100000) {
        sort(portals.begin(), portals.end(), compareByWidth);
    }

    // Initialize the universe singular sets for our first search.
    reset_sets();

    // Print the largest width of the smallest portal that is used to 
    // solve the problem.
    cout << portals[binary_search(0, m - 1)].width << endl;

    return 0;
}