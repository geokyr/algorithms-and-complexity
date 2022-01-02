#include <iostream>
using namespace std;

// Define max n and max k value and some global variables
// to store input and use in order to solve the problem.
#define N 200005
#define K 1000000005
int n, k, bonuses[N], answer = 0;

int main() {
    ios_base::sync_with_stdio(false);

    // Read input and the average christmas bonus per year.
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        cin >> bonuses[i];
    }

    // Solution

    if (answer == 0) {
        cout << "-1" << endl;
    }
    else {
        cout << answer << endl;
    }

    return 0;
}