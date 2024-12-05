#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[1000];


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

    bool bEnabled = true;

    vector<int64_t> vnFirstPageRule;
    vector<int64_t> vnSecondPageRule;

    bool bFirstSection = true;

    /* Read each line from file */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        /* Read the lines and if it is the first section, then the number of 
         * characters is less than or equal to 7 */
        if (strlen(arr) > 2 && bFirstSection == true)
        {
            int64_t nFirstNumber;
            int64_t nSecondNumber;

            /* Read the first section's numbers first and second rule */
            sscanf(arr, "%" PRIi64 "|%" PRIi64, &nFirstNumber, &nSecondNumber);
            /* Place them in two vectors */
            vnFirstPageRule.push_back(nFirstNumber);
            vnSecondPageRule.push_back(nSecondNumber);
        }
        else if (strlen(arr) <= 2)
        {
            /* If seen just a new line without any rule, assume that section 1 
             * is done */
            bFirstSection = false;
        }
        else
        {
            /* In the section 2, store each line's update in a vector */
            vector<int64_t> nUpdate;
            for (cnt2 = 0; cnt2 < strlen(arr)-1; cnt2 += 3)
            {
                /* Each number is a two digit number */
                string sNumb;
                sNumb += arr[cnt2];
                sNumb += arr[cnt2 + 1];
                nUpdate.push_back(stoll(sNumb));
            }
            /* Lucky this logic worked */
            /* Split the entire rule into numbers of two, then search if the 
             * first number is in first page ordering rule and second number
             * in the second page rule */
            for (cnt2 = 1; cnt2 < nUpdate.size(); cnt2++)
            {
                for (cnt3 = 0; cnt3 < vnFirstPageRule.size(); cnt3++)
                {
                    if (nUpdate[cnt2-1] == vnFirstPageRule[cnt3] && nUpdate[cnt2] == vnSecondPageRule[cnt3])
                    {
                        /* If true, then the number is part of the correct rule */
                        break;
                    }
                }
                /* If not found, then the ordering is incorrect */
                if (cnt3 == vnFirstPageRule.size())
                {
                    break;
                }
            }
            /* If correct order for all the pair of two's, then sum the middle 
             * rule into part (a)'s answer */
            if (cnt2 == nUpdate.size())
            {
                nFirstPart += nUpdate[nUpdate.size()/2];
            }
            /* If one number is not in the correct order, move to part two below */
            else
            {
                /* Run a while 1 loop until you get the whole rule sorted */
                while (true)
                {
                    /* Run the same part as before */
                    for (cnt2 = 1; cnt2 < nUpdate.size(); cnt2++)
                    {
                        for (cnt3 = 0; cnt3 < vnFirstPageRule.size(); cnt3++)
                        {
                            if (nUpdate[cnt2-1] == vnFirstPageRule[cnt3] && nUpdate[cnt2] == vnSecondPageRule[cnt3])
                            {
                                break;
                            }
                        }
                        /* If could not find the correct rule, swap as that would be
                         * part of the rule */
                        if (cnt3 == vnFirstPageRule.size())
                        {
                            swap(nUpdate[cnt2-1], nUpdate[cnt2]);
                            break;
                        }
                    }
                    /* After all sorts are done and it firs the rule, then 
                     * add the middle number */
                    if (cnt2 == nUpdate.size())
                    {
                        nSecondPart += nUpdate[nUpdate.size()/2];
                        break;
                    }
                }
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
