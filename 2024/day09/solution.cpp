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
    int64_t nPosStartX = 0, nPosStartY = 0, nPosStartXBackup = 0, nPosStartYBackup = 0;

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* List of space occupied by files */
    vector<int64_t> vFile;
    /* A copy of the file space */
    vector<int64_t> vFileCopy;
    /* List of space occupied by free space */
    vector<int64_t> vFree;
    /* A copy of the free space */
    vector<int64_t> vFreeCopy;

    /* Start index (block number) of each file in order of first to last */
    vector<int64_t> vFileStartIdx;

    int64_t nTotalBlocks = 0;
    int64_t nTotalFileBlocks = 0;

    while (feof(fp) == 0)
    {
        /* Read the first character - file blocks */
        char cFile = fgetc(fp);
        if (cFile == EOF)
        {
            break;
        }
        
        /* Store the number of blocks for each file in vFile vector  */
        vFile.push_back(cFile-'0');

        /* Make a copy of the free space vector */
        vFileCopy.push_back(cFile-'0');

        /* Total file blocks */
        nTotalFileBlocks += (cFile-'0');

        /* Store the file's start block index in a vector */
        vFileStartIdx.push_back(nTotalBlocks);

        /* Read the second character - free block blocks */
        char cFree = fgetc(fp);
        if (cFree == EOF)
        {
            break;
        }

        /* Store the number of blocks for each free space in vFree vector */
        vFree.push_back(cFree-'0');

        /* Make a copy of the free space vector */
        vFreeCopy.push_back(cFree-'0');

        /* Total blocks read would be sum of the file and the free space blocks 
         * until the current character */
        nTotalBlocks += (cFile-'0') + (cFree-'0');

        /* Increment count */
        ++cnt1;
    }

    /* Close the file */
    fclose(fp);

    /* Calculate the part (a) */

    int64_t nBlockPos = 0;

    /* Run a loop for all files and accumulate the checksum */
    for (cnt3 = 0; cnt3 < vFile.size(); cnt3++)
    {
        /* First is a file */
        for (cnt4 = 0; cnt4 < vFile[cnt3]; cnt4++)
        {
            /* Accumulate the checksum in part (a) */
            nFirstPart += (nBlockPos * cnt3);
            /* Increment the number of blocks */
            nBlockPos++;
        }

        /* When the total number of blocks reach the total number of file blocks
         * exit the loop to avoid counting multiple blocks */
        if (nBlockPos >= nTotalFileBlocks)
        {
            break;
        }

        /* Next is the free space */
        for (cnt4 = 0; cnt4 < vFree[cnt3]; cnt4++)
        {
            /* Insert each file from the end in each free space */
            if (vFile[vFile.size()-1] > 0)
            {
                /* Reduce the count of the files to avoid counting multiple count */
                vFile[vFile.size()-1]--;
                /* Accumulate the checksum in part (a) */
                nFirstPart += (nBlockPos * (vFile.size()-1));
                /* Increment the number of blocks */
                nBlockPos++;
            }
            else
            {
                /* If zero after decrementing the end file, remove from list */
                vFile.pop_back();
                /* Reduce the count of the penaltimate file */
                vFile[vFile.size()-1]--;
                /* Accumulate the checksum in part (a) */
                nFirstPart += (nBlockPos * (vFile.size()-1));
                /* Increment the number of blocks */
                nBlockPos++;
            }
        }
    }

    /* Calculate the part (b) */

    /* Restore the file for the second part */
    vFile = vFileCopy;
    
    /* Take the index of the last file into a variable */
    uint64_t nLastFileIdx = vFile.size()-1;

    /* As long as the last index is greater than zero */
    while (nLastFileIdx > 0)
    {
        /* Take the last file and see if there is minimum number of blocks
         * to insert them in between */
        for (cnt4 = 0; cnt4 < min(vFree.size(), nLastFileIdx); cnt4++)
        {
            /* If space is present */
            if (vFile[nLastFileIdx] <= vFree[cnt4])
            {
                /* Calculate the number of blocks - the index as below
                 * All the blocks before the file blocks
                 * All the blocks before the free space blocks
                 * The free space blocks already filled by the file
                */
                nBlockPos = vFile[0];
                for (cnt5 = 0; cnt5 < cnt4; cnt5++)
                {
                    nBlockPos += vFile[cnt5+1];
                    nBlockPos += (vFreeCopy[cnt5]);
                }
                nBlockPos += (vFreeCopy[cnt4]) - vFree[cnt4];

                /* Update the start index of the file given by block pos */
                vFileStartIdx[nLastFileIdx] = nBlockPos;

                /* Update the free space by removing the size of the file */
                vFree[cnt4] -= vFile[nLastFileIdx];
                break;
            }
        }
        nLastFileIdx--;
    }

    /* cnt2 - file ID */
    for (cnt2 = 0; cnt2 < vFileStartIdx.size(); cnt2++)
    {
        /* cnt3 - offset fromt eh file start index */
        for (cnt3 = 0; cnt3 < vFile[cnt2]; cnt3++)
        {
            /* Compute the second part by using the start index of each file */
            nSecondPart += cnt2 * (vFileStartIdx[cnt2] + cnt3);
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

