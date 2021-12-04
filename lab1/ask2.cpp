#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int *sumArray;
int *people;

// void refreshSumArray(int index, int lengthOfArray, int targetSum)
// {
//     // loop through people array and create all different subarrays
//     for (int i = index; i < lengthOfArray; i++)
//     {
//         int currentSumOfSubArray = people[i];
//         for (int j = i; j < lengthOfArray; j++)
//         {
//             if (i != j)
//             {
//                 currentSumOfSubArray += people[j];
//             }

//             if (currentSumOfSubArray <= targetSum)
//             {
//                 int lengthOfSubarray = j - i + 1;
//                 if (sumArray[currentSumOfSubArray - 1] > lengthOfSubarray || sumArray[currentSumOfSubArray - 1] == -1)
//                 {
//                     sumArray[currentSumOfSubArray - 1] = lengthOfSubarray;
//                 }
//             }
//             else
//                 break;
//         }
//     }
// }

void refreshSumArrayDynamic(int index, int lengthOfArray, int targetSum)
{
    // people[index] is the inserted element in sumArray

    if (sumArray[people[index] - 1] == -1)
    {
        sumArray[people[index] - 1] = 1;
    }

    for (int i = 0; i < targetSum; i++)
    {
        if (sumArray[i] != -1 && i + 1 + people[index] <= targetSum)
        {
            int currentLength = sumArray[i] + 1;
            if (sumArray[i + people[index]] > currentLength)
            {
                sumArray[i + people[index]] = currentLength;
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    int N, K;
    cin >> N;
    cin >> K;
    int result = INT_MAX;
    sumArray = (int *)malloc(K * sizeof(int));
    people = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < K; i++)
    {
        sumArray[i] = -1;
    }

    for (int i = 0; i < N; i++)
    {
        cin >> people[i];
    }

    int i, j;
    for (i = N - 1; i >= 0; i--)
    {
        // check if its not the last element
        if (i != N - 1)
        {
            refreshSumArrayDynamic(i + 1, N, K);
        }

        int currentSum = people[i];
        if (currentSum == K)
        {
            cout << 1 << endl;
            return 0;
        }

        for (j = i; j >= 0; j--)
        {
            if (i != j)
            {
                currentSum += people[j];
            }
            if (currentSum > K)
                break;
            else
            {
                int requestSum = K - currentSum;
                int currentLengthSubArray = i - j + 1;
                // possible error
                if (sumArray[requestSum - 1] != -1)
                {
                    int possibleResult = sumArray[requestSum - 1] + currentLengthSubArray;
                    if (possibleResult < result)
                    {
                        result = possibleResult;
                    }
                }
            }
        }
    }
    if (result == INT_MAX)
        cout << -1 << endl;
    else
        cout << result << endl;
    return 0;
}