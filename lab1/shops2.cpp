#include <iostream>
using namespace std;

// Define max N and max K value and some global variables
// to store input and use to solve the problem.
#define N 20005
#define K 1000005
int n, k, residents[N], aux[K], answer = 20005;

// Function that initializes all aux array values to 0.
void clear_aux() {
    for (int i = 0; i < k; i++) {
        aux[i] = 0;
    }
}

// Function that updates the aux array with the minimum
// length of every subarray sum less than k, starting 
// from index and going until the last element.
// On the aux array, index i has value equal to the
// minimum length of a subarray with sum i.
void update_aux(int index) {
    // Updated the aux at position equal to residents[index],
    // since the minimum length is one for that sum.    
    aux[residents[index]] = 1;
    
    // Follow a logic similar to our main solution for the left
    // side, but now perform it on the right side and add
    // one element to the sum each one, increasing the length
    // by one and checking if there is a new minimum length
    // for that sum.
    int sum = 0, length = 0;
    for (index; index < n; index++) {
        sum += residents[index];
        length++;
        if (sum > k) {
            break;
        }
        else {
            if ((aux[sum] > length) || !aux[sum]) {
                aux[sum] = length;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    // Read input and the residents distribution.
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        cin >> residents[i];
    }

    // Initialize the aux array.
    clear_aux();

    // Loop for n elements with fixed y starting from the
    // end of the residents array.
    for (int y = n - 1; y >= 0; y--) {
        // If it is the last element then we don't need
        // to update the aux array since there is no
        // subarray to the right of the last element
        // and the aux array has just been initialized.
        // Else, update the aux array.
        if (y != n - 1) {
            update_aux(y + 1);
        }
        // Now check every subarray starting at x and
        // ending at y, that has a certain sum, by adding
        // a new element its time, and increasing the length
        // by one.
        int sum = 0, length = 0;
        for (int x = y; x >= 0; x--) {
            sum += residents[x];
            length++;
            
            // If that sum is equal to k then check if the
            // length is less than our current answer and 
            // update the answer if necessary.
            if (sum == k) {
                if (length < answer) {
                    answer = length;
                }
            }
            // Else, if that sum is less than k, then check if 
            // there is a subarray to the right of y (either 
            // a disconnected one or one that connnects with y),
            // so that the two subarrays have a total sum equal 
            // to k. Then check if their combined length is less
            // than our answer and update the answer if necessary.
            else if (sum < k) {
                if (aux[k - sum]) {
                    int current = aux[k - sum] + length; 
                    if (current < answer) {
                        answer = current;
                    }
                }
            }
            // Else, if that sum is greater than k, then break,
            // since there is no point to continue checking for 
            // a subarray with sum greater than k.
            else {
                break;
            }
        }
    }

    // If the answer hasn't been updated from the initial value of
    // 20005, then that means there is no answer, so print "-1".
    if (answer == 20005) {
        cout << "-1" << endl;
    }
    // Else, print the value of the answer, that is the minimum
    // length of at most two subarrays with sum equal to K.
    else {
        cout << answer << endl;
    }

    return 0;
}