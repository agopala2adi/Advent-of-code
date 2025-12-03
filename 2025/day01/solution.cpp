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

    vector<int64_t> firstCol;
    vector<int64_t> secondCol;

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    int64_t nDial = 50;
    int64_t nDialPrev = 50;

    /* Read each line from file */
    while (feof(fp) == 0)
    {
        /* Read lines */
        int tempRet = fscanf(fp, "%s", arr[cnt1]);

        if (strlen(arr[cnt1]) < 2)
        {
            /* If line is empty, break the loop */
            break;
        }

        /* Rotation alphabet, L or R */
        char rot = arr[cnt1][0];
        /* Number to append after rotation */
        int64_t nDistance = atoll(&arr[cnt1][1]);
        if (rot == 'L')
        {
            /* If rotation is L, decrement the dial by distance */
            nDial -= nDistance;
        }
        else if (rot == 'R')
        {
            /* If rotation is R, increment the dial by distance */
            nDial += nDistance;
        }
        else
        {
            cerr << "Invalid rotation character." << endl;
            return -1;
        }

        /* Normalize the dial within 0-99 */
        while (nDial < 0)
        {
            nDial += 100;
            /* Since, each time the dial does a loop, it would have clicked zero
             * once, so increment the password of second part */
            ++nSecondPart;

            /* Keep moving and incrementing the password until you get a positive 
             * result */
        }

        /* However, when we start from zero, then there would always be an extra
         * click which needs to be corrected.
         * 
         * For example: 
         * If say we are at 0 and it goes left by 3, the needle then goes to
         * 0-3 = -3, -3 mod 100 = 97, but we would have clicked once incorrectly 
         * from the above while loop */
        if (nDialPrev == 0 && rot == 'L')
        {
            --nSecondPart;
        }

        while (nDial >= 100)
        {
            nDial -= 100;
            /* Since, each time the dial does a loop, it would have clicked zero
             * once, so increment the password of second part */
            if (nDial != 0)
            {
                /* We do not need to increment in the case where it
                 * would have pointed to zero at the end.
                 * This is because we would have already accounted that in
                 * this loop 
                 * 
                 * For example:
                 * If say we are at 95 and it goes right by 5 reaching 100, or 0,
                 * then we would have clicked once. However, at the end, we are 
                 * clicking once again when the current needle is at 0. So, this
                 * would be double counting. Hence, we skip this increment once.
                 */
                ++nSecondPart;
            }
            /* Keep moving and incrementing the password until you get a value
             * within 0-99 */
        }

        if (nDial == 0)
        {
            /* Only if the final result is zero, increment the first part's 
             * and second part's password */
            ++nFirstPart;
            ++nSecondPart;
        }

        /* Load the previous dial position */
        nDialPrev = nDial;

        /* Increment count */
        ++cnt1;
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

