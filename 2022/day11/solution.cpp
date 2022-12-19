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

    vector<int64_t> nMonkeyVals[8];
    vector<int64_t> nMonkeyVals1[8];  /* Copy for 10000 */
    vector<int64_t> nMonkeyOper[8];
    vector<int64_t> nMonkeyCase[8];
    vector<int64_t> nMonkeyCounted;
    int64_t nMonkeyDiv[8];

    int64_t nMaxMod = 1;

    cnt2 = 0;

    /* Read every line */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        /* If the line does not have anything, then there is a new set of monkey*/
        if (strlen(arr[cnt1]) <= 2)
        {
            ++cnt2;
            continue;
        }

        /* Split into words and read each word */
        stringstream iss(arr[cnt1]);
        string word;
        while (iss >> word)
        {
            if (word == "Starting")
            {
                iss >> word; /* Read "items:" */
                while (iss >> word)
                {
                    /* Read values after that */
                    nMonkeyVals[cnt2].push_back(stoll(word));
                    nMonkeyVals1[cnt2].push_back(stoll(word));
                }
            }
            else if (word == "Operation:")
            {
                iss >> word; /* Read "new" */
                iss >> word; /* Read "=" */
                iss >> word; /* Read "old" */
                iss >> word; /* Read "+" or "*" */
                if (word == "+")
                {
                    /* If "+", use zero */
                    nMonkeyOper[cnt2].push_back(0);
                }
                else
                {
                    /* If "*", use one */
                    nMonkeyOper[cnt2].push_back(1);
                }
                iss >> word;
                if (word == "old")
                {
                    /* If the value is old, store -1 */
                    nMonkeyOper[cnt2].push_back(-1);
                }
                else
                {
                    /* else store the value */
                    nMonkeyOper[cnt2].push_back(stoll(word));
                }
            }
            else if (word == "Test:")
            {
                iss >> word; /* Read "divisible" */
                iss >> word; /* Read "by" */
                iss >> word; /* Read value */
                nMonkeyDiv[cnt2] = (stoll(word));
            }
            else if (word == "If")
            {
                iss >> word; /* Read "true:" */
                if (word == "true:" || word == "false:")
                {
                    iss >> word; /* Read "throw" */
                    iss >> word; /* Read "to" */
                    iss >> word; /* Read "monkey" */
                    iss >> word; /* Read value */
                    nMonkeyCase[cnt2].push_back(stoll(word));
                }
                else
                {
                    cout << "Error: Not true and false. " << endl;
                }
            }
        }
    }
    /* Increment the count2 to add the last entry */
    ++cnt2;

    /* Accumulate all the div values for max mod */
    for (cnt3 = 0; cnt3 < cnt2; cnt3++)
    {
        nMaxMod *= nMonkeyDiv[cnt3];
        /* Set monkey counted to zero */
        nMonkeyCounted.push_back(0);
    }

    /* Part (a) run for 20 */
    for (cnt7 = 0; cnt7 < 20; cnt7++)
    {
        /* Read through all monkeys */
        for (cnt3 = 0; cnt3 < cnt2; cnt3++)
        {
            /* Add the items to be processed of the monkey */
            nMonkeyCounted[cnt3] += nMonkeyVals[cnt3].size();
            /* Process each item */
            for (cnt4 = 0; cnt4 < nMonkeyVals[cnt3].size(); cnt4++)
            {
                /* Read the current item */
                cnt5 = nMonkeyVals[cnt3][cnt4];
                /* If addition and no self addition */
                if (nMonkeyOper[cnt3][0] == 0 && nMonkeyOper[cnt3][1] != -1)
                {
                    cnt5 += nMonkeyOper[cnt3][1];
                }
                /* If self addition */
                else if (nMonkeyOper[cnt3][0] == 0)
                {
                    cnt5 += cnt5;
                }
                /* If multiplication and no self multiplication */
                else if (nMonkeyOper[cnt3][0] == 1 && nMonkeyOper[cnt3][1] != -1)
                {
                    cnt5 *= nMonkeyOper[cnt3][1];
                }
                /* If self multiplication */
                else
                {
                    cnt5 *= cnt5;
                }
                /* Divide the result by 3 */
                cnt5 = cnt5 / 3;

                /* If divisible by the div value, then concatinate the first monkey */
                if (cnt5 % nMonkeyDiv[cnt3] == 0)
                {
                    nMonkeyVals[nMonkeyCase[cnt3][0]].push_back(cnt5 % nMaxMod);
                }
                /* If not divisible by the div value, then concatinate the sec monkey */
                else
                {
                    nMonkeyVals[nMonkeyCase[cnt3][1]].push_back(cnt5 % nMaxMod);
                }
            }
            /* Delete all the processed items */
            cnt5 = nMonkeyVals[cnt3].size();
            for (cnt4 = 0; cnt4 < cnt5; cnt4++)
            {
                nMonkeyVals[cnt3].pop_back();
            }
        }
    }
    /* Sort the counted values by monkey in acc and display the product of last two */
    sort(nMonkeyCounted.begin(), nMonkeyCounted.end());
    cout << "Part (a): " << nMonkeyCounted[cnt2-1] * nMonkeyCounted[cnt2-2] << endl;

    /* Reset the counted vales for part (b) */
    for (cnt3 = 0; cnt3 < cnt2; cnt3++)
    {
        nMonkeyCounted[cnt3] = 0;
    }

    /* Part (b) run for 10000 */
    for (cnt7 = 0; cnt7 < 10000; cnt7++)
    {
        /* Read through all monkeys */
        for (cnt3 = 0; cnt3 < cnt2; cnt3++)
        {
            /* Add the items to be processed of the monkey */
            nMonkeyCounted[cnt3] += nMonkeyVals1[cnt3].size();
            /* Process each item */
            for (cnt4 = 0; cnt4 < nMonkeyVals1[cnt3].size(); cnt4++)
            {
                /* Read the current item */
                cnt5 = nMonkeyVals1[cnt3][cnt4];
                /* If addition and no self addition */
                if (nMonkeyOper[cnt3][0] == 0 && nMonkeyOper[cnt3][1] != -1)
                {
                    cnt5 += nMonkeyOper[cnt3][1];
                }
                /* If self addition */
                else if (nMonkeyOper[cnt3][0] == 0)
                {
                    cnt5 += cnt5;
                }
                /* If multiplication and no self multiplication */
                else if (nMonkeyOper[cnt3][0] == 1 && nMonkeyOper[cnt3][1] != -1)
                {
                    cnt5 *= nMonkeyOper[cnt3][1];
                }
                /* If self multiplication */
                else
                {
                    cnt5 *= cnt5;
                }

                /* If divisible by the div value, then concatinate the first monkey */
                if (cnt5 % nMonkeyDiv[cnt3] == 0)
                {
                    nMonkeyVals1[nMonkeyCase[cnt3][0]].push_back(cnt5 % nMaxMod);
                }
                /* If not divisible by the div value, then concatinate the sec monkey */
                else
                {
                    nMonkeyVals1[nMonkeyCase[cnt3][1]].push_back(cnt5 % nMaxMod);
                }
            }

            /* Delete all the processed items */
            cnt5 = nMonkeyVals1[cnt3].size();
            for (cnt4 = 0; cnt4 < cnt5; cnt4++)
            {
                nMonkeyVals1[cnt3].pop_back();
            }
        }
    }

    /* Sort the counted values by monkey in acc and display the product of last two */
    sort(nMonkeyCounted.begin(), nMonkeyCounted.end());
    cout << "Part (b): " << nMonkeyCounted[cnt2-1] * nMonkeyCounted[cnt2-2] << endl;


    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

