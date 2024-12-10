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

unordered_map<string, bool> umapLavaMap;

int64_t startHike(vector<string>& vsLavaMap, int64_t nPosX, int64_t nPosY, bool nPartTwo = false);

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

    vector<string> vsLavaMap;

    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        /* Store the read array in a vector of strings */
        vsLavaMap.push_back(arr);
        /* Remove the newline characters - if any */
        if (vsLavaMap[cnt1][vsLavaMap[cnt1].size()-1] == '\n' || vsLavaMap[cnt1][vsLavaMap[cnt1].size()-1] == '\r')
        {
            vsLavaMap[cnt1].pop_back();
        }
        /* Remove the newline characters - if any again */
        if (vsLavaMap[cnt1][vsLavaMap[cnt1].size()-1] == '\n' || vsLavaMap[cnt1][vsLavaMap[cnt1].size()-1] == '\r')
        {
            vsLavaMap[cnt1].pop_back();
        }

        /* Increment count */
        ++cnt1;
    }

    /* Parse through the entire map and find a trial head - a zero */
    for (cnt2 = 0; cnt2 < vsLavaMap.size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < vsLavaMap[0].size(); cnt3++)
        {
            /* If the position is a zero, start the hike */
            if (vsLavaMap[cnt2][cnt3] == '0')
            {
                /* Clear the map for each trial - for part (a)*/
                umapLavaMap.clear();
                nFirstPart += startHike(vsLavaMap, cnt2, cnt3);
                nSecondPart += startHike(vsLavaMap, cnt2, cnt3, true);
            }
        }
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


/**
 * @brief Recursively counts the number of times the digit '9' appears in a lava map.
 *
 * This function traverses a 2D vector representing a lava map and counts the occurrences
 * of the digit '9'. The traversal is done recursively, and the function can operate in
 * two modes: part one and part two. In part one mode, the function also keeps track of
 * visited positions to avoid counting the same position multiple times.
 *
 * @param vsLavaMap A reference to a 2D vector of strings representing the lava map.
 * @param nPosX The current x-coordinate (row index) in the lava map.
 * @param nPosY The current y-coordinate (column index) in the lava map.
 * @param nPartTwo A boolean flag indicating whether to operate in part two mode (default is false).
 * @return The number of times the digit '9' has been counted.
 */
int64_t startHike(vector<string>& vsLavaMap, int64_t nPosX, int64_t nPosY, bool nPartTwo)
{
    /* Number of times 9 has been counted */
    int64_t nCount = 0;

    /* If part (a), check whether the number 9's co-ordinates is already repeated */
    if (nPartTwo == false)
    {
        if (vsLavaMap[nPosX][nPosY] == '9' && umapLavaMap.find(to_string(nPosX)+to_string(nPosY)) == umapLavaMap.end())
        {
            /* If not, add it to the co-ordinates */
            umapLavaMap[to_string(nPosX)+to_string(nPosY)] = true;
            /* Return 1 to show that we have counted a nine */
            return nCount + 1;
        }
    }
    else
    {
        /* For part (b), this is not required, count all the times 9 is seen */
        if (vsLavaMap[nPosX][nPosY] == '9')
        {
            return nCount + 1;
        }
    }
    /* Check in all directions - down if incremented by one */
    if (nPosX+1 >= 0 && nPosX+1 < vsLavaMap.size() && 
             vsLavaMap[nPosX][nPosY] == vsLavaMap[nPosX+1][nPosY] - 1)
    {
        /* Recursively call the function until reaching a nine */
        nCount += startHike(vsLavaMap, nPosX+1, nPosY, nPartTwo);
    }
    /* Check in all directions - up if incremented by one */
    if (nPosX-1 >= 0 && nPosX-1 < vsLavaMap.size() && 
             vsLavaMap[nPosX][nPosY] == vsLavaMap[nPosX-1][nPosY] - 1)
    {
        /* Recursively call the function until reaching a nine */
        nCount += startHike(vsLavaMap, nPosX-1, nPosY, nPartTwo);
    }
    /* Check in all directions - right if incremented by one */
    if (nPosY+1 >= 0 && nPosY+1 < vsLavaMap[0].size() && 
             vsLavaMap[nPosX][nPosY] == vsLavaMap[nPosX][nPosY+1] - 1)
    {
        /* Recursively call the function until reaching a nine */
        nCount += startHike(vsLavaMap, nPosX, nPosY+1, nPartTwo);
    }
    /* Check in all directions - left if incremented by one */
    if (nPosY-1 >= 0 && nPosY-1 < vsLavaMap[0].size() && 
             vsLavaMap[nPosX][nPosY] == vsLavaMap[nPosX][nPosY-1] - 1)
    {
        /* Recursively call the function until reaching a nine */
        nCount += startHike(vsLavaMap, nPosX, nPosY-1, nPartTwo);
    }

    return nCount;
}


