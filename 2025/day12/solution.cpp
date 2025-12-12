#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[2000][10000];

int main(void)
{
    auto startTime = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(startTime);

    FILE* fp = fopen("input.txt", "r");

    if (fp == nullptr)
    {
        cerr << "Cannot open input file." << endl;
        return -1;
    }

    cout << "Start Time: " << ctime(&start_time) << endl;

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
    int64_t cnt15 = 0, cnt16 = 0, cnt17 = 0, cnt18 = 0, cnt19 = 0, cnt20 = 0, cnt21 = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* A vector that stores the number of #'s in each row */
    vector<int64_t> nSizes;

    int64_t nNumerOfHashes = 0;

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

        /* When we see a new line, add the total count of #'s into the vector */
        if (sLine.size() == 0)
        {
            nSizes.push_back(nNumerOfHashes);
            /* Reset it so that we can start again freshly */
            nNumerOfHashes = 0;
            ++cnt1;
            continue;
        }

        /* Count the number of #'s in this line, check if the line starts with 
         * a dot or a hash as we want to ignore the rest */
        if (sLine[0] == '.' || sLine[0] == '#')
        {
            /* Count the number of #'s in this line */
            for (cnt3 = 0; cnt3 < sLine.size(); cnt3++)
            {
                if (sLine[cnt3] == '#')
                {
                    ++nNumerOfHashes;
                }
            }
        }

        /* If starting with a number that is not a colon at the end, then we have
         * reached the last set of lines */
        else if (sLine.back() != ':')
        {
            /* Replace all 'x' and ':' with spaces so that we can split into 
             * words with stringstream easily */
            for (cnt2 = 0; cnt2 < sLine.size(); cnt2++)
            {
                /* Replace with space */
                if (sLine[cnt2] == 'x' || sLine[cnt2] == ':')
                {
                    sLine[cnt2] = ' ';
                }
            }

            /* Create a stringstream from the modified line */
            stringstream ssLine(sLine);

            int64_t nRow, nCol;
            /* Read the first two and find the product which gives us the grid
             * size */
            ssLine >> nRow;
            ssLine >> nCol;

            int64_t nTotalGridSize = nRow * nCol;

            int64_t nTotalHashesInShape = 0;
            int64_t nIdx = 0;

            while (ssLine >> cnt5)
            {
                nTotalHashesInShape += cnt5*nSizes[nIdx++];
            }

            /* Just check the obvious cases first 
             * If you have less #'s than the grid size, it is valid
             */
            if (nTotalHashesInShape < nTotalGridSize)
            {
                nFirstPart++;
            }
        }

        /* Increment count */
        ++cnt1;
    }



    /* Display part - 1 and 2 answers */
    cout << "Part (a): " << nFirstPart << endl;
    cout << "Part (b): There is no part (b)" << endl;

    /* Close the file */
    fclose(fp);

    auto endTime = chrono::system_clock::now();
    chrono::duration<double> elapsedSecs = endTime-startTime;
    time_t end_time = chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}
