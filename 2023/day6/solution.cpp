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

    /* Store the time of each race here */
    vector <int64_t> nTime;
    /* Store the distance of each race here */
    vector <int64_t> nDist;

    /* Temp string to get words in input */
    string word;
    /* Temp string for part 2 to concat all inputs */
    string race;

    /* Read first line of input - time */
    fgets(arr[cnt1], sizeof(arr[cnt1]), fp);
    /* Split by space */
    stringstream iss(arr[cnt1]);
    /* Read first word and ignore */
    iss >> word;

    /* Read other numbers */   
    while (iss >> word)
    {
        /* Store it in time */
        nTime.push_back(atoll(word.c_str()));
        /* Concat all time values */
        race += word;
    }
    /* Store the concat value into the last time index */
    nTime.push_back(atoll(race.c_str()));

    /* Read second line of input - distance */
    fgets(arr[cnt1], sizeof(arr[cnt1]), fp);

    /* Split by space */
    stringstream iss2(arr[cnt1]);
    /* Read first word and ignore */
    iss2 >> word;
    
    /* Reset race for reading concatenating distances */
    race = "";

    /* Read other numbers */
    while (iss2 >> word)
    {
        /* Store it in distance */
        nDist.push_back(atoll(word.c_str()));
        /* Concat all distance values */
        race += word;
    }
    /* Store the concat value into the last distance index */
    nDist.push_back(atoll(race.c_str()));

    /* Reset part1 and part2 to 1 */
    nPartOneSum = 1;

    /* Run a loop for all numbers except the last */
    for (cnt1 = 0; cnt1 < nTime.size()-1; cnt1++)
    {
        /* count to store all the cases where we beat the record */
        cnt3 = 0;
        /* Loop through all possible times */
        for (cnt2 = 0; cnt2 < nTime[cnt1]; cnt2++)
        {
            /* If we beat the record */
            if (cnt2*(nTime[cnt1]-cnt2) > nDist[cnt1])
            {
                /* Increment the count */
                ++cnt3;
            }
        }

        /* If we beat the record at least once multiply to part one */
        if (cnt3 > 0)
        {
            nPartOneSum *= cnt3;
        }
    }

    /* Count for part 2 */
    nPartTwoSum = 0;
    /* Loop through all possible times */
    for (cnt2 = 0; cnt2 < nTime[cnt1]; cnt2++)
    {
        /* If we beat the record */
        if (cnt2*(nTime[cnt1]-cnt2) > nDist[cnt1])
        {
            /* Increment the count */
            ++nPartTwoSum;
        }
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

