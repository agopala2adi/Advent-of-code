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
/* Commands string */
vector<string> cmds[1000];

/* Stores the sum of all dirs that have size less than 100000 */
int64_t gnNumDirsSize = 0;
/* To compute the least dir size atleast greater than gnMinDirVal */
int64_t gnMinDirVal = 70000000ll;
/* Space required for the program to run */
int64_t gnReqSize;

/* Recursive function to get the size of a particular dir
 * dirName - Directory name to look for size
 * nSize   - Total number of commands
 * nIdx    - Starting index of the dir command
*/
uint32_t nCalculateDirSize(string dirName, int64_t nSize, int64_t nIdx);

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen("input.txt", "r");

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
    int64_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    uint64_t max_val = 0;
    uint64_t min_val = 10000000ull;

    /* Map all characters (alphabet) of array into arrChars */
    uint32_t arrChars[26];

    vector<int64_t> nElfVec;

    uint32_t nLevel = 0;

    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        stringstream iss(arr[cnt1]);
        string word;

        /* Store all the commands into the vector */
        while (iss >> word)
        {
            cmds[cnt1].push_back(word);
        }
        cnt1++;
    }


    cnt6 = nCalculateDirSize("/", cnt1, 0);
    cout << "Part (a): " << gnNumDirsSize << endl;
    /* Remaining size is 70000000 minus the size of "/"
     * Size required by the program to run is 30000000.
     * Therefore, at least (30000000 - remaining size) must be freed
    */
    gnReqSize = 30000000ll - (70000000ll - cnt6);
    /* Reset the value of MinDirVal to run the calculate dir size again */
    gnMinDirVal = 70000000ll;
    cnt6 = nCalculateDirSize("/", cnt1, 0);
    cout << "Part (b): " << gnMinDirVal << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

uint32_t nCalculateDirSize(string dirName, int64_t nSize, int64_t nIdx)
{
    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;

    int64_t nCurrSize = 0;

    int64_t nFolderLevel = 0;

    /* Start from the current line of the command */
    for (cnt1 = nIdx; cnt1 < nSize; cnt1++)
    {
        /* Only if the current line has 3 words */
        if (cmds[cnt1].size() > 2)
        {
            /* Go back one folder if coming accross "cd .." */
            if (cmds[cnt1][0] == "$" && cmds[cnt1][1] == "cd" && cmds[cnt1][2] == "..")
            {
                nFolderLevel--;
            }
            /* Go forward one directory if seeing cd */
            else if (cmds[cnt1][0] == "$" && cmds[cnt1][1] == "cd")
            {
                nFolderLevel++;
            }
            /* Check if the current dir has the same name as the desination dir and we are only one level into the folder */
            if (cmds[cnt1][0] == "$" && cmds[cnt1][1] == "cd" && cmds[cnt1][2] == dirName && nFolderLevel == 1)
            {
                /* Start from the 2nd line as the first line always contains "$ ls" */
                for (cnt2 = cnt1+2; cnt2 < nSize; cnt2++)
                {
                    /* Compute the size of all the folders under that dir */

                    /* If seeing a command, stop accumulating the sizes */
                    if (cmds[cnt2][0] == "$")
                    {
                        break;
                    }
                    /* If found a dir, compute the size of the dir and add it with the current dir */
                    else if (cmds[cnt2][0] == "dir")
                    {
                        nCurrSize += nCalculateDirSize(cmds[cnt2][1], nSize, cnt2);
                    }
                    /* Add the size of the current files */
                    else
                    {
                        nCurrSize += int64_t(stol(cmds[cnt2][0]));
                    }
                }
                break;
            }
        }
    }

    /* Used for computing part (b) */
    if (gnMinDirVal >= nCurrSize && nCurrSize >= gnReqSize)
    {
        /* Get the least dir size at least greater than gnReqSize */
        gnMinDirVal = nCurrSize;
    }

    /* If the size of the current dir is less than 100000, then add its size */
    if (nCurrSize <= 100000ll)
    {
        gnNumDirsSize += nCurrSize;
    }

    return nCurrSize;
}
