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


        /* For first part */

        /* Start with a position of -1, for the first digit */
        int64_t curr_pos = -1;
        /* Current joult value */
        int64_t curr_joult = 0;

        /* Iterate this 2 times for getting the largest 2 digit number */
        for (cnt3 = 0; cnt3 < 2; cnt3++)
        {
            int64_t max_value = 0;
            /* Calculate the max value from the allowed limit 
             * 
             * We freeze the digits from the beginning.
             * Find the largest number from the allowed number of digits.
             * - For the 1st digit, we can use all the digits minus 1 
             *   (to leave space for the 2nd digit)
             * - For the 2nd digit, we can use all the digits minus 0.
             * - Start the loop from the next position of the last found max
             */
            for (cnt2 = curr_pos+1; cnt2 <= strLine.length()-(2-cnt3); cnt2++)
            {
                /* Calculate the max and the position */
                if (max_value < strLine[cnt2])
                {
                    max_value = strLine[cnt2];
                    curr_pos = cnt2;
                }
            }
            /* Calculate the joultage by left shifting by 1 position and adding
             * the new maximum jolt value */
            curr_joult = curr_joult * 10 + (max_value - '0');
        }
        /* Add the calculated joultage to the first part sum */
        nFirstPart += curr_joult;

        /* For second part */

        /* Reset current position and joult value */
        curr_pos = -1;
        curr_joult = 0;

        /* Iterate this 12 times for getting the largest 12 digit number */
        for (cnt3 = 0; cnt3 < 12; cnt3++)
        {
            int64_t max_value = 0;

            /* Calculate the max value from the allowed limit
             * 
             * We freeze the digits from the beginning.
             * Find the largest number from the allowed number of digits.
             * - For the 1st digit, we can use all the digits minus 11 
             *   (to leave space for the remaining 11 digits)
             * - For the 2nd digit, we can use all the digits minus 10.
             * ...
             * - For the 12th digit, we can use all the digits minus 0.
             * - Start the loop from the next position of the last found max
            */
            for (cnt2 = curr_pos+1; cnt2 <= strLine.length()-(12-cnt3); cnt2++)
            {
                /* Calculate the max and the position */
                if (max_value < strLine[cnt2])
                {
                    max_value = strLine[cnt2];
                    curr_pos = cnt2;
                }
            }
            /* Calculate the joultage by left shifting by 1 position and adding
             * the new maximum jolt value */
            curr_joult = curr_joult * 10 + (max_value - '0');
        }
        /* Add the calculated joultage to the second part sum */
        nSecondPart += curr_joult;

        /* Increment count */
        ++cnt1;
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

