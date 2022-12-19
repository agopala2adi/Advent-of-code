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
char arr[10000][1000];

/* Contains the name of each valve as a string */
string gsValve[100];
/* Rate of flow of pressure of each valve */
int64_t gnValveRate[100];
/* Name of the valve converted from string to index, 0 to N-1
 * Each valve connects to other valves using a tunnel. This contains the
 * connections from the starting valve to the destination valve */
vector<int64_t> gnValveIdx[100];
/* Total number of valves in the puzzle */
int64_t gnTotalValves;
/* Starting index of string "AA" (where we start) */
int64_t gnIdxAA = 0;
/* Number of non-zero rate valves (which could be open) */
vector <int32_t> gnNonZeroRate;
/* The shortest cost from one valve to another */
int64_t gnShortCost[100][100];

/* Recursive function that finds the total pressure from a given valve and a
 * current time
 */
int64_t getPressurePartA(int64_t nStartIdx, int64_t nCurrTime, unordered_map<int64_t, int64_t> &nAlreadyOpened);

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen(input_file, "r");

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
    int64_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    uint64_t max_val = 0;
    uint64_t min_val = 10000000ull;

    vector<int64_t> nElfVec;

    /* Read every line */
    while (feof(fp) == 0)
    {
        char sValve[10];
        char sTunnel[20];
        char leads[20];

        /* Read the array into valve string and valve rate
         * Note: tunnel(s) and lead(s) are read as they may be just tunnel or
         * tunnels, and leads or lead. It is ignored after reading
         */
        fscanf(fp, "Valve %s has flow rate=%ld; %s %s to valves", sValve, &gnValveRate[cnt1], &sTunnel[0], &leads[0]);
        /* Store the string into gsValue strings */
        gsValve[cnt1] = sValve;

        if (gsValve[cnt1] == "AA")
        {
            /* If the current string is "AA", store the index of this string
             * to start the processing */
            gnIdxAA = cnt1;
        }

        /* Read the remaining string to avoid incorrect values to be read in
         * fscanf the next time */
        if (fgets(arr[cnt1], sizeof(arr[0]), fp) == NULL)
        {
            break;
        }
        /* Calculate the total number of lines */
        ++cnt1;
    }

    /* Move the pointer to the beginning */
    fseek(fp, 0L, SEEK_SET);

    /* Set the total number of valves to a variable */
    gnTotalValves = cnt1;
    cnt1 = 0;

    /* Read every line once again */
    while (feof(fp) == 0)
    {
        char sValve[10];
        char sTunnel[20];
        char leads[20];
        int64_t nTempRate;

        /* Read the array into valve string and valve rate
         * Note: tunnel(s) and lead(s) are read as they may be just tunnel or
         * tunnels, and leads or lead. It is ignored after reading
         */
        fscanf(fp, "Valve %s has flow rate=%ld; %s %s to valves", sValve, &nTempRate, &sTunnel[0], &leads[0]);

        /* Read the remaining string to get the valve connections and avoid bad
         * values into fscanf the next time */
        if (fgets(arr[cnt1], sizeof(arr[0]), fp) == NULL)
        {
            break;
        }

        stringstream iss(arr[cnt1]);
        string word;

        /* Read teh next set of strings word by word */
        while (iss >> word)
        {
            /* If the word contains a ',', remove the ',' */
            if (word[word.size()-1] == ',')
            {
                word.pop_back();
            }
            /* Find out the index of the connected valves */
            for (cnt2 = 0; cnt2 < gnTotalValves; cnt2++)
            {
                if (gsValve[cnt2] == word)
                {
                    break;
                }
            }
            /* Store the index into a variable */
            gnValveIdx[cnt1].push_back(cnt2);
        }
        /* Calculate the total number of lines */
        ++cnt1;
    }

    /* Already visited or not variable to find shortest path using Djikstra */
    int64_t nAlreadyVisited[100];

    /* Temp variable to hold the cost and the index */
    vector <int64_t> nCost[2];

    /* Initially set a very high cost for all variables */
    for (cnt2 = 0; cnt2 < gnTotalValves; cnt2++)
    {
        for (cnt3 = 0; cnt3 < gnTotalValves; cnt3++)
        {
            /* This variable gives the cost from cnt2 to cnt3 */
            gnShortCost[cnt2][cnt3] = 10000;
        }
    }

    /* Find the cost from all valves using Djikstra */
    for (cnt3 = 0; cnt3 < gnTotalValves; cnt3++)
    {
        /* Store the analysis variable into cost variable
         * along with the cost to visit itself (which is zero)
        */
        nCost[0].push_back(cnt3);
        nCost[1].push_back(0);

        /* Assign the shortest cost from a vatiable to itself to zero */
        gnShortCost[cnt3][cnt3] = 0;

        /* Set the value of already visited to false */
        for (cnt2 = 0; cnt2 < gnTotalValves; cnt2++)
        {
            nAlreadyVisited[cnt2] = 0;
        }

        /* As long as we have valves to consider, keep analysing */
        while (nCost[0].size() > 0)
        {
            /* Take the begining value of valve index and erase it */
            int64_t nCurrVal = nCost[0][0];
            /* Set the variable of valve to already visited */
            nAlreadyVisited[nCurrVal] = 1;

            /* Erase the valve and its cost */
            nCost[0].erase(nCost[0].begin());
            nCost[1].erase(nCost[1].begin());

            /* Analyse all of valve's connections */
            for (cnt2 = 0; cnt2 < gnValveIdx[nCurrVal].size(); cnt2++)
            {
                /* If the variable is already visited, ignore */
                if (nAlreadyVisited[gnValveIdx[nCurrVal][cnt2]] == 0)
                {
                    /* Else, check if the existing cost in the node is lesser than
                     * the cost from current node + 1
                     * if so, update the cost
                     * Note: Cost from any valve / node to any other connected valve
                     * is 1 */
                    if (gnShortCost[cnt3][gnValveIdx[nCurrVal][cnt2]] > gnShortCost[cnt3][nCurrVal] + 1)
                    {
                        gnShortCost[cnt3][gnValveIdx[nCurrVal][cnt2]] = gnShortCost[cnt3][nCurrVal] + 1;
                        /* Store the cost and node into the cost variable */
                        for (cnt4 = 0; cnt4 < nCost[1].size(); cnt4++)
                        {
                            /* If the valve cost is just smaller than value in the array */
                            if (gnShortCost[cnt3][gnValveIdx[nCurrVal][cnt2]] < nCost[1][cnt4])
                            {
                                break;
                            }
                        }
                        /* Store costs in ascending order */
                        nCost[1].insert(nCost[1].begin()+cnt4, gnShortCost[cnt3][gnValveIdx[nCurrVal][cnt2]]);
                        nCost[0].insert(nCost[0].begin()+cnt4, gnValveIdx[nCurrVal][cnt2]);
                    }
                }
            }
        }
    }
    /* Received the shortest cost into the gnShortCost[from][to] array */

    /* Store all the non-zero valves into array */
    for (cnt2 = 0; cnt2 < gnTotalValves; cnt2++)
    {
        if (gnValveRate[cnt2] > 0)
        {
            gnNonZeroRate.push_back(cnt2);
        }
    }
    /* Use a hash map to avoid revisiting the same arrays again */
    unordered_map <int64_t, int64_t> nTempVec;

    /* Display the total pressure from "AA" */
    cout << "Part (a): " << getPressurePartA(gnIdxAA, 30, nTempVec) << endl;

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

/* Recursive function to get the total pressure from starting index and
 * current time
 * nStartIdx - Starting index of the valve
 * nCurrTime - Time remaining
 * nAlreadyOpened - If the valve is already open do not waste time in opening it
 *                  again
 */
int64_t getPressurePartA(int64_t nStartIdx, int64_t nCurrTime, unordered_map<int64_t, int64_t> &nAlreadyOpened)
{
    /* Temp variables */
    int64_t nCnt1;
    int64_t nCnt2;
    int64_t nCnt3;
    int64_t nCnt4;

    /* Temp pressure */
    int64_t nPressure = 0;
    /* Maximum pressure */
    int64_t nMaxPressure = 0;

    /* If the time has been elapsed, return the pressure as zero as no valve
     * can be open after time runs out */
    if (nCurrTime <= 0)
    {
        return nMaxPressure;
    }

    /* Loop through all the values of non-zero rate and move to a non-zero rate
     * next to open the valve */
    for (nCnt1 = 0; nCnt1 < gnNonZeroRate.size(); nCnt1++)
    {
        /* If the valve is already open, skip and move on to next valve */
        if (nAlreadyOpened[gnNonZeroRate[nCnt1]] == 1)
        {
            continue;
        }

        /* Current pressure is zero */
        nPressure = 0;

        /* If there is enough time to visit the next valve and open it (1 more
         * than the cost to open the valve) the go into the valve and open it */
        if (nCurrTime > (gnShortCost[nStartIdx][gnNonZeroRate[nCnt1]] + 1))
        {
            /* Open the valve and set the already opened flag to true */
            nAlreadyOpened[gnNonZeroRate[nCnt1]] = 1;
            /* Calculate the total pressure using remaining time and
             * the current flow rate of the valve */
            nPressure += (nCurrTime - gnShortCost[nStartIdx][gnNonZeroRate[nCnt1]] - 1) * gnValveRate[gnNonZeroRate[nCnt1]];
            /* Move into the valve to open a new valve (recursive all next
             * valves, using the start idx as the current non-zero opened valve
             * index). Update the remaining time accordingly */
            nPressure += getPressurePartA(gnNonZeroRate[nCnt1],
                                         (nCurrTime - gnShortCost[nStartIdx][gnNonZeroRate[nCnt1]] - 1),
                                         nAlreadyOpened);
            /* Set already opened back to zero, as now we will move instead
             * to a different valve as though we have not touched the valve */
            nAlreadyOpened[gnNonZeroRate[nCnt1]] = 0;
        }

        /* Update the maximum pressure received */
        if (nMaxPressure < nPressure)
        {
            nMaxPressure = nPressure;
        }
    }

    /* Return the maximum pressure */
    return nMaxPressure;
}
