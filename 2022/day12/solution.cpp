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

char input_file[] = "input.txt";
char arr[10000][1000];
static int64_t arrvals[10000][10000] = {0};

int64_t nMaxX;
int64_t nMaxY;

void computeSpiral(int64_t nCurrPosX, int64_t nCurrPosY, int64_t nPrevCost);
void resetArrVals(void);

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen(input_file, "r");

    if (fp == NULL)
    {
        cout << "Error. Unable to open file, \"" << input_file << "\"" << endl;
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

    int64_t nGlobalMin = 10000000;
    int64_t nEIdxX;
    int64_t nEIdxY;

    int64_t nPartAAns;

    /* Read every line */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        /* Calculate the total number of lines */
        ++cnt1;
    }

    /* Get the width of the first line (width is the same for all lines) */
    cnt2 = strlen(arr[0])-1;

    /* Store rows and columns into maxX and maxY */
    nMaxX = cnt1;
    nMaxY = cnt2;

    /* Find the index (x, y) of 'E' */
    for (cnt3 = 0; cnt3 < cnt1; cnt3++)
    {
        for (cnt4 = 0; cnt4 < cnt2; cnt4++)
        {
            if (arr[cnt3][cnt4] == 'E')
            {
                break;
            }
        }
        if (cnt4 != cnt2)
        {
            break;
        }
    }
    /* Store E's index into (EIdxX, EIDxY) */
    nEIdxX = cnt3;
    nEIdxY = cnt4;

    /* Loop through all the values in matrix */
    for (cnt3 = 0; cnt3 < cnt1; cnt3++)
    {
        for (cnt4 = 0; cnt4 < cnt2; cnt4++)
        {
            /* If the value is 'S', or 'a', then call the "spiral" function */
            if (arr[cnt3][cnt4] == 'S' || arr[cnt3][cnt4] == 'a')
            {
                /* Count to check the number of times the loop has run */
                ++cnt7;
                /* Reset the value of arrayVals, arrayVals have very large values initally */
                resetArrVals();
                /* Call the spiral function to get the lowest sum value  */
                computeSpiral(cnt3, cnt4, 0);
                /* Check if the current minimum is lower than the global minimum */
                if (arrvals[nEIdxX][nEIdxY] < nGlobalMin)
                {
                    /* If yes, make this as the new global minimum */
                    nGlobalMin = arrvals[nEIdxX][nEIdxY];
                }
                /* For part 1, compute the value starting at 'S' and display it */
                if (arr[cnt3][cnt4] == 'S')
                {
                    cout << "Part (a): " << arrvals[nEIdxX][nEIdxY] << endl;
                }
            }
        }
    }
    /* Display global minimum for part b */
    cout << "Part (b): " << nGlobalMin << endl;
    /* Display the total number of times the spiral function was called */
    cout << "Info: Ran a total of " << cnt7 << " times." << endl;

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

/* Reset the array values to large costs */
void resetArrVals(void)
{
    int64_t cnt1 = nMaxX;
    int64_t cnt2 = nMaxY;

    for (cnt1 = 0; cnt1 < nMaxX; cnt1++)
    {
        for (cnt2 = 0; cnt2 < nMaxY; cnt2++)
        {
            arrvals[cnt1][cnt2] = 10000000;
        }
    }
}

void computeSpiral(int64_t nCurrPosX, int64_t nCurrPosY, int64_t nPrevCost)
{
    int64_t cnt1 = nCurrPosX;
    int64_t cnt2 = nCurrPosY;

    char nCurrElev = 'a';
    /* If the current value is 'S' assume it to be 'a' */
    if (arr[cnt1][cnt2] != 'S')
    {
        nCurrElev = arr[cnt1][cnt2];
    }
    /* If the current value is an 'E', assume it to be 'z' */
    else if (arr[cnt1][cnt2] == 'E')
    {
        nCurrElev = 'z';
    }

    /* If the current x position is greater than 0, call the same function
     * with lower value of x co-ordinate */
    if (cnt1 > 0)
    {
        /* If the next value is 'E', do no call the function again */
        if (arr[cnt1-1][cnt2] == 'E')
        {
            /* Compute the lowest sum for 'E' */
            if ((int64_t('z') - int64_t(nCurrElev)) < 2)
            {
                if (arrvals[cnt1-1][cnt2] > nPrevCost+1)
                {
                    arrvals[cnt1-1][cnt2] = nPrevCost+1;
                }
            }
        }
        /* If the current idx's value and next idx's value is not more than 1 */
        else if ((int64_t(arr[cnt1-1][cnt2]) - int64_t(nCurrElev)) < 2)
        {
            /* Check if the cost can be lower, if yes, then call the spiral function again */
            if (arrvals[cnt1-1][cnt2] > nPrevCost+1)
            {
                arrvals[cnt1-1][cnt2] = nPrevCost+1;
                computeSpiral(cnt1-1, cnt2, nPrevCost+1);
            }
        }
    }
    /* If the current x position is lesser than maxX-1, call the same function
     * with higher value of x co-ordinate */
    if (cnt1 < nMaxX-1)
    {
        if (arr[cnt1+1][cnt2] == 'E')
        {
            /* Compute the lowest sum for 'E' */
            if ((int64_t('z') - int64_t(nCurrElev)) < 2)
            {
                if (arrvals[cnt1+1][cnt2] > nPrevCost+1)
                {
                    arrvals[cnt1+1][cnt2] = nPrevCost+1;
                }
            }
        }
        /* If the current idx's value and next idx's value is not more than 1 */
        else if ((int64_t(arr[cnt1+1][cnt2]) - int64_t(nCurrElev)) < 2)
        {
            /* Check if the cost can be lower, if yes, then call the spiral function again */
            if (arrvals[cnt1+1][cnt2] > nPrevCost+1)
            {
                arrvals[cnt1+1][cnt2] = nPrevCost+1;
                computeSpiral(cnt1+1, cnt2, nPrevCost+1);
            }
        }
    }
    /* If the current y position is greater than 0, call the same function
     * with lower value of y co-ordinate */
    if (cnt2 > 0)
    {
        if (arr[cnt1][cnt2-1] == 'E')
        {
            /* Compute the lowest sum for 'E' */
            if ((int64_t('z') - int64_t(nCurrElev)) < 2)
            {
                if (arrvals[cnt1][cnt2-1] > nPrevCost+1)
                {
                    arrvals[cnt1][cnt2-1] = nPrevCost+1;
                }
            }
        }
        /* If the current idx's value and next idx's value is not more than 1 */
        else if ((int64_t(arr[cnt1][cnt2-1]) - int64_t(nCurrElev)) < 2)
        {
            /* Check if the cost can be lower, if yes, then call the spiral function again */
            if (arrvals[cnt1][cnt2-1] > nPrevCost+1)
            {
                arrvals[cnt1][cnt2-1] = nPrevCost+1;
                computeSpiral(cnt1, cnt2-1, nPrevCost+1);
            }
        }
    }
    /* If the current y position is lower than max-Y, call the same function
     * with higher value of y co-ordinate */
    if (cnt2 < nMaxY-1)
    {
        if (arr[cnt1][cnt2+1] == 'E')
        {
            /* Compute the lowest sum for 'E' */
            if ((int64_t('z') - int64_t(nCurrElev)) < 2)
            {
                if (arrvals[cnt1][cnt2+1] > nPrevCost+1)
                {
                    arrvals[cnt1][cnt2+1] = nPrevCost+1;
                }
            }
        }
        /* If the current idx's value and next idx's value is not more than 1 */
        else if ((int64_t(arr[cnt1][cnt2+1]) - int64_t(nCurrElev)) < 2)
        {
            /* Check if the cost can be lower, if yes, then call the spiral function again */
            if (arrvals[cnt1][cnt2+1] > nPrevCost+1)
            {
                arrvals[cnt1][cnt2+1] = nPrevCost+1;
                computeSpiral(cnt1, cnt2+1, nPrevCost+1);
            }
        }
    }
}
