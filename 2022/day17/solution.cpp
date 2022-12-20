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
char fallblock_file[] = "fall-block.txt";

char arr[100][20000];

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen(fallblock_file, "r");

    if (fp == NULL)
    {
        cout << "Error. Unable to open file, \"" << fallblock_file << "\"" << endl;
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

    /* Get each fall-block into an array of strings */
    vector <string> nFallBlocks[10];

    /* Design the chamber using a hash-map for faster access
     * Values of (X, Y) accessed as (7*Y + X) */
    unordered_map<int64_t, int8_t> nChamber;

    /* Read every line of fall-block.txt file */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        /* If found an empty line, increment the number of blocks */
        if (strlen(arr[cnt1]) < 2)
        {
            cnt2++;
        }
        else
        {
            /* If the last character is a new-line character, remove it from
             * the blocks */
            string strTmp = arr[cnt1];
            if (strTmp[strTmp.size()-1] == '\n')
            {
                strTmp.pop_back();
            }
            /* Add the current line into the new block's new line */
            nFallBlocks[cnt2].push_back(strTmp);
        }
        ++cnt1;
    }
    /* To include the last block */
    cnt2++;

    /* Close this file and open the input file */
    fclose(fp);

    fp = fopen(input_file, "r");
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

    /* Just read one line from the current file and close the file */
    fgets(arr[cnt1], sizeof(arr[0]), fp);

    fclose(fp);

    /* Store this left right info into a string for easy access */
    string leftRightStr = arr[cnt1];
    /* If the current line has a new-line at the end, strip the new-line */
    if (leftRightStr[leftRightStr.size()-1] == '\n')
    {
        leftRightStr.pop_back();
    }

    /* Left-right index (< or >) */
    int64_t nLeftRightIdx = 0;
    /* Current block number */
    int64_t nCurrBlock = 0;

    /* Block index containing the (X, Y) of the block that has "#" */
    vector <int64_t> nBlockIdx[2];
    /* (X, Y) of all blocks that contains "#" */
    vector <int64_t> nBlocksIdx[10][2];
    /* Size of each block */
    vector <int64_t> nBlocksSize;
    /* Maximum height of chamber */
    int64_t nChamberHeight = 0;
    /* Increment to chamber height after seeing a patern */
    int64_t nChambHeightInc = 0;
    /* Previous chamber height */
    int64_t nPrevChambHeight = 0;
    /* Difference between chamber heights */
    int64_t nChambDiff = 0;
    /* Difference between curr block and prev block indices */
    int64_t nBlockDiff = 0;
    /* Index of previous block */
    int64_t nPrevBlock = 0;

    /* Set the starting 0'th height position of chamber to blocked */
    for (cnt3 = 0; cnt3 < 7; cnt3++)
    {
        nChamber[cnt3] = 1;
    }

    /* Store the co-ordinates (X, Y) of all blocks that have "#" */
    /* Iterate through all blocks */
    for (cnt6 = 0; cnt6 < cnt2; cnt6++)
    {
        /* Iterate each block through each Y value */
        for (cnt4 = nFallBlocks[cnt6].size()-1; cnt4 >= 0; cnt4--)
        {
            /* Iterate each block's X value */
            for (cnt5 = 0; cnt5 < (int64_t)nFallBlocks[cnt6][cnt4].size(); cnt5++)
            {
                /* If found "#", store its corresponding (X, Y) into blocks-Idx */
                if (nFallBlocks[cnt6][cnt4][cnt5] == '#')
                {
                    /* Store the value of X+2 as the blocks start with offset */
                    nBlocksIdx[cnt6][0].push_back(cnt5+2);
                    /* Store the value of Y in reversed otder as the blocks with
                     * lowest number is on top. Add offset of 4 as they start with
                     * 4 more than the height of the chamber */
                    nBlocksIdx[cnt6][1].push_back(nFallBlocks[cnt6].size() - cnt4 - 1 + 4);
                }
            }
        }
        /* Store the length of total "#"'s */
        nBlocksSize.push_back(nBlocksIdx[cnt6][0].size());
    }

    int64_t nTotalBlocks = 2022;

    /* Iterate for a total of 2022 values */
    for (cnt3 = 0; cnt3 < nTotalBlocks; cnt3++)
    {
        /* Clear the current analysis block */
        nBlockIdx[0].clear();
        nBlockIdx[1].clear();

        /* Store the co-ordinates of the analysis block from the nBlocksIdx */
        for (cnt4 = 0; cnt4 < nBlocksSize[nCurrBlock]; cnt4++)
        {
            nBlockIdx[0].push_back(nBlocksIdx[nCurrBlock][0][cnt4]);
            /* Increment the chamber height in the Y co-ordinate */
            nBlockIdx[1].push_back(nBlocksIdx[nCurrBlock][1][cnt4] + nChamberHeight);
        }

        /* Collect the number of co-ordinates */
        int64_t nBlockIdx0Size = nBlockIdx[0].size();
        cnt6 = 1;

        int64_t nMaxRightXValue = *max_element(nBlockIdx[0].begin(), nBlockIdx[0].end());
        int64_t nMaxLeftXValue = *min_element(nBlockIdx[0].begin(), nBlockIdx[0].end());

        /* Iterate until the blocks cannot move */
        while (cnt6 > 0)
        {
            cnt6 = 0;
            /* If seeing a ">", move the blocks to the right if possible */
            if (leftRightStr[nLeftRightIdx] == '>')
            {
                /* Get the value of maximum X index to check if the it could
                 * be moved to the right */
                if (nMaxRightXValue < 6)
                {
                    /* if it could be moved to the right, check if there is no
                     * block in the chamber obstructing it */
                    for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                    {
                        if (nChamber[(7 * nBlockIdx[1][cnt4]) + (nBlockIdx[0][cnt4] + 1)] == 1)
                        {
                            break;
                        }
                    }
                    /* If there is no block obstructing it, move all the blocks
                     * to the right */
                    if (cnt4 == nBlockIdx0Size)
                    {
                        for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                        {
                            nBlockIdx[0][cnt4] = nBlockIdx[0][cnt4] + 1;
                        }
                        /* Increment the value of right and left maximums as
                         * the whole block has right shifted */
                        nMaxRightXValue++;
                        nMaxLeftXValue++;
                    }
                }
            }
            /* If seeing a "<", move the blocks to the left if possible */
            else
            {
                /* Get the value of minimum X index to check if the it could
                 * be moved to the left */
                if (nMaxLeftXValue > 0)
                {
                    /* if it could be moved to the left, check if there is no
                     * block in the chamber obstructing it */
                    for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                    {
                        if (nChamber[(7 * nBlockIdx[1][cnt4]) + (nBlockIdx[0][cnt4] - 1)] == 1)
                        {
                            break;
                        }
                    }
                    /* If there is no block obstructing it, move all the blocks
                     * to the left */
                    if (cnt4 == nBlockIdx0Size)
                    {
                        for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                        {
                            nBlockIdx[0][cnt4] = nBlockIdx[0][cnt4] - 1;
                        }
                        /* Decrement the value of right and left maximums as
                         * the whole block has left shifted */
                        nMaxLeftXValue--;
                        nMaxRightXValue--;
                    }
                }
            }

            /* Now try to move all the blocks one step down */
            for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
            {
                /* If there is a block obstructing it do not move it down */
                if (nBlockIdx[1][cnt4] > 0 && (nChamber[(7*(nBlockIdx[1][cnt4]-1)) + nBlockIdx[0][cnt4]] == 1))
                {
                    break;
                }
            }
            /* If there is no block in chamber obstructing it, move the entire
             * block one step down */
            if (cnt4 == nBlockIdx0Size)
            {
                for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                {
                    nBlockIdx[1][cnt4] = nBlockIdx[1][cnt4] - 1;
                }
                cnt6++;
            }

            /* Wrap around the left right string index if overflown
             * nLeftRightIdx = (nLeftRightIdx + 1) MOD leftRightStr.size() */
            nLeftRightIdx++;
            if (nLeftRightIdx >= (int64_t)leftRightStr.size())
            {
                nLeftRightIdx -= leftRightStr.size();
            }
        }

        /* Block the value of the index in chamber that the block is currently at */
        for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
        {
            nChamber[(7 * nBlockIdx[1][cnt4]) + (nBlockIdx[0][cnt4])] = 1;
        }
        /* Increment the block number, wrap around the total blocks if exceeding */
        nCurrBlock++;
        if (nCurrBlock >= cnt2)
        {
            nCurrBlock -= cnt2;
        }
        /* Get the maximum height of the chamber */
        nChamberHeight = max(nChamberHeight, *max_element(nBlockIdx[1].begin(), nBlockIdx[1].end()));
    }

    /* Display the chamber height */
    cout << "Part (a): " << nChamberHeight << endl;


    /* Reset the parameters for part b */

    nChamber.clear();

    /* Set the starting 0'th height position of chamber to blocked */
    for (cnt3 = 0; cnt3 < 7; cnt3++)
    {
        nChamber[cnt3] = 1;
    }

    nChamberHeight = 0;
    nLeftRightIdx = 0;
    nCurrBlock = 0;
    nTotalBlocks = 1000000000000;

    /* Iterate for a total of 2022 values */
    for (cnt3 = 0; cnt3 < nTotalBlocks; cnt3++)
    {
        /* Clear the current analysis block */
        nBlockIdx[0].clear();
        nBlockIdx[1].clear();

        /* Store the co-ordinates of the analysis block from the nBlocksIdx */
        for (cnt4 = 0; cnt4 < nBlocksSize[nCurrBlock]; cnt4++)
        {
            nBlockIdx[0].push_back(nBlocksIdx[nCurrBlock][0][cnt4]);
            /* Increment the chamber height in the Y co-ordinate */
            nBlockIdx[1].push_back(nBlocksIdx[nCurrBlock][1][cnt4] + nChamberHeight);
        }

        /* Collect the number of co-ordinates */
        int64_t nBlockIdx0Size = nBlockIdx[0].size();
        cnt6 = 1;

        int64_t nMaxRightXValue = *max_element(nBlockIdx[0].begin(), nBlockIdx[0].end());
        int64_t nMaxLeftXValue = *min_element(nBlockIdx[0].begin(), nBlockIdx[0].end());

        /* Iterate until the blocks cannot move */
        while (cnt6 > 0)
        {
            cnt6 = 0;
            /* If seeing a ">", move the blocks to the right if possible */
            if (leftRightStr[nLeftRightIdx] == '>')
            {
                /* Get the value of maximum X index to check if the it could
                 * be moved to the right */
                if (nMaxRightXValue < 6)
                {
                    /* if it could be moved to the right, check if there is no
                     * block in the chamber obstructing it */
                    for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                    {
                        if (nChamber[(7 * nBlockIdx[1][cnt4]) + (nBlockIdx[0][cnt4] + 1)] == 1)
                        {
                            break;
                        }
                    }
                    /* If there is no block obstructing it, move all the blocks
                     * to the right */
                    if (cnt4 == nBlockIdx0Size)
                    {
                        for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                        {
                            nBlockIdx[0][cnt4] = nBlockIdx[0][cnt4] + 1;
                        }
                        /* Increment the value of right and left maximums as
                         * the whole block has right shifted */
                        nMaxRightXValue++;
                        nMaxLeftXValue++;
                    }
                }
            }
            /* If seeing a "<", move the blocks to the left if possible */
            else
            {
                /* Get the value of minimum X index to check if the it could
                 * be moved to the left */
                if (nMaxLeftXValue > 0)
                {
                    /* if it could be moved to the left, check if there is no
                     * block in the chamber obstructing it */
                    for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                    {
                        if (nChamber[(7 * nBlockIdx[1][cnt4]) + (nBlockIdx[0][cnt4] - 1)] == 1)
                        {
                            break;
                        }
                    }
                    /* If there is no block obstructing it, move all the blocks
                     * to the left */
                    if (cnt4 == nBlockIdx0Size)
                    {
                        for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                        {
                            nBlockIdx[0][cnt4] = nBlockIdx[0][cnt4] - 1;
                        }
                        /* Decrement the value of right and left maximums as
                         * the whole block has left shifted */
                        nMaxLeftXValue--;
                        nMaxRightXValue--;
                    }
                }
            }

            /* Now try to move all the blocks one step down */
            for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
            {
                /* If there is a block obstructing it do not move it down */
                if (nBlockIdx[1][cnt4] > 0 && (nChamber[(7*(nBlockIdx[1][cnt4]-1)) + nBlockIdx[0][cnt4]] == 1))
                {
                    break;
                }
            }
            /* If there is no block in chamber obstructing it, move the entire
             * block one step down */
            if (cnt4 == nBlockIdx0Size)
            {
                for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
                {
                    nBlockIdx[1][cnt4] = nBlockIdx[1][cnt4] - 1;
                }
                cnt6++;
            }

            /* Wrap around the left right string index if overflown
             * nLeftRightIdx = (nLeftRightIdx + 1) MOD leftRightStr.size() */
            nLeftRightIdx++;
            if (nLeftRightIdx >= (int64_t)leftRightStr.size())
            {
                /* Check if the difference between chamber height is remaining
                 * constant */
                if ((nChambDiff == (nChamberHeight - nPrevChambHeight)) &&
                    (nBlockDiff == (cnt3 - nPrevBlock)))
                {
                    /* If the difference is constant increment a counter */
                    ++cnt7;
                }
                else
                {
                    /* if it does not, reset the counter */
                    cnt7 = 0;
                }

                /* Check this for around 10 iterations, and for the past 10
                 * iterations, if the count remains same, then just reduce
                 * the block count*/
                if (cnt7 > 5)
                {
                    /* Theory: For every nBlockDiff, the chamber increases by
                     * nChambDiff.
                     *
                     * From the remaining blocks to be processed, find the
                     * number of nBlockDiff packs of blocks that form nChambDiff
                     * height.
                     * If one nBlockDiff gives nChambDiff height, then nBlockDiff
                     * packs gives a height of nChambDiff * pack
                     *
                     * Let cnt9 store the value of the number of packs
                     */
                    cnt9 = (nTotalBlocks - cnt3) / nBlockDiff;
                    /* Chamber height to be increased by cnt9 * nChambDiff
                     * height */
                    nChambHeightInc += cnt9 * nChambDiff;
                    /* Increment the value of count, cnt3 by the packs * nBlockDiff
                     * as equivalently, so many blocks are processed */
                    cnt3 += cnt9 * nBlockDiff;
                }
                /* Chamber height difference = current chamber height minus prev
                 * chamber height */
                nChambDiff = nChamberHeight - nPrevChambHeight;
                /* Assign previous chamber height to current chamber height */
                nPrevChambHeight = nChamberHeight;
                /* Calculate the number of blocks difference = current block idx
                 * minus previous block index */
                nBlockDiff = cnt3 - nPrevBlock;
                /* Assign previous block idx to current block idx */
                nPrevBlock = cnt3;

                nLeftRightIdx -= leftRightStr.size();
            }
        }

        /* Block the value of the index in chamber that the block is currently at */
        for (cnt4 = 0; cnt4 < nBlockIdx0Size; cnt4++)
        {
            nChamber[(7 * nBlockIdx[1][cnt4]) + (nBlockIdx[0][cnt4])] = 1;
        }
        /* Increment the block number, wrap around the total blocks if exceeding */
        nCurrBlock++;
        if (nCurrBlock >= cnt2)
        {
            nCurrBlock -= cnt2;
        }
        /* Get the maximum height of the chamber */
        nChamberHeight = max(nChamberHeight, *max_element(nBlockIdx[1].begin(), nBlockIdx[1].end()));
    }

    /* Display the chamber height */
    cout << "Part (b): " << nChamberHeight + nChambHeightInc << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

