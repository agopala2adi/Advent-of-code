#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;


typedef enum DIRECTION
{
    NORTH,
    EAST,
    SOUTH,
    WEST
} DIRECTION;


char arr[10000][1000];
char arr2[10000][1000];

bool findInsideOutside(int64_t y_pos, int64_t x_pos, DIRECTION nDir);

int64_t nLoopLen;

int64_t nXSize;
int64_t nYSize;

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

    /* Y index */
    int64_t nYIdx = 0;
    /* X index */
    int64_t nXIdx = 0;

    /* Direction from previous to current */
    DIRECTION nPrevDir = NORTH;
    /* Direction from S to next element part of pipe */
    DIRECTION nSDir = NORTH;

    /* X coordinate of S */
    int64_t nS_XLocation = 0;
    /* Y coordinate of S */
    int64_t nS_YLocation = 0;

    /* Direction from the current pipe to the next pipe */
    DIRECTION nCurrDir = NORTH;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        for (cnt2 = 0; cnt2 < strlen(arr[0]); cnt2++)
        {
            /* Keep a copy of the pipe in arr2 */
            arr2[cnt1][cnt2] = arr[cnt1][cnt2];
            if (arr[cnt1][cnt2] == 'S')
            {
                nS_YLocation = cnt1;
                nS_XLocation = cnt2;
                arr2[cnt1][cnt2] = 'X';
            }
        }
        /* Increment count to move to next line */
        ++cnt1;
    }

    nYSize = cnt1;
    /* Do not include the new line character */
    nXSize = strlen(arr[0])-1;;

    /* From S move to a nearest valid pipe */
    if ((nS_XLocation < nXSize) && (arr[nS_YLocation][nS_XLocation+1] == 'J' || arr[nS_YLocation][nS_XLocation+1] == '7' || arr[nS_YLocation][nS_XLocation+1] == '-'))
    {
        /* Location right of S should have pipes, J, 7 or - */
        nYIdx = nS_YLocation;
        nXIdx = nS_XLocation + 1;
        nPrevDir = EAST;
        nSDir = EAST;
    }
    else if ((nS_YLocation < nYSize) && (arr[nS_YLocation+1][cnt4] == 'J' || arr[nS_YLocation+1][cnt4] == '|' || arr[nS_YLocation+1][cnt4] == 'L'))
    {
        /* Location down of S should have pipes, J, | or L */
        nYIdx = nS_YLocation + 1;
        nXIdx = nS_XLocation;
        nPrevDir = SOUTH;
        nSDir = SOUTH;
    }
    else if ((cnt4 > 0) && (arr[nS_YLocation][cnt4-1] == 'F' || arr[nS_YLocation][cnt4-1] == 'L' || arr[nS_YLocation][cnt4-1] == '-'))
    {
        /* Location left of S should have pipes, F, L or - */
        nYIdx = nS_YLocation;
        nXIdx = nS_XLocation - 1;
        nPrevDir = WEST;
        nSDir = WEST;
    }
    else if ((nS_YLocation > 0) && (arr[nS_YLocation-1][cnt4] == 'F' || arr[nS_YLocation-1][cnt4] == '7' || arr[nS_YLocation-1][cnt4] == '|'))
    {
        /* Location up of S should have pipes, F, 7 or | */
        nYIdx = nS_YLocation - 1;
        nXIdx = nS_XLocation;
        nPrevDir = NORTH;
        nSDir = NORTH;
    }
    else
    {
        cout << "Unable to process input." << endl;
    }

    /* Continue moving along the pipe until reaching 'S' */
    while (true)
    {
        /* Increment count to track the number of pipes from S to S */
        ++cnt7;

        /* Mark X in the valid pipe locations */
        arr2[nYIdx][nXIdx] = 'X';

        /* If reaching 'S' again, stop processing */
        if (arr[nYIdx][nXIdx] == 'S')
        {
            /* Replace with the appropriate pipe where S was present */
            if (nPrevDir == NORTH && nSDir == NORTH)
            {
                arr[nYIdx][nXIdx] = '|';
            }
            else if ((nPrevDir == NORTH && nSDir == EAST) ||
                     (nPrevDir == WEST && nSDir == SOUTH))
            {
                arr[nYIdx][nXIdx] = 'F';
            }
            else if ((nPrevDir == NORTH && nSDir == WEST) ||
                     (nPrevDir == EAST && nSDir == SOUTH))
            {
                arr[nYIdx][nXIdx] = '7';
            }
            else if ((nPrevDir == EAST && nSDir == NORTH) ||
                     (nPrevDir == SOUTH && nSDir == WEST))
            {
                arr[nYIdx][nXIdx] = 'J';
            }
            else if (nPrevDir == EAST && nSDir == EAST)
            {
                arr[nYIdx][nXIdx] = '-';
            }
            else if ((nPrevDir == WEST && nSDir == NORTH) ||
                     (nPrevDir == SOUTH && nSDir == EAST))
            {
                arr[nYIdx][nXIdx] = 'L';
            }
            break;
        }
        /* If the current pipe is J */
        if (arr[nYIdx][nXIdx] == 'J')
        {
            /* If the direction from previous is east, then the next direction
             * is north and y coordinate is decremented */
            if (nPrevDir == EAST && nYIdx > 0)
            {
                nPrevDir = NORTH;
                nYIdx--;
            }
            /* If the direction from previous is south, then the next direction
             * is west and x coordinate is incremented */
            else if (nPrevDir == SOUTH && nXIdx > 0)
            {
                nPrevDir = WEST;
                nXIdx--;
            }
            else
            {
                /* There is some error otherwise */
                break;
            }
        }
        /* If the current pipe is F */
        else if (arr[nYIdx][nXIdx] == 'F')
        {
            /* If the direction from previous is north, then the next direction
             * is east and x coordinate is incremented */
            if (nPrevDir == NORTH && nXIdx < nXSize)
            {
                nPrevDir = EAST;
                nXIdx++;
            }
            /* If the direction from previous is west, then the next direction
             * is south and y coordinate is incremented */
            else if (nPrevDir == WEST && nYIdx < nYSize)
            {
                nPrevDir = SOUTH;
                nYIdx++;
            }
            else
            {
                /* There is some error otherwise */
                break;
            }
        }
        /* If the current pipe is 7 */
        else if (arr[nYIdx][nXIdx] == '7')
        {
            if (nPrevDir == EAST && nYIdx < nYSize)
            {
                nPrevDir = SOUTH;
                nYIdx++;
            }
            else if (nPrevDir == NORTH && nXIdx > 0)
            {
                nPrevDir = WEST;
                nXIdx--;
            }
            else
            {
                /* There is some error otherwise */
                break;
            }
        }
        /* If the current pipe is L */
        else if (arr[nYIdx][nXIdx] == 'L')
        {
            if (nPrevDir == SOUTH && nXIdx < nXSize)
            {
                nPrevDir = EAST;
                nXIdx++;
            }
            else if (nPrevDir == WEST && nYIdx > 0)
            {
                nPrevDir = NORTH;
                nYIdx--;
            }
            else
            {
                /* There is some error otherwise */
                break;
            }
        }
        /* If the current pipe is - */
        else if (arr[nYIdx][nXIdx] == '-')
        {
            if (nPrevDir == EAST && nXIdx < nXSize)
            {
                nPrevDir = EAST;
                nXIdx++;
            }
            else if (nPrevDir == WEST && nXIdx > 0)
            {
                nPrevDir = WEST;
                nXIdx--;
            }
            else
            {
                /* There is some error otherwise */
                break;
            }
        }
        /* If the current pipe is | */
        else if (arr[nYIdx][nXIdx] == '|')
        {
            if (nPrevDir == NORTH && nYIdx > 0)
            {
                nPrevDir = NORTH;
                nYIdx--;
            }
            else if (nPrevDir == SOUTH && nYIdx < nYSize)
            {
                nPrevDir = SOUTH;
                nYIdx++;
            }
            else
            {
                /* There is some error otherwise */
                break;
            }
        }
        else
        {
            /* There is some error otherwise */
            break;
        }

    }

    /* Store the loop count */
    nLoopLen = cnt7;
    /* Part 1 is half of loop count as farthest is 50% of total distance */
    nPartOneSum = cnt7/2;

    /* Replace all non main pipe with dot */
    for (cnt3 = 0; cnt3 < nYSize; cnt3++)
    {
        for (cnt4 = 0; cnt4 < nXSize; cnt4++)
        {
            if (arr2[cnt3][cnt4] != 'X')
            {
                arr[cnt3][cnt4] = '.';
            }
        }
    }

    /* Find sure outside and replace '.' with 'O' */
    for (cnt3 = 0; cnt3 < nYSize; cnt3++)
    {
        /* Going from left to right */
        for (cnt4 = 0; cnt4 < nXSize; cnt4++)
        {
            if (arr[cnt3][cnt4] == '.')
            {
                arr[cnt3][cnt4] = 'O';
            }
            else
            {
                break;
            }
        }
        /* Going from right to left */
        for (cnt4 = nXSize-1; cnt4 >= 0; cnt4--)
        {
            if (arr[cnt3][cnt4] == '.')
            {
                arr[cnt3][cnt4] = 'O';
            }
            else
            {
                break;
            }
        }
    }

    /* Find sure outside and replace '.' with 'O' */
    for (cnt4 = 0; cnt4 < nXSize; cnt4++)
    {
        /* Going from top to bottom */
        for (cnt3 = 0; cnt3 < nYSize; cnt3++)
        {
            if (arr[cnt3][cnt4] == '.' || arr[cnt3][cnt4] == 'O')
            {
                arr[cnt3][cnt4] = 'O';
            }
            else
            {
                break;
            }
        }
        /* Going from bottom to top */
        for (cnt3 = nYSize-1; cnt3 >= 0; cnt3--)
        {
            if (arr[cnt3][cnt4] == '.' || arr[cnt3][cnt4] == 'O')
            {
                arr[cnt3][cnt4] = 'O';
            }
            else
            {
                break;
            }
        }
    }

    cnt8 = 1;
    /* Loop till all dots are covered */
    while (cnt8 != 0)
    {
        cnt8 = 0;
        for (cnt3 = 0; cnt3 < nYSize; cnt3++)
        {
            for (cnt4 = 0; cnt4 < nXSize; cnt4++)
            {
                /* If encountering a dot */
                if (arr[cnt3][cnt4] == '.')
                {
                    /* Increment the count to perform again */
                    ++cnt8;

                    /* If the next cell is outside, treat this also outside */
                    if ((cnt3 < cnt1-1 && arr[cnt3+1][cnt4] == 'O') ||
                        (cnt3 > 0 && arr[cnt3-1][cnt4] == 'O') ||
                        (cnt4 < nXSize-1 && arr[cnt3][cnt4+1] == 'O') ||
                        (cnt4 > 0 && arr[cnt3][cnt4-1] == 'O'))
                    {
                        arr[cnt3][cnt4] = 'O';
                    }
                    /* If the next cell is inside, treat this also inside */
                    else if ((cnt3 < cnt1-1 && arr[cnt3+1][cnt4] == 'I') ||
                        (cnt3 > 0 && arr[cnt3-1][cnt4] == 'I') ||
                        (cnt4 < nXSize-1 && arr[cnt3][cnt4+1] == 'I') ||
                        (cnt4 > 0 && arr[cnt3][cnt4-1] == 'I'))
                    {
                        arr[cnt3][cnt4] = 'I';
                    }
                    /* If the next cell is not a dot, process this dot */
                    else if (cnt3 < cnt1-1 && arr[cnt3+1][cnt4] != '.')
                    {
                        /* Move south */
                        nCurrDir = SOUTH;
                        if (findInsideOutside(cnt3, cnt4, nCurrDir) == false)
                        {
                            arr[cnt3][cnt4] = 'O';
                        }
                        else
                        {
                            arr[cnt3][cnt4] = 'I';
                        }
                    }
                    else if (cnt4 < nXSize-1 && arr[cnt3][cnt4+1] != '.')
                    {
                        /* Move east */
                        nCurrDir = EAST;
                        if (findInsideOutside(cnt3, cnt4, nCurrDir) == false)
                        {
                            arr[cnt3][cnt4] = 'O';
                        }
                        else
                        {
                            arr[cnt3][cnt4] = 'I';
                        }
                    }
                    else if (cnt3 > 0 && arr[cnt3-1][cnt4] != '.')
                    {
                        /* Move north */
                        nCurrDir = NORTH;
                        if (findInsideOutside(cnt3, cnt4, nCurrDir) == false)
                        {
                            arr[cnt3][cnt4] = 'O';
                        }
                        else
                        {
                            arr[cnt3][cnt4] = 'I';
                        }
                    }
                    else if (cnt4 > 0 && arr[cnt3][cnt4-1] != '.')
                    {
                        /* Move west */
                        nCurrDir = WEST;
                        if (findInsideOutside(cnt3, cnt4, nCurrDir) == false)
                        {
                            arr[cnt3][cnt4] = 'O';
                        }
                        else
                        {
                            arr[cnt3][cnt4] = 'I';
                        }
                    }
                }
            }
        }
    }

    /* Count the number of elements inside the loop - replaced with I */
    for (cnt3 = 0; cnt3 < cnt1; cnt3++)
    {
        for (cnt4 = 0; cnt4 < nXSize; cnt4++)
        {
            if (arr[cnt3][cnt4] == 'I')
            {
                ++nPartTwoSum;
            }
        }
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

/* Returns if the element given by (x_pos, y_pos) is inside or outside */
bool findInsideOutside(int64_t y_pos, int64_t x_pos, DIRECTION nDir)
{
    DIRECTION nCurrDir = NORTH;

    int64_t cnt1 = 0;

    /* Find the direction of the test position away from the pipe */
    if (nDir == NORTH)
    {
        if (arr[y_pos-1][x_pos] == '-')
        {
            nCurrDir = EAST;
            y_pos--;
            nDir = SOUTH;
        }
        else if (arr[y_pos-1][x_pos] == 'J')
        {
            nCurrDir = NORTH;
            y_pos--;
            nDir = EAST;
        }
        else if (arr[y_pos-1][x_pos] == 'L')
        {
            nCurrDir = NORTH;
            y_pos--;
            nDir = WEST;
        }
    }
    else if (nDir == EAST)
    {
        if (arr[y_pos][x_pos+1] == '|')
        {
            nCurrDir = SOUTH;
            x_pos++;
            nDir = WEST;
        }
        else if (arr[y_pos][x_pos+1] == 'F')
        {
            nCurrDir = SOUTH;
            x_pos++;
            nDir = WEST;
        }
        else if (arr[y_pos][x_pos+1] == 'L')
        {
            nCurrDir = EAST;
            x_pos++;
            nDir = SOUTH;
        }
    }
    else if (nDir == SOUTH)
    {
        if (arr[y_pos+1][x_pos] == '-')
        {
            nCurrDir = EAST;
            y_pos++;
            nDir = NORTH;
        }
        else if (arr[y_pos+1][x_pos] == 'F')
        {
            nCurrDir = EAST;
            y_pos++;
            nDir = NORTH;
        }
        else if (arr[y_pos+1][x_pos] == '7')
        {
            nCurrDir = SOUTH;
            y_pos++;
            nDir = EAST;
        }
    }
    else if (nDir == WEST)
    {
        if (arr[y_pos][x_pos-1] == '|')
        {
            nCurrDir = SOUTH;
            x_pos--;
            nDir = EAST;
        }
        else if (arr[y_pos][x_pos-1] == '7')
        {
            nCurrDir = SOUTH;
            x_pos--;
            nDir = EAST;
        }
        else if (arr[y_pos][x_pos-1] == 'J')
        {
            nCurrDir = WEST;
            x_pos--;
            nDir = SOUTH;
        }
    }

    /* Check if you have completed one full loop */
    while (cnt1 < nLoopLen)
    {
        /* If the pipe is north of the current position, consider as out */
        if (nDir == NORTH && (y_pos == 0 || arr[y_pos-1][x_pos] == 'O'))
        {
            return false;
        }
        /* If the pipe is east of the current position, consider as out */
        else if (nDir == EAST && (x_pos == nYSize-1 || arr[y_pos][x_pos+1] == 'O'))
        {
            return false;
        }
        /* If the pipe is south of the current position, consider as out */
        else if (nDir == SOUTH && (y_pos == nXSize-1 || arr[y_pos+1][x_pos] == 'O'))
        {
            return false;
        }
        /* If the pipe is west of the current position, consider as out */
        else if (nDir == WEST && (x_pos == 0 || arr[y_pos][x_pos-1] == 'O'))
        {
            return false;
        }

        /* If the next pipe is inside consider as inside */
        if (nDir == NORTH && (y_pos != 0 && arr[y_pos-1][x_pos] == 'I'))
        {
            return true;
        }
        /* If the next pipe is inside consider as inside */
        else if (nDir == EAST && (x_pos != nYSize-1 && arr[y_pos][x_pos+1] == 'I'))
        {
            return true;
        }
        /* If the next pipe is inside consider as inside */
        else if (nDir == SOUTH && (y_pos != nXSize-1 && arr[y_pos+1][x_pos] == 'I'))
        {
            return true;
        }
        /* If the next pipe is inside consider as inside */
        else if (nDir == WEST && (x_pos != 0 && arr[y_pos][x_pos-1] == 'I'))
        {
            return true;
        }

        /* Follow the pipe until you reach outside or inside */
        if (nCurrDir == NORTH)
        {
            if (arr[y_pos][x_pos] == 'J' || arr[y_pos][x_pos] == '|' || arr[y_pos][x_pos] == 'L')
            {
                y_pos--;
                if (arr[y_pos][x_pos] == '|')
                {
                    nCurrDir = NORTH;
                    nDir = nDir;
                }
                else if (arr[y_pos][x_pos] == '7')
                {
                    nCurrDir = WEST;
                    if (nDir == WEST)
                    {
                        nDir = SOUTH;
                    }
                    else
                    {
                        nDir = NORTH;
                    }
                }
                else if (arr[y_pos][x_pos] == 'F')
                {
                    nCurrDir = EAST;
                    if (nDir == WEST)
                    {
                        nDir = NORTH;
                    }
                    else
                    {
                        nDir = SOUTH;
                    }
                }
            }
        }
        else if (nCurrDir == EAST)
        {
            if (arr[y_pos][x_pos] == 'F' || arr[y_pos][x_pos] == '-' || arr[y_pos][x_pos] == 'L')
            {
                x_pos++;
                if (arr[y_pos][x_pos] == '-')
                {
                    nCurrDir = EAST;
                    nDir = nDir;
                }
                else if (arr[y_pos][x_pos] == 'J')
                {
                    nCurrDir = NORTH;
                    if (nDir == NORTH)
                    {
                        nDir = WEST;
                    }
                    else
                    {
                        nDir = EAST;
                    }
                }
                else if (arr[y_pos][x_pos] == '7')
                {
                    nCurrDir = SOUTH;
                    if (nDir == NORTH)
                    {
                        nDir = EAST;
                    }
                    else
                    {
                        nDir = WEST;
                    }
                }
            }
        }
        else if (nCurrDir == SOUTH)
        {
            if (arr[y_pos][x_pos] == '|' || arr[y_pos][x_pos] == 'F' || arr[y_pos][x_pos] == '7')
            {
                y_pos++;
                if (arr[y_pos][x_pos] == '|')
                {
                    nCurrDir = SOUTH;
                    nDir = nDir;
                }
                else if (arr[y_pos][x_pos] == 'J')
                {
                    nCurrDir = WEST;
                    if (nDir == EAST)
                    {
                        nDir = SOUTH;
                    }
                    else
                    {
                        nDir = NORTH;
                    }
                }
                else if (arr[y_pos][x_pos] == 'L')
                {
                    nCurrDir = EAST;
                    if (nDir == WEST)
                    {
                        nDir = SOUTH;
                    }
                    else
                    {
                        nDir = NORTH;
                    }
                }
            }
        }
        else if (nCurrDir == WEST)
        {
            if (arr[y_pos][x_pos] == '-' || arr[y_pos][x_pos] == 'J' || arr[y_pos][x_pos] == '7')
            {
                x_pos--;
                if (arr[y_pos][x_pos] == '-')
                {
                    nCurrDir = WEST;
                    nDir = nDir;
                }
                else if (arr[y_pos][x_pos] == 'F')
                {
                    nCurrDir = SOUTH;
                    if (nDir == SOUTH)
                    {
                        nDir = EAST;
                    }
                    else
                    {
                        nDir = WEST;
                    }
                }
                else if (arr[y_pos][x_pos] == 'L')
                {
                    nCurrDir = NORTH;
                    if (nDir == SOUTH)
                    {
                        nDir = WEST;
                    }
                    else
                    {
                        nDir = EAST;
                    }
                }
            }
        }

        ++cnt1;
    }

    return true;
}

