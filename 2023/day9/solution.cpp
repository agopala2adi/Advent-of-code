#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[10000][1000];

int64_t getDifference(vector <int64_t> nSequence, bool bForward);

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen("input.txt", "r");

    fseek(fp, 0L, SEEK_SET);

    // read a line -> fgets(arr, sizeof(arr), fp);
    // while(fgets(arr, sizeof(arr), fp) != NULL)
    // read a formatted character -> fscanf(fp, "%d-%d %c: %s", &a, &b, &c, &arr);
    // while(feof(fp) == 0)
    // To scan string -> sscanf( arr, "%d-%d %c: %s", &a, &b, &c, &arr);
    // To printf uint64_t -> printf("%llu ", fin);

    // String stream: stringstream iss(arr);
    // Store word from string to string iss >> word
    // Display: printf("%s\n",word.c_str());

    // list<string> totalStrings;
    // for (auto it = totalStrings.begin(); it != totalStrings.end(); ++it)
    //     string str = *it;


    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t mavXYCord = 0;
    const int64_t nYCordMax = 10000000ll;

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        stringstream iss(arr[cnt1]);
        string word;

        vector<int64_t> nSequence;

        while (iss >> word)
        {
            /* Store the number into sequence */
            nSequence.push_back(atoll(word.c_str()));
        }

        /* Get the forward difference */
        cnt2 = getDifference(nSequence, true);

        /* Store the difference  */
        cnt4 = cnt2 + nSequence[nSequence.size()-1];
        /* Accumulate part 1 solution */
        nPartOneSum += cnt4;

        /* Get the backward difference */
        cnt2 = getDifference(nSequence, false);

        /* Store the difference  */
        cnt4 = -cnt2 + nSequence[0];
        /* Accumulate part 2 solution */
        nPartTwoSum += cnt4;

        /* Increment count to move to next line */
        ++cnt1;
    }


    /* Display part a and b answers */
    cout << "Part (a): " << nPartOneSum << endl;

    cout << "Part (b): " << nPartTwoSum << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

/* Get the difference - recursively */
int64_t getDifference(vector <int64_t> nSequence, bool bForward)
{
    int64_t cnt1 = 0, cnt2 = 0, cnt3;
    vector <int64_t> nNewSequence;

    cnt2 = nSequence[1] - nSequence[0];

    /* Check if the difference between subsequent elements is same */
    for (cnt1 = 1; cnt1 < nSequence.size(); cnt1++)
    {
        if (cnt2 != (nSequence[cnt1] - nSequence[cnt1-1]))
        {
            break;
        }
    }

    /* If all differences are same, return the difference */
    if (cnt1 == nSequence.size())
    {
        return cnt2;
    }
    else
    {
        /* Else, create another array with the differences */
        for (cnt1 = 1; cnt1 < nSequence.size(); cnt1++)
        {
            nNewSequence.push_back(nSequence[cnt1]-nSequence[cnt1-1]);
        }
        /* If forward difference, return diff + last sequence value */
        if (bForward == true)
        {
            cnt3 = nNewSequence[nNewSequence.size()-1] + getDifference(nNewSequence, bForward);
        }
        /* If backward difference, return first sequence value - diff */
        else
        {
            cnt3 = nNewSequence[0] - getDifference(nNewSequence, bForward);
        }
        return cnt3;
    }
}
