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
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    uint64_t max_val = 0;
    uint64_t min_val = 10000000ull;

    vector<uint64_t> nElfVec;
    nElfVec.push_back(0);

    char op, my;

    while (feof(fp) == 0)
    {
        /* Read as char with new line */
        fscanf(fp, "%c %c\n", &op, &my);

        /* Convert A,B,C and X,Y,Z to 0,1,2 */
        cnt1 = int64_t(op - 'A');
        cnt2 = int64_t(my - 'X');

        /* Add my score first */
        cnt4 += (cnt2 + 1);

        /* If my choice is one more than my opponent's (mod 3), I win */
        if (cnt1 == (cnt2 + 3 - 1) % 3)
        {
            cnt4 += 6;
        }
        /* If my choice is same as my opponent's, I draw */
        else if (cnt1 == cnt2)
        {
            cnt4 += 3;
        }
    }

    cout << "Part (a): " << cnt4 << endl;

    fseek(fp, 0L, SEEK_SET);

    cnt4 = 0;
    while (feof(fp) == 0)
    {
        /* Read as char with new line */
        fscanf(fp, "%c %c\n", &op, &my);

        /* Convert A,B,C and X,Y,Z to 0,1,2 */
        cnt1 = int64_t(op - 'A');
        cnt2 = int64_t(my - 'X');

        /* Add winning or losing score times 3
         * Losing is 0 with 0 points
         * Drawing is 1 with 3 points
         * Winning is 2 with 6 points
         */
        cnt4 += (cnt2 * 3);

        /* If draw add my opponent's points */
        if (cnt2 == 1)
        {
            cnt5 = cnt1 + 1;
        }
        /* If losing, add one point less than my opponent's (mod 3) */
        else if (cnt2 == 0)
        {
            cnt5 = (cnt1 + 3 - 1) % 3 + 1;
        }
        /* If winning, add one point more than my opponent's (mod 3) */
        else
        {
            cnt5 = (cnt1 + 1) % 3 + 1;
        }
        cnt4 += cnt5;
    }

    cout << "Part (b): " << cnt4 << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

