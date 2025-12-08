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

/* Keep a count of the tachyon pairs in each cell of the manifold */
vector<vector<int64_t>> vvCount;


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
        /* Push all zeros equal to the length of the line*/
        vvCount.push_back(vector<int64_t>(sLine.size(), 0));

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
                    /* Store the value 1 at the start position 'S' since
                     * it is present there first */
                    vvCount[cnt1][cnt2] = 1;
                    break;
                }
            }
        }

        /* Increment count */
        ++cnt1;
    }

    /* Now propagate the tachyon pairs through the manifold except the last line */
    for (cnt2 = 0; cnt2 < vvCount.size()-1; cnt2++)
    {
        for (cnt3 = 0; cnt3 < vvCount[cnt2].size(); cnt3++)
        {
            /* If the next line element is a split '^', the add the count 
             * to the left and right elements */
            if (sLines[cnt2+1][cnt3] == '^')
            {
                vvCount[cnt2+1][cnt3-1] += vvCount[cnt2][cnt3];
                vvCount[cnt2+1][cnt3+1] += vvCount[cnt2][cnt3];
                /* Increment the first part count if at least one tachyon pair 
                 * is present in the line above the split, '^' */
                if (vvCount[cnt2][cnt3] > 0)
                {
                    ++nFirstPart;
                }
            }
            /* If not add the count to the element directly below */
            else
            {
                vvCount[cnt2+1][cnt3] += vvCount[cnt2][cnt3];
            }
        }
    }

    /* Sum up all tachyon pairs in the last line for part - 2 answer */
    for (cnt2 = 0; cnt2 < vvCount[vvCount.size()-1].size(); cnt2++)
    {
        nSecondPart += vvCount[vvCount.size()-1][cnt2];
    }

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
