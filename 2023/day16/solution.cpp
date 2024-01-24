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

/* Input layout */
vector <string> layout;
/* Movement of the beam, #'s if present, else .'s */
vector <string> beamMove;
/* Stores all direction of the beam entered in each cell */
vector <int64_t> beamDirs[1000];

/* Moves the beam next and updates the global beanMove vector */ 
void beamMovementNext(int64_t nIdx1, int64_t nIdx2, int64_t nDir);


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

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        string sInpLine = arr[cnt1];

        /* Remove the last '\n' */
        if (sInpLine[sInpLine.size()-1] == '\n' || sInpLine[sInpLine.size()-1] == '\r')
        {
            sInpLine.pop_back();
        }
        if (sInpLine[sInpLine.size()-1] == '\n' || sInpLine[sInpLine.size()-1] == '\r')
        {
            sInpLine.pop_back();
        }

        /* Store the input line in layout's row */
        layout.push_back(sInpLine);

        beamMove.push_back("");
        /* In beamMove, store line length of dots in each line */
        for (cnt2 = 0; cnt2 < layout[0].size(); cnt2++)
        {
            beamMove[beamMove.size()-1].push_back('.');
            /* Store the direction to be zero, since no direction has been visited */
            beamDirs[cnt1].push_back(0);
        }
        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Part 1 - Move the beam from (0, 0) position and to the right (1) */
    beamMovementNext(0, 0, 1);
    nPartOneSum = 0;

    for (cnt2 = 0; cnt2 < layout.size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < layout[0].size(); cnt3++)
        {
            /* Count the number of hashes in the beam and replace them with 
             * dots after counting */
            if (beamMove[cnt2][cnt3] == '#')
            {
                nPartOneSum++;
            }
            beamMove[cnt2][cnt3] = '.';
            /* Reset directions to zero again */
            beamDirs[cnt2][cnt3] = 0;
        }
    }

    /* Start with the top, move the beam downward, i.e., 2 */
    for (cnt1 = 0; cnt1 < layout[0].size(); cnt1++)
    {
        beamMovementNext(0, cnt1, 2);
        /* Count each time after moving the beam */
        cnt7 = 0;
        for (cnt2 = 0; cnt2 < layout.size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < layout[0].size(); cnt3++)
            {
                /* Count the number of hashes in the beam and replace them with 
                 * dots after counting */
                if (beamMove[cnt2][cnt3] == '#')
                {
                    cnt7++;
                }
                beamMove[cnt2][cnt3] = '.';
                /* Reset directions to zero again */
                beamDirs[cnt2][cnt3] = 0;
            }
        }
        /* Get the maximum value into part two sum */
        if (nPartTwoSum < cnt7)
        {
            nPartTwoSum = cnt7;
        }
    }
    /* Start with the bottom, move the beam upward, i.e., 0 */
    for (cnt1 = 0; cnt1 < layout[0].size(); cnt1++)
    {
        beamMovementNext(layout.size()-1, cnt1, 0);
        /* Count each time after moving the beam */
        cnt7 = 0;
        for (cnt2 = 0; cnt2 < layout.size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < layout[0].size(); cnt3++)
            {
                /* Count the number of hashes in the beam and replace them with 
                 * dots after counting */
                if (beamMove[cnt2][cnt3] == '#')
                {
                    cnt7++;
                }
                beamMove[cnt2][cnt3] = '.';
                /* Reset directions to zero again */
                beamDirs[cnt2][cnt3] = 0;
            }
        }
        /* Get the maximum value into part two sum */
        if (nPartTwoSum < cnt7)
        {
            nPartTwoSum = cnt7;
        }
    }
    /* Start with left, move the beam right, i.e., 1 */
    for (cnt1 = 0; cnt1 < layout.size(); cnt1++)
    {
        beamMovementNext(cnt1, 0, 1);
        /* Count each time after moving the beam */
        cnt7 = 0;
        for (cnt2 = 0; cnt2 < layout.size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < layout[0].size(); cnt3++)
            {
                /* Count the number of hashes in the beam and replace them with 
                 * dots after counting */
                if (beamMove[cnt2][cnt3] == '#')
                {
                    cnt7++;
                }
                beamMove[cnt2][cnt3] = '.';
                /* Reset directions to zero again */
                beamDirs[cnt2][cnt3] = 0;
            }
        }
        /* Get the maximum value into part two sum */
        if (nPartTwoSum < cnt7)
        {
            nPartTwoSum = cnt7;
        }
    }
    /* Start with right, move the beam left, i.e., 3 */
    for (cnt1 = 0; cnt1 < layout.size(); cnt1++)
    {
        beamMovementNext(cnt1, layout[0].size()-1, 3);
        /* Count each time after moving the beam */
        cnt7 = 0;
        for (cnt2 = 0; cnt2 < layout.size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < layout[0].size(); cnt3++)
            {
                /* Count the number of hashes in the beam and replace them with 
                 * dots after counting */
                if (beamMove[cnt2][cnt3] == '#')
                {
                    cnt7++;
                }
                beamMove[cnt2][cnt3] = '.';
                /* Reset directions to zero again */
                beamDirs[cnt2][cnt3] = 0;
            }
        }
        /* Get the maximum value into part two sum */
        if (nPartTwoSum < cnt7)
        {
            nPartTwoSum = cnt7;
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

/* Keep moving the beam recursively until reaching itself back again 
 * nIdx1 - Row index 
 * nIdx2 - Column index
 * nDIr  - Direction (0, 1, 2, 3) => (top, right, bottom, left)*/
void beamMovementNext(int64_t nIdx1, int64_t nIdx2, int64_t nDir)
{
    int64_t cnt1;
    int64_t cnt2;
    int64_t cnt3;
    while (true)
    {
        /* If the beam has already entered the same input and with the same 
         * direction, then break out of the loop 
         * For direction, check if the required direction bit is set */
        if (beamMove[nIdx1][nIdx2] == '#' && ((beamDirs[nIdx1][nIdx2] & (1 << nDir)) != 0))
        {
            break;
        }
        /* If not, set the direction bit and movement cell */
        beamMove[nIdx1][nIdx2] = '#';
        beamDirs[nIdx1][nIdx2] |= 1 << nDir;

        /* If the current direction is top (zero) */
        if (nDir == 0)
        {
            /* If the beam can still keep moving up and the layout allows it */
            if (nIdx1 > 0 && (layout[nIdx1][nIdx2] == '.' || layout[nIdx1][nIdx2] == '|'))
            {
                --nIdx1;
            }
            /* If the layout splits the beam into two */
            else if (layout[nIdx1][nIdx2] == '-')
            {
                /* If both splits are possible, one beam moving left, continue 
                 * in loop and the right beam, call the same function again */
                if (nIdx2 > 0 && nIdx2 < layout[0].size()-1)
                {
                    nIdx2--;
                    nDir = 3;
                    beamMovementNext(nIdx1, nIdx2+1, 1);
                }
                /* If only right beam split is possible, keep moving right in 
                 * loop - do not call recursive function */
                else if (nIdx2 > 0)
                {
                    nIdx2--;
                    nDir = 3;
                }
                /* If only left beam split is possible, keep moving left in 
                 * loop - do not call recursive function */
                else if (nIdx2 < layout[0].size()-1)
                {
                    nIdx2++;
                    nDir = 1;
                }
                /* If nothing is possible, break */
                else
                {
                    break;
                }
            }
            /* If the layout diverts the beam into different direction */
            else if (layout[nIdx1][nIdx2] == '/')
            {
                /* If movement is possible, keep moving */
                if (nIdx2 < layout[0].size()-1)
                {
                    nDir = 1;
                    nIdx2++;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If the layout diverts the beam into different direction */
            else if (layout[nIdx1][nIdx2] == '\\')
            {
                /* If movement is possible, keep moving */
                if (nIdx2 > 0)
                {
                    nDir = 3;
                    nIdx2--;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If not, break */
            else
            {
                break;
            }
        }
        /* If the current direction is right (one) */
        else if (nDir == 1)
        {
            /* If the beam can still keep moving right and the layout allows it */
            if (nIdx2 < layout[0].size()-1 && (layout[nIdx1][nIdx2] == '.' || layout[nIdx1][nIdx2] == '-'))
            {
                nIdx2++;
            }
            /* If the layout splits the beam into two */
            else if (layout[nIdx1][nIdx2] == '|')
            {
                /* If both splits are possible, one beam moving up, continue 
                 * in loop and for the bottom beam, call the same function again */
                if (nIdx1 > 0 && nIdx1 < layout.size()-1)
                {
                    nIdx1--;
                    nDir = 0;
                    beamMovementNext(nIdx1+1, nIdx2, 2);
                }
                /* If only up beam split is possible, keep moving up in 
                 * loop - do not call recursive function */
                else if (nIdx1 > 0)
                {
                    nIdx1--;
                    nDir = 0;
                }
                /* If only down beam split is possible, keep moving down in 
                 * loop - do not call recursive function */
                else if (nIdx1 < layout.size()-1)
                {
                    nIdx1++;
                    nDir = 2;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If the layout diverts the beam into different direction */
            else if (layout[nIdx1][nIdx2] == '/')
            {
                /* If movement is possible, keep moving */
                if (nIdx1 > 0)
                {
                    nDir = 0;
                    nIdx1--;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If the layout diverts the beam into different direction */
            else if (layout[nIdx1][nIdx2] == '\\')
            {
                /* If movement is possible, keep moving */
                if (nIdx1 < layout.size()-1)
                {
                    nDir = 2;
                    nIdx1++;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If not, break */
            else
            {
                break;
            }
        }
        /* If the current direction is bottom (two) */
        else if (nDir == 2)
        {
            /* If the beam can still keep moving down and the layout allows it */
            if (nIdx1 < layout.size()-1 && (layout[nIdx1][nIdx2] == '.' || layout[nIdx1][nIdx2] == '|'))
            {
                nIdx1++;
            }
            /* If the layout splits the beam into two */
            else if (layout[nIdx1][nIdx2] == '-')
            {
                /* If both splits are possible, one beam moving left, continue 
                 * in loop and for the right beam, call the same function again */
                if (nIdx2 > 0 && nIdx2 < layout[0].size()-1)
                {
                    nIdx2--;
                    nDir = 3;
                    beamMovementNext(nIdx1, nIdx2+1, 1);
                }
                /* If only left beam split is possible, keep moving left in 
                 * loop - do not call recursive function */
                else if (nIdx2 > 0)
                {
                    nIdx2--;
                    nDir = 3;
                }
                /* If only right beam split is possible, keep moving right in 
                 * loop - do not call recursive function */
                else if (nIdx2 < layout[0].size()-1)
                {
                    nIdx2++;
                    nDir = 1;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If the layout diverts the beam into different direction */
            else if (layout[nIdx1][nIdx2] == '/')
            {
                /* If movement is possible, keep moving */
                if (nIdx2 > 0)
                {
                    nIdx2--;
                    nDir = 3;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If the layout diverts the beam into different direction */
            else if (layout[nIdx1][nIdx2] == '\\')
            {
                /* If movement is possible, keep moving */
                if (nIdx2 < layout[0].size()-1)
                {
                    nDir = 1;
                    nIdx2++;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        /* If the current direction is left (three) */
        else if (nDir == 3)
        {
            /* If the beam can still keep moving left and the layout allows it */
            if (nIdx2 > 0 && (layout[nIdx1][nIdx2] == '.' || layout[nIdx1][nIdx2] == '-'))
            {
                nIdx2--;
            }
            /* If the layout splits the beam into two */
            else if (layout[nIdx1][nIdx2] == '|')
            {
                /* If both splits are possible, one beam moving up, continue 
                 * in loop and for the down beam, call the same function again */
                if (nIdx1 > 0 && nIdx1 < layout.size()-1)
                {
                    nIdx1--;
                    nDir = 0;
                    beamMovementNext(nIdx1+1, nIdx2, 2);
                }
                /* If only top beam split is possible, keep moving up in 
                 * loop - do not call recursive function */
                else if (nIdx1 > 0)
                {
                    nIdx1--;
                    nDir = 0;
                }
                /* If only bottom beam split is possible, keep moving down in 
                 * loop - do not call recursive function */
                else if (nIdx1 < layout.size()-1)
                {
                    nIdx1++;
                    nDir = 2;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If the layout diverts the beam into different direction */
            else if (layout[nIdx1][nIdx2] == '/')
            {
                /* If movement is possible, keep moving */
                if (nIdx1 < layout.size()-1)
                {
                    nDir = 2;
                    nIdx1++;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If the layout diverts the beam into different direction */
            else if (layout[nIdx1][nIdx2] == '\\')
            {
                /* If movement is possible, keep moving */
                if (nIdx1 > 0)
                {
                    nDir = 0;
                    nIdx1--;
                }
                /* If not, break */
                else
                {
                    break;
                }
            }
            /* If not, break */
            else
            {
                break;
            }
        }
        /* If not, break */
        else
        {
            break;
        }
    }
}

