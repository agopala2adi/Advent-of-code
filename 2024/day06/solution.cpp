#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[1000];

enum DIRECTION
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
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
    int64_t nPosStartX = 0, nPosStartY = 0, nPosStartXBackup = 0, nPosStartYBackup = 0;

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    vector<string> vsMap;
    vector<string> vsMapCopy;

    vector<int64_t> vnXPositions;
    vector<int64_t> vnYPositions;

    /* Read each line from file */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        /* Store the row into a vector of strings */        
        vsMap.push_back(arr);

        /* Remove the end new line characters */
        if (vsMap[cnt1][vsMap[cnt1].size()-1] == '\n' || vsMap[cnt1][vsMap[cnt1].size()-1] == '\r')
        {
            vsMap[cnt1].pop_back();
        }
        /* Remove the end new line characters - check again if both present */
        if (vsMap[cnt1][vsMap[cnt1].size()-1] == '\n' || vsMap[cnt1][vsMap[cnt1].size()-1] == '\r')
        {
            vsMap[cnt1].pop_back();
        }

        /* Find the starting place given by '^ */
        if (find(vsMap[cnt1].begin(), vsMap[cnt1].end(), '^') != vsMap[cnt1].end())
        {
            nPosStartX = cnt1;
            nPosStartY = vsMap[cnt1].find('^');

            /* Store the position of X and Y as a backup */
            nPosStartXBackup = nPosStartX;
            nPosStartYBackup = nPosStartY;
            vsMap[nPosStartX][nPosStartY] = 'X';
        }

        /* Increment count */
        ++cnt1;
    }

    DIRECTION eDir = UP;
    vsMapCopy = vsMap;

    /* Part (a) */
    while (true)
    {
        /* If the current direction is up keep moving up until observing a hash */
        if (eDir == UP)
        {
            for (cnt2 = nPosStartX; cnt2 >= 0; cnt2--)
            {
                if (vsMap[cnt2][nPosStartY] == '#')
                {
                    break;
                }
                else
                {
                    /* Replace the indices of movement with X to count at the end */
                    vsMap[cnt2][nPosStartY] = 'X';
                }
            }
            /* If trying to move outside the boundary stop moving */
            if (cnt2 < 0)
            {
                break;
            }
            else
            {
                /* Rotate the dir counter-clockwise by 1 */
                eDir = static_cast<DIRECTION>((static_cast<int>(eDir) + 1) % 4);
                /* Update only the starting x position */
                nPosStartX = cnt2 + 1;
            }
        }
        /* If the current direction is right, keep moving right until a hash */
        else if (eDir == RIGHT)
        {
            for (cnt2 = nPosStartY; cnt2 < vsMap[0].size(); cnt2++)
            {
                if (vsMap[nPosStartX][cnt2] == '#')
                {
                    break;
                }
                else
                {
                    vsMap[nPosStartX][cnt2] = 'X';
                }
            }
            /* If trying to move outside the boundary stop moving */
            if (cnt2 == vsMap[0].size())
            {
                break;
            }
            else
            {
                /* Rotate the dir counter-clockwise by 1 */
                eDir = static_cast<DIRECTION>((static_cast<int>(eDir) + 1) % 4);
                /* Update only the starting y position */
                nPosStartY = cnt2 - 1;
            }
        }
        /* If the current direction is down, keep moving down until a hash */
        else if (eDir == DOWN)
        {
            for (cnt2 = nPosStartX; cnt2 < vsMap.size(); cnt2++)
            {
                if (vsMap[cnt2][nPosStartY] == '#')
                {
                    break;
                }
                else
                {
                    vsMap[cnt2][nPosStartY] = 'X';
                }
            }
            /* If trying to move outside the boundary stop moving */
            if (cnt2 == vsMap.size())
            {
                break;
            }
            else
            {
                /* Rotate the dir counter-clockwise by 1 */
                eDir = static_cast<DIRECTION>((static_cast<int>(eDir) + 1) % 4);
                /* Update only the starting x position */
                nPosStartX = cnt2 - 1;
            }
        }
        /* If the current direction is left, keep moving left until a hash */
        else if (eDir == LEFT)
        {
            for (cnt2 = nPosStartY; cnt2 >= 0; cnt2--)
            {
                if (vsMap[nPosStartX][cnt2] == '#')
                {
                    break;
                }
                else
                {
                    vsMap[nPosStartX][cnt2] = 'X';
                }
            }
            /* If trying to move outside the boundary stop moving */
            if (cnt2 < 0)
            {
                break;
            }
            else
            {
                /* Rotate the dir counter-clockwise by 1 */
                eDir = static_cast<DIRECTION>((static_cast<int>(eDir) + 1) % 4);
                /* Update only the starting y position */
                nPosStartY = cnt2 + 1;
            }
        }
        else
        {
            /* Empty else */
        }
        /* Continue moving */
    }

    /* When stopped moving count all X's */
    for (cnt2 = 0; cnt2 < vsMap.size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < vsMap[cnt2].size(); cnt3++)
        {
            if (vsMap[cnt2][cnt3] == 'X')
            {
                ++nFirstPart;
                /* Store the positions of X in this vectors for part (b) */
                vnXPositions.push_back(cnt2);
                vnYPositions.push_back(cnt3);
            }
        }
    }

    /* After part (a), copy back original into vsMap */
    vsMap = vsMapCopy; 

    /* Part (b) */

    /* Take all the points of  */
    for (cnt6 = 0; cnt6 < vnXPositions.size(); cnt6++)
    {
        int64_t nCurrXPos = vnXPositions[cnt6];
        int64_t nCurrYPos = vnYPositions[cnt6];

        /* If the current position is not a hash, replace it with a hash 
         * and see if it forms a loop */
        if (vsMap[nCurrXPos][nCurrYPos] != '#')
        {
            /* Default direction is up */
            eDir = UP;
            /* Set the starting x, and y positions from backup */
            nPosStartX = nPosStartXBackup;
            nPosStartY = nPosStartYBackup;

            /* Set the position to a hash */
            vsMap[nCurrXPos][nCurrYPos] = '#';

            /* Use a hash map with string of visited or not 
             * Note that only end positions near a block # needs to be 
             * included in the hash 
            */
            unordered_map<string, bool> umVisited;

            /* Run a while 1 loop to see if it forms a loop or breaks the 
             * map */
            while (true)
            {
                /* If the current direction is up keep moving up until observing a hash */
                if (eDir == UP)
                {
                    for (cnt2 = nPosStartX; cnt2 >= 0; cnt2--)
                    {
                        if (vsMap[cnt2][nPosStartY] == '#')
                        {
                            /* If seeing a block, store the position and direction
                             * into the hash to avoid it from repeating */
                            string sDirPosConcat = to_string(eDir) + " " + to_string(nPosStartX) + " " + to_string(nPosStartY);
                            umVisited[sDirPosConcat] = true;
                            break;
                        }
                    }
                    /* If trying to move outside the boundary stop moving */
                    if (cnt2 < 0)
                    {
                        break;
                    }
                    else
                    {
                        /* Rotate the dir counter-clockwise by 1 */
                        eDir = static_cast<DIRECTION>((static_cast<int>(eDir) + 1) % 4);
                        /* Update only the starting x position */
                        nPosStartX = cnt2 + 1;
                    }
                }
                /* If the current direction is right, keep moving right until a hash */
                else if (eDir == RIGHT)
                {
                    for (cnt2 = nPosStartY; cnt2 < vsMap[0].size(); cnt2++)
                    {
                        if (vsMap[nPosStartX][cnt2] == '#')
                        {
                            /* If seeing a block, store the position and direction
                             * into the hash to avoid it from repeating */
                            string sDirPosConcat = to_string(eDir) + " " + to_string(nPosStartX) + " " + to_string(nPosStartY);
                            umVisited[sDirPosConcat] = 1;
                            break;
                        }
                    }
                    /* If trying to move outside the boundary stop moving */
                    if (cnt2 == vsMap[0].size())
                    {
                        break;
                    }
                    else
                    {
                        /* Rotate the dir counter-clockwise by 1 */
                        eDir = static_cast<DIRECTION>((static_cast<int>(eDir) + 1) % 4);
                        /* Update only the starting y position */
                        nPosStartY = cnt2 - 1;
                    }
                }
                /* If the current direction is down, keep moving down until a hash */
                else if (eDir == DOWN)
                {
                    for (cnt2 = nPosStartX; cnt2 < vsMap.size(); cnt2++)
                    {
                        if (vsMap[cnt2][nPosStartY] == '#')
                        {
                            /* If seeing a block, store the position and direction
                             * into the hash to avoid it from repeating */
                            string sDirPosConcat = to_string(eDir) + " " + to_string(nPosStartX) + " " + to_string(nPosStartY);
                            umVisited[sDirPosConcat] = 1;
                            break;
                        }
                    }
                    /* If trying to move outside the boundary stop moving */
                    if (cnt2 == vsMap.size())
                    {
                        break;
                    }
                    else
                    {
                        /* Rotate the dir counter-clockwise by 1 */
                        eDir = static_cast<DIRECTION>((static_cast<int>(eDir) + 1) % 4);
                        /* Update only the starting x position */
                        nPosStartX = cnt2 - 1;
                    }
                }
                /* If the current direction is left, keep moving left until a hash */
                else if (eDir == LEFT)
                {
                    for (cnt2 = nPosStartY; cnt2 >= 0; cnt2--)
                    {
                        if (vsMap[nPosStartX][cnt2] == '#')
                        {
                            /* If seeing a block, store the position and direction
                             * into the hash to avoid it from repeating */
                            string sDirPosConcat = to_string(eDir) + " " + to_string(nPosStartX) + " " + to_string(nPosStartY);
                            umVisited[sDirPosConcat] = 1;
                            break;
                        }
                    }
                    /* If trying to move outside the boundary stop moving */
                    if (cnt2 < 0)
                    {
                        break;
                    }
                    else
                    {
                        /* Rotate the dir counter-clockwise by 1 */
                        eDir = static_cast<DIRECTION>((static_cast<int>(eDir) + 1) % 4);
                        /* Update only the starting y position */
                        nPosStartY = cnt2 + 1;
                    }
                }
                else
                {
                    /* Empty else */
                }

                /* If the same position with direction is present in the hashmap
                 * as before, consider that the map is a loop */
                string sToFind = to_string(eDir) + " " + to_string(nPosStartX) + " " + to_string(nPosStartY);
                if (umVisited.find(sToFind) != umVisited.end())
                {
                    ++nSecondPart;
                    break;
                }
            }

            /* Restore the map back to a dot for the next iteration */
            vsMap[nCurrXPos][nCurrYPos] = '.';
        }
    }

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
