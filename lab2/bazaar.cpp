#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Define max n and max m value and some global variables and arrays +
// vectors to store input and use in order to solve the problem.
#define N 5005
#define M 1505
vector<pair<int,unsigned long long int>> pairs[3][3];
vector<unsigned long long int> optimal[3][3];
unsigned long long int answer = INT_MAX;
unsigned long long int dp[M][N];
int n, m;

// Function that returns an int in {1, 2, 3} matching in the
// same order as the value of character x in {A, B, C}.
int item_char_to_int(char x) {
    return x - 64;
}

// Function that calculates the dp array values for each item
// and copies them to the optimal array.
void calculate_dp(int merchant, int item) {
    // Number of offers for certain item by the merchant.
    int offers = pairs[merchant][item].size();

    // First column of dp array remains equal to 0 (0 quantity of item
    // equals 0 price). First row of dp array is initialized using 
    // INT_MAX values starting (index j = 1 to n + 1 sets, since 
    // first column must remain 0).
    for (int j = 1; j < n + 1; j++) {
        dp[0][j] = INT_MAX;
    }

    // For every offer fill in its dp array (index i = 1 to offers + 1,
    // since first column must remain 0).
    for (int i = 1; i < offers + 1; i++) {
        // Get the quantity and total price of the offer from
        // the pairs vector.
        int quantity = pairs[merchant][item][i - 1].first;
        int total_price = pairs[merchant][item][i - 1].second;

        // Calculate the lowest price to pay for j quantity of this
        // item, based on the total price and quantity of current
        // and previous offers.
        for(int j = 1; j < n + 1; j++) {
            dp[i][j] = min(dp[i - 1][max(0, j - quantity)] + total_price, dp[i - 1][j]);
        }
    }
    
    // Pass the lowest price for j quantity of an item to optimal array.
    for (int j = 0; j < n + 1; j++) {
        optimal[merchant][item].push_back(dp[offers][j]);
    }
}

// Function that calculates the final optimal array values. by adding
// the values of other 2 items to the respective first item, forming
// the lowest price for a set of items for j quantity.
void calculate_optimal() {
    // For every merchant and for up to n quantity, add the values 
    // of the other 2 items to the first one, to form the lowest
    // price for j quantity of a set of items.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n + 1; j++) {
            optimal[i][0][j] += optimal[i][1][j] + optimal[i][2][j];
        }
    }
}

// Function that calculates the minimum price based
// on the optimal array values.
int calculate_minimum_price() {
    // Keep the lowest price found on variable answer, while searching
    // for new possible combinations, starting from buying 0 sets from
    // merchants 1 and 2 and n from 3 and ending on buying n sets from
    // merchant 1 and 0 from 2 and 3.
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            if(n - i - j >= 0) {
                answer = min(answer, optimal[0][0][i] + optimal[1][0][j] + optimal[2][0][max(0, n - i - j)]);
            }
            else {
                break;
            }
        }
    }

    // If answer is equal to its initial value (INT_MAX),
    // then no valid combination was found, so return -1.
    if (answer == INT_MAX) {
        return -1;
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);

    // Read input and the merchants' offers.
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        // Temporary string to read the merchant ID and item ID.
        string xy;
        int a;
        unsigned long long int p;

        // Read the merchant ID, the item ID, the quantity and the total price.
        cin >> xy >> a >> p;
        int merchant = xy[0] - '0';
        int item = item_char_to_int(xy[1]);
        
        // Push back the offer read into its respective vector of pairs.
        pairs[merchant - 1][item - 1].push_back(make_pair(a, p));
    }

    // Calculate the values of the dp array and the optimal array.
    for (int merchant = 0; merchant < 3; merchant++) {
        for (int item = 0; item < 3; item++) {
            calculate_dp(merchant, item);
        }
    }
    calculate_optimal();

    // Calculate the minimum price.
    cout << calculate_minimum_price() << endl;

    return 0;
}