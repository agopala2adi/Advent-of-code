#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[100000][1000];


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

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    vector<pair<int64_t, int64_t>> freshIds;

    bool bReadingFresh = true;


    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Read a line from the file */
        string sLine = arr[cnt1];

        /* Remove newline character */
        if (sLine.back() == '\n' || sLine.back() == '\r')
        {
            sLine.pop_back();
        }
        if (sLine.back() == '\n' || sLine.back() == '\r')
        {
            sLine.pop_back();
        }


        if (sLine.length() == 0)
        {
            bReadingFresh = false;
        }
        else if (bReadingFresh == true)
        {
            /* Read the ranges of fresh contents */
            sscanf(sLine.c_str(), "%lu-%lu", &cnt2, &cnt3);
            /* Store that in a vector of pair values */
            freshIds.push_back(make_pair(cnt2, cnt3));
        }
        else
        {
            /* Now start reading the ingredient IDs */
            sscanf(sLine.c_str(), "%lu", &cnt3);

            /* Check if the ingredient ID is within the fresh ranges */
            for (cnt2 = 0; cnt2 < freshIds.size(); ++cnt2)
            {
                if (freshIds[cnt2].first <= cnt3 && cnt3 <= freshIds[cnt2].second)
                {
                    break;
                }
            }

            /* If true increment the part 1's sum */
            if (cnt2 < freshIds.size())
            {
                ++nFirstPart;
            }
        }

        /* Increment count */
        ++cnt1;
    }

    /* Now we need to merge fresh ingredient IDs to remove duplicates */
    bool bDoAgain = true;

    /* Keep doing it until there is no change required */
    while (bDoAgain == true)
    {
        bDoAgain = false;

        /* Do a nested for loop to iterate through all freshIds */
        for (cnt2 = 0; cnt2 < freshIds.size(); ++cnt2)
        {
            /* Compare the current ID will all the previously looked IDs */
            for (cnt3 = 0; cnt3 < cnt2; cnt3++)
            {
                /* If the current ID is completely with the previous ID, remove
                 * it and restart from beginning 
                 *
                 * <-------|------|-------|-----|----------->
                 *         a      c       b     d
                 * 
                 * Where [a, b] is the freshIds[cnt2] -> previous ID
                 *       [c, d] is the freshIds[cnt3] -> current ID
                 */
                if (freshIds[cnt3].first >= freshIds[cnt2].first && freshIds[cnt3].second <= freshIds[cnt2].second)
                {
                    freshIds.erase(freshIds.begin() + cnt3);
                    bDoAgain = true;
                    break;
                }
                /* If the previous ID is completely with the current ID, remove
                 * the current ID and restart from beginning 
                 * 
                 * <-------|------|-------|-----|----------->
                 *         c      a       b     d
                 * 
                 * Where [a, b] is the freshIds[cnt2] -> previous ID
                 *       [c, d] is the freshIds[cnt3] -> current ID
                 */
                else if (freshIds[cnt3].first <= freshIds[cnt2].first && freshIds[cnt3].second >= freshIds[cnt2].second)
                {
                    freshIds.erase(freshIds.begin() + cnt2);
                    bDoAgain = true;
                    break;
                }
                /* If the current ID overlaps with the previous ID, merge them 
                 * and restart from beginning
                 * 
                 * <-------|------|-------|-----|----------->
                 *         a      c       b     d
                 * 
                 * Where [a, b] is the freshIds[cnt2] -> previous ID
                 *       [c, d] is the freshIds[cnt3] -> current ID
                */
                else if (freshIds[cnt3].first >= freshIds[cnt2].first && freshIds[cnt3].second >= freshIds[cnt2].second &&
                        freshIds[cnt3].first <= freshIds[cnt2].second)
                {
                    freshIds[cnt2].second = freshIds[cnt3].second;
                    freshIds.erase(freshIds.begin() + cnt3);
                    bDoAgain = true;
                    break;
                }
                /*
                 * If the previous ID overlaps with the current ID, merge them 
                 * and restart from beginning
                 * 
                 * <-------|------|-------|-----|----------->
                 *         c      a       d     b
                 * 
                 * Where [a, b] is the freshIds[cnt2] -> previous ID
                 *       [c, d] is the freshIds[cnt3] -> current ID
                */
                else if (freshIds[cnt3].first <= freshIds[cnt2].first && freshIds[cnt3].second <= freshIds[cnt2].second &&
                        freshIds[cnt3].second >= freshIds[cnt2].first)
                {
                    freshIds[cnt2].first = freshIds[cnt3].first;
                    freshIds.erase(freshIds.begin() + cnt3);
                    bDoAgain = true;
                    break;
                }
                else
                {
                    /* Empty else */
                }
            }

            if (bDoAgain == true)
            {
                break;
            }
        }
    }

    /* Now add all the fresh IDs and they would be unique */
    for (cnt2 = 0; cnt2 < freshIds.size(); ++cnt2)
    {
        nSecondPart += (freshIds[cnt2].second - freshIds[cnt2].first + 1);
    }


    /* Display part a and b answers */
    cout << "Part (a): " << nFirstPart << endl;

    cout << "Part (b): " << nSecondPart << endl;

    /* Close the file */
    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

