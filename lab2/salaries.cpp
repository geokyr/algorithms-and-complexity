#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Define max n and max k value and some global variables and
// arrays to store input and use in order to solve the problem.
#define N 200005
#define K 1000000005
int n, k, bonuses [N], bon_mod[N];

// Struct of an info block that is used to store everything
// needed for each array used.
struct info {
    int size;
    int element;

    // Default empty body constructor for declaration.
    info() {};

    // Parametrized constructor for easier initialization.
    info(int a, int b) : size(a), element(b) {}
};

// Global arrays of info blocks.
info lis[N], lds[N], lis_plus[N], lds_plus[N];

// Function that returns if an info block is empty based on its LS size.
bool empty_block(const info &block) {
    return (block.size == 0);
}

// Function that outputs an info block to ostream in order to print it.
ostream& operator<<(ostream &os, const info &block) {
    return os << "Size: " << block.size << "\t"
              << "Element: " << block.element << endl;
}

// Function that prints an info array by printing every non-empty block.
void print_array(info (&arr)[N]) {
    for(info x : arr) {
        if (!empty_block(x)) {
            cout << x << endl;
        }
    }
}

// Function that prints the 4 constructed arrays.
void print_arrays() {
    print_array(lis);
    cout << "-----------------------------------------------------" << endl;
    print_array(lis_plus);
    cout << "-----------------------------------------------------" << endl;
    print_array(lds);
    cout << "-----------------------------------------------------" << endl;
    print_array(lds_plus);
}

// Function that constructs the lis and lis_plus array. 
// Basically, an element of lis/lis_plus on position i is the LIS including
// elements up to i/the LIS including elements up to i, with i included.
void construct_lises() {
    vector<int> sorted;
    int len = 0;

    for(int i = 0; i < n; i++) {
        // Increasing subsequence, so lower_bound is used, since
        // it returns an iterator to "next greater than or equal to".
        auto it = lower_bound(begin(sorted), end(sorted), bonuses[i]);
        
        // Greatest, so insert it. The len is equal to the new sorted vector size.
        if(it == end(sorted)) {
            sorted.push_back(bonuses[i]);
            len = sorted.size();
        }
        // Else, replace. The len is equal to the index that iterator it is pointing.
        else {
            *it = bonuses[i];
            len = distance(sorted.begin(), it) + 1;
        }

        // Create an info block with the size of the LIS and the last element
        // of the LIS and append it to the lis array.
        info temp(sorted.size(), sorted[sorted.size() - 1]);
        lis[i] = temp;

        // Create an info block with the size of the increasing subsequence ending at
        // the lastly appended or replaced element and append it to the lis_plus array.
        info temp_(len, bonuses[i]);
        lis_plus[i] = temp_;
    }
}

// Function that constructs the lds and lds_plus array.
// Basically an element of lds/lds_plus on position i is the LDS including
// elements up to i/the LDS including elements up to i, with i included.
void construct_ldses() {
    vector<int> sorted;
    int len = 0;

    for(int i = 0; i < n; i++) {
        // Decreasing subsequence, so lower_bound is used, but 
        // this time with a 4th argument greater<int>() as a comparator
        // function, so that it returns an iterator to "next less than".
        auto it = lower_bound(begin(sorted), end(sorted), bon_mod[i], greater<int>());
        
        // Smallest, so insert it. The len is equal to the new sorted vector size.
        if(it == end(sorted)) {
            sorted.push_back(bon_mod[i]);
            len = sorted.size();
        }
        // Else, replace. The len is equal to the index that iterator it is pointing.
        else {
            *it = bon_mod[i];
            len = distance(sorted.begin(), it) + 1;
        }

        // Create an info block with the size of the LDS and the last element
        // of the LDS and append it to the lds array.
        info temp(sorted.size(), sorted[sorted.size() - 1]);
        lds[i] = temp;
        
        // Create an info block with the size of the decreasing subsequence ending at
        // the lastly appended or replaced element and append it to the lds_plus array.
        info temp_(len, bon_mod[i]);
        lds_plus[i] = temp_;
    }
}

// Function that calculates the max size of the subsequence.
int calculate_max_size() {
    int answer = 0;

    // Iterate the 4 combinations of the arrays constructed (pair of lis/lis_plus and
    // lds/lds_plus) and if these two can be connected through k, update max value of
    // answer, if the combination of the 2 lengths is greater.
    // Since a reversed and modified (+k) bonuses array is used to calculate the
    // lds/lds_plus, its indexes need to be reversed (done by using n - i - 1). 
    // In addition to that, we want to check the lis/lis_plus up to i_th element
    // and the lds/lds_plus starting (or rather ending) on the (i+1)_th element,
    // so, finally, an index of n - i - 2 is used for the lds/lds_plus.
    for (int i = 0; i < n - 1; i++) {
        if(lis[i].element < lds[n - i - 2].element) {
            answer = max(answer, lis[i].size + lds[n - i - 2].size);
        }
        if(lis[i].element < lds_plus[n - i - 2].element) {
            answer = max(answer, lis[i].size + lds_plus[n - i - 2].size);
        }
        if(lis_plus[i].element < lds[n - i - 2].element) {
            answer = max(answer, lis_plus[i].size + lds[n - i - 2].size);
        }
        if(lis_plus[i].element < lds_plus[n - i - 2].element) {
            answer = max(answer, lis_plus[i].size + lds_plus[n - i - 2].size);
        }
    }
    
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);

    // Read input and the average christmas bonus per year.
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        cin >> bonuses[i];
    }
    
    // Fill in the bonuses modified array which is equal to a reversed
    // bonuses array with every bonus increased by k.
    for (int i = 0; i < n; i++) {
        bon_mod[i] = bonuses[n - i - 1] + k;
    }

    // Construct the 4 arrays with their respective info blocks.
    construct_lises();
    construct_ldses();

    // Print the 4 arrays to check if they are as expected.
    // print_arrays();

    cout << calculate_max_size() << endl;

    return 0;
}