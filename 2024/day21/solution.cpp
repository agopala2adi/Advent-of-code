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

/**
 * @brief Processes a sequence of numerical key presses and generates all possible movement codes.
 *
 * This function takes a string representing a sequence of numerical key presses and a 4x3 character array representing
 * the numerical keypad layout. It generates all possible movement codes to reach each key in the sequence starting from
 * the initial position of 'A' on the keypad.
 *
 * @param sLine A string representing the sequence of numerical key presses.
 * @param anNumKeyPad A 4x3 character array representing the numerical keypad layout.
 * @return A vector of strings, where each string represents a possible movement code to reach the keys in the sequence.
 */
vector<string> processNumKeyCode(string sLine, char anNumKeyPad[4][3])
{
    /* Return codes - all dir key options for the given numerical sequences */
    vector<string> vnCodes;

    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;

    /* Starting position of A */
    int64_t nXPos = 3;
    int64_t nYPos = 2;

    /* Store a empty string to start with */
    vnCodes.push_back("");

    /* Iterate through all characters of number keys */
    for (cnt1 = 0; cnt1 < sLine.size(); cnt1++)
    {
        /* The next movement for the keys */
        int64_t nXPosNext = 0;
        int64_t nYPosNext = 0;
        string currMovement = "";

        /* Find the next position of the key */
        for (cnt2 = 0; cnt2 < 4; cnt2++)
        {
            for (cnt3 = 0; cnt3 < 3; cnt3++)
            {
                if (anNumKeyPad[cnt2][cnt3] == sLine[cnt1])
                {
                    nXPosNext = cnt2;
                    nYPosNext = cnt3;
                    break;
                }
            }
        }

        /* Split this with respect to "3" selection */

        /* If both current x and next x don't have 3, it is easy */
        if (nXPosNext != 3 && nXPos != 3)
        {
            string currMovement1 = "";
            string currMovement2 = "";

            /* Choose left arrow or right arrow based on y pos */
            if (nYPosNext > nYPos)
            {
                for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                {
                    currMovement1 += '>';
                }
            }
            else
            {
                for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                {
                    currMovement1 += '<';
                }
            }

            /* Choose up arrow or down arrow based on x pos */
            if (nXPosNext > nXPos)
            {
                for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                {
                    currMovement2 += 'v';
                }
            }
            else
            {
                for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                {
                    currMovement2 += '^';
                }
            }

            nXPos = nXPosNext;
            nYPos = nYPosNext;

            vector<string> vnCodesCopy;

            for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
            {
                /* Place both movements as we do not know which would give us
                 * shortest possible count just yet 
                 * Left and then up or
                 * Up and then left
                 */
                string nCurrWord = vnCodes[cnt2];
                vnCodesCopy.push_back(nCurrWord+currMovement1+currMovement2+'A');
                vnCodesCopy.push_back(nCurrWord+currMovement2+currMovement1+'A');
            }

            vnCodes = vnCodesCopy;
        }
        /* If both are in the same line and are 3 */
        else if (nXPos == 3 && nXPosNext == 3)
        {
            /* Choose left arrow or right arrow based on y pos */
            if (nYPosNext > nYPos)
            {
                for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                {
                    currMovement += '>';
                }
            }
            else
            {
                for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                {
                    currMovement += '<';
                }
            }

            nXPos = nXPosNext;
            nYPos = nYPosNext;

            /* Add the movement to all the codes */
            for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
            {
                vnCodes[cnt2] += currMovement+'A';
            }
        }
        /* If either of x positions is 3 and y positions are same */
        else if ((nXPos == 3 || nXPosNext == 3) && nYPos == nYPosNext)
        {
            /* Choose up arrow or down arrow based on x pos */
            if (nXPosNext > nXPos)
            {
                for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                {
                    currMovement += 'v';
                }
            }
            else
            {
                for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                {
                    currMovement += '^';
                }
            }
            /* Add the movement to all the codes */
            for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
            {
                vnCodes[cnt2] += currMovement+'A';
            }

            nXPos = nXPosNext;
            nYPos = nYPosNext;
        }
        /* If current x position is 3 and next x position is not 3 */
        else if (nXPos == 3 && nXPosNext != 3)
        {
            /* If the next y position is in first column */
            if (nYPosNext == 0)
            {
                string currMovement1 = "";
                string currMovement2 = "";
                /* Choose left arrow or right arrow based on y pos */
                if (nYPosNext > nYPos)
                {
                    /* Concat number of R's as the difference between ypos and yposnum */
                    for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                    {
                        currMovement1 += '>';
                    }
                }
                else
                {
                    for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                    {
                        currMovement1 += '<';
                    }
                }
                /* Choose up arrow or down arrow based on x pos */
                if (nXPosNext > nXPos)
                {
                    /* Concat number of D's as the difference between xpos and xposnum */
                    for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                    {
                        currMovement2 += 'v';
                    }
                }
                else
                {
                    for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                    {
                        currMovement2 += '^';
                    }
                }

                nXPos = nXPosNext;
                nYPos = nYPosNext;

                /* Add the movement to all the codes */
                for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                {
                    /* This movement is practically verified */
                    vnCodes[cnt2] += (currMovement2+currMovement1+'A');
                }

            }
            /* If the positions differ by 1 and are in 1 or 2 */
            else if ((nYPosNext == 1 && nYPos == 2) || (nYPosNext == 2 && nYPos == 1))
            {
                string currMovement1 = "";
                string currMovement2 = "";
                /* Choose left arrow or right arrow based on y pos */
                if (nYPosNext > nYPos)
                {
                    for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                    {
                        currMovement1 += '>';
                    }
                }
                else
                {
                    for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                    {
                        currMovement1 += '<';
                    }
                }

                /* Choose up arrow or down arrow based on x pos */
                if (nXPosNext > nXPos)
                {
                    /* Concat number of D's as the difference between xpos and xposnum */
                    for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                    {
                        currMovement2 += 'v';
                    }
                }
                else
                {
                    for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                    {
                        currMovement2 += '^';
                    }
                }

                nXPos = nXPosNext;
                nYPos = nYPosNext;
                /* Add the movement to all the codes */
                for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                {
                    /* This movement is practically verified */
                    vnCodes[cnt2] += (currMovement1+currMovement2+'A');
                }
            }
            else
            {
                /* Error check to debug */
                cout << "Error position " << __LINE__ << endl;
            }

            /* Assign current positions with next positions */
            nXPos = nXPosNext;
            nYPos = nYPosNext;
        }
        /* If next x position is 3 and current x position is not 3 */
        else if (nXPos != 3 && nXPosNext == 3)
        {
            /* If the current y position is 0 */
            if (nYPos == 0)
            {
                string currMovement1 = "";
                string currMovement2 = "";
                /* Choose left arrow or right arrow based on y pos */
                if (nYPosNext > nYPos)
                {
                    for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                    {
                        currMovement1 += '>';
                    }
                }
                else
                {
                    for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                    {
                        currMovement1 += '<';
                    }
                }
                /* Choose up arrow or down arrow based on x pos */
                if (nXPosNext > nXPos)
                {
                    for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                    {
                        currMovement2 += 'v';
                    }
                }
                else
                {
                    for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                    {
                        currMovement2 += '^';
                    }
                }

                nXPos = nXPosNext;
                nYPos = nYPosNext;

                /* Add the movement to all the codes */
                for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                {
                    /* This movement is practically verified */
                    vnCodes[cnt2] += (currMovement1+currMovement2+'A');
                }
            }
            /* If the positions differ by 1 and are in 1 or 2 */
            else if ((nYPosNext == 1 && nYPos == 2) || (nYPosNext == 2 && nYPos == 1))
            {
                string currMovement1 = "";
                string currMovement2 = "";
                /* Choose left arrow or right arrow based on y pos */
                if (nYPosNext > nYPos)
                {
                    for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                    {
                        currMovement1 += '>';
                    }
                }
                else
                {
                    for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                    {
                        currMovement1 += '<';
                    }
                }
                /* Choose up arrow or down arrow based on x pos */
                if (nXPosNext > nXPos)
                {
                    for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                    {
                        currMovement2 += 'v';
                    }
                }
                else
                {
                    for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                    {
                        currMovement2 += '^';
                    }
                }

                nXPos = nXPosNext;
                nYPos = nYPosNext;
                /* Add the movement to all the codes */
                for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                {
                    /* This movement is practically verified */
                    vnCodes[cnt2] += (currMovement2+currMovement1+'A');
                }
            }
            else
            {
                /* Error check to debug */
                cout << "Error position " << __LINE__ << endl;
            }

            /* Assign current positions with next positions */
            nXPos = nXPosNext;
            nYPos = nYPosNext;
        }

        else
        {
            /* Error check to debug */
            cout << "Error position " << __LINE__ << endl;
        }
    }

    return vnCodes;
}

/**
 * @brief Processes a sequence of directional key presses and returns the corresponding movement codes.
 *
 * This function takes a string representing a sequence of directional key presses and a 2x3 character array
 * representing the directional keypad. It calculates the movement codes required to navigate through the keypad
 * based on the given sequence of key presses.
 *
 * @param sLine A string representing the sequence of directional key presses.
 * @param anDirKeyPad A 2x3 character array representing the directional keypad.
 * @return A vector of strings, where each string represents the movement codes for the given sequence of key presses.
 */
vector<string> processDirKeyCode(string sLine, char anDirKeyPad[2][3])
{
    /* Return codes - all dir key options for the dir key sequences */
    vector<string> vnCodes;

    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;

    /* Starting position of A */
    int64_t nXPos = 0;
    int64_t nYPos = 2;

    vnCodes.push_back("");

    /* Iterate through all characters of dir keys */
    for (cnt1 = 0; cnt1 < sLine.size(); cnt1++)
    {
        int64_t nXPosNext = 0;
        int64_t nYPosNext = 0;
        string currMoveent = "";

        /* Find the next position of the key */
        for (cnt2 = 0; cnt2 < 2; cnt2++)
        {
            for (cnt3 = 0; cnt3 < 3; cnt3++)
            {
                if (anDirKeyPad[cnt2][cnt3] == sLine[cnt1])
                {
                    nXPosNext = cnt2;
                    nYPosNext = cnt3;
                    break;
                }
            }
        }
        /* If both current x/y and next or x/y are same, it is easy */
        if (nYPosNext == nYPos)
        {
            /* Choose up arrow or down arrow based on x pos */
            if (nXPosNext > nXPos)
            {
                for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                {
                    currMoveent += 'v';
                }
            }
            else
            {
                for (cnt2 = 0; cnt2 < abs(nXPosNext-nXPos); cnt2++)
                {
                    currMoveent += '^';
                }
            }
            /* Add the movement to all the codes */
            for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
            {
                vnCodes[cnt2] += currMoveent+'A';
            }
        }
        /* If both current x/y and next or x/y are same, it is easy */
        else if (nXPosNext == nXPos)
        {
            /* Choose left arrow or right arrow based on y pos */
            if (nYPosNext > nYPos)
            {
                for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                {
                    currMoveent += '>';
                }
            }
            else
            {
                for (cnt2 = 0; cnt2 < abs(nYPosNext-nYPos); cnt2++)
                {
                    currMoveent += '<';
                }
            }

            /* Add the movement to all the codes */
            for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
            {
                vnCodes[cnt2] += currMoveent+'A';
            }
        }
        /* If the previous x position is 0 */
        else if (nXPos == 0)
        {
            /* If previous y position is 1 */
            if (nYPos == 1)
            {
                /* If next y pos is 0 */
                if (nYPosNext == 0)
                {
                    /* Hardcode the path - practically verified to be smallest */
                    for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                    {
                        vnCodes[cnt2] += "v<A";
                    }
                }
                /* If next y pos is 2 */
                else if (nYPosNext == 2)
                {
                    /* Hardcode the path - practically verified to be smallest */
                    for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                    {
                        vnCodes[cnt2] += "v>A";
                    }
                }
                else
                {
                    /* Error check to debug */
                    cout << "Error position " << __LINE__ << endl;
                    exit(1);
                }
            }
            /* If previous y position is 2 */
            else if (nYPos == 2)
            {
                /* If next y pos is 1 */
                if (nYPosNext == 1)
                {
                    /* Hardcode the path - practically verified to be smallest */
                    for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                    {
                        vnCodes[cnt2] += "<vA";
                    }
                }
                /* If the next y pos is 0 */
                else if (nYPosNext == 0)
                {
                    /* Hardcode the path - practically verified to be smallest */
                    for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                    {
                        vnCodes[cnt2] += "v<<A";
                    }
                }
                else
                {
                    /* Error check to debug */
                    cout << "Error position " << __LINE__ << endl;
                    exit(1);
                }
            }
            else
            {
                cout << "Error position" << endl;
                exit(1);
            }
        }
        /* If the previous x position is 1 */
        else if (nXPos == 1)
        {
            /* If the previous y position is 0 */
            if (nYPos == 0)
            {
                /* If the next y position is 1 */
                if (nYPosNext == 1)
                {
                    /* Hardcode the path - practically verified to be smallest */
                    for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                    {
                        vnCodes[cnt2] += ">^A";
                    }
                }
                /* If the next y position is 2 */
                else if (nYPosNext == 2)
                {
                    /* Hardcode the path - practically verified to be smallest */
                    for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                    {
                        vnCodes[cnt2] += ">>^A";
                    }
                }
                else
                {
                    /* Error check to debug */
                    cout << "Error position " << __LINE__ << endl;
                    exit(1);
                }
            }
            /* If the previous y position is 1 */
            else if (nYPos == 1)
            {
                /* If the next y position is 0 */
                for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                {
                    vnCodes[cnt2] += "^>A";
                }
            }
            /* If the previous y position is 2 */
            else if (nYPos == 2)
            {
                /* If the next y position is 1 */
                if (nYPosNext == 1)
                {
                    /* Hardcode the path - practically verified to be smallest */
                    for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
                    {
                        vnCodes[cnt2] += "<^A";
                    }
                }
                else
                {
                    /* Error check to debug */
                    cout << "Error position " << __LINE__ << endl;
                    exit(1);
                }
            }
            else
            {
                /* Error check to debug */
                cout << "Error position " << __LINE__ << endl;
                exit(1);
            }
        }
        else
        {
            /* Error check to debug */
            cout << "Error position " << __LINE__ << endl;
            exit(1);
        }
        nXPos = nXPosNext;
        nYPos = nYPosNext;
    }

    return vnCodes;
}

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


    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, nRobotIterations = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* Numerical keypad - 0 to 9 and A */
    char anNumKeyPad[4][3] = 
        {
            '7', '8', '9',
            '4', '5', '6',
            '1', '2', '3',
              0, '0', 'A'
        };
    /* Directional keypad - up, down, left and right, and A */
    char anDirKeyPad[2][3] = 
        {
              0, '^', 'A',
            '<', 'v', '>',
        };


    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        string sLine = arr;

        if (sLine[sLine.size()-1] == '\n' || sLine[sLine.size()-1] == '\r')
        {
            sLine.pop_back();
        }
        if (sLine[sLine.size()-1] == '\n' || sLine[sLine.size()-1] == '\r')
        {
            sLine.pop_back();
        }

        /* Read the current line and first process the numerical keys */
        vector<string> vnCodes = processNumKeyCode(sLine, anNumKeyPad);

        /* Set lowest size for both parts to be max integers */
        uint64_t nLowestSizePart1 = LONG_MAX;
        uint64_t nLowestSizePart2 = LONG_MAX;

        /* Use a hash map to store the sequences and its count
         * 
         * Each sequence is made of arrows and A
         * Since all sequencies after A, reset, this would be unique irrespective
         * of the position of its occurrence
         * For example:
         * If we have a sequence ">>A>vA", we could divide this into two sequencies
         * ">>A" and ">vA" and compute the count individually.
         * This hash map would contain the occurrences of each sequence. 
         * Select 1000 as the size of the hash map as we are not sure of the number of
         * sequences that would be generated.
        */
        unordered_map<string, int64_t> umMap[1000];

        /* For all sequences */
        for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
        {
            cnt5 = 0;
            /* Split this into smaller sequences with A in them */
            for (cnt3 = 0; cnt3 < vnCodes[cnt2].size(); cnt3++)
            {
                /* Put them in the hash map and increment the count */
                if (vnCodes[cnt2][cnt3] == 'A')
                {
                    umMap[cnt2][vnCodes[cnt2].substr(cnt5, cnt3-cnt5+1)]++;
                    cnt5 = cnt3+1;
                }
            }
        }

        /* For each robot iterations */
        for (int64_t nRobotIterations = 0; nRobotIterations < 25; nRobotIterations++)
        {
            /* Set the lowest size to max integer */
            uint64_t nLowestSize1 = LONG_MAX;
            uint64_t nLowestSize2 = LONG_MAX;
            /* Store the sequences in a hash map - temp while taking note of
             * the first hash map */
            unordered_map<string, int64_t> umMap2[1000];

            /* For all hash maps */
            for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
            {
                /* Get all subsequences and its count */
                for (auto it = umMap[cnt2].begin(); it != umMap[cnt2].end(); ++it)
                {
                    string sKey = it->first;
                    int64_t nValue = it->second;
                    /* Check the directional key presses for each subsequence */
                    vector<string> vnCodes2 = processDirKeyCode(sKey, anDirKeyPad);
                    /* Ensure that the return of the dir does not have more than 1
                     * option */
                    if (vnCodes2.size() > 1)
                    {
                        cout << "Error position " << __LINE__ << endl;
                        exit(1);
                    }

                    /* Split this into smaller sequences with A in them */
                    cnt7 = 0;
                    for (cnt5 = 0; cnt5 < vnCodes2[0].size(); cnt5++)
                    {
                        /* Put them in the hash map and increment the count 
                         * with the number of occurrences of the first hash map */
                        if (vnCodes2[0][cnt5] == 'A')
                        {
                            umMap2[cnt2][vnCodes2[0].substr(cnt7, cnt5-cnt7+1)] += nValue;
                            cnt7 = cnt5+1;
                        }
                    }
                    
                }
                /* Copy the second hash map into the first */
                umMap[cnt2] = umMap2[cnt2];
            }

            /* Get the least count */
            for (cnt2 = 0; cnt2 < vnCodes.size(); cnt2++)
            {
                uint64_t nCurrSize = 0;
                for (auto it = umMap[cnt2].begin(); it != umMap[cnt2].end(); ++it)
                {
                    nCurrSize += it->second * it->first.size();
                }

                if (nLowestSize2 > nCurrSize)
                {
                    nLowestSize2 = nCurrSize;
                }
            }

            /* For part (a), store the lowest count */
            if (nRobotIterations == 1)
            {
                nLowestSizePart1 = nLowestSize2;
            }

            /* For part (b), store the lowest count */
            nLowestSizePart2 = nLowestSize2;
        }

        string sValue = "";

        /* Extract only the digits from the inputs */
        for (cnt2 = 0; cnt2 < sLine.size(); cnt2++)
        {
            if (sLine[cnt2] >= '0' && sLine[cnt2] <= '9')
            {
                sValue += sLine[cnt2];
            }
        }

        /* Calculate part (a) and (b) sum */
        nFirstPart += (stoll(sValue)*nLowestSizePart1);
        nSecondPart += (stoll(sValue)*nLowestSizePart2);

        /* Increment count */
        ++cnt1;
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

