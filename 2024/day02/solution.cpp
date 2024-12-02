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

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Read each line and convert to string stream */
        stringstream iss(arr[cnt1]);
        string word;

        /* Store each report in a vector */
        vector<int64_t> report;
        /* Store a copy for part two */
        vector<int64_t> report_cpy;

        /* Read each word from the line */
        while (iss >> word)
        {
            /* Store each level (conv to int) in the vector */
            report_cpy.push_back(stoll(word));
        }

        /* For part two to remove each single level to store in report */
        for (cnt4 = 0; cnt4 < report_cpy.size()+1; cnt4++)
        {
            /* Make a copy before removing the level */
            report = report_cpy;
            /* If first time, do not remove a level */
            if (cnt4 > 0)
            {
                /* Else remove a level in n'th position from start given by (cnt4 - 1) */
                report.erase(report.begin() + cnt4-1);
            }

            /* Find whether the levels are increasing or decreasing be comparing 
             * the first two levels in the report */
            bool bIncreasing = false;
            if (report[1] >= report[0])
            {
                bIncreasing = true;
            }

            /* Run a loop from the second level and compare with the previous
             * level and check whether the report is all increasing or decreasing */
            for (cnt2 = 1; cnt2 < report.size(); cnt2++)
            {
                /* If the report is increasing level report, and if the current 
                 * level is less than or equal to the previous level, or the difference
                 * between the current and previous level is more than 3, then the
                 * report is not safe 
                 */ 
                if (bIncreasing == true && 
                    ((report[cnt2] <= report[cnt2-1]) || (report[cnt2] - report[cnt2-1]) > 3))
                {
                    break;
                }
                /* If the report is decreasing level report, and if the current 
                 * level is greater than or equal to the previous level, or the 
                 * difference between the current and previous level is more than 3, 
                 * then the report is not safe 
                 */ 
                else if (bIncreasing == false && 
                         ((report[cnt2] >= report[cnt2-1]) || (report[cnt2-1] - report[cnt2]) > 3))
                {
                    break;
                }
                else
                {
                    /* Empty else */
                }
            }
            /* If the report is safe */
            if (cnt2 == report.size())
            {
                /* For part (a) - if no level is removed */
                if (cnt4 == 0)
                {
                    nFirstPart++;
                }
                /* Increment part (b) nonetheless */
                nSecondPart++;
                break;
            }
        }

        /* Increment count */
        ++cnt1;
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

