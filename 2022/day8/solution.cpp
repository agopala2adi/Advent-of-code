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
    int64_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    uint64_t max_val = 0;
    uint64_t min_val = 10000000ull;

    vector<int64_t> nElfVec;

    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        cnt1++;
    }

    /* cnt1 has the number of rows */

    /* Get the number of columns (store into cnt7) = length of the first array */
    cnt7 = strlen(arr[0]) -  1;

    /* Loop through all the rows (except first and last) */
    for (cnt2 = 1; cnt2 < cnt1-1; cnt2++)
    {
        /* Loop through all the columns (except first and last) */
        for (cnt3 = 1; cnt3 < cnt7 - 1; cnt3++)
        {
            /* For all values above, in the column line of the tree */
            for (cnt4 = 0; cnt4 < cnt2; cnt4++)
            {
                /* If a tree is blocking the view stop checking for more trees */
                if (arr[cnt4][cnt3] >= arr[cnt2][cnt3])
                {
                    break;
                }
            }
            /* If there is no tree blocking, add the count */
            if (cnt4 == cnt2)
            {
                ++cnt9;
            }
            else
            {
                /* For all trees below, in the column line of the tree */
                for (cnt4 = cnt2+1; cnt4 < cnt1; cnt4++)
                {
                    /* If a tree is blocking the view stop checking for more trees */
                    if (arr[cnt4][cnt3] >= arr[cnt2][cnt3])
                    {
                        break;
                    }
                }
                /* If there is no tree blocking, add the count */
                if (cnt4 == cnt1)
                {
                    ++cnt9;
                }
                else
                {
                    /* For all trees to the left, in the row line of the tree */
                    for (cnt5 = 0; cnt5 < cnt3; cnt5++)
                    {
                        /* If a tree is blocking the view stop checking for more trees */
                        if (arr[cnt2][cnt5] >= arr[cnt2][cnt3])
                        {
                            break;
                        }
                    }
                    /* If there is no tree blocking, add the count */
                    if (cnt5 == cnt3)
                    {
                        ++cnt9;
                    }
                    else
                    {
                        /* For all trees to the right, in the row line of the tree */
                        for (cnt5 = cnt3+1; cnt5 < cnt7; cnt5++)
                        {
                            /* If a tree is blocking the view stop checking for more trees */
                            if (arr[cnt2][cnt5] >= arr[cnt2][cnt3])
                            {
                                break;
                            }
                        }
                        /* If there is no tree blocking, add the count */
                        if (cnt5 == cnt7)
                        {
                            ++cnt9;
                        }
                    }
                }
            }
        }
    }

    /* Print with adding all the boundaries = 2 * (NUM_ROWS + NUM_COLUMNS - 2)*/
    cout << "Part (a): " << (cnt9 + cnt1 * 2 + (cnt7-2)*2) << endl;

    /* Store the maximum if cnt8 */
    cnt8 = 0;

    /* Loop through all the rows (except first and last) */
    for (cnt2 = 1; cnt2 < cnt1-1; cnt2++)
    {
        /* Loop through all the columns (except first and last) */
        for (cnt3 = 1; cnt3 < cnt7 - 1; cnt3++)
        {
            /* Temp count to check number of trees in the surrounding */
            int64_t nCnt1 = 0, nCnt2 = 0, nCnt3 = 0, nCnt4 = 0;

            /* Check for the trees above in the same column */
            for (cnt4 = cnt2-1; cnt4 >= 0; cnt4--)
            {
                ++nCnt1;
                if (arr[cnt4][cnt3] >= arr[cnt2][cnt3])
                {
                    break;
                }
            }
            /* Check for the trees below in the same column */
            for (cnt4 = cnt2+1; cnt4 < cnt1; cnt4++)
            {
                ++nCnt2;
                if (arr[cnt4][cnt3] >= arr[cnt2][cnt3])
                {
                    break;
                }
            }
            /* Check for the trees left in the same row */
            for (cnt4 = cnt3-1; cnt4 >= 0; cnt4--)
            {
                ++nCnt3;
                if (arr[cnt2][cnt4] >= arr[cnt2][cnt3])
                {
                    break;
                }
            }
            /* Check for the trees right in the same row */
            for (cnt4 = cnt3+1; cnt4 < cnt7; cnt4++)
            {
                ++nCnt4;
                if (arr[cnt2][cnt4] >= arr[cnt2][cnt3])
                {
                    break;
                }
            }

            /* Compute score and compare with max */
            cnt9 = (nCnt1 * nCnt2 * nCnt3 * nCnt4);
            if (cnt8 < cnt9)
            {
                cnt8 = cnt9;
            }
        }
    }

    cout << "Part (b): " << cnt8 << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

