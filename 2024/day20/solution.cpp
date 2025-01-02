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

/* Direction enum - Right, Down, Left, Up */
enum DIRECTION
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};


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
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    vector<string> vsMap;

    /* To store the co-ordinates of the start position */
    pair<int64_t, int64_t> nStart = make_pair(0, 0);
    /* To store the co-ordinates of the current position */
    pair<int64_t, int64_t> nCurrent = make_pair(0, 0);
    /* To store the co-ordinates of the end position */
    pair<int64_t, int64_t> nEnd = make_pair(0, 0);

    /* Store the co-ordinates of all the dots */
    vector<pair<int64_t, int64_t>> vPath;
    /* For each co-ordinate, store the distance required by it from start */
    vector<int64_t> vDistanceFromStart;
    /* For each co-ordinate, store the distance required by it to end  */
    vector<int64_t> vDistanceFromEnd;

    /* Each co-ordinate has a distance from start and distance to end */

    /* Start with a current direction of left and start from end */
    DIRECTION eCurrDir = LEFT;

    /* Gain in time when using the cheat, at least 100 picoseconds save */
    int64_t nAllowedDiff = 100;
    /* Allowed cheats - 2 - part (a) */
    int64_t nAllowedCheatsFirstPart = 2;
    /* Allowed cheats - 20 - part (b) */
    int64_t nAllowedCheatsSecondPart = 20;

    /* Total distance of the maze when not using any cheat */
    int64_t nTotalMazeDist = 0;

    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        /* Get input and store each line in vsMap */
        vsMap.push_back(arr);

        /* Remove new line characters if any */
        if (vsMap[cnt1][vsMap[cnt1].size()-1] == '\n' || vsMap[cnt1][vsMap[cnt1].size()-1] == '\r')
        {
            vsMap[cnt1].pop_back();
        }
        if (vsMap[cnt1][vsMap[cnt1].size()-1] == '\n' || vsMap[cnt1][vsMap[cnt1].size()-1] == '\r')
        {
            vsMap[cnt1].pop_back();
        }

        /* Find for S */
        if (nStart.first == 0 && nStart.second == 0)
        {
            if (vsMap[cnt1].find_first_of('S') != string::npos)
            {
                /* Store the start position */
                nStart.first = cnt1;
                nStart.second = vsMap[cnt1].find_first_of('S');
                vsMap[cnt1][nStart.second] = '.';
            }
        }
        /* Find for E */
        if (nEnd.first == 0 && nEnd.second == 0)
        {
            if (vsMap[cnt1].find_first_of('E') != string::npos)
            {
                /* Store the end position */
                nEnd.first = cnt1;
                nEnd.second = vsMap[cnt1].find_first_of('E');
                vsMap[cnt1][nEnd.second] = '.';
            }
        }
        /* Increment count */
        ++cnt1;
    }

    /* Since we are tracing the maze from back, start from the end co-ordinate */
    nCurrent = nEnd;

    /* Store that into the vector and store the distance from end */
    vPath.push_back(nCurrent);

    int64_t nDistFromEnd = 0;
    /* Since we are at the end, store the distance as zero */
    vDistanceFromEnd.push_back(nDistFromEnd);

    /* Traverse the maze until start is reached */
    while (nCurrent != nStart)
    {
        /* If the current direction is right, try to move in any direction
         * other than right and update the current co-ordinates */
        if (eCurrDir == RIGHT)
        {
            if (nCurrent.second < vsMap[0].size()-1 && vsMap[nCurrent.first][nCurrent.second+1] == '.')
            {
                nCurrent.second += 1;
                eCurrDir = RIGHT;
            }
            else if (nCurrent.first > 0 && vsMap[nCurrent.first-1][nCurrent.second] == '.')
            {
                nCurrent.first -= 1;
                eCurrDir = UP;
            }
            else if (nCurrent.first < vsMap.size()-1 && vsMap[nCurrent.first+1][nCurrent.second] == '.')
            {
                nCurrent.first += 1;
                eCurrDir = DOWN;
            }
            else
            {
                cout << "Error: Cannot find path: " << __LINE__ << endl;
                break;
            }
        }
        /* If the current direction is left, try to move in any direction
         * other than left and update the current co-ordinates */
        else if (eCurrDir == LEFT)
        {
            if (nCurrent.second > 0 && vsMap[nCurrent.first][nCurrent.second-1] == '.')
            {
                nCurrent.second -= 1;
                eCurrDir = LEFT;
            }
            else if (nCurrent.first < vsMap.size()-1 && vsMap[nCurrent.first+1][nCurrent.second] == '.')
            {
                nCurrent.first += 1;
                eCurrDir = DOWN;
            }
            else if (nCurrent.first > 0 && vsMap[nCurrent.first-1][nCurrent.second] == '.')
            {
                nCurrent.first -= 1;
                eCurrDir = UP;
            }
            else
            {
                cout << "Error: Cannot find path: " << __LINE__ << endl;
                break;
            }
        }
        /* If the current direction is up, try to move in any direction
         * other than up and update the current co-ordinates */
        else if (eCurrDir == UP)
        {
            if (nCurrent.first > 0 && vsMap[nCurrent.first-1][nCurrent.second] == '.')
            {
                nCurrent.first -= 1;
                eCurrDir = UP;
            }
            else if (nCurrent.second < vsMap[0].size()-1 && vsMap[nCurrent.first][nCurrent.second+1] == '.')
            {
                nCurrent.second += 1;
                eCurrDir = RIGHT;
            }
            else if (nCurrent.second > 0 && vsMap[nCurrent.first][nCurrent.second-1] == '.')
            {
                nCurrent.second -= 1;
                eCurrDir = LEFT;
            }
            else
            {
                cout << "Error: Cannot find path: " << __LINE__ << endl;
                break;
            }
        }
        /* If the current direction is down, try to move in any direction
         * other than down and update the current co-ordinates */
        else if (eCurrDir == DOWN)
        {
            if (nCurrent.first < vsMap.size()-1 && vsMap[nCurrent.first+1][nCurrent.second] == '.')
            {
                nCurrent.first += 1;
                eCurrDir = DOWN;
            }
            else if (nCurrent.second > 0 && vsMap[nCurrent.first][nCurrent.second-1] == '.')
            {
                nCurrent.second -= 1;
                eCurrDir = LEFT;
            }
            else if (nCurrent.second < vsMap[0].size()-1 && vsMap[nCurrent.first][nCurrent.second+1] == '.')
            {
                nCurrent.second += 1;
                eCurrDir = RIGHT;
            }
            else
            {
                cout << "Error: Cannot find path: " << __LINE__ << endl;
                break;
            }
        }
        else
        {
            cout << "Error: Cannot find path: " << __LINE__ << endl;
            break;
        }
        /* Increment distance from end as we have move one step */
        ++nDistFromEnd;
        /* Store the co-ordinate and distance from end */
        vPath.push_back(nCurrent);
        vDistanceFromEnd.push_back(nDistFromEnd);
    }

    /* Final count for start is the total maze length */
    nTotalMazeDist = nDistFromEnd;

    /* Store the distance from start as total maze distance minus distance from
     * end */
    for (cnt1 = 0; cnt1 < vPath.size(); ++cnt1)
    {
        vDistanceFromStart.push_back(nTotalMazeDist - vDistanceFromEnd[cnt1]);
    }

    /* Check between a pair of points on the maze
     * 
     * For first point, check the distance from start and for the second point,
     * check the distance from end.
     * Apply the cheat between the first and the second point.
     * If the sum of both distances and the distance between the two points is 
     * less than the total maze distance, then increment a count.
    */

    /* Traverse the path from start to end */
    for (cnt1 = vPath.size()-1; cnt1 >= 0; cnt1--)
    {
        /* If the distance from start is itself more than the maze total, 
         * exit from the loop */
        if (vDistanceFromStart[cnt1] + nAllowedDiff > nTotalMazeDist)
        {
            break;
        }
        /* Traverse the path from end to start */
        for (cnt2 = 0; cnt2 < vPath.size(); cnt2++)
        {
            /* If seeing the same co-ordinate, skip */
            if (cnt1 == cnt2)
            {
                continue;
            }
            /* If the distance from end is itself more than the maze total,
             * exit from the loop */
            if (vDistanceFromEnd[cnt2] + nAllowedDiff > nTotalMazeDist)
            {
                break;
            }
            /* To check if the cheat is allowed, by checking the Manhattan distance */
            int64_t nCheatDist = abs(vPath[cnt1].first - vPath[cnt2].first) + abs(vPath[cnt1].second - vPath[cnt2].second);
            /* Manhattan distance between the two points must be lower than the
             * allowed cheats */
            /* Part (a) */
            if (nCheatDist <= nAllowedCheatsFirstPart)
            {
                /* Calculate the total distance = distance from start + distance 
                 * from end and distance traversed in cheats 
                 * If that is less than the total maze distance, increment the
                 * count
                 */
                if ((vDistanceFromStart[cnt1] + vDistanceFromEnd[cnt2] + nCheatDist + nAllowedDiff) <= nTotalMazeDist)
                {
                    nFirstPart++;
                }
            }
            /* Part (b) */
            if (nCheatDist <= nAllowedCheatsSecondPart)
            {
                /* Calculate the total distance = distance from start + distance 
                 * from end and distance traversed in cheats 
                 * If that is less than the total maze distance, increment the
                 * count
                 */
                if ((vDistanceFromStart[cnt1] + vDistanceFromEnd[cnt2] + nCheatDist + nAllowedDiff) <= nTotalMazeDist)
                {
                    nSecondPart++;
                }
            }
        }
    }

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

