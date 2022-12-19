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

    while (feof(fp) == 0)
    {
        int a, b, c, d;
        /* Read data into a, b, c, and d */
        fscanf(fp, "%d-%d,%d-%d\n", &a, &b, &c, &d);

        /* If a and b both are contained inside c and d  (a <= c and b >= d)  -- (a, c, d, b)
         * (or) c and d both contained inside a and b    (c <= a and d >= b)  -- (c, a, b, d)
         * Then one is contained inside the other
        */
        if ((a >= c && b <= d) || (a <= c && b >= d))
        {
            ++cnt1;
        }
    }
    cout << "Part (a): " << cnt1 << endl;

    fseek(fp, 0L, SEEK_SET);
    cnt1 = 0;

    while (feof(fp) == 0)
    {
        int a, b, c, d;
        /* Read data into a, b, c, and d */
        fscanf(fp, "%d-%d,%d-%d\n", &a, &b, &c, &d);

        /* Check if one of them overlap portion into the other
         * Case 1: a, b, c, d - No overlap
         * Case 2: a, c, b, d - Overlap
         * Case 3: c, a, d, b - Overlap
         * Case 4: c, d, a, b - No overlap
         * Therefore: We find: b >= c and a <= b for overlap
        */
        if (b >= c && a <= d)
        {
            ++cnt1;
        }
    }
    cout << "Part (b): " << cnt1 << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

