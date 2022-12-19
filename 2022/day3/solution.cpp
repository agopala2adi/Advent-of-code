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

    vector<uint64_t> nElfVec;
    nElfVec.push_back(0);

    char op, my;

    while (fgets(arr[cnt1], sizeof(arr), fp))
    {
        /* Divide the current line string into two */
        cnt2 = strlen(arr[cnt1])/2;

        /* Traverse the first half of the string */
        for (cnt3 = 0; cnt3 < cnt2; cnt3++)
        {
            cnt5 = 0;
            /* Traverse the second half of the string */
            for (cnt4 = 0; cnt4 < cnt2; cnt4++)
            {
                /* Check if the character from first and second are equal */
                if (arr[cnt1][cnt3] == arr[cnt1][cnt4+cnt2])
                {
                    /* Add the value of the character */
                    if (arr[cnt1][cnt3] >= 'A' && arr[cnt1][cnt3] <= 'Z')
                    {
                        /* Store the count in cnt6 */
                        cnt6 += 27 + int64_t(arr[cnt1][cnt3] - 'A');
                    }
                    else
                    {
                        cnt6 += 1 + int64_t(arr[cnt1][cnt3] - 'a');
                    }
                    /* If equality is found exit from the loops */
                    cnt5 = 1;
                    break;
                }
            }
            /* Equality found */
            if (cnt5 == 1)
            {
                break;
            }
        }
        cnt1++;
    }
    cout << "Part (a): " << cnt6 << endl;

    /* Reset cnt6 */
    cnt6 = 0;
    /* Store the count of total strings in cnt7 and use cnt1 as index */
    cnt7 = cnt1;
    /* Reset cnt1 to zero */
    cnt1 = 0;

    /* Traverse all the strings once again */
    while (cnt1 < cnt7)
    {
        cnt1++;
        /* After finding every third string:  */
        if (cnt1 % 3 == 0)
        {
            /* Traverse through the last string (3rd) */
            for (cnt2 = 0; cnt2 < strlen(arr[cnt1-1]); cnt2++)
            {
                cnt5 = 0;
                /* Traverse through the second last string (2nd) */
                for (cnt3 = 0; cnt3 < strlen(arr[cnt1-2]); cnt3++)
                {
                    /* Traverse through the third last string (1st) */
                    for (cnt4 = 0; cnt4 < strlen(arr[cnt1-3]); cnt4++)
                    {
                        /* If all three chars from strings are equal */
                        if ((arr[cnt1-3][cnt4] == arr[cnt1-2][cnt3]) &&
                            ( arr[cnt1-3][cnt4] == arr[cnt1-1][cnt2]))
                        {
                            /* Add the value in cnt6 */
                            if (arr[cnt1-3][cnt4] >= 'A' && arr[cnt1-3][cnt4] <= 'Z')
                            {
                                cnt6 += 27 + int64_t(arr[cnt1-3][cnt4] - 'A');
                            }
                            else
                            {
                                cnt6 += 1 + int64_t(arr[cnt1-3][cnt4] - 'a');
                            }
                            /* Char found */
                            cnt5 = 1;
                            break;
                        }
                    }
                    /* Char found */
                    if (cnt5 == 1)
                    {
                        break;
                    }
                }
                /* Char found */
                if (cnt5 == 1)
                {
                    break;
                }
            }
        }
    }

    cout << "Part (b): " << cnt6 << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

