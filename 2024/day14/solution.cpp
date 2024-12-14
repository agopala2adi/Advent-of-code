#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[10000];

// #define DISPLAY_STATES
#define DISPLAY_FINAL (true)

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
    // To printf uint -> printf("%llu ", fin);

    // String stream: stringstream iss(arr);
    // Store word from string to string iss >> word
    // Display: printf("%s\n",word.c_str());

    // list<string> totalStrings;
    // for (auto it = totalStrings.begin(); it != totalStrings.end(); ++it)
    //     string str = *it;


    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int64_t nPosStartX = 0, nPosStartY = 0, nPosStartXBackup = 0, nPosStartYBackup = 0;

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* Width and height of the space */
    const int64_t nWidth = 101;
    const int64_t nHeight = 103;

    /* A matrix containing the robots - true if present, else false */
    bool mRobots[nHeight][nWidth] = { false };

    /* x, y positions of the robots */
    vector<int64_t> vXPosition;
    vector<int64_t> vYPosition;

    /* x, y velocities of the robots */
    vector<int64_t> vXVelocity;
    vector<int64_t> vYVelocity;

    /* A copy of the first x, y position of robot to check for repetition */
    vector<int64_t> vXPositionCopy;
    vector<int64_t> vYPositionCopy;

    /* Position of robots for the easter egg */
    vector<int64_t> vXPositionEasterEgg;
    vector<int64_t> vYPositionEasterEgg;

    /* Use symmetry (because Christmas tree is symmetrical) to check if 
     * easter egg is found or not 
    */
    int64_t nMaxSymmetry = 0;

    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        int64_t xPosition;
        int64_t yPosition;
        int64_t xVelocity;
        int64_t yVelocity;

        /* Read x,y position and x,y velocity */
        // sscanf(arr, "p=%ld,%ld v=%ld,%ld", &xPosition, &yPosition, &xVelocity, &yVelocity);
        sscanf(arr, "p=%" PRId64 ",%" PRId64 " v=%" PRId64 ",%" PRId64, &xPosition, &yPosition, &xVelocity, &yVelocity);

        /* Store the velocity and position in a vector */
        vXPosition.push_back(xPosition);
        vYPosition.push_back(yPosition);

        /* Set the position in the matrix as true */
        mRobots[yPosition][xPosition] = true;

        vXVelocity.push_back(xVelocity);
        vYVelocity.push_back(yVelocity);

        /* Increment count */
        ++cnt1;
    }

    /* Store the first robot positions (x, y) in the copy */
    vXPositionCopy = vXPosition;
    vYPositionCopy = vYPosition;

    /* Run a while (1) loop with the count of number of seconds */
    for (cnt1 = 1; ; cnt1++)
    {
        /* Initialize the matrix to false */
        for (cnt2 = 0; cnt2 < nHeight; cnt2++)
        {
            for (cnt3 = 0; cnt3 < nWidth; cnt3++)
            {
                mRobots[cnt2][cnt3] = false;
            }
        }

        /* For each robot, update the position */
        for (cnt2 = 0; cnt2 < vXPosition.size(); cnt2++)
        {
            vXPosition[cnt2] += vXVelocity[cnt2];

            /* Ensure that the position is within the bounds */
            while (vXPosition[cnt2] < 0)
            {
                vXPosition[cnt2] += nWidth;
            }
            while (vXPosition[cnt2] >= nWidth)
            {
                vXPosition[cnt2] -= nWidth;
            }

            vYPosition[cnt2] += vYVelocity[cnt2];

            while (vYPosition[cnt2] < 0)
            {
                vYPosition[cnt2] += nHeight;
            }
            while (vYPosition[cnt2] >= nHeight)
            {
                vYPosition[cnt2] -= nHeight;
            }

            /* Set the position in the matrix as true */
            mRobots[vYPosition[cnt2]][vXPosition[cnt2]] = true;
        }

#ifdef DISPLAY_STATES
        /* Display the state if enabled */
        cout << "Current iteration - " << cnt1 << endl;

        for (cnt2 = 0; cnt2 < nHeight; cnt2++)
        {
            for (cnt3 = 0; cnt3 < nWidth; cnt3++)
            {
                if (mRobots[cnt2][cnt3])
                {
                    cout << "#";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }

        /* About 5 millisecond sleep */
        usleep(5000);

        for (cnt2 = 0; cnt2 < nHeight; cnt2++)
        {
            cout << "\033[F";
        }

        cout << "\033[F";
#endif
        /* After completing 100 iterations (100 minus 1 since started from zero) */
        if (cnt1 == 100)
        {
            int64_t nQuadLeftTop = 0;
            int64_t nQuadRightTop = 0;
            int64_t nQuadLeftBottom = 0;
            int64_t nQuadRightBottom = 0;

            /* Count the number of robots in each quadrant */
            for (cnt2 = 0; cnt2 < vXPosition.size(); cnt2++)
            {
                if (vXPosition[cnt2] >= 0 && vXPosition[cnt2] < (nWidth/2))
                {
                    if (vYPosition[cnt2] >= 0 && vYPosition[cnt2] < (nHeight/2))
                    {
                        nQuadLeftTop++;
                    }
                    else if (vYPosition[cnt2] > (nHeight/2) && vYPosition[cnt2] < nHeight)
                    {
                        nQuadLeftBottom++;
                    }
                }
                else if (vXPosition[cnt2] > (nWidth/2) && vXPosition[cnt2] < nWidth)
                {
                    if (vYPosition[cnt2] >= 0 && vYPosition[cnt2] < (nHeight/2))
                    {
                        nQuadRightTop++;
                    }
                    else if (vYPosition[cnt2] > (nHeight/2) && vYPosition[cnt2] < nHeight)
                    {
                        nQuadRightBottom++;
                    }
                }
            }

            /* Calculate the safety factor */
            nFirstPart = nQuadLeftTop * nQuadRightBottom * nQuadLeftBottom * nQuadRightTop;

        }

        /* Check if repeated, if yes, break */
        if (vXPositionCopy == vXPosition && vYPositionCopy == vYPosition && cnt1 > 100)
        {
            break;
        }

        /* Store a current second symmetry */
        int64_t nSymmetryInCurrSecond = 0;

        /* Check symmetry about each column for columns 10 to width minus 10
         * This is arbitrary
         * Christmas tree is assumed to be symmetrical
        */
        for (cnt2 = 10; cnt2 < nWidth-10; cnt2++)
        {
            int64_t nSymmCount = 0;
            for (cnt3 = 0; cnt3 < nHeight; cnt3++)
            {
                for (cnt4 = 1; cnt4 < min(cnt2, nWidth-cnt2); cnt4++)
                {
                    if (mRobots[cnt3][cnt2-cnt4] == mRobots[cnt3][cnt2+cnt4])
                    {
                        ++nSymmCount;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            nSymmetryInCurrSecond = max(nSymmetryInCurrSecond, nSymmCount);
        }

        /* Update the second count for part 1 if found higher symmetry */
        if (nMaxSymmetry < nSymmetryInCurrSecond)
        {
            nMaxSymmetry = nSymmetryInCurrSecond;
            nSecondPart = cnt1;
            vXPositionEasterEgg = vXPosition;
            vYPositionEasterEgg = vYPosition;
        }
    }

#ifdef DISPLAY_FINAL

    /* Display the final Christmas tree state from the highest symmetry */
    cout << "After finding Christmas Tree :- " << endl << endl;
    for (cnt1 = 0; cnt1 < nHeight; cnt1++)
    {
        for (cnt2 = 0; cnt2 < nWidth; cnt2++)
        {
            for (cnt3 = 0; cnt3 < vXPositionEasterEgg.size(); cnt3++)
            {
                if (vXPositionEasterEgg[cnt3] == cnt2 && vYPositionEasterEgg[cnt3] == cnt1)
                {
                    cout << "#";
                    break;
                }
            }
            if (cnt3 == vXPositionEasterEgg.size())
            {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
#endif

    /* Close the file */
    fclose(fp);

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

