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
char arr[100][20000];

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

    /* Store the (X,Y,Z) positions of the cube */
    vector<int64_t> cubePos[3];

    /* Read every line */
    while (feof(fp) == 0)
    {
        int64_t x, y, z;
        fscanf(fp, "%ld,%ld,%ld\n", &x, &y, &z);
        cubePos[0].push_back(x);
        cubePos[1].push_back(y);
        cubePos[2].push_back(z);
        ++cnt1;
    }

    /* Total surface area of all cubes = 6 * length of side * total number of cubes */
    int64_t nTotalArea = 6 * cubePos[0].size();

    /* Loop through all cubes to find the cubes that are touching */
    for (cnt1 = 0; cnt1 < cubePos[0].size(); cnt1++)
    {
        /* Loop through remaining N-1 cubes */
        for (cnt2 = cnt1+1; cnt2 < cubePos[0].size(); cnt2++)
        {
            /* If the X and Y co-ordinate is same and the Z co-ordinate differs
             * by exactly 1, then the cubes are touching */
            if ((cubePos[0][cnt1] == cubePos[0][cnt2]) &&
                (cubePos[1][cnt1] == cubePos[1][cnt2]) &&
                abs(cubePos[2][cnt1]-cubePos[2][cnt2]) == 1)
            {
                /* Subract the total area with two as the number of common areas
                 * to be left out is two */
                --nTotalArea;
                --nTotalArea;
            }
            /* If the Y and Z co-ordinate is same and the X co-ordinate differs
             * by exactly 1, then the cubes are touching */
            else if ((cubePos[1][cnt1] == cubePos[1][cnt2]) &&
                    (cubePos[2][cnt1] == cubePos[2][cnt2]) &&
                    abs(cubePos[0][cnt1]-cubePos[0][cnt2]) == 1)
            {
                /* Subract the total area with two as the number of common areas
                 * to be left out is two */
                --nTotalArea;
                --nTotalArea;
            }
            /* If the X and Z co-ordinate is same and the Y co-ordinate differs
             * by exactly 1, then the cubes are touching */
            else if ((cubePos[0][cnt1] == cubePos[0][cnt2]) &&
                    (cubePos[2][cnt1] == cubePos[2][cnt2]) &&
                    abs(cubePos[1][cnt1]-cubePos[1][cnt2]) == 1)
            {
                /* Subract the total area with two as the number of common areas
                 * to be left out is two */
                --nTotalArea;
                --nTotalArea;
            }
        }
    }

    /* Print the remaining area */
    cout << "Part (a): " << nTotalArea << endl;

    fseek(fp, 0L, SEEK_SET);

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

