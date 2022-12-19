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

/* High value of X and Y, just to be on safer side */
char blocks[5000000];

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

    vector<int64_t> nSensors[2];
    vector<int64_t> nBeacons[2];

    /* Read every line */
    while (feof(fp) == 0)
    {
        int64_t sensX;
        int64_t sensY;

        int64_t beacX;
        int64_t beacY;

        /* Read formated intput from file */
        fscanf(fp, "Sensor at x=%ld, y=%ld: closest beacon is at x=%ld, y=%ld\n", &sensX, &sensY, &beacX, &beacY);

        /* Store the values of sensor's (X, Y) co-ordinate into
         * (nSensors[0], nSensors[1])
         * Store the values of corresponding beacon's (X, Y) co-ordinate into
         * (nBeacons[0], nBeacons[1]) */
        nSensors[0].push_back(sensX);
        nSensors[1].push_back(sensY);
        nBeacons[0].push_back(beacX);
        nBeacons[1].push_back(beacY);

        /* Calculate the total number of lines */
        ++cnt1;
    }

    vector<int64_t> nBeacPosAtYPos;
    int64_t nYPosGiv = 2000000;

    /* Store all beacons's x positions that have y co-ordinate nYPosGiv
     * into a hash map
    */
    unordered_map<int64_t, int64_t> uniqueXPosAtYPos;

    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        if (nBeacons[1][cnt2] == nYPosGiv)
        {
            uniqueXPosAtYPos[nBeacons[1][cnt2]] = 1;
        }
    }

    cnt5 = 0;

    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        /* Find the maximum distance, given by the man-distance between the
         * sensor and its closest beacon = |sens_x - beac_x| + |sens_y - beac_y|
         */
        int64_t nMaxDist = abs(nSensors[0][cnt2] - nBeacons[0][cnt2]) + abs(nSensors[1][cnt2] - nBeacons[1][cnt2]);

        cnt3 = 0;

        /* Get all x co-ordinate that has man-distance between (x_coo, nYPosGiv)
         * and sensor[cnt2] at most nMaxDist */

        /* Find the y-distance bewtween  */
        int64_t nYDistance = abs(nSensors[1][cnt2] - nYPosGiv);

        while (nMaxDist >= (cnt3 + nYDistance))
        {
            /* If the x co-ordinate is already not present in the hash map,
             * if not present increment add to the map and increment the cnt5
             * count */
            if (uniqueXPosAtYPos[nSensors[0][cnt2] - cnt3] != 1)
            {
                uniqueXPosAtYPos[nSensors[0][cnt2] - cnt3] = 1;
                ++cnt5;
            }
            if (uniqueXPosAtYPos[nSensors[0][cnt2] + cnt3] != 1)
            {
                uniqueXPosAtYPos[nSensors[0][cnt2] + cnt3] = 1;
                ++cnt5;
            }
            ++cnt3;
        }
    }

    cout << "Part (a): " << cnt5 << endl;

    /*--------------------- Part B ---------------------*/

    /* Current test Y coordinate */
    int64_t nYCord;

    /* Maximum coordinate value of X and Y */
    int64_t nMaxPos = 4000000;

    /* Array no beacon X position maximum in corresponding nYCord */
    vector<int64_t> noBeacXMax;
    /* Array no beacon X position minimum in corresponding nYCord */
    vector<int64_t> noBeacXMin;

    /* Current no beacon X position maximum */
    int64_t noCurrBeacXMax;
    /* Current no beacon X position minimum */
    int64_t noCurrBeacXMin;

    /* Iterate the value of Y (called test Y) from 0 to maximum */
    for (nYCord = 0; nYCord <= nMaxPos; nYCord++)
    {
        /* Remove elements in the min and max no beacon arrays */
        noBeacXMin.clear();
        noBeacXMax.clear();

        /* Iterate through all the inputs */
        for (cnt2 = 0; cnt2 < cnt1; cnt2++)
        {
            /* Find the maximum distance, given by the man-distance between the
             * sensor and its closest beacon = |sens_x - beac_x| + |sens_y - beac_y|
             */
            int64_t nMaxDist = abs(nSensors[0][cnt2] - nBeacons[0][cnt2]) + abs(nSensors[1][cnt2] - nBeacons[1][cnt2]);

            /* If the man-distance is at least the distance between the sensor's
             * y and current test Y coordinate */
            if (nMaxDist >= abs(nSensors[1][cnt2] - nYCord))
            {
                /* Calculate the room left (how much the x-coordinate in the
                 * test Y can move and yet the distance between the (X, test Y)
                 * and (sensor) does not exceed nMaxDist */
                int64_t nRoomLeft = nMaxDist - abs(nSensors[1][cnt2] - nYCord);

                /* Store this range into the min and max beacon X buffers */
                noBeacXMin.push_back(nSensors[0][cnt2] - nRoomLeft);
                noBeacXMax.push_back(nSensors[0][cnt2] + nRoomLeft);
            }
        }

        /* Ignore the values less than 0 and greater than nMaxPos.
         * Clip them to 0 and nMaxPos */
        for (cnt2 = 0; cnt2 < noBeacXMax.size(); cnt2++)
        {
            noBeacXMax[cnt2] = min(noBeacXMax[cnt2], nMaxPos);
            noBeacXMin[cnt2] = min(noBeacXMin[cnt2], nMaxPos);
            noBeacXMax[cnt2] = max(noBeacXMax[cnt2], (int64_t)0);
            noBeacXMin[cnt2] = max(noBeacXMin[cnt2], (int64_t)0);
        }

        /* Store the value of the last no beacon X maximum */
        noCurrBeacXMax = (noBeacXMax[noBeacXMax.size()-1]);
        /* Store the value of the last no beacon X minimum */
        noCurrBeacXMin = (noBeacXMin[noBeacXMax.size()-1]);

        /* Remove them from the array */
        noBeacXMax.pop_back();
        noBeacXMin.pop_back();

        /* To check if there is a gap between all the no beacon values */
        int64_t foundGap = 1;

        /* Iterate until the elements of X-max is present */
        while (noBeacXMax.size() > 0)
        {
            foundGap = 1;

            /* Iterator to get the starting of no beacon minimum */
            auto itMin = noBeacXMin.begin();
            /* Iterator to get the starting of no beacon maximum */
            /* Iterate all the elements of noBeacX */
            for (auto itMax = noBeacXMax.begin(); itMax != noBeacXMax.end(); ++itMax, ++itMin)
            {
                /* If you can stitch the gap between the current X max and the
                 * value present in the array, modify the current X and remove
                 * the value present in the array */

                /* If the currnet X max is greater than the array X min (x-min - 1)
                 * and the current X max is lesser than the array X max (x-max + 1)
                 * Number line : -
                 * --- ..., *itMin, ..., noCurrBeacXMax, ..., *itMax, ...
                 *
                 * If noCurrBeacXMax is in between *itMin and *itMax, then make
                 * noCurrBeacXMax equal to *itMax */
                if (noCurrBeacXMax >= (*itMin-1) && noCurrBeacXMax <= (*itMax+1))
                {
                    /* Unset found gap claiming there is no gap */
                    foundGap = 0;
                    /* Set noCurrBeacXMax to *itMax */
                    noCurrBeacXMax = *itMax;

                    /* If also the noCurrBeacXMin is in between *itMax and
                     * *itMin, then equate noCurrBeacXMin to *itMin
                     *
                     * Number line : -
                     * --- ..., *itMin, ..., noCurrBeacXMin, ..., *itMax, ...
                     */
                    if (noCurrBeacXMin <= (*itMax+1) && noCurrBeacXMin >= (*itMin-1))
                    {
                        /* Set noCurrBeacXMin to *itMin */
                        noCurrBeacXMin = *itMin;
                    }
                    /* Remove the value from the arrays as they were used in
                     * processing */
                    noBeacXMax.erase(itMax);
                    noBeacXMin.erase(itMin);
                    break;
                }
                /* If the currnet X min is greater than the array X min (x-min - 1)
                 * and the current X max is lesser than the array X max (x-max + 1)
                 * Number line : -
                 * --- ..., *itMin, ..., noCurrBeacXMin, ..., *itMax, ...
                 *
                 * If noCurrBeacXMin is in between *itMin and *itMax, then make
                 * noCurrBeacXMin equal to *itMin */
                else if (noCurrBeacXMin <= (*itMax+1) && noCurrBeacXMin >= (*itMin-1))
                {
                    /* Unset found gap claiming there is no gap */
                    foundGap = 0;

                    /* Set noCurrBeacXMin to *itMin */
                    noCurrBeacXMin = *itMin;

                    /* Remove the value from the arrays as they were used in
                     * processing */
                    noBeacXMax.erase(itMax);
                    noBeacXMin.erase(itMin);
                    break;
                }
                /* If the value of (*itMin, *itMax) is in between
                 * (noCurrBeacXMin, noCurrBeacXMax), then do not make changes
                 * to noCurrBeacXMax and noCurrBeacXMin, but remove the element
                 * from the array and reset foundGap
                 *
                 * Number line : -
                 * ..., noCurrBeacXMin, ... *itMin, ... *itMax, ... noCurrBeacXMax
                 */
                else if (noCurrBeacXMin <= *itMin && noCurrBeacXMax >= *itMax)
                {
                    foundGap = 0;
                    noBeacXMax.erase(itMax);
                    noBeacXMin.erase(itMin);
                    break;
                }
            }
            /* After all the values in the loop, if there are gaps in between,
             * break the loop */
            if (foundGap == 1)
            {
                break;
            }
        }

        /* If all values of noBeacXMax are not removed */
        if (noBeacXMax.size() > 0)
        {
            /* Set the value of blocks to zero */
            for (cnt2 = 0; cnt2 < nMaxPos; cnt2++)
            {
                blocks[cnt2] = 0;
            }
            /* Add the current value of noCurrBeacXMax and noCurrBeacXMin into
             * the array */
            noBeacXMax.push_back(noCurrBeacXMax);
            noBeacXMin.push_back(noCurrBeacXMin);

            /* Mark all the values of blocks from min to max from the noBeac
             * arrays to one */
            for (cnt2 = 0; cnt2 < noBeacXMax.size(); cnt2++)
            {
                /* Start from noBeacXMin and end at noBeacXMax */
                int64_t nStart = noBeacXMin[cnt2];
                int64_t nEnd = noBeacXMax[cnt2];
                /* If the max is less than zero or if the min is greater than
                 * nMaxPos, do not mark anything in blocks */
                if (noBeacXMax[cnt2] < 0 || noBeacXMin[cnt2] > nMaxPos)
                {
                    continue;
                }
                /* If the value of noBeacXMin is lesser than zero clip it to zero */
                if (noBeacXMin[cnt2] < 0)
                {
                    nStart = 0;
                }
                /* If the value of noBeacXMax is greater than nMaxPos clip it to nMax */
                if (noBeacXMax[cnt2] > nMaxPos)
                {
                    nEnd = nMaxPos;
                }

                /* Mark the values in blocks to 1 */
                for (cnt3 = nStart; cnt3 <= nEnd; cnt3++)
                {
                    blocks[cnt3] = 1;
                }
            }

            /* Check if a value in nMaxPos is not marked with 1 */
            for (cnt2 = 0; cnt2 < nMaxPos; cnt2++)
            {
                /* If found, compute the tuning frequency using
                 * 4000000 * X_cord + nYCord
                 * X_cord is the unmarked pos in nMaxPos */
                if (blocks[cnt2] == 0)
                {
                    /* Display part b */
                    cout << "Part (b): " << (cnt2 * 4000000 + nYCord) << endl;
                    break;
                }
            }
            /* Set loop count var to max loop count and break out of loop */
            nYCord = nMaxPos;
            break;
        }
    }

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}
