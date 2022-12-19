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

    uint32_t nSizeChars = 9;

    vector<int64_t> nElfVec[100];
    vector<int64_t> nElfVec1[100];
    vector<int64_t> nElfVec2[100];
    vector<int32_t> nMove[100];

    while (fgets(arr[cnt1], sizeof(arr), fp) != NULL)
    {
        /* If there is a new line character line, break and start collecting "move" */
        if (strlen(arr[cnt1]) <= 1)
        {
            break;
        }

        cnt3 = 0;
        for (cnt2 = 0; cnt2 < strlen(arr[cnt1]); cnt2 += 4)
        {
            if (arr[cnt1][cnt2] != ' ')
            {
                /* Store the characters into N different arrays at the correct indices */
                nElfVec[cnt3].push_back(int64_t(arr[cnt1][cnt2+1] - 'A'));
            }
            cnt3++;
        }
        cnt1++;
    }

    /* Find the total number of indices */
    nSizeChars = (arr[cnt1-1][strlen(arr[cnt1-1])-2] - '0');

    /* Collect all "move"s into 3 vectors */
    while (feof(fp) == 0)
    {
        int32_t a, b, c;
        fscanf(fp, "move %d from %d to %d\n", &a, &b, &c);
        nMove[0].push_back(a);
        nMove[1].push_back(b);
        nMove[2].push_back(c);
        cnt1++;
    }

    /* Inverse the vector elements and store it in another vectors to implement stack */
    for (cnt2 = 0; cnt2 < nSizeChars; cnt2++)
    {
        for (cnt3 = nElfVec[cnt2].size()-1; cnt3 >= 0; cnt3--)
        {
            nElfVec1[cnt2].push_back(nElfVec[cnt2][cnt3]);
            nElfVec2[cnt2].push_back(nElfVec[cnt2][cnt3]);
        }
    }

    /* For part A, implement a stack move
     * Move N (vector 1) data from the vector 2's index to vector 3's index one-by-one,
     * from last element with popping.
    */
    for (cnt2 = 0; cnt2 < nMove[0].size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < nMove[0][cnt2]; cnt3++)
        {
            int32_t a = nElfVec1[nMove[1][cnt2]-1][nElfVec1[nMove[1][cnt2]-1].size()-1];
            nElfVec1[nMove[1][cnt2]-1].pop_back();
            nElfVec1[nMove[2][cnt2]-1].push_back(a);
        }
    }
    /* Print the last values of the arrays */
    cout << "Part (a): ";
    for (cnt2 = 0; cnt2 < nSizeChars; cnt2++)
    {
        cout << char(nElfVec1[cnt2][nElfVec1[cnt2].size()-1] + 'A');
    }
    cout << endl;

    /* For part B, implement a block move
     * Move N (vector 1) data from the vector 2's index to vector 3's index one-by-one,
     * from beginning, and after completing the move pop.
    */
    for (cnt2 = 0; cnt2 < nMove[0].size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < nMove[0][cnt2]; cnt3++)
        {
            int32_t a = nElfVec2[nMove[1][cnt2]-1][nElfVec2[nMove[1][cnt2]-1].size()-nMove[0][cnt2]+cnt3];
            nElfVec2[nMove[2][cnt2]-1].push_back(a);
        }
        for (cnt3 = 0; cnt3 < nMove[0][cnt2]; cnt3++)
        {
            nElfVec2[nMove[1][cnt2]-1].pop_back();
        }
    }
    /* Print the last values of the arrays */
    cout << "Part (b): ";
    for (cnt2 = 0; cnt2 < nSizeChars; cnt2++)
    {
        cout << char(nElfVec2[cnt2][nElfVec2[cnt2].size()-1] + 'A');
    }
    cout << endl;

    fseek(fp, 0L, SEEK_SET);
    cnt1 = 0;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

