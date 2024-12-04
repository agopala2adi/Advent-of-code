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

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    bool bEnabled = true;

    vector<string> vsPuzzle;

    /* Read each line from file */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        string sRowPuzzle(arr);
        vsPuzzle.push_back(sRowPuzzle);

        /* Increment count */
        ++cnt1;
    }

    /* Get the column size */
    cnt2 = vsPuzzle[0].size();
    /* Row size is in cnt1 */

    /* Part (a) */ 
    /* Check all rows */
    for (cnt3 = 0; cnt3 < cnt1; cnt3++)
    {
        for (cnt4 = 0; cnt4 < cnt2-3; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'X' && vsPuzzle[cnt3][cnt4+1] == 'M' && vsPuzzle[cnt3][cnt4+2] == 'A' && vsPuzzle[cnt3][cnt4+3] == 'S')
            {
                ++nFirstPart;
            }
        }
    }
    /* Check rows backwards */
    for (cnt3 = 0; cnt3 < cnt1; cnt3++)
    {
        for (cnt4 = 3; cnt4 < cnt2; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'X' && vsPuzzle[cnt3][cnt4-1] == 'M' && vsPuzzle[cnt3][cnt4-2] == 'A' && vsPuzzle[cnt3][cnt4-3] == 'S')
            {
                ++nFirstPart;
            }
        }
    }
    /* Check all columns */
    for (cnt3 = 0; cnt3 < cnt1-3; cnt3++)
    {
        for (cnt4 = 0; cnt4 < cnt2; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'X' && vsPuzzle[cnt3+1][cnt4] == 'M' && vsPuzzle[cnt3+2][cnt4] == 'A' && vsPuzzle[cnt3+3][cnt4] == 'S')
            {
                ++nFirstPart;
            }
        }
    }
    /* Check all columns backwards */
    for (cnt3 = 3; cnt3 < cnt1; cnt3++)
    {
        for (cnt4 = 0; cnt4 < cnt2; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'X' && vsPuzzle[cnt3-1][cnt4] == 'M' && vsPuzzle[cnt3-2][cnt4] == 'A' && vsPuzzle[cnt3-3][cnt4] == 'S')
            {
                ++nFirstPart;
            }
        }
    }
    /* Check main diagonal (down and right) */
    for (cnt3 = 0; cnt3 < cnt1-3; cnt3++)
    {
        for (cnt4 = 0; cnt4 < cnt2-3; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'X' && vsPuzzle[cnt3+1][cnt4+1] == 'M' && vsPuzzle[cnt3+2][cnt4+2] == 'A' && vsPuzzle[cnt3+3][cnt4+3] == 'S')
            {
                ++nFirstPart;
            }
        }
    }
    /* Check main diagonal (down and right) backwards */
    for (cnt3 = 3; cnt3 < cnt1; cnt3++)
    {
        for (cnt4 = 3; cnt4 < cnt2; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'X' && vsPuzzle[cnt3-1][cnt4-1] == 'M' && vsPuzzle[cnt3-2][cnt4-2] == 'A' && vsPuzzle[cnt3-3][cnt4-3] == 'S')
            {
                ++nFirstPart;
            }
        }
    }

    /* Check main diagonal (down and left) */
    for (cnt3 = 0; cnt3 < cnt1-3; cnt3++)
    {
        for (cnt4 = 3; cnt4 < cnt2; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'X' && vsPuzzle[cnt3+1][cnt4-1] == 'M' && vsPuzzle[cnt3+2][cnt4-2] == 'A' && vsPuzzle[cnt3+3][cnt4-3] == 'S')
            {
                ++nFirstPart;
            }
        }
    }

    /* Check main diagonal (down and left) backwards */
    for (cnt3 = 3; cnt3 < cnt1; cnt3++)
    {
        for (cnt4 = 0; cnt4 < cnt2-3; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'X' && vsPuzzle[cnt3-1][cnt4+1] == 'M' && vsPuzzle[cnt3-2][cnt4+2] == 'A' && vsPuzzle[cnt3-3][cnt4+3] == 'S')
            {
                ++nFirstPart;
            }
        }
    }

    /* Part (b) */

    for (cnt3 = 1; cnt3 < cnt1-1; cnt3++)
    {
        for (cnt4 = 1; cnt4 < cnt2-1; cnt4++)
        {
            if (vsPuzzle[cnt3][cnt4] == 'A')
            {
                /*
                    M   M
                      A
                    S   S
                */
                if ((vsPuzzle[cnt3-1][cnt4-1] == 'M' && vsPuzzle[cnt3+1][cnt4+1] == 'S') && 
                    (vsPuzzle[cnt3-1][cnt4+1] == 'M' && vsPuzzle[cnt3+1][cnt4-1] == 'S'))
                {
                    ++nSecondPart;
                }
                /*
                    M   S
                      A
                    M   S
                */
                else if ((vsPuzzle[cnt3-1][cnt4-1] == 'M' && vsPuzzle[cnt3+1][cnt4+1] == 'S') && 
                    (vsPuzzle[cnt3+1][cnt4-1] == 'M' && vsPuzzle[cnt3-1][cnt4+1] == 'S'))
                {
                    ++nSecondPart;
                }
                /*
                    S   S
                      A
                    M   M
                */
                else if ((vsPuzzle[cnt3-1][cnt4-1] == 'S' && vsPuzzle[cnt3+1][cnt4+1] == 'M') && 
                    (vsPuzzle[cnt3-1][cnt4+1] == 'S' && vsPuzzle[cnt3+1][cnt4-1] == 'M'))
                {
                    ++nSecondPart;
                }
                /*
                    S   M
                      A
                    S   M
                */
                else if ((vsPuzzle[cnt3-1][cnt4-1] == 'S' && vsPuzzle[cnt3+1][cnt4+1] == 'M') && 
                    (vsPuzzle[cnt3+1][cnt4-1] == 'S' && vsPuzzle[cnt3-1][cnt4+1] == 'M'))
                {
                    ++nSecondPart;
                }
                else
                {
                    /* Empty else */
                }
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

