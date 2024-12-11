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
    int64_t nPosStartX = 0, nPosStartY = 0, nPosStartXBackup = 0, nPosStartYBackup = 0;

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* Use a hash map to store the numbers so that repetition is avoided */
    unordered_map<int64_t, int64_t> umapNumber;

    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        stringstream iss(arr);
        string sNumber;

        /* Read each string into sNumber */
        while (iss >> sNumber)
        {
            /* Convert the string to an integer and store into the hash map 
             * as (key = number, value = 1)
             * Assumed - the numbers do repeat.
            */
            umapNumber[stoll(sNumber)] = 1;
        }

        /* Increment count */
        ++cnt1;
    }

    /* Run the code for 75 iterations */
    for (cnt1 = 0; cnt1 < 75; cnt1++)
    {
        /* Store the number in a vector */
        vector<int64_t> nNumber;
        /* Store the number of occurrences of each number in another vector */
        vector<int64_t> nNumberCount;

        /* Since the number changes, create a new vector and store the numbers
         * there while iterating through the numbers
         */
        vector<int64_t> nNumberNext;
        /* Store the changed number's count into another vector */
        vector<int64_t> nNumberNextCount;

        /* When the count reaches 25 count for part (a) */
        if (cnt1 == 25)
        {
            for (auto it = umapNumber.begin(); it != umapNumber.end(); ++it)
            {
                nFirstPart += it->second;
            }
        }

        /* Take the numbers stored in the hash map with the number of times */
        for (auto it = umapNumber.begin(); it != umapNumber.end(); ++it)
        {
            if (it->second > 0)
            {
                nNumber.push_back(it->first);
                nNumberCount.push_back(it->second);
            }
        }

        /* Iterate through all the numbers */
        for (cnt2 = 0; cnt2 < nNumber.size(); cnt2++)
        {
            /* If the number is a zero */
            if (nNumber[cnt2] == 0)
            {
                /* Add 1 to the next number */
                nNumberNext.push_back(1);
                /* Add the count of 0 to the new number's count */
                nNumberNextCount.push_back(nNumberCount[cnt2]);
            }
            /* If the number of digits is divisible by two, convert to sting and
             * compute the number of characters in that string */
            else if (to_string(nNumber[cnt2]).size() % 2 == 0)
            {
                /* Convert the number to a string */
                string sNumber = to_string(nNumber[cnt2]);

                /* Split the number into two numbers */
                string sFirstHalf = sNumber.substr(0, sNumber.size()/2);
                string sSecondHalf = sNumber.substr(sNumber.size()/2, sNumber.size()/2);

                /* Store the first number and its count into the next number vector */
                nNumberNext.push_back(stoll(sFirstHalf));
                nNumberNextCount.push_back(nNumberCount[cnt2]);
                /* Same for the second number */
                nNumberNext.push_back(stoll(sSecondHalf));
                nNumberNextCount.push_back(nNumberCount[cnt2]);
            }
            /* If none of that is true, then store the number times 2024 into
             * the new vector with its count */
            else
            {
                nNumberNext.push_back(nNumber[cnt2]*2024);
                nNumberNextCount.push_back(nNumberCount[cnt2]);
            }
        }

        /* Clear the hash map for making new changes */
        umapNumber.clear();

        /* Store the numbers into the hash map as (key = number, value = count) */
        for (cnt2 = 0; cnt2 < nNumberNext.size(); cnt2++)
        {
            umapNumber[nNumberNext[cnt2]] += nNumberNextCount[cnt2];
        }
    }

    /* After 75 iterations, count the total count into part (b) */
    for (auto it = umapNumber.begin(); it != umapNumber.end(); ++it)
    {
        nSecondPart += it->second;
    }


    /* Close the file */
    fclose(fp);


    /* Display part a and b answers */
    cout << "Part (a): " << nFirstPart << endl;

    cout << "Part (b): " << nSecondPart << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

