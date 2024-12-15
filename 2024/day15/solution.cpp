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
    int64_t nStartXPart2 = 0, nStartYPart2 = 0, nStartX = 0, nStartY = 0;

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    string sMovements = "";

    vector<string> vsMap;
    vector<string> vsMapPart2;

    bool bDirectionInput = false;
    bool bStartPosSet = false;

    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        if (strlen(arr) <= 2)
        {
            /* If the current line only has new line character(s), set the next 
             * input as true */
            bDirectionInput = 1;
        }
        else if (bDirectionInput == false)
        {
            string sLine = arr;
            /* Remove new line character(s) */
            if (sLine[sLine.size()-1] == '\n' || sLine[sLine.size()-1] == '\r')
            {
                sLine.pop_back();
            }
            if (sLine[sLine.size()-1] == '\n' || sLine[sLine.size()-1] == '\r')
            {
                sLine.pop_back();
            }
            
            /* If position of @ is not computed, compute it */
            if (nStartX == 0 && nStartY == 0)
            {
                /* Store the position of @ in (X, Y)  */
                if (find(sLine.begin(), sLine.end(), '@') != sLine.end())
                {
                    nStartX = cnt1;
                    nStartY = find(sLine.begin(), sLine.end(), '@') - sLine.begin();
                    sLine[nStartY] = '.';
                    bStartPosSet = true;
                }
            }
            /* Add the line to the map */
            vsMap.push_back(sLine);

            /* Replace the @ back into the string for computing the @ for part (b) */
            if (bStartPosSet == true)
            {
                sLine[nStartY] = '@';
                bStartPosSet = false;
            }

            /* Construct the expanded map for part (b) */
            for (cnt3 = 0; cnt3 < sLine.size(); cnt3++)
            {
                /* If the current block is a '#', replace it with two '#'s */
                if (sLine[cnt3] == '#')
                {
                    sLine.insert(cnt3+1, 1, '#');
                    cnt3++;
                }
                /* If the current block is a '.', replace it with two '.'s */
                else if (sLine[cnt3] == '.')
                {
                    sLine.insert(cnt3+1, 1, '.');
                    cnt3++;
                }
                /* If the current block is a '@', replace it with two '.'s */
                else if (sLine[cnt3] == '@')
                {
                    sLine.insert(cnt3+1, 1, '.');
                    cnt3++;
                }
                /* If the current block is a 'O', replace it with '[', ']' */
                else if (sLine[cnt3] == 'O')
                {
                    sLine[cnt3] = '[';
                    sLine.insert(cnt3+1, 1, ']');
                    cnt3++;
                }
            }

            /* If position of @ is not computed, compute it (Part-b) */
            if (nStartXPart2 == 0 && nStartYPart2 == 0)
            {
                /* Store the position of @ in (X, Y) (Part-b) */
                if (find(sLine.begin(), sLine.end(), '@') != sLine.end())
                {
                    nStartXPart2 = cnt1;
                    nStartYPart2 = find(sLine.begin(), sLine.end(), '@') - sLine.begin();
                    sLine[nStartYPart2] = '.';
                }
            }

            /* Add the line into part(b)'s map */
            vsMapPart2.push_back(sLine);
        }
        else
        {
            /* If the new line character is read, the next set of lines would be 
             * direction instruction */
            sMovements += arr;
            /* Remove new line character(s) */
            if (sMovements[sMovements.size()-1] == '\n' || sMovements[sMovements.size()-1] == '\r')
            {
                sMovements.pop_back();
            }
            if (sMovements[sMovements.size()-1] == '\n' || sMovements[sMovements.size()-1] == '\r')
            {
                sMovements.pop_back();
            }
        }
        /* Increment count */
        ++cnt1;
    }

    /* Part (a) */
    for (cnt1 = 0; cnt1 < sMovements.size(); cnt1++)
    {
        /* For every movement, check if it is <, >, ^ or v */
        if (sMovements[cnt1] == '<')
        {
            /* If the movement is left */ 

            /* If the left element is a block, don't do anything */
            if (vsMap[nStartX][nStartY-1] == '#')
            {
                continue;
            }
            /* If the left element is a dot, just move the start position 
             * left by 1 */
            if (vsMap[nStartX][nStartY-1] == '.')
            {
                nStartY -= 1;
                continue;
            }
            /* If the left element is a box keep moving left until finding a 
             * block or a dot */
            cnt2 = nStartY-1;
            while (vsMap[nStartX][cnt2] != '#' && vsMap[nStartX][cnt2] != '.')
            {
                cnt2--;
            }
            /* If found a block, don't do anything */
            if (vsMap[nStartX][cnt2] == '#')
            {
                continue;
            }
            /* If found a dot */
            nStartY--;
            /* Replace the current position by a dot */
            vsMap[nStartX][nStartY] = '.';

            /* Replace all the spaced between start and dot by boxes */
            for (cnt3 = nStartY-1; cnt3 >= cnt2; cnt3--)
            {
                vsMap[nStartX][cnt3] = 'O';
            }
        }
        else if (sMovements[cnt1] == '^')
        {
            /* If the movement is up */

            /* If the up element is a block, don't do anything */
            if (vsMap[nStartX-1][nStartY] == '#')
            {
                continue;
            }
            /* If the up element is a dot, just move the start position 
             * up by 1 */
            if (vsMap[nStartX-1][nStartY] == '.')
            {
                nStartX -= 1;
                continue;
            }
            /* If the up element is a box keep moving up until finding a 
             * block or a dot */
            cnt2 = nStartX-1;
            while (vsMap[cnt2][nStartY] != '#' && vsMap[cnt2][nStartY] != '.')
            {
                cnt2--;
            }
            /* If found a block, don't do anything */
            if (vsMap[cnt2][nStartY] == '#')
            {
                continue;
            }
            /* If found a dot */
            nStartX--;
            /* Replace the current position by a dot */
            vsMap[nStartX][nStartY] = '.';
            /* Replace all the spaced between start and dot by boxes */
            for (cnt3 = nStartX-1; cnt3 >= cnt2; cnt3--)
            {
                vsMap[cnt3][nStartY] = 'O';
            }
        }
        else if (sMovements[cnt1] == '>')
        {
            /* If the movement is right */

            /* If the right element is a block, don't do anything */
            if (vsMap[nStartX][nStartY+1] == '#')
            {
                continue;
            }
            /* If the right element is a dot, just move the start position 
             * right by 1 */
            if (vsMap[nStartX][nStartY+1] == '.')
            {
                nStartY += 1;
                continue;
            }
            /* If the right element is a box keep moving right until finding a 
             * block or a dot */
            cnt2 = nStartY+1;
            while (vsMap[nStartX][cnt2] != '#' && vsMap[nStartX][cnt2] != '.')
            {
                cnt2++;
            }
            /* If found a block, don't do anything */
            if (vsMap[nStartX][cnt2] == '#')
            {
                continue;
            }
            /* If found a dot */
            nStartY++;
            /* Replace the current position by a dot */
            vsMap[nStartX][nStartY] = '.';
            /* Replace all the spaced between start and dot by boxes */
            for (cnt3 = nStartY+1; cnt3 <= cnt2; cnt3++)
            {
                vsMap[nStartX][cnt3] = 'O';
            }
        }
        else if (sMovements[cnt1] == 'v')
        {
            /* If the movement is down */

            /* If the down element is a block, don't do anything */
            if (vsMap[nStartX+1][nStartY] == '#')
            {
                continue;
            }
            /* If the down element is a dot, just move the start position 
             * down by 1 */
            if (vsMap[nStartX+1][nStartY] == '.')
            {
                nStartX += 1;
                continue;
            }
            /* If the down element is a box keep moving down until finding a 
             * block or a dot */
            cnt2 = nStartX+1;
            while (vsMap[cnt2][nStartY] != '#' && vsMap[cnt2][nStartY] != '.')
            {
                cnt2++;
            }
            /* If found a block, don't do anything */
            if (vsMap[cnt2][nStartY] == '#')
            {
                continue;
            }
            /* If found a dot */
            nStartX++;
            /* Replace the current position by a dot */
            vsMap[nStartX][nStartY] = '.';
            /* Replace all the spaced between start and dot by boxes */
            for (cnt3 = nStartX+1; cnt3 <= cnt2; cnt3++)
            {
                vsMap[cnt3][nStartY] = 'O';
            }
        }
    }

    /* Compute the GPS for each box given by 100x + y */
    for (cnt1 = 0; cnt1 < vsMap.size(); cnt1++)
    {
        for (cnt2 = 0; cnt2 < vsMap[cnt1].size(); cnt2++)
        {
            /* Sum all the GPS values for the boxes */
            if (vsMap[cnt1][cnt2] == 'O')
            {
                nFirstPart += cnt1 * 100 + cnt2;
            }
        }
    }


    /* Part (b) */
    for (cnt1 = 0; cnt1 < sMovements.size(); cnt1++)
    {
        /* For every movement, check if it is <, >, ^ or v */
        if (sMovements[cnt1] == '<')
        {
            /* If the movement is left */ 

            /* If the left element is a block, don't do anything */
            if (vsMapPart2[nStartXPart2][nStartYPart2-1] == '#')
            {
                continue;
            }
            /* If the left element is a dot, just move the start position 
             * left by 1 */
            if (vsMapPart2[nStartXPart2][nStartYPart2-1] == '.')
            {
                nStartYPart2 -= 1;
                continue;
            }
            /* If the left element is a box keep moving left until finding a 
             * block or a dot */
            cnt2 = nStartYPart2-1;
            while (vsMapPart2[nStartXPart2][cnt2] != '#' && vsMapPart2[nStartXPart2][cnt2] != '.')
            {
                cnt2--;
            }
            /* If found a block, don't do anything */
            if (vsMapPart2[nStartXPart2][cnt2] == '#')
            {
                continue;
            }
            /* If found a dot */
            nStartYPart2--;

            /* Move all the boxes by one position to the left */
            for (cnt3 = cnt2; cnt3 < nStartYPart2; cnt3++)
            {
                vsMapPart2[nStartXPart2][cnt3] = vsMapPart2[nStartXPart2][cnt3+1];
            }

            /* Replace the current position by a dot */
            vsMapPart2[nStartXPart2][nStartYPart2] = '.';
        }
        else if (sMovements[cnt1] == '^')
        {
            /* If the movement is up */

            /* If the up element is a block, don't do anything */
            if (vsMapPart2[nStartXPart2-1][nStartYPart2] == '#')
            {
                continue;
            }
            /* If the up element is a dot, just move the start position 
             * up by 1 */
            if (vsMapPart2[nStartXPart2-1][nStartYPart2] == '.')
            {
                nStartXPart2 -= 1;
                continue;
            }

            /* Create a queue with x, y pair for assessing the boxes */
            queue<pair<int64_t, int64_t>> qBoxes;
            /* Store all the assessed boxes into a vector as well */
            vector<pair<int64_t, int64_t>> vBoxes;

            /* Add the position up from the current position into the queue */
            qBoxes.push(make_pair(nStartXPart2-1, nStartYPart2));
            /* Add the same into the vector as well */
            vBoxes.push_back(make_pair(nStartXPart2-1, nStartYPart2));

            /* If the current up box is a [, also add the corresponding ] */
            if (vsMapPart2[nStartXPart2-1][nStartYPart2] == '[')
            {
                /* Into both the queue and the vector */
                qBoxes.push(make_pair(nStartXPart2-1, nStartYPart2+1));
                vBoxes.push_back(make_pair(nStartXPart2-1, nStartYPart2+1));
            }
            /* If the current up box is a ], also add the corresponding [ */
            else
            {
                /* Into both the queue and the vector */
                qBoxes.push(make_pair(nStartXPart2-1, nStartYPart2-1));
                vBoxes.push_back(make_pair(nStartXPart2-1, nStartYPart2-1));
            }
            /* A flag to check if the movement is possible */
            bool bPossible = true;

            /* Process all boxes, add boxes there are still boxes that are 
             * touching the box above */
            while (!qBoxes.empty())
            {
                /* Process the current box */
                pair<int64_t, int64_t> pBox = qBoxes.front();
                qBoxes.pop();

                /* If the box just above is a block, do not process anything
                 * Skip it */
                if (vsMapPart2[pBox.first-1][pBox.second] == '#')
                {
                    bPossible = false;
                    break;
                }

                /* Else if there is another box, add that as well into the 
                 * queue and vector */
                if (vsMapPart2[pBox.first-1][pBox.second] == '[')
                {
                    qBoxes.push(make_pair(pBox.first-1, pBox.second));
                    qBoxes.push(make_pair(pBox.first-1, pBox.second+1));
                    vBoxes.push_back(make_pair(pBox.first-1, pBox.second));
                    vBoxes.push_back(make_pair(pBox.first-1, pBox.second+1));
                }
                else if (vsMapPart2[pBox.first-1][pBox.second] == ']')
                {
                    qBoxes.push(make_pair(pBox.first-1, pBox.second));
                    qBoxes.push(make_pair(pBox.first-1, pBox.second-1));
                    vBoxes.push_back(make_pair(pBox.first-1, pBox.second));
                    vBoxes.push_back(make_pair(pBox.first-1, pBox.second-1));
                }
            }
            /* If it is not possible to move the boxes, do not move */
            if (bPossible == false)
            {
                continue;
            }
            /* Else, do the movement */
            nStartXPart2 -= 1;

            /* Remove duplicate boxes for procssing from the vector of boxes */
            for (cnt2 = 0; cnt2 < vBoxes.size(); cnt2++)
            {
                for (cnt3 = cnt2+1; cnt3 < vBoxes.size(); cnt3++)
                {
                    if (vBoxes[cnt2].first == vBoxes[cnt3].first && vBoxes[cnt2].second == vBoxes[cnt3].second)
                    {
                        vBoxes.erase(vBoxes.begin()+cnt3);
                        cnt3--;
                    }
                }
            }

            /* For all boxes in the list */
            while (vBoxes.size() > 0)
            {
                /* Start movement from the top */
                /* Find the lowest value of X */
                int64_t nLowestX = INT_MAX;
                for (cnt3 = 0; cnt3 < vBoxes.size(); cnt3++)
                {
                    if (vBoxes[cnt3].first < nLowestX)
                    {
                        nLowestX = vBoxes[cnt3].first;
                    }
                }
                /* Move all the lowest value up by 1 */
                for (cnt3 = 0; cnt3 < vBoxes.size(); cnt3++)
                {
                    if (vBoxes[cnt3].first == nLowestX)
                    {
                        vsMapPart2[vBoxes[cnt3].first-1][vBoxes[cnt3].second] = vsMapPart2[vBoxes[cnt3].first][vBoxes[cnt3].second];
                        vsMapPart2[vBoxes[cnt3].first][vBoxes[cnt3].second] = '.';
                        /* Delete from the vector */
                        vBoxes.erase(vBoxes.begin()+cnt3);
                        cnt3--;
                    }
                }
            }
        }
        else if (sMovements[cnt1] == '>')
        {
            /* If the movement is right */

            /* If the right element is a block, don't do anything */
            if (vsMapPart2[nStartXPart2][nStartYPart2+1] == '#')
            {
                continue;
            }
            /* If the right element is a dot, just move the start position 
             * right by 1 */
            if (vsMapPart2[nStartXPart2][nStartYPart2+1] == '.')
            {
                nStartYPart2 += 1;
                continue;
            }
            /* If the right element is a box keep moving right until finding a 
             * block or a dot */
            cnt2 = nStartYPart2+1;
            while (vsMapPart2[nStartXPart2][cnt2] != '#' && vsMapPart2[nStartXPart2][cnt2] != '.')
            {
                cnt2++;
            }
            /* If found a block, don't do anything */
            if (vsMapPart2[nStartXPart2][cnt2] == '#')
            {
                continue;
            }
            /* If found a dot */
            nStartYPart2++;

            /* Move all the boxes by one position to the right */
            for (cnt3 = cnt2; cnt3 >= nStartYPart2+1; cnt3--)
            {
                vsMapPart2[nStartXPart2][cnt3] = vsMapPart2[nStartXPart2][cnt3-1];
            }
            /* Replace the current position by a dot */
            vsMapPart2[nStartXPart2][nStartYPart2] = '.';
        }
        else if (sMovements[cnt1] == 'v')
        {
            /* If the movement is down */

            /* If the down element is a block, don't do anything */
            if (vsMapPart2[nStartXPart2+1][nStartYPart2] == '#')
            {
                continue;
            }
            /* If the down element is a dot, just move the start position 
             * down by 1 */
            if (vsMapPart2[nStartXPart2+1][nStartYPart2] == '.')
            {
                nStartXPart2 += 1;
                continue;
            }

            /* Create a queue with x, y pair for assessing the boxes */
            queue<pair<int64_t, int64_t>> qBoxes;
            /* Store all the assessed boxes into a vector as well */
            vector<pair<int64_t, int64_t>> vBoxes;

            /* Add the position down from the current position into the queue */
            qBoxes.push(make_pair(nStartXPart2+1, nStartYPart2));
            /* Add the same into the vector as well */
            vBoxes.push_back(make_pair(nStartXPart2+1, nStartYPart2));

            /* If the current down box is a [, also add the corresponding ] */
            if (vsMapPart2[nStartXPart2+1][nStartYPart2] == '[')
            {
                qBoxes.push(make_pair(nStartXPart2+1, nStartYPart2+1));
                vBoxes.push_back(make_pair(nStartXPart2+1, nStartYPart2+1));
            }
            /* If the current down box is a ], also add the corresponding [ */
            else
            {
                qBoxes.push(make_pair(nStartXPart2+1, nStartYPart2-1));
                vBoxes.push_back(make_pair(nStartXPart2+1, nStartYPart2-1));
            }
            /* A flag to check if the movement is possible */
            bool bPossible = true;

            /* Process all boxes, add boxes there are still boxes that are 
             * touching the box below */
            while (!qBoxes.empty())
            {
                /* Process the current box */
                pair<int64_t, int64_t> pBox = qBoxes.front();
                qBoxes.pop();

                /* If the box just below is a block, do not process anything
                 * Skip it */
                if (vsMapPart2[pBox.first+1][pBox.second] == '#')
                {
                    bPossible = false;
                    break;
                }

                /* Else if there is another box, add that as well into the 
                 * queue and vector */
                if (vsMapPart2[pBox.first+1][pBox.second] == '[')
                {
                    qBoxes.push(make_pair(pBox.first+1, pBox.second));
                    qBoxes.push(make_pair(pBox.first+1, pBox.second+1));
                    vBoxes.push_back(make_pair(pBox.first+1, pBox.second));
                    vBoxes.push_back(make_pair(pBox.first+1, pBox.second+1));
                }
                else if (vsMapPart2[pBox.first+1][pBox.second] == ']')
                {
                    qBoxes.push(make_pair(pBox.first+1, pBox.second));
                    qBoxes.push(make_pair(pBox.first+1, pBox.second-1));
                    vBoxes.push_back(make_pair(pBox.first+1, pBox.second));
                    vBoxes.push_back(make_pair(pBox.first+1, pBox.second-1));
                }
            }

            /* If it is not possible to move the boxes, do not move */
            if (bPossible == false)
            {
                continue;
            }
            /* Else, do the movement */
            nStartXPart2 += 1;

            /* Remove duplicate boxes */
            for (cnt2 = 0; cnt2 < vBoxes.size(); cnt2++)
            {
                for (cnt3 = cnt2+1; cnt3 < vBoxes.size(); cnt3++)
                {
                    if (vBoxes[cnt2].first == vBoxes[cnt3].first && vBoxes[cnt2].second == vBoxes[cnt3].second)
                    {
                        vBoxes.erase(vBoxes.begin()+cnt3);
                        cnt3--;
                    }
                }
            }

            /* For all boxes in the list */
            while (vBoxes.size() > 0)
            {
                /* Start movement from the bottom */

                /* Find the lowest value of X */
                int64_t nLowestX = INT_MIN;
                for (cnt3 = 0; cnt3 < vBoxes.size(); cnt3++)
                {
                    if (vBoxes[cnt3].first > nLowestX)
                    {
                        nLowestX = vBoxes[cnt3].first;
                    }
                }
                /* Move all the lowest value up by 1 */
                for (cnt3 = 0; cnt3 < vBoxes.size(); cnt3++)
                {
                    if (vBoxes[cnt3].first == nLowestX)
                    {
                        vsMapPart2[vBoxes[cnt3].first+1][vBoxes[cnt3].second] = vsMapPart2[vBoxes[cnt3].first][vBoxes[cnt3].second];
                        vsMapPart2[vBoxes[cnt3].first][vBoxes[cnt3].second] = '.';
                        /* Delete from the vector */
                        vBoxes.erase(vBoxes.begin()+cnt3);
                        cnt3--;
                    }
                }
            }
        }
    }

    /* Compute the GPS for each box given by 100x + y */
    for (cnt1 = 0; cnt1 < vsMapPart2.size(); cnt1++)
    {
        for (cnt2 = 0; cnt2 < vsMapPart2[cnt1].size(); cnt2++)
        {
            /* Sum all the GPS values for the boxes only for a '[' */
            if (vsMapPart2[cnt1][cnt2] == '[')
            {
                nSecondPart += cnt1 * 100 + cnt2;
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

