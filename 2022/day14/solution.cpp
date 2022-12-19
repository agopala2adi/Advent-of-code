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
static char blocks[100000][100000];

int64_t checkLeftRight(string, string);

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

    int64_t nHighestX = 0;
    int64_t nHighestY = 0;
    int64_t nLowestX = 10000000000;
    int64_t nLowestY = 10000000000;

    /* Read every line */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        stringstream iss(arr[cnt1]);
        string word;

        int64_t nIdx1;
        int64_t nIdx2;

        /* Find the highest x coordinate and y coordinate */

        while (iss >> word)
        {
            if (word != "->")
            {
                sscanf(word.c_str(), "%ld,%ld", &nIdx1, &nIdx2);
            }
            if (nHighestX < nIdx1)
            {
                nHighestX = nIdx1;
            }
            if (nLowestX > nIdx1)
            {
                nLowestX = nIdx1;
            }
            if (nHighestY < nIdx2)
            {
                nHighestY = nIdx2;
            }
            if (nLowestY > nIdx2)
            {
                nLowestY = nIdx2;
            }
        }

        /* Calculate the total number of lines */
        ++cnt1;
    }

    /* Let the starting value of X go lower than lowest by 1000 */
    int64_t nStartIdX = nLowestX - 1000;
    /* Let the starting value of Y be 0 as it does not matter */
    int64_t nStartIdY = 0;

    /* Should place blocks at Y+2 (part b) */
    int64_t nMaxY = nHighestY + 2;

    /* Start with cnt2 = 0 and run loop till cnt1*/
    cnt2 = 0;

    while (cnt2 < cnt1)
    {
        /* Split each line into words */
        stringstream iss(arr[cnt2]);
        string word;

        int64_t nIdx1;
        int64_t nIdx2;

        /* Start with a bogus previous value (x, y) to avoid checking the first time */
        int64_t nIdxPrev1 = -1;
        int64_t nIdxPrev2 = -1;

        while (iss >> word)
        {
            if (word != "->")
            {
                /* Store the (x, y) indices into (nIdx1, nIdx2) */
                sscanf(word.c_str(), "%ld,%ld", &nIdx1, &nIdx2);
            }
            else
            {
                /* If seeing "->", read the next indices */
                continue;
            }
            /* Subract the value of nStartIdx to get the current X-array index*/
            nIdx1 -= nStartIdX;

            /* If at least one previous value exist */
            if (nIdxPrev1 != -1)
            {
                /* Compare if the previous X value is same as current X value */
                if (nIdx1 == nIdxPrev1)
                {
                    /* If same assign #'s to the blocks in Y direction */
                    if (nIdx2 > nIdxPrev2)
                    {
                        for (cnt3 = nIdxPrev2; cnt3 <= nIdx2; cnt3++)
                        {
                            blocks[cnt3][nIdx1] = '#';
                        }
                    }
                    else if (nIdx2 < nIdxPrev2)
                    {
                        for (cnt3 = nIdxPrev2; cnt3 >= nIdx2; cnt3--)
                        {
                            blocks[cnt3][nIdx1] = '#';
                        }
                    }
                }
                /* Else compare if the previous Y value is same as current Y value */
                else if (nIdx2 == nIdxPrev2)
                {
                    /* If same assign #'s to the blocks in X direction */
                    if (nIdx1 > nIdxPrev1)
                    {
                        for (cnt3 = nIdxPrev1; cnt3 <= nIdx1; cnt3++)
                        {
                            blocks[nIdx2][cnt3] = '#';
                        }
                    }
                    else if (nIdx1 < nIdxPrev1)
                    {
                        for (cnt3 = nIdxPrev1; cnt3 >= nIdx1; cnt3--)
                        {
                            blocks[nIdx2][cnt3] = '#';
                        }
                    }
                }
            }

            /* Equate current value into previous for next comparision */
            nIdxPrev1 = nIdx1;
            nIdxPrev2 = nIdx2;
        }

        /* Calculate the total number of lines */
        ++cnt2;
    }

    /* Start with cnt4 as zero. cnt4 gives the number of times the o was thrown */
    cnt4 = 0;

    while (1)
    {
        int64_t nBallX = 500 - nStartIdX;
        int64_t nBallY = 0;

        /* If the current block is itself a 'o', then break the loop as it is done */

        if (blocks[nBallY][nBallX] == 'o')
        {
            break;
        }

        /* Run the loop for a large 1000 values */
        for (cnt3 = 0; cnt3 < 1000; cnt3++)
        {
            /* If the ball can move in the Y direction, keep moving */
            if (blocks[nBallY+1][nBallX] != 'o' && blocks[nBallY+1][nBallX] != '#')
            {
                nBallY++;
            }
            /* If the ball cannot move in the Y direction, but can move in diagnal
             * X-1 direction, keep moving */
            else if (blocks[nBallY+1][nBallX-1] != 'o' && blocks[nBallY+1][nBallX-1] != '#')
            {
                nBallY++;
                nBallX--;
            }
            /* If the ball cannot move both in the Y direction and diagnal
             * X-1 direction, but can move in diagnal X+1 direction, keep moving */
            else if (blocks[nBallY+1][nBallX+1] != 'o' && blocks[nBallY+1][nBallX+1] != '#')
            {
                nBallY++;
                nBallX++;
            }
            /* If the ball cannot move at all, break the loop */
            else
            {
                break;
            }
        }

        /* For free fall ball: if the loop does not terminate even after 1000
         * rounds, break from loop */
        if (cnt3 != 1000)
        {
            /* If terminated before 1000 rounds, assign the current Y and X positon
             * as a 'o' */
            blocks[nBallY][nBallX] = 'o';

            /* Update the value of lowest(X,Y) and highesst(X,Y) to set it as
             * zeros for the next part */
            if (nBallY < nLowestY)
            {
                nLowestY = nBallY;
            }
            if (nBallY > nHighestY)
            {
                nHighestY = nBallY;
            }
            if (nBallX < nLowestX)
            {
                nLowestX = nBallX;
            }
            if (nBallX > nHighestX)
            {
                nHighestX = nBallX;
            }
        }
        else
        {
            break;
        }
        /* increment the count of the unit */
        cnt4++;
    }

    /* Display part a */
    cout << "Part (a): " << cnt4 << endl;

    /*------------- Part B ------------- */

    /* Set the blocks as zeros between highest(X,Y) and lowest(X,Y)*/
    for (cnt2 = nLowestY; cnt2 < nHighestY; cnt2++)
    {
        for (cnt3 = nLowestX-nStartIdX; cnt3 < nHighestX-nStartIdX; cnt3++)
        {
            blocks[cnt2][cnt3] = 0;
        }
    }

    /* Set the base block after maximum of two blocks as "#"'s */
    for (cnt2 = 0; cnt2 < 10000; cnt2++)
    {
        blocks[nMaxY][cnt2] = '#';
    }

    /* Reset cnt2 and run a loop till reaching cnt1 */
    cnt2 = 0;

    while (cnt2 < cnt1)
    {
        /* Split each line into words */
        stringstream iss(arr[cnt2]);
        string word;

        int64_t nIdx1;
        int64_t nIdx2;

        /* Start with a bogus previous value (x, y) to avoid checking the first time */
        int64_t nIdxPrev1 = -1;
        int64_t nIdxPrev2 = -1;

        while (iss >> word)
        {
            if (word != "->")
            {
                /* Store the (x, y) indices into (nIdx1, nIdx2) */
                sscanf(word.c_str(), "%ld,%ld", &nIdx1, &nIdx2);
            }
            else
            {
                /* If seeing "->", read the next indices */
                continue;
            }
            /* Subract the value of nStartIdx to get the current X-array index*/
            nIdx1 -= nStartIdX;

            /* If at least one previous value exist */
            if (nIdxPrev1 != -1)
            {
                /* Compare if the previous X value is same as current X value */
                if (nIdx1 == nIdxPrev1)
                {
                    /* If same assign #'s to the blocks in Y direction */
                    if (nIdx2 > nIdxPrev2)
                    {
                        for (cnt3 = nIdxPrev2; cnt3 <= nIdx2; cnt3++)
                        {
                            blocks[cnt3][nIdx1] = '#';
                        }
                    }
                    else if (nIdx2 < nIdxPrev2)
                    {
                        for (cnt3 = nIdxPrev2; cnt3 >= nIdx2; cnt3--)
                        {
                            blocks[cnt3][nIdx1] = '#';
                        }
                    }
                }
                /* Else compare if the previous Y value is same as current Y value */
                else if (nIdx2 == nIdxPrev2)
                {
                    /* If same assign #'s to the blocks in X direction */
                    if (nIdx1 > nIdxPrev1)
                    {
                        for (cnt3 = nIdxPrev1; cnt3 <= nIdx1; cnt3++)
                        {
                            blocks[nIdx2][cnt3] = '#';
                        }
                    }
                    else if (nIdx1 < nIdxPrev1)
                    {
                        for (cnt3 = nIdxPrev1; cnt3 >= nIdx1; cnt3--)
                        {
                            blocks[nIdx2][cnt3] = '#';
                        }
                    }
                }
            }

            /* Equate current value into previous for next comparision */
            nIdxPrev1 = nIdx1;
            nIdxPrev2 = nIdx2;
        }

        /* Calculate the total number of lines */
        ++cnt2;
    }

    /* Start with cnt4 as zero. cnt4 gives the number of times the o was thrown */
    cnt4 = 0;

    while (1)
    {
        int64_t nBallX = 500 - nStartIdX;
        int64_t nBallY = 0;

        /* If the current block is itself a 'o', then break the loop as it is done */

        if (blocks[nBallY][nBallX] == 'o')
        {
            break;
        }

        /* Run the loop for a large 1000 values */
        for (cnt3 = 0; cnt3 < 1000; cnt3++)
        {
            /* If the ball can move in the Y direction, keep moving */
            if (blocks[nBallY+1][nBallX] != 'o' && blocks[nBallY+1][nBallX] != '#')
            {
                nBallY++;
            }
            /* If the ball cannot move in the Y direction, but can move in diagnal
             * X-1 direction, keep moving */
            else if (blocks[nBallY+1][nBallX-1] != 'o' && blocks[nBallY+1][nBallX-1] != '#')
            {
                nBallY++;
                nBallX--;
            }
            /* If the ball cannot move both in the Y direction and diagnal
             * X-1 direction, but can move in diagnal X+1 direction, keep moving */
            else if (blocks[nBallY+1][nBallX+1] != 'o' && blocks[nBallY+1][nBallX+1] != '#')
            {
                nBallY++;
                nBallX++;
            }
            /* If the ball cannot move at all, break the loop */
            else
            {
                break;
            }
        }

        /* For free fall ball: if the loop does not terminate even after 1000
         * rounds, break from loop */
        if (cnt3 != 1000)
        {
            /* If terminated before 1000 rounds, assign the current Y and X positon
             * as a 'o' */
            blocks[nBallY][nBallX] = 'o';
        }
        else
        {
            break;
        }
        /* increment the count of the unit */
        cnt4++;
    }

    /* Display part b */
    cout << "Part (b): " << cnt4 << endl;

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}
