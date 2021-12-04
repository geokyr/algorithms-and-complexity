#include <iostream>
using namespace std;

#define N 20005
#define K 1000005
int n, k, residents[N], aux[K], answer = 20005;

void clear_aux() {
    for (int i = 0; i < k; i++) {
        aux[i] = 0;
    }
}

void calculate_aux(int index) {
    aux[residents[index]] = 1;
    
    int sum = residents[index];
    int length = 1;
    for (int i = index + 1; i < n; i++) {
        sum += residents[i];
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

    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        cin >> residents[i];
    }

    clear_aux();

    for (int y = n - 1; y >= 0; y--) {
        if (y != n - 1) {
            calculate_aux(y + 1);
        }
        // Now check every subarray starting at x and
        // ending at y. That subarray has sum s. If s
        // is less than k, then check if there is a
        // a subarray to the right of y, so that the
        // two subarrays have sum k and have the least
        // length possible.
        int sum = 0;
        for (int x = y; x >= 0; x--) {
            sum += residents[x];

            int length = y - x + 1;

            if (sum == k) {
                if (length < answer) {
                    answer = length;
                }
            }
            else if (sum < k) {
                if (aux[k - sum]) {
                    int current = aux[k - sum] + length; 
                    if (current < answer) {
                        answer = current;
                    }
                }
            }
            else {
                break;
            }
        }
    }

    if (answer == 20005) {
        cout << "-1" << endl;
    }
    else {
        cout << answer << endl;
    }

    return 0;
}