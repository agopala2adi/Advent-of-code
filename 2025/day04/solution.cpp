#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[100000][1000];


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

    vector<string> lines;
    /* A copy of lines */
    vector<string> lines2;

    /* Read each line from file */
    while (feof(fp) == 0)
    {
        /* Read a line from the file */
        int tempfsresult = fscanf(fp, "%s", arr[cnt1]);

        /* Convert the array to a string data type */
        string strLine = arr[cnt1];

        /* If we have reached the end of file, break */
        if (strLine.length() <= 2)
        {
            break;
        }

        /* Remove unwanted new lines */
        if ((strLine[strLine.length()-1] == '\n') || (strLine[strLine.length()-1] == '\r'))
        {
            strLine.pop_back();
        }
        if ((strLine[strLine.length()-1] == '\n') || (strLine[strLine.length()-1] == '\r'))
        {
            strLine.pop_back();
        }

        lines.push_back(strLine);
        /* Store it into the copy as well */
        lines2.push_back(strLine);

        /* Increment count */
        ++cnt1;
    }

    bool changed = true;
    cnt5 = 0;

    /* As long as there is at least one paper roll removed */
    while (changed == true)
    {
        /* Set it to zero to begin with */
        changed = false;
        cnt5++;

        /* Iterate through the entire grid */
        for (cnt2 = 0; cnt2 < lines.size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < lines[0].length(); cnt3++)
            {
                /* Keep a count of its neighboring paper rolls */
                cnt4 = 0;

                /* Only if the current cell is a paper roll */
                if (lines[cnt2][cnt3] == '@')
                {
                    /* Go through all the 8 neighbours and keep incrementing
                     * the count when the neighbour is a paper roll */
                    if (cnt2 > 0) 
                    {
                        if (lines[cnt2-1][cnt3] == '@')
                        {
                            cnt4++;
                        }
                        if (cnt3 > 0 && lines[cnt2-1][cnt3-1] == '@')
                        {
                            cnt4++;
                        }
                        if (cnt3 < lines[0].length()-1 && lines[cnt2-1][cnt3+1] == '@')
                        {
                            cnt4++;
                        }
                    }
                    if (cnt2 < lines.size()-1)
                    {
                        if (lines[cnt2+1][cnt3] == '@')
                        {
                            cnt4++;
                        }
                        if (cnt3 > 0 && lines[cnt2+1][cnt3-1] == '@')
                        {
                            cnt4++;
                        }
                        if (cnt3 < lines[0].length()-1 && lines[cnt2+1][cnt3+1] == '@')
                        {
                            cnt4++;
                        }
                    }
                    if (cnt3 > 0 && lines[cnt2][cnt3-1] == '@')
                    {
                        cnt4++;
                    }
                    if (cnt3 < lines[0].length()-1 && lines[cnt2][cnt3+1] == '@')
                    {
                        cnt4++;
                    }

                    /* Finally, if the count of neighbouring paper rolls is less than 4 */
                    if (cnt4 < 4)
                    {
                        /* Replace the paper roll with no paper roll X in the copy
                         * so that we would not distroy the original grid */
                        lines2[cnt2][cnt3] = 'X';
                        if (cnt5 == 1)
                        {
                            /* Increment the first part sum only for first time */
                            nFirstPart++;
                        }
                        /* Increment the second part sum regardless */
                        nSecondPart++;
                        /* Mark the changed as true */
                        changed = true;
                    }
                }
            }
        }

        /* Store the copy grid back to original for the next iteration */
        lines = lines2;
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

