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

    vector<int64_t> firstCol;
    vector<int64_t> secondCol;

    /* Read each line from file */
    while (feof(fp) == 0)
    {
        /* Read the first and second number */
        int tempRet = fscanf(fp, "%ld %ld\n", &cnt1, &cnt2);
        /* Use temporary return variable to avoid warning */
        if (tempRet == EOF)
        {
            break;
        }

        /* Store the first number in the first column and second number in
         * second column */
        firstCol.push_back(cnt1);
        secondCol.push_back(cnt2);

        /* Increment count */
        ++cnt3;
    }

    /* Sort both the column arrays */
    sort(firstCol.begin(), firstCol.end());
    sort(secondCol.begin(), secondCol.end());

    /* Find the distances of both the pairs */
    for (cnt1 = 0; cnt1 < cnt3; cnt1++)
    {
        cnt5 += abs(firstCol[cnt1] - secondCol[cnt1]);
    }

    /* Part - 2 */
    /* Find the number of times of occurrence of the number from first col
     * in the second */
    for (cnt1 = 0; cnt1 < cnt3; cnt1++)
    {
        /* Store the number of occurrence of the number in second column in cnt4 */
        cnt4 = 0;
        for (cnt2 = 0; cnt2 < cnt3; cnt2++)
        {
            if (firstCol[cnt1] == secondCol[cnt2])
            {
                cnt4++;
            }
        }
        cnt6 += cnt4 * firstCol[cnt1];
    }

    /* Display part a and b answers */
    cout << "Part (a): " << cnt5 << endl;

    cout << "Part (b): " << cnt6 << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

