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
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t nFirstPart = 0;
    string nSecondPart = "";

    /* Store connections of computers as a pair of vectors */
    vector<pair<string, string>> vsConnections;
    /* Hash map to store all connections */
    unordered_set<string> usConnections;
    /* Hash map to store all computers */
    unordered_set<string> usComps;
    /* All connections trio */
    vector<string> vsConnectionsTrio[3];
    /* String of vectors of a large size to store all connections of computers */
    vector<string> vsAllConnections[10000];


    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        string sLine = arr;
        /* Split by -, store the first 2 characters and last two characters as a 
         * pair into the vector of pair of strings */
        vsConnections.push_back(make_pair(sLine.substr(0, 2), sLine.substr(3, 2)));
        /* Store the concat version into a hash map */
        usConnections.insert(vsConnections[cnt1].first + vsConnections[cnt1].second);
        /* Store each computer into the list of computers */
        usComps.insert(vsConnections[cnt1].first);
        usComps.insert(vsConnections[cnt1].second);
        /* Increment count */
        ++cnt1;
    }

    /* Part (a) */

    for (cnt1 = 0; cnt1 < vsConnections.size(); ++cnt1)
    {
        /* Get the from and two computers */
        string sFrom = vsConnections[cnt1].first;
        string sTo = vsConnections[cnt1].second;

        /* If "t" is not present, don't bother */
        if (sFrom[0] != 't' && sTo[0] != 't')
        {
            continue;
        }

        /* Iterate through all the computer list */
        for (auto it = usComps.begin(); it != usComps.end(); ++it)
        {
            string sComp = *it;
            /* Check if that computer that was iterated has a connection with 
             * all the computers stored in the vector */
            string sConnFrom1 = sFrom + sComp;
            string sConnFrom2 = sComp + sFrom;
            string sConnTo1 = sTo + sComp;
            string sConnTo2 = sComp + sTo;

            /* Check if the connection is present */
            if ((usConnections.find(sConnFrom1) != usConnections.end() || usConnections.find(sConnFrom2) != usConnections.end()) &&
                (usConnections.find(sConnTo1) != usConnections.end() || usConnections.find(sConnTo2) != usConnections.end()))
            {
                /* Sort and place into vsConnectionsTrio */
                if (sFrom < sTo && sFrom < sComp)
                {
                    vsConnectionsTrio[0].push_back(sFrom);
                    if (sTo < sComp)
                    {
                        vsConnectionsTrio[1].push_back(sTo);
                        vsConnectionsTrio[2].push_back(sComp);
                    }
                    else
                    {
                        vsConnectionsTrio[1].push_back(sComp);
                        vsConnectionsTrio[2].push_back(sTo);
                    }
                }
                else if (sTo < sFrom && sTo < sComp)
                {
                    vsConnectionsTrio[0].push_back(sTo);
                    if (sFrom < sComp)
                    {
                        vsConnectionsTrio[1].push_back(sFrom);
                        vsConnectionsTrio[2].push_back(sComp);
                    }
                    else
                    {
                        vsConnectionsTrio[1].push_back(sComp);
                        vsConnectionsTrio[2].push_back(sFrom);
                    }
                }
                else if (sComp < sFrom && sComp < sTo)
                {
                    vsConnectionsTrio[0].push_back(sComp);
                    if (sFrom < sTo)
                    {
                        vsConnectionsTrio[1].push_back(sFrom);
                        vsConnectionsTrio[2].push_back(sTo);
                    }
                    else
                    {
                        vsConnectionsTrio[1].push_back(sTo);
                        vsConnectionsTrio[2].push_back(sFrom);
                    }
                }
                else
                {
                    cerr << "Error in sorting found at " << __LINE__ << endl;
                }
            }
        }
    }

    /* Remove duplicates from the list */
    for (cnt1 = 0; cnt1 < vsConnectionsTrio[0].size(); ++cnt1)
    {
        for (cnt2 = cnt1+1; cnt2 < vsConnectionsTrio[0].size(); ++cnt2)
        {
            if (vsConnectionsTrio[0][cnt1] == vsConnectionsTrio[0][cnt2] &&
                vsConnectionsTrio[1][cnt1] == vsConnectionsTrio[1][cnt2] &&
                vsConnectionsTrio[2][cnt1] == vsConnectionsTrio[2][cnt2])
            {
                vsConnectionsTrio[0].erase(vsConnectionsTrio[0].begin() + cnt2);
                vsConnectionsTrio[1].erase(vsConnectionsTrio[1].begin() + cnt2);
                vsConnectionsTrio[2].erase(vsConnectionsTrio[2].begin() + cnt2);
                --cnt2;
            }
        }
    }

    /* The number of elements in vsConnectionsTrio gives the computer connection
     * having the letter "t" in the start */
    nFirstPart = vsConnectionsTrio[0].size();

    /* Part (b) */
    int64_t nIdx = 0;

    /* For all connections */
    for (cnt1 = 0; cnt1 < vsConnections.size(); ++cnt1)
    {
        /* Get the from and two computers */
        string sFrom = vsConnections[cnt1].first;
        string sTo = vsConnections[cnt1].second;

        /* Store that into the vector as we know that both these belong */
        vsAllConnections[nIdx].push_back(sFrom);
        vsAllConnections[nIdx].push_back(sTo);

        /* Iterate through all the computer list */
        for (auto it = usComps.begin(); it != usComps.end(); ++it)
        {
            string sComp = *it;
            /* Check if that computer that was iterated has a connection with 
             * all the computers stored in the vector */
            for (cnt2 = 0; cnt2 < vsAllConnections[nIdx].size(); ++cnt2)
            {
                /* Check is by comparing if the vectors are present as:-
                 * "computer under check" cat "computer in the vector" 
                 * or "computer in the vector" cat "computer under check"
                 * 
                 * If both are not present, then the computer does not form a chain
                 * with each other
                 */
                string sConn = vsAllConnections[nIdx][cnt2] + sComp;
                string sConn2 = sComp + vsAllConnections[nIdx][cnt2];

                if (usConnections.find(sConn) == usConnections.end() && usConnections.find(sConn2) == usConnections.end())
                {
                    break;
                }
            }
            if (cnt2 == vsAllConnections[nIdx].size())
            {
                /* If the computer has a connection with all the other computers
                 * store that into the vector 
                */
                vsAllConnections[nIdx].push_back(sComp);
            }
        }

        /* Increment the index */
        ++nIdx;
    }

    /* Find the maximum size of the vector */
    int64_t nMaxSize = 0;
    /* Store the index of the maximum size */
    int64_t nIdxMax = 0;

    /* Iterate through all the vectors */
    for (cnt1 = 0; cnt1 < nIdx; ++cnt1)
    {
        /* Find the maximum size */
        if (nMaxSize < (int64_t)vsAllConnections[cnt1].size())
        {
            nMaxSize = (int64_t)vsAllConnections[cnt1].size();
            /* Store the index */
            nIdxMax = cnt1;
        }
    }

    /* Store the second part answer */
    sort(vsAllConnections[nIdxMax].begin(), vsAllConnections[nIdxMax].end());

    /* Insert a comma between the computers */
    for (cnt1 = 0; cnt1 < vsAllConnections[nIdxMax].size(); ++cnt1)
    {
        nSecondPart += vsAllConnections[nIdxMax][cnt1] + ",";
    }
    /* Remove the ending comma */
    nSecondPart.pop_back();

    /* Close the file */
    fclose(fp);

    /* Display part a and b answer */
    cout << "Part (a): " << nFirstPart << endl;
    cout << "Part (b): " << nSecondPart << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

