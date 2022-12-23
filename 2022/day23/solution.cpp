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
char arr[10000][20000];

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

    int64_t nMinValueRow;
    int64_t nMaxValueRow;
    int64_t nMinValueCol;
    int64_t nMaxValueCol;

    /* Coordinates of "#" into field */
    vector<int64_t> field[2];
    /* Coordinates of all possible movements into (field2[0], field2[1])
     * Store the corresponding value of original (X, Y) into (field2[2], field2[3])
     */
    vector<int64_t> field2[4];
    /* Store the not moved values of (X, Y) into (field3[0], field3[1]) */
    vector<int64_t> field3[2];

    /* Read every line */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        /* Get the length of the string */
        cnt2 = strlen(arr[cnt1]);
        /* Check for "#"s, if found, place it in the co-ordinates, (X,Y) in
         * (field[0], field[1]) arrays */
        for (cnt3 = 0; cnt3 < cnt2; cnt3++)
        {
            if (arr[cnt1][cnt3] == '#')
            {
                field[0].push_back(cnt3);
                field[1].push_back(cnt1);
            }
        }
        /* Increment the count */
        ++cnt1;
    }
    /* Ignore the last "\n" character */
    cnt2--;

    /* Run a loop with cnt4 as a loop variable */
    for (cnt4 = 0; ; cnt4++)
    {
        /* Start field2 and field3 afresh */
        field2[0].clear();
        field2[1].clear();
        field2[2].clear();
        field2[3].clear();
        field3[0].clear();
        field3[1].clear();

        /* Loop through all the values in (field[0], field[1]) */
        for (cnt5 = 0; cnt5 < field[0].size(); cnt5++)
        {
            /* Store the value of X and Y into seperate variables for ease */
            int64_t x_value = field[0][cnt5];
            int64_t y_value = field[1][cnt5];
            /* Store the co-ordinates of all the eight neighbouring #'s of a
             * given "#" */
            vector<int64_t> nEightNeigh[2];
            /* Check if a # is cnt5 hash's neighbour */
            for (cnt6 = 0; cnt6 < field[0].size(); cnt6++)
            {
                /* Ignore the self */
                if (cnt6 == cnt5)
                {
                    continue;
                }
                /* Store the test value of (X, Y) into a new variable. Again this
                 * is for ease */
                int64_t x_newvalue = field[0][cnt6];
                int64_t y_newvalue = field[1][cnt6];

                /* Check if this is a neighbour by comparing the difference
                 * between x and y co-ordinates */
                if (abs(x_newvalue-x_value) < 2 && abs(y_newvalue-y_value) < 2)
                {
                    nEightNeigh[0].push_back(x_newvalue);
                    nEightNeigh[1].push_back(y_newvalue);
                }
            }
            /* If there is at least one neighbour */
            if (nEightNeigh[0].size() > 0)
            {
                /* Start the count with zero */
                cnt6 = 0;
                /* Check all 4 directions */
                while (cnt6 < 4)
                {
                    /* Loop through the check, first north, then south, then
                     * west and then east */
                    if ((cnt4 + cnt6) % 4 == 0)
                    {
                        /* If north */
                        for (cnt7 = 0; cnt7 < nEightNeigh[0].size(); cnt7++)
                        {
                            /* You must not have any neighbour that has a value
                             * of y lower than the current position of #
                             * by 1 */
                            if (nEightNeigh[1][cnt7] == y_value-1)
                            {
                                break;
                            }
                        }
                        /* If there are not any, store the "north"ed position
                         * and its original position */
                        if (cnt7 == nEightNeigh[0].size())
                        {
                            field2[0].push_back(x_value);
                            field2[1].push_back((y_value-1));
                            field2[2].push_back(x_value);
                            field2[3].push_back(y_value);
                            break;
                        }
                        /* Else, increase the count to check for other directions */
                        cnt6++;
                    }
                    else if ((cnt4 + cnt6) % 4 == 1)
                    {
                        /* If south */
                        for (cnt7 = 0; cnt7 < nEightNeigh[0].size(); cnt7++)
                        {
                            /* You must not have any neighbour that has a value
                             * of y greater than the current position of #
                             * by 1 */
                            if (nEightNeigh[1][cnt7] == y_value+1)
                            {
                                break;
                            }
                        }
                        /* If there are not any, store the "north"ed position
                         * and its original position */
                        if (cnt7 == nEightNeigh[0].size())
                        {
                            field2[0].push_back(x_value);
                            field2[1].push_back((y_value+1));
                            field2[2].push_back(x_value);
                            field2[3].push_back((y_value));
                            break;
                        }
                        /* Else, increase the count to check for other directions */
                        cnt6++;
                    }
                    else if ((cnt4 + cnt6) % 4 == 2)
                    {
                        /* If west */
                        for (cnt7 = 0; cnt7 < nEightNeigh[0].size(); cnt7++)
                        {
                            /* You must not have any neighbour that has a value
                             * of x lower than the current position of #
                             * by 1 */
                            if (nEightNeigh[0][cnt7] == x_value-1)
                            {
                                break;
                            }
                        }
                        /* If there are not any, store the "north"ed position
                         * and its original position */
                        if (cnt7 == nEightNeigh[0].size())
                        {
                            field2[0].push_back((x_value - 1));
                            field2[1].push_back(y_value);
                            field2[2].push_back(x_value);
                            field2[3].push_back(y_value);
                            break;
                        }
                        /* Else, increase the count to check for other directions */
                        cnt6++;
                    }
                    else if ((cnt4 + cnt6) % 4 == 3)
                    {
                        /* If east */
                        for (cnt7 = 0; cnt7 < nEightNeigh[0].size(); cnt7++)
                        {
                            /* You must not have any neighbour that has a value
                             * of x higher than the current position of #
                             * by 1 */
                            if (nEightNeigh[0][cnt7] == x_value+1)
                            {
                                break;
                            }
                        }
                        /* If there are not any, store the "north"ed position
                         * and its original position */
                        if (cnt7 == nEightNeigh[0].size())
                        {
                            field2[0].push_back((x_value + 1));
                            field2[1].push_back(y_value);
                            field2[2].push_back(x_value);
                            field2[3].push_back(y_value);
                            break;
                        }
                        /* Else, increase the count to check for other directions */
                        cnt6++;
                    }
                }
                /* If checked all directions and still could not get to move
                 * anywhere, store the original # pos into field3 */
                if (cnt6 == 4)
                {
                    field3[0].push_back(field[0][cnt5]);
                    field3[1].push_back(field[1][cnt5]);
                }
            }
            /* If could not find any neighbour, store the original # pos into
             * field3 */
            else
            {
                field3[0].push_back(field[0][cnt5]);
                field3[1].push_back(field[1][cnt5]);
            }
        }
        /* If all elements of field are in field3, we are done, the values cannot
         * move anywhere */
        if (field[0].size() == field3[0].size())
        {
            /* Break out of the loop and display the count */
            break;
        }
        /* To analyse, remove the all coordinates in field */
        field[0].clear();
        field[1].clear();
        /* Loop through all values in field2 */
        for (cnt5 = 0; cnt5 < field2[0].size(); cnt5++)
        {
            /* Check if two Elves have called the same position by checking if
             * there is a repitition in the field2 array */
            for (cnt6 = 0; cnt6 < field2[0].size(); cnt6++)
            {
                /* Do not check for itself */
                if (cnt6 == cnt5)
                {
                    continue;
                }
                /* If the value is the same, quit from the loop */
                if (field2[0][cnt5] == field2[0][cnt6] && field2[1][cnt5] == field2[1][cnt6])
                {
                    break;
                }
            }
            /* If there is no repitition, add the fresh value into field */
            if (cnt6 == field2[0].size())
            {
                field[0].push_back(field2[0][cnt5]);
                field[1].push_back(field2[1][cnt5]);
            }
            /* Else, add the original value into field */
            else
            {
                field[0].push_back(field2[2][cnt5]);
                field[1].push_back(field2[3][cnt5]);
            }
        }
        /* Add the remaining values that did not get a chance to move */
        for (cnt5 = 0; cnt5 < field3[0].size(); cnt5++)
        {
            field[0].push_back(field3[0][cnt5]);
            field[1].push_back(field3[1][cnt5]);
        }

        /* If the count has reached 9, (counted from 0), compute the size of
         * rectange */
        if (cnt4 == 9)
        {
            /* Start with min/max row number and column by the first value */
            nMinValueRow = field[0][0];
            nMaxValueRow = field[0][0];
            nMinValueCol = field[1][0];
            nMaxValueCol = field[1][0];

            /* Compute the min/max values of rows and columns */
            for (cnt5 = 1; cnt5 < field[0].size(); cnt5++)
            {
                int64_t nXVal = field[0][cnt5];
                int64_t nYVal = field[1][cnt5];

                if (nMinValueCol > nXVal)
                {
                    nMinValueCol = nXVal;
                }
                if (nMaxValueCol < nXVal)
                {
                    nMaxValueCol = nXVal;
                }
                if (nMinValueRow > nYVal)
                {
                    nMinValueRow = nYVal;
                }
                if (nMaxValueRow < nYVal)
                {
                    nMaxValueRow = nYVal;
                }
            }

            /* Display the number dots by computing the area of rectange and
             * subtracting the number of #'s */
            cout << "Part (a): " << (nMaxValueRow - nMinValueRow + 1) * (nMaxValueCol - nMinValueCol + 1) - field[0].size() << endl;

        }
    }

    /* Display the value of the current index */
    cout << "Part (b): " << cnt4+1 << endl;

    fseek(fp, 0L, SEEK_SET);

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

