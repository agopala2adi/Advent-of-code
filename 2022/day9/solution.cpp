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

/* Maximum value of Y co-ordinate for hash map */
const int64_t nMaxValY = 10000000ll;

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        cout << "Unable to open file: input.txt" << endl;
        auto endTime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSecs = endTime-startTime;
        std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
        cout << "\nEnd time: " << std::ctime(&end_time);
        cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";
        return -1;
    }

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

    // Unordered map - hash map :
    // unordered_map<int64_t, int64_t> uniqueSet1;


    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int64_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    uint64_t max_val = 0;
    uint64_t min_val = 10000000ull;

    vector<int64_t> nElfVec;

    int64_t x_hpos = 0;
    int64_t y_hpos = 0;

    int64_t x_tpos[9] = {0};
    int64_t y_tpos[9] = {0};

    unordered_map<int64_t, int64_t> uniqueSet1;
    unordered_map<int64_t, int64_t> uniqueSet9;

    uniqueSet1[0] = 1;
    uniqueSet9[0] = 1;

    for (cnt1 = 0; cnt1 < 9; cnt1++)
    {
        x_tpos[cnt1] = 0;
        y_tpos[cnt1] = 0;
    }
    cnt1 = 0;
    cnt10 = 1;
    cnt9 = 1;

    while (feof(fp) == 0)
    {
        char dir;
        int pos;

        /* Read direction and position to be moved in that direction */
        fscanf(fp, "%c %d\n", &dir, &pos);

        /* Loop through the values of position */
        for (cnt1 = 0; cnt1 < pos; cnt1++)
        {
            /* Increment the current Head (h_pos) based on the direction once */
            if (dir == 'R')
            {
                x_hpos++;
            }
            else if (dir == 'U')
            {
                y_hpos++;
            }
            else if (dir == 'L')
            {
                x_hpos--;
            }
            else if (dir == 'D')
            {
                y_hpos--;
            }

            /* Use the previous position for future use */
            int64_t xPrevhpos = x_hpos;
            int64_t yPrevhpos = y_hpos;

            /* Loop through 9 times for all the chains */
            for (cnt2 = 0; cnt2 < 9; cnt2++)
            {
                /* If the current tail's position is at most 1 more than the
                 * previous head's position, do not continue, break out of the loop*/
                if (abs(xPrevhpos - x_tpos[cnt2]) <= 1 && abs(yPrevhpos - y_tpos[cnt2]) <= 1)
                {
                    break;
                }
                /* If the current tail is less than previous head's position,
                 * increment the current tail - x direction */
                if (xPrevhpos > x_tpos[cnt2])
                {
                    x_tpos[cnt2]++;
                }
                /* If the current tail is more than previous head's position,
                 * decrement the current tail - x direction */
                else if (xPrevhpos < x_tpos[cnt2])
                {
                    x_tpos[cnt2]--;
                }
                /* If the current tail is less than previous head's position,
                 * increment the current tail - y direction */
                if (yPrevhpos > y_tpos[cnt2])
                {
                    y_tpos[cnt2]++;
                }
                /* If the current tail is more than previous head's position,
                 * decrement the current tail - y direction */
                else if (yPrevhpos < y_tpos[cnt2])
                {
                    y_tpos[cnt2]--;
                }

                /* Store the previous count for the next iteration */
                xPrevhpos = x_tpos[cnt2];
                yPrevhpos = y_tpos[cnt2];
            }

            /* Check if the co-ordinate (x, y) is already present in the map
             * If no, add count for 9th tail.
            */
            if (uniqueSet9[nMaxValY*x_tpos[8] + y_tpos[8]] != 1)
            {
                uniqueSet9[nMaxValY*x_tpos[8] + y_tpos[8]] = 1;
                ++cnt9;
            }
            /* Check if the co-ordinate (x, y) is already present in the map
             * If no, add count for 1st tail.
            */
            if (uniqueSet1[nMaxValY*x_tpos[0] + y_tpos[0]] != 1)
            {
                uniqueSet1[nMaxValY*x_tpos[0] + y_tpos[0]] = 1;
                ++cnt10;
            }
        }
    }

    /* Print the size of 1st and 9th tails */
    cout << "Part (a): " << cnt10 << endl;
    cout << "Part (b): " << cnt9 << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

