#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[1000][100000];


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

    int64_t mavXYCord = 0;
    const int64_t nYCordMax = 10000000ll;

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    vector <string> sGalaxies;

    int64_t nTotalLines = 0;

    vector<int64_t> nDistanceX;
    vector<int64_t> nDistanceY;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        string galaxy = arr[cnt1];
        /* Remove \n and \r */
        if (galaxy[galaxy.size()-1] == '\n' || galaxy[galaxy.size()-1] == '\r')
        {
            galaxy.pop_back();
        }
        if (galaxy[galaxy.size()-1] == '\n' || galaxy[galaxy.size()-1] == '\r')
        {
            galaxy.pop_back();
        }

        /* Store input into galaxies */
        sGalaxies.push_back(galaxy);

        /* Check if the current line is all dots */
        for (cnt2 = 0; cnt2 < galaxy.size(); cnt2++)
        {
            if (arr[cnt1][cnt2] != '.')
            {
                break;
            }
        }
        /* If so, add additional line of dots */
        if (cnt2 == galaxy.size())
        {
            sGalaxies.push_back(galaxy);
            nTotalLines++;
        }
        /* Increment count to move to next line */
        ++cnt1;
        nTotalLines++;
    }

    /* Check for columns, if a column is all dots */
    for (cnt2 = 0; cnt2 < sGalaxies[0].size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < nTotalLines; cnt3++)
        {
            if (sGalaxies[cnt3][cnt2] != '.')
            {
                cnt5 = cnt3;
                break;
            }
        }
        /* If the whole column is dots, add additional column of dots */
        if (cnt3 == nTotalLines)
        {
            for (cnt3 = 0; cnt3 < nTotalLines; cnt3++)
            {
                sGalaxies[cnt3].insert(cnt2+1, ".");
            }
            /* Increment the count to not process again */
            cnt2++;
        }
    }

    /* Get all coordinates of galaxies */
    for (cnt2 = 0; cnt2 < nTotalLines; cnt2++)
    {
        for (cnt3 = 0; cnt3 < sGalaxies[0].size(); cnt3++)
        {
            if (sGalaxies[cnt2][cnt3] == '#')
            {
                nDistanceX.push_back(cnt2);
                nDistanceY.push_back(cnt3);
            }
        }
    }

    /* Find the Manhattan distance between all galaxies */
    for (cnt2 = 0; cnt2 < nDistanceX.size(); cnt2++)
    {
        for (cnt3 = cnt2+1; cnt3 < nDistanceY.size(); cnt3++)
        {
            nPartOneSum += abs(nDistanceX[cnt2]-nDistanceX[cnt3]);
            nPartOneSum += abs(nDistanceY[cnt2]-nDistanceY[cnt3]);
        }
    }

    /* For part 2 */
    nDistanceX.clear();
    nDistanceY.clear();

    /* Check for columns, if a column is all dots */
    for (cnt2 = 0; cnt2 < sGalaxies[0].size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < nTotalLines; cnt3++)
        {
            if (sGalaxies[cnt3][cnt2] != '.')
            {
                break;
            }
        }
        /* If the whole column is dots, add additional column of dots */
        if (cnt3 == nTotalLines)
        {
            for (cnt3 = 0; cnt3 < nTotalLines; cnt3++)
            {
                sGalaxies[cnt3].insert(cnt2+1, ".");
            }
            /* Increment the count to not process again */
            cnt2++;
        }
    }

    /* Check for rows */
    /* Check if the current line is all dots */
    for (cnt1 = 0; cnt1 < nTotalLines; cnt1++)
    {
        for (cnt2 = 0; cnt2 < sGalaxies[0].size(); cnt2++)
        {
            if (sGalaxies[cnt1][cnt2] != '.')
            {
                break;
            }
        }

        if (cnt2 == sGalaxies[0].size())
        {
            sGalaxies.insert(sGalaxies.begin() + cnt1 + 1, sGalaxies[cnt1]);
            cnt1++;
            nTotalLines++;
        }
    }
    /* Now, we have expanded four times from the beginning */

    /* Get all coordinates of galaxies */
    for (cnt2 = 0; cnt2 < nTotalLines; cnt2++)
    {
        for (cnt3 = 0; cnt3 < sGalaxies[0].size(); cnt3++)
        {
            if (sGalaxies[cnt2][cnt3] == '#')
            {
                nDistanceX.push_back(cnt2);
                nDistanceY.push_back(cnt3);
            }
        }
    }

    /* Find the Manhattan distance between all galaxies */
    for (cnt2 = 0; cnt2 < nDistanceX.size(); cnt2++)
    {
        for (cnt3 = cnt2+1; cnt3 < nDistanceY.size(); cnt3++)
        {
            cnt7 += abs(nDistanceX[cnt2]-nDistanceX[cnt3]);
            cnt7 += abs(nDistanceY[cnt2]-nDistanceY[cnt3]);
        }
    }

    /* Store the difference between the number times 1000000/2-1 */
    nPartTwoSum = (cnt7 - nPartOneSum) * (1000000/2 - 1) + nPartOneSum;


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

