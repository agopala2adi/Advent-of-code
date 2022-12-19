#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

#include <inttypes.h>

using namespace std;

char arr[10000][1000];

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        cout << "Error. Unable to open file, \"input.txt\"" << endl;
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
    // unordered_map<int64_t, int64_t> uniqueSet;

    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int64_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    uint64_t max_val = 0;
    uint64_t min_val = 10000000ull;

    vector<int64_t> nElfVec;

    int64_t cycles = 0;
    int64_t X_reg = 1;
    int64_t nTotal = 0;

    /* Cycle char is the final charaters in CRT */
    char cycleChar[40*6];
    for (cnt2 = 0; cnt2 < 40*6; cnt2++)
    {
        cycleChar[cnt2] = '.';
    }

    /* Sprite position */
    char spritePos[40];
    for (cnt2 = 0; cnt2 < 40; cnt2++)
    {
        spritePos[cnt2] = '.';
    }
    spritePos[0] = '#';
    spritePos[1] = '#';
    spritePos[2] = '#';

    /* Read current line from file */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        char addx[10];
        int64_t ncrrVal = 0;

        /* If the current line is a noop, increment cycles and check for values
         * of 20, 60, 100, 140, 180 and 220. */
        if (arr[cnt1][0] == 'n')
        {
            ++cycles;
            if (cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180 || cycles == 220)
            {
                nTotal += X_reg * cycles;
            }
        }
        else
        {
            /* Get the value for the current increment in X register */
            sscanf(arr[cnt1], "%s %" PRId64 "\n", &addx[0], &ncrrVal);
            ++cycles;
            /* Increment cycles and check for values of 20, 60, 100, 140, 180
             * and 220. */
            if (cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180 || cycles == 220)
            {
                nTotal += X_reg * cycles;
            }
            ++cycles;
            /* Increment cycles and check for values of 20, 60, 100, 140, 180
             * and 220. */
            if (cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180 || cycles == 220)
            {
                nTotal += X_reg * cycles;
            }
            /* Add the value into X register */
            X_reg += ncrrVal;
        }

        cnt1++;
    }

    cout << "Part (a): " << nTotal << endl << endl;

    /* Reset cycles and X_reg values */
    cycles = 0;
    X_reg = 1;

    /* Re loop through the entire loop once more */
    for (cnt4 = 0; cnt4 < cnt1; cnt4++)
    {
        char addx[10];
        int64_t ncrrVal;
        /* If the current instruction is a noop, then check if the current cycle
         * count of sprite position is # */
        if (arr[cnt4][0] == 'n')
        {
            if (spritePos[cycles % 40] == '#')
            {
                cycleChar[cycles] = '#';
            }
            else
            {
                cycleChar[cycles] = '.';
            }
            /* Increment the cycles */
            ++cycles;
        }
        else
        {
            /* Read the value of increment count */
            sscanf(arr[cnt4], "%s %" PRId64 "\n", &addx[0], &ncrrVal);
            /* Check if the current cycle count of sprite position is # */
            if (spritePos[cycles % 40] == '#')
            {
                cycleChar[cycles] = '#';
            }
            else
            {
                cycleChar[cycles] = '.';
            }
            /* Increment the cycles and again check */
            ++cycles;
            if (spritePos[cycles % 40] == '#')
            {
                cycleChar[cycles] = '#';
            }
            else
            {
                cycleChar[cycles] = '.';
            }
            ++cycles;
            X_reg += ncrrVal;
            /* Reset the value in sprite position with the new X register value */
            for (cnt2 = 0; cnt2 < 40; cnt2++)
            {
                spritePos[cnt2] = '.';
            }
            spritePos[X_reg-1] = '#';
            spritePos[X_reg] = '#';
            spritePos[X_reg+1] = '#';
        }
    }

    /* Display part b solution */
    cout << "Part (b): " << endl;
    for (cnt3 = 0; cnt3 < 6; cnt3++)
    {
        for (cnt2 = 0; cnt2 < 40; cnt2++)
        {
            cout << cycleChar[cnt3*40 + cnt2];
        }
        cout << endl;
    }

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

