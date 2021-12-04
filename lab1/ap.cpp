#include <iostream>
#include <iterator>
#include <set>
#include <fstream>
#include <bits/stdc++.h>
// #include <algorithm>
// #include <climits>

#include <unordered_map>
#include <iterator>

using namespace std;

int N;
int K;
 

// Calculates prefix sum array
void calcPrefixSums(int *arr)
{
    for (int i = 1; i < N; i++)
        arr[i] = arr[i - 1] + arr[i];
}


void findOptimalSubSums(int arr[], int prefixSums[], int* optimal, int index){
    int i = index;
    for(int j=i; j<N; j++){
        if(i == j) {
            if(arr[i] > K) break;
            else {
                if(1 < optimal[arr[i]] || optimal[arr[i]] == 0) optimal[arr[i]] = 1;
            }
        }
        else{
            int sum = ( i == 0 ? prefixSums[j] : prefixSums[j] - prefixSums[i-1] );
            // cout << "Sum: "<< sum << endl; 
            int length = j - i + 1;

            if(sum > K ) break;
            else {
                if(length < optimal[sum] || optimal[sum] == 0) optimal[sum] = length;
            }
        }
    }

    // return *optimal;
}

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // ------------------------------------------------------
    cin >> N;
    cin >> K;
    
    int buildings[N];
    int prefixSums[N];

    for(int i=0; i<N; i++){
        cin >> buildings[i];
        prefixSums[i] = buildings[i];
    } 

    int i = 0, j = 0, minLength = INT_MAX;

    calcPrefixSums(prefixSums);

    // Initialise optimal array at 0
    int optimal[K+1];
    memset( optimal, 0, (K+1)*sizeof(int) );

    for(i=N-1; i>=0; i--){
        for(j=i; j>=0; j--){
            int sum ;
            if(i == j) sum = buildings[i];
            else sum = ( j == 0 ? prefixSums[i] : prefixSums[i] - prefixSums[j-1] );

            int length = i - j + 1;

            if(sum > K ) break;
            else if(sum == K && length < minLength) minLength = length;
            else if(optimal[K-sum] != 0 && length + optimal[K-sum] < minLength) minLength = length + optimal[K-sum];
        }    
        findOptimalSubSums(buildings, prefixSums, optimal, i);
    }

    if(minLength == INT_MAX) cout << -1 << endl;
    else cout << minLength << endl;

}