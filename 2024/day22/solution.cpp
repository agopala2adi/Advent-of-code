#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[10000];

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);

    FILE* fp = fopen("input.txt", "r");

    if (fp == nullptr)
    {
        cerr << "Cannot open input file." << endl;
        return -1;
    }

    cout << "Start Time: " << std::ctime(&start_time) << endl;

    fseek(fp, 0L, SEEK_SET);

    // read a line -> fgets(arr, sizeof(arr), fp);
    // while(fgets(arr, sizeof(arr), fp) != NULL)
    // read a formatted character -> fscanf(fp, "%d-%d %c: %s", &a, &b, &c, &arr);
    // while(feof(fp) == 0)
    // To scan string -> sscanf( arr, "%d-%d %c: %s", &a, &b, &c, &arr);
    // To printf uint -> printf("%llu ", fin);

    // String stream: stringstream iss(arr);
    // Store word from string to string iss >> word
    // Display: printf("%s\n",word.c_str());

    // list<string> totalStrings;
    // for (auto it = totalStrings.begin(); it != totalStrings.end(); ++it)
    //     string str = *it;


    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    vector<int64_t> vnNumbers;

    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        string sInitSecret = arr;
        if (sInitSecret[sInitSecret.size()-1] == '\n' || sInitSecret[sInitSecret.size()-1] == '\r')
        {
            sInitSecret.pop_back();
        }
        if (sInitSecret[sInitSecret.size()-1] == '\n' || sInitSecret[sInitSecret.size()-1] == '\r')
        {
            sInitSecret.pop_back();
        }

        vnNumbers.push_back(stoll(sInitSecret));

        /* Increment count */
        ++cnt1;
    }

    /* Rates (last digit) for each initial secret upto 2000 */
    vector<vector<char>> vnRates;
    /* Difference vector (last digit) between each iteration */
    vector<vector<char>> vnRateDiff;

    /* Calculate rates for each initial secret */
    for (cnt1 = 0; cnt1 < vnNumbers.size(); cnt1++)
    {
        /* Rates for each initial secret */
        vector<char> vnRateSecret;

        /* Initial secret number is the initial provided secret */
        int64_t nSecNumb = vnNumbers[cnt1];

        /* Store that inside the rate secret number */
        vnRateSecret.push_back(nSecNumb % 10);

        /* Iterate 2000 times for the given secret */
        for (cnt2 = 0; cnt2 < 2000; cnt2++)
        {
            /* Calculate the result of multiplying the secret number by 64. 
             * Then, mix this result into the secret number. Finally, prune the
             * secret number. */
            int64_t nGivenNumb = nSecNumb * 64;
            nSecNumb = nSecNumb ^ nGivenNumb;
            nSecNumb %= 16777216;

            /* Calculate the result of dividing the secret number by 32. 
             * Then, mix this result into the secret number. Finally, prune the
             * secret number. */
            nGivenNumb = nSecNumb / 32;
            nSecNumb = nSecNumb ^ nGivenNumb;
            nSecNumb %= 16777216;

            /* Calculate the result of multiplying the secret number by 2048. 
             * Then, mix this result into the secret number. Finally, prune the
             * secret number. */
            nGivenNumb = nSecNumb * 2048;
            nSecNumb = nSecNumb ^ nGivenNumb;
            nSecNumb %= 16777216;

            /* Store only the last unit's place digit */
            vnRateSecret.push_back(nSecNumb % 10);
        }
        /* Store the rates vector of vector the rates of the current secret */
        vnRates.push_back(vnRateSecret);

        /* For part (a), add all secrets after 2000 iterations */
        nFirstPart += nSecNumb;
    }

    /* Display part a answer */
    cout << "Part (a): " << nFirstPart << endl;

    /* Part (b) - brute force */

    /* Assume that there are no more than 10k buyers 
     * Create a hash map storeing the four diffs and the cost as key and value*/
    unordered_map<string, char> umMap[10000];

    /* For each buyer */
    for (cnt1 = 0; cnt1 < vnRates.size(); cnt1++)
    {
        /* Get the diff for each secret buyer */
        vector<char> vnRateDiffSecret;
        for (cnt2 = 1; cnt2 < vnRates[cnt1].size(); cnt2++)
        {
            /* Store the diff */
            vnRateDiffSecret.push_back(vnRates[cnt1][cnt2]-vnRates[cnt1][cnt2-1]);
            /* If the diff is greater than 3, store the last 4 digits */
            if (cnt2 > 3)
            {
                string sValue = "";
                /* Store the last 4 digits's diff into the hash map */
                sValue = to_string(vnRateDiffSecret[cnt2-4]) + to_string(vnRateDiffSecret[cnt2-3]) + to_string(vnRateDiffSecret[cnt2-2]) + to_string(vnRateDiffSecret[cnt2-1]);
                /* Check if that combination is already present */
                if (umMap[cnt1].find(sValue) == umMap[cnt1].end())
                {
                    /* If not, add into the hash map - (4 diffs, bananas) */
                    umMap[cnt1][sValue] = vnRates[cnt1][cnt2];
                }
            }
        }
        /* Push all the differences of the current secret */
        vnRateDiff.push_back(vnRateDiffSecret);
    }

    /* For each buyer - brute force */
    for (cnt1 = 0; cnt1 < vnRates.size(); cnt1++)
    {
        cout << cnt1 << flush << "\r";
        /* Iterate through all the 4 diffs stored in the hash map */
        for (auto it = umMap[cnt1].begin(); it != umMap[cnt1].end(); ++it)
        {
            /* Store the banana's into the total cost variable  */
            int64_t nTotalCost = it->second;
            /* For all buyers, except the already considered buyer */
            for (cnt2 = 0; cnt2 < vnRates.size(); cnt2++)
            {
                /* If buyers are same, do not do anything */
                if (cnt1 == cnt2)
                {
                    continue;
                }
                /* Check if the difference is present in the next buyer's list */
                if (umMap[cnt2].find(it->first) != umMap[cnt2].end())
                {
                    /* If present, add the cost */
                    nTotalCost += umMap[cnt2][it->first];
                }
            }

            /* If cost is greater than previous, modify the cost */
            nSecondPart = max(nSecondPart, nTotalCost);
        }
    }

    /* Close the file */
    fclose(fp);

    /* Display part b answer */
    cout << "Part (b): " << nSecondPart << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

