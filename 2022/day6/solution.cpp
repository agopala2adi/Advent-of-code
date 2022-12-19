#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[100][100000];

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen("input.txt", "r");

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
    int64_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    uint64_t max_val = 0;
    uint64_t min_val = 10000000ull;

    /* Map all characters (alphabet) of array into arrChars */
    uint32_t arrChars[26];

    vector<int64_t> nElfVec;

    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        cnt1++;
    }

    /* Store the length of the array in cnt7 */
    cnt7 = strlen(arr[0]);

    /* Loop through all the values in array */
    for (cnt2 = 0; cnt2 < cnt7; cnt2++)
    {
        cnt4 = 0;
        /* Initialise the arrChars to zero for next iteration */
        for (cnt3 = 0; cnt3 < 26; cnt3++)
        {
            arrChars[cnt3] = 0;
        }
        /* Check the next 4 characters */
        for (cnt3 = 0; cnt3 < 4; cnt3++)
        {
            /* Increment the count of array alphabet */
            arrChars[arr[0][cnt2+cnt3]-'a']++;
        }
        for (cnt3 = 0; cnt3 < 26; cnt3++)
        {
            /* If the count is two or more, the array has repeated */
            if (arrChars[cnt3] >= 2)
            {
                cnt4 = 1;
                break;
            }
        }
        if (cnt4 == 0)
        {
            /* If there is no repetition */
            cnt5 = cnt2 + 4;
            break;
        }
    }

    cout << "Part (a): " << cnt5 << endl;

    /* Loop through all the values in array */
    for (cnt2 = 0; cnt2 < cnt7; cnt2++)
    {
        cnt4 = 0;
        /* Initialise the arrChars to zero for next iteration */
        for (cnt3 = 0; cnt3 < 26; cnt3++)
        {
            arrChars[cnt3] = 0;
        }
        /* Check the next 14 characters */
        for (cnt3 = 0; cnt3 < 14; cnt3++)
        {
            /* Increment the count of array alphabet */
            arrChars[arr[0][cnt2+cnt3]-'a']++;
        }
        for (cnt3 = 0; cnt3 < 26; cnt3++)
        {
            /* If the count is two or more, the array has repeated */
            if (arrChars[cnt3] >= 2)
            {
                cnt4 = 1;
                break;
            }
        }
        if (cnt4 == 0)
        {
            /* If there is no repetition */
            cnt5 = cnt2 + 14;
            break;
        }
    }

    cout << "Part (b): " << cnt5 << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

