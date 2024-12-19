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

/* Use a hash map to memoise the substring 
 * Store the number of different combinations possible for the substring 
*/
unordered_map<string, int64_t> umDesiredPatterns;

int64_t getTowelSubstringCombinations(string &sDesiredPatterns, vector<string> &vsPatterns, int64_t nCount)
{
    /* Total number of combinations possible for the current substring */
    int64_t nCombinations = 0;

    /* If the total count reaches the size of the string, that means there is a
     * match and return 1 */
    if (nCount == sDesiredPatterns.size())
    {
        return 1;
    }

    /* Else, check if we have already stored in memoised list */
    if (umDesiredPatterns.find(sDesiredPatterns.substr(nCount, sDesiredPatterns.size())) != umDesiredPatterns.end())
    {
        /* If yes, return the memoised count */
        nCombinations += umDesiredPatterns[sDesiredPatterns.substr(nCount, sDesiredPatterns.size())];
        return nCombinations;
    }

    /* If we have not memoised, check for all cases where the available towels
     * match the first n characters of desired towel's substring
     * Where n is the size of the available towels
     */
    for (int64_t cnt1 = 0; cnt1 < vsPatterns.size(); cnt1++)
    {
        /* If we have enough characters in the desired design towel */
        if (sDesiredPatterns.size()-nCount >= vsPatterns[cnt1].size())
        {
            /* Compare sDesiredPatterns with vsPatterns substring */
            if (sDesiredPatterns.compare(nCount, vsPatterns[cnt1].size(), vsPatterns[cnt1]) == 0)
            {
                nCombinations += getTowelSubstringCombinations(sDesiredPatterns, vsPatterns, nCount+vsPatterns[cnt1].size());
            }
        }
    }

    /* Store the substring and its count into the hash map for future memoisation */
    umDesiredPatterns[sDesiredPatterns.substr(nCount, sDesiredPatterns.size())] = nCombinations;

    return nCombinations;
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


    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    bool bDesiredPatternStart = false;

    vector<string> vsPatterns;


    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        /* If the current line is just a new line, set the  */
        if (strlen(arr) <= 2)
        {
            bDesiredPatternStart = true;
        }
        /* If we have not yet seen a new line, store all the towels */
        else if (bDesiredPatternStart == false)
        {
            /* Since the towels are separated by a comma, replace it with
             * a space 
            */
            string sPatternLine = arr;
            for (cnt2 = 0; cnt2 < sPatternLine.size(); cnt2++)
            {
                if (sPatternLine[cnt2] == ',')
                {
                    sPatternLine[cnt2] = ' ';
                }
            }

            /* Store all of them in a vector know as patterns */
            stringstream iss(sPatternLine);
            string sTowel;

            while (iss >> sTowel)
            {
                vsPatterns.push_back(sTowel);
            }
        }
        else
        {
            /* Now, for each desired pattern: */
            string sDesiredPatterns = arr;

            /* Remove new line characters (if any) */
            if (sDesiredPatterns[sDesiredPatterns.size()-1] == '\n' || sDesiredPatterns[sDesiredPatterns.size()-1] == '\r')
            {
                sDesiredPatterns.pop_back();
            }
            if (sDesiredPatterns[sDesiredPatterns.size()-1] == '\n' || sDesiredPatterns[sDesiredPatterns.size()-1] == '\r')
            {
                sDesiredPatterns.pop_back();
            }

            /* Get the current sub-string matched towels */
            int64_t nCurrentCombinationCount = getTowelSubstringCombinations(sDesiredPatterns, vsPatterns, 0);

            /* If there is at least one combination */
            if (nCurrentCombinationCount > 0)
            {
                /* Increment part 1 */
                nFirstPart++;
            }
            /* Increment for second part regardless */
            nSecondPart += nCurrentCombinationCount;
        }

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

