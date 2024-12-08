#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[1000];

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

    vector<string> vsMap;
    vector<string> vsMapCopy;


    /* Read each line from file */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        vsMap.push_back(arr);

        /* Remove the new line characters at the end */
        if (vsMap[cnt1][vsMap[cnt1].size()-1] == '\n' || vsMap[cnt1][vsMap[cnt1].size()-1] == '\r')
        {
            vsMap[cnt1].pop_back();
        }
        /* Remove the new line characters at the end again if it contains both */
        if (vsMap[cnt1][vsMap[cnt1].size()-1] == '\n' || vsMap[cnt1][vsMap[cnt1].size()-1] == '\r')
        {
            vsMap[cnt1].pop_back();
        }

        /* Increment count */
        ++cnt1;
    }

    /* Keep a copy of the map and modify the elements of the copy */
    vsMapCopy = vsMap;

    /* Run a loop across all characters in the map */
    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        for (cnt3 = 0; cnt3 < vsMap[0].size(); cnt3++)
        {
            /* if the current character in the map is an antenna */
            if (vsMap[cnt2][cnt3] != '.')
            {
                /* Scan through all the whole map once again */
                for (cnt4 = 0; cnt4 < vsMap.size(); cnt4++)
                {
                    for (cnt5 = 0; cnt5 < vsMap[0].size(); cnt5++)
                    {
                        /* If found another antenna of same type (ensure that it 
                         * is not the same antenna by checking the x and y 
                         * co-ordinates)
                        */
                        if ((vsMap[cnt4][cnt5] == vsMap[cnt2][cnt3]) && 
                            (cnt3 != cnt5 || cnt2 != cnt4))
                        {
                            int64_t nDiffX = cnt4 - cnt2;
                            int64_t nDiffY = cnt5 - cnt3;

                            /* Check if the antinode lie within the antenna limit */
                            if (cnt4 + (nDiffX) >= 0 && cnt4 + (nDiffX) < vsMap.size() &&
                                cnt5 + (nDiffY) >= 0 && cnt5 + (nDiffY) < vsMap[0].size())
                            {
                                /* If so place the antinode with a hash */
                                vsMapCopy[cnt4 + nDiffX][cnt5 + nDiffY] = '#';
                            }
                        }
                    }
                }
            }
        }
    }

    /* Count all the antinodes */
    for (cnt2 = 0; cnt2 < vsMap.size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < vsMap[cnt2].size(); cnt3++)
        {
            if (vsMapCopy[cnt2][cnt3] == '#')
            {
                ++nFirstPart;
            }
        }
    }

    /* Restore the original map for part (2) */
    vsMapCopy = vsMap;

    /* Run a loop across all characters in the map */
    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        for (cnt3 = 0; cnt3 < vsMap[0].size(); cnt3++)
        {
            /* if the current character in the map is an antenna */
            if (vsMap[cnt2][cnt3] != '.')
            {
                for (cnt4 = 0; cnt4 < vsMap.size(); cnt4++)
                {
                    for (cnt5 = 0; cnt5 < vsMap[0].size(); cnt5++)
                    {
                        /* If found another antenna of same type (ensure that it 
                         * is not the same antenna by checking the x and y 
                         * co-ordinates)
                        */
                        if ((vsMap[cnt4][cnt5] == vsMap[cnt2][cnt3]) && 
                            (cnt3 != cnt5 || cnt2 != cnt4))
                        {
                            int64_t nMultiple = 1;
                            /* Check if the antinode lie within the antenna limit
                             * Run a while loop to collect all the antennas 
                             * that are part of the map 
                            */
                            while (cnt4 + nMultiple*(cnt4 - cnt2) >= 0 && cnt4 + nMultiple*(cnt4 - cnt2) < vsMap.size() &&
                                   cnt5 + nMultiple*(cnt5 - cnt3) >= 0 && cnt5 + nMultiple*(cnt5 - cnt3) < vsMap[0].size())
                            {
                                vsMapCopy[cnt4 + nMultiple*(cnt4 - cnt2)][cnt5 + nMultiple*(cnt5 - cnt3)] = '#';
                                nMultiple++;
                            }
                        }
                    }
                }
            }
        }
    }

    /* Count all the antinodes - include all the nodes that are not a dot */
    for (cnt2 = 0; cnt2 < vsMap.size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < vsMap[cnt2].size(); cnt3++)
        {
            if (vsMapCopy[cnt2][cnt3] != '.')
            {
                ++nSecondPart;
            }
        }
    }


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

