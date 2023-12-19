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
char arr2[10000][100000] = {0};

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
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t mavXYCord = 0;
    const int64_t nYCordMax = 10000000ll;

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    vector <string> heatLoss;

    int64_t nCurrIdX = 0;
    int64_t nCurrIdY = 0;
    int64_t nCurrId2X = 0;
    int64_t nCurrId2Y = 0;

    cnt8 = 10000000ll;
    cnt9 = 10000000ll;

    vector <int64_t> nPoints[2];
    vector <int64_t> nPoints2[2];

    /* NOTE: Sorry for the confusion, my Y is horizontal and X is vertical */

    /* Store the origin, (0, 0) in points vector, keep storing other vertices too */
    nPoints[0].push_back(nCurrIdX);
    nPoints[1].push_back(nCurrIdY);

    /* Same for part 2 */
    nPoints2[0].push_back(nCurrId2X);
    nPoints2[1].push_back(nCurrId2Y);


    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Extract words from line */
        stringstream iss(arr[cnt1]);
        string dir;
        string value;
        
        /* Get the direction */
        iss >> dir;
        /* Get the value */
        iss >> value;

        /* If right, increase the Y index by position */
        if (dir == "R")
        {
            cnt3 = atoll(value.c_str());
            nCurrIdY += cnt3;
        }
        /* If left, decrease the Y index by position  */
        else if (dir == "L")
        {
            cnt3 = atoll(value.c_str());
            nCurrIdY -= cnt3;
        }
        /* If down, decrease the X index by position  */
        else if (dir == "D")
        {
            cnt3 = atoll(value.c_str());
            nCurrIdX -= cnt3;
        }
        /* If up, increase the X index by position  */
        else if (dir == "U")
        {
            cnt3 = atoll(value.c_str());
            nCurrIdX += cnt3;
        }

        /* Add the points, (X, Y) into the points vector */
        nPoints[0].push_back(nCurrIdX);
        nPoints[1].push_back(nCurrIdY);

        /* For part 2, extract the colour information that contains value */
        iss >> value;
        /* Remove the first two characters of string, which is "(#" */
        value.erase(0, 2);
        /* Remove the last parenthesis as well */
        value.pop_back();

        /* Direction is the last character */
        dir = value[value.size()-1];
        /* Remove the direction character from value */
        value.pop_back();

        /* Convert the hex into decimal */
        cnt4 = strtol(value.c_str(), NULL, 16);

        /* If right, increase the Y index by position */
        if (dir == "0")
        {
            cnt3 = cnt4;
            nCurrId2Y += cnt3;
        }
        /* If left, decrease the Y index by position  */
        else if (dir == "2")
        {
            cnt3 = cnt4;
            nCurrId2Y -= cnt3;
        }
        /* If down, decrease the X index by position  */
        else if (dir == "1")
        {
            cnt3 = cnt4;
            nCurrId2X -= cnt3;
        }
        /* If up, increase the X index by position  */
        else if (dir == "3")
        {
            cnt3 = cnt4;
            nCurrId2X += cnt3;
        }

        /* Add the points, (X, Y) into the points vector */
        nPoints2[0].push_back(nCurrId2X);
        nPoints2[1].push_back(nCurrId2Y);

        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Set the initial count to 1 as we are off by 1 */
    nPartOneSum = 1;
    nPartTwoSum = 1;

    /* Store the first (X, Y) coordinate into current X and Y */
    nCurrIdX = nPoints[0][0];
    nCurrIdY = nPoints[1][0];
    /* Same fro part 2 */
    nCurrId2X = nPoints2[0][0];
    nCurrId2Y = nPoints2[1][0];

    /* Start from the second point and iterate through all points
     * The concept here is to add area under the curve for point going towards
     * right and remove area under the curve when points are moving towards left
     */
    for (cnt2 = 1; cnt2 < nPoints[0].size(); cnt2++)
    {
        /* If the X position (height) is same, then add if Y increases  */
        if (nCurrIdX == nPoints[0][cnt2])
        {
            /* If the Y point (horizontal point) increases */
            if (nPoints[1][cnt2] > nCurrIdY)
            {
                /* Add area = height * (Y2 - Y1) */
                nPartOneSum += (nPoints[1][cnt2] - nCurrIdY) * nCurrIdX;
            }
            else
            {
                /* If the point is reducing, subtract the area, but because 
                 * we also want the #'s to be also included, and not subtract
                 * them, the area is only (height - 1) * (Y2 - Y1) */
                nPartOneSum += (nPoints[1][cnt2] - nCurrIdY) * (nCurrIdX-1);
            }
        }
        /* If the Y position (vertical) is same, then add if X changes  */
        else if (nCurrIdY == nPoints[1][cnt2])
        {
            /* Add to the sum only the if the count is increasing, as we 
             * accommodated into area when X was reducing */
            if (nPoints[0][cnt2] < nCurrIdX)
            {
                nPartOneSum += abs(nCurrIdX - nPoints[0][cnt2]);
            }
        }
        else
        {
            /* If not true, flag error */
            cout << "Error" << endl;
        }
        nCurrIdX = nPoints[0][cnt2];
        nCurrIdY = nPoints[1][cnt2];

        /* Part 2: */

        /* If the X position (height) is same, then add if Y increases  */
        if (nCurrId2X == nPoints2[0][cnt2])
        {
            /* If the Y point (horizontal point) increases */
            if (nPoints2[1][cnt2] > nCurrId2Y)
            {
                /* Add area = height * (Y2 - Y1) */
                nPartTwoSum += (nPoints2[1][cnt2] - nCurrId2Y) * nCurrId2X;
            }
            else
            {
                /* If the point is reducing, subtract the area, but because 
                 * we also want the #'s to be also included, and not subtract
                 * them, the area is only (height - 1) * (Y2 - Y1) */
                nPartTwoSum += (nPoints2[1][cnt2] - nCurrId2Y) * (nCurrId2X-1);
            }
        }
        /* If the Y position (vertical) is same, then add if X changes  */
        else if (nCurrId2Y == nPoints2[1][cnt2])
        {
            /* Add to the sum only the if the count is increasing, as we 
             * accommodated into area when X was reducing */
            if (nPoints2[0][cnt2] < nCurrId2X)
            {
                nPartTwoSum += abs(nCurrId2X - nPoints2[0][cnt2]);
            }
        }
        else
        {
            /* If not true, flag error */
            cout << "Error" << endl;
        }
        nCurrId2X = nPoints2[0][cnt2];
        nCurrId2Y = nPoints2[1][cnt2];
    }

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

