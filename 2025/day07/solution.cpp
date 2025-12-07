#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[1000][10000];

/* Store the input lines into a vector */
vector<string> sLines;

/* Function prototype for calculating options recursively */
int64_t calculateOptions(int64_t nX);

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

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* Lets use a hash-set for storing pairs of tachyons 
     * This would only contain the y-coordinates of the tachyon pairs
     * as we read each line (x-coordinate) from the file
     */
    unordered_set<int64_t> usTachyonPairs;

    /* Get the start (x, y) of tachyon, given by 'S' */
    int64_t nXIdxOfS = -1;
    int64_t nYIdxOfS = -1;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Read a line from the file */
        string sLine = arr[cnt1];

        /* Remove newline character */
        if (sLine.back() == '\n' || sLine.back() == '\r')
        {
            sLine.pop_back();
        }
        if (sLine.back() == '\n' || sLine.back() == '\r')
        {
            sLine.pop_back();
        }

        /* Store each input of the file into a vector of strings */
        sLines.push_back(sLine);

        /* If we have not seen a start position 'S' yet */
        if (nYIdxOfS == -1)
        {
            /* Search for the start position 'S' */
            for (cnt2 = 0; cnt2 < sLine.size(); cnt2++)
            {
                /* If we find 'S', store its (x, y) position */
                if (sLine[cnt2] == 'S')
                {
                    nYIdxOfS = cnt2;
                    nXIdxOfS = cnt1;
                    /* Also insert the y-coordinate of the start position
                     * into the hash-set */
                    usTachyonPairs.insert(cnt2);
                    break;
                }
            }
        }
        else
        {
            /* Create a copy of the current set of tachyon pairs as we would need
             * to keep modifying the set while iterating */
            unordered_set<int64_t> usTachyonPairsCpy = usTachyonPairs;

            /* For each tachyon pair y-coordinate */
            for (auto it = usTachyonPairs.begin(); it != usTachyonPairs.end(); ++it)
            {
                /* If we find the '^' character, we split into two tachyons */
                if (sLine[*it] == '^')
                {
                    /* See if there is space in the manifold to the left */
                    if (*it > 0)
                    {
                        /* Insert a new tachyon pair to the left */
                        usTachyonPairsCpy.insert(*it-1);
                    }
                    /* See if there is space in the manifold to the right */
                    if (*it < sLine.size()-1)
                    {
                        /* Insert a new tachyon pair to the right */
                        usTachyonPairsCpy.insert(*it+1);
                    }

                    /* Increment the first part as we have split a tachyon */
                    ++nFirstPart;
                    /* Remove the current tachyon pair from the copy set */
                    usTachyonPairsCpy.erase(*it);
                }
            }
            /* Update the original set of tachyon pairs */
            usTachyonPairs = usTachyonPairsCpy;
        }
        /* Increment count */
        ++cnt1;
    }

    /* Now, calculate the second part using a recursive function that calculates
     * the number of options from a given (x, y) position in the manifold
     * 
     * The start position is given by (nXIdxOfS, nYIdxOfS)
     * It is encoded as (nYIdxOfS * 0x1000000) + nYIdxOfS
     * This encoding is required as unordered_map in C++ does not support
     * pair as key directly.
     * 
     * Choose a hexadecimal multiplier (0x1000000) large enough to hold
     * the maximum possible y-coordinate value.
     * And it also ensures that division and modulo operations can quicly
     * extract x and y coordinates.
     */
    nSecondPart = calculateOptions((nXIdxOfS*0x1000000ULL) + nYIdxOfS);


    /* Display part a and b answers */
    cout << "Part (a): " << nFirstPart << endl;

    cout << "Part (b): " << nSecondPart << endl;

    /* Close the file */
    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

/* Use a hash map to memoize the number of options from each position 
 * The position is encoded as (x * 0x1000000) + y to store both coordinates
 * in a single integer. This is required as unordered_map in C++ does not support
 * pair as key directly.
 * 
 * 
*/
unordered_map<int64_t, int64_t> nOptions;

/* Recursive function to calculate the number of options from a given (x, y)
 * position in the manifold
 * The input nX is encoded as (x * 0x1000000) + y to store both coordinates
 * in a single integer
 */
int64_t calculateOptions(int64_t nX)
{
    /* Extract x and y coordinates */
    int64_t nY = nX % 0x1000000ULL;
    nX = nX / 0x1000000ULL;

    /* If we have already calculated the number of options from this position
     * return the value quickly 
    */
    if (nOptions.find((nX*0x1000000ULL) + nY) != nOptions.end())
    {
        return nOptions[(nX*0x1000000ULL) + nY];
    }

    /* If we have reached the last line of the manifold */
    if (nX == sLines.size()-1)
    {
        nOptions[(nX*0x1000000ULL) + nY] = 1;
        return 1;
    }


    /* Total number of options from this position */
    int64_t nTotalOptions = 0;

    /* Move downwards in the manifold until we hit a non-empty space */
    int64_t nStart = nX;
    
    while (sLines[nX][nY] == '.' || sLines[nX][nY] == 'S')
    {
        nX++;
        /* If we have already calculated the number of options from this position
         * return the value quickly 
        */
        if (nOptions.find((nX*0x1000000ULL) + nY) != nOptions.end())
        {
            return nOptions[(nX*0x1000000ULL) + nY];
        }
        /* If we have reached the last line of the manifold */
        if (nX == sLines.size()-1)
        {
            /* All positions from nStart to end, lead to 1 option only 
             * store that into the hash map or memoize it */
            for (int64_t cnt = nStart; cnt <= nX; cnt++)
            {
                nOptions[(cnt*0x1000000ULL) + nY] = 1;
            }
            /* Return 1 option */
            return 1;
        }
    }

    /* If we can move left */
    if (nY > 0)
    {
        /* If there is a '^', then we split left by recursively calculating options */
        if (sLines[nX][nY] == '^')
        {
            /* Also add to the total options as we need to keep a count */
            nTotalOptions += calculateOptions((nX*0x1000000ULL) + (nY-1));
        }
    }
    /* If we can move right */
    if (nY < sLines[0].size()-1)
    {
        /* If there is a '^', then we split right by recursively calculating options */
        if (sLines[nX][nY] == '^')
        {
            /* Also add to the total options as we need to keep a count */
            nTotalOptions += calculateOptions((nX*0x1000000ULL) + (nY+1));
        }
    }

    /* Memoize the total options from this position */
    nOptions[(nX*0x1000000ULL) + nY] = nTotalOptions;

    /* Return the total options from this position */
    return nTotalOptions;
}

