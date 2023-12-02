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

    int64_t nMaxBlueAllowed  = 14;
    int64_t nMaxRedAllowed   = 12;
    int64_t nMaxGreenAllowed = 13;

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* To get each word */
        stringstream iss(arr[cnt1]);
        string word;

        int64_t nBlueMax = 0;
        int64_t nRedMax = 0; 
        int64_t nGreenMax = 0;

        int64_t nNumberOfCubes = 0;
        int64_t nGameNumber = 0;

        bool bGamePossible = true;

        /* Get string "Game" */
        iss >> word;
        /* Get game number number */
        iss >> word;

        /* Get game number in terms of a integer variable */
        sscanf(word.c_str(), "%ld:", &nGameNumber);

        /* Parse through each word */
        while (iss >> word)
        {
            /* First word is a number if between 0 and 9 */
            if (word[0] >= '0' && word[0] <= '9')
            {
                /* Convert the number in text format to number in integer */
                sscanf(word.c_str(), "%ld", &nNumberOfCubes);
            }
            /* Else, a colour: blue, red or green */
            else
            {
                /* If the colour of the cube is blue, */
                if (word == "blue;" || word == "blue" || word == "blue,")
                {
                    /* If the number of blue cubes is more than max allowed,
                     * set this game to be impossible
                     */
                    if (nNumberOfCubes > nMaxBlueAllowed)
                    {
                        bGamePossible = false;
                    }
                    /* Get the max number of blue coloured cubes */
                    if (nBlueMax < nNumberOfCubes)
                    {
                        nBlueMax = nNumberOfCubes;
                    }
                }
                /* If the colour of the cube is red, */
                else if (word == "red;" || word == "red" || word == "red,")
                {
                    /* If the number of red cubes is more than max allowed,
                     * set this game to be impossible
                     */
                    if (nNumberOfCubes > nMaxRedAllowed)
                    {
                        bGamePossible = false;
                    }
                    /* Get the max number of red coloured cubes */
                    if (nRedMax < nNumberOfCubes)
                    {
                        nRedMax = nNumberOfCubes;
                    }
                }
                /* If the colour of the cube is green, */
                else if (word == "green;" || word == "green" || word == "green,")
                {
                    /* If the number of green cubes is more than max allowed,
                     * set this game to be impossible
                     */
                    if (nNumberOfCubes > nMaxGreenAllowed)
                    {
                        bGamePossible = false;
                    }
                    /* Get the max number of green coloured cubes */
                    if (nGreenMax < nNumberOfCubes)
                    {
                        nGreenMax = nNumberOfCubes;
                    }
                }
                else
                {
                    cout << "Something wrong in the input in line: " << cnt1 << endl;
                }
            }
        }

        /* If this game were to be possible, add the game number to 1st part */
        if (bGamePossible == true)
        {
            nPartOneSum += nGameNumber;
        }

        /* Multiply green, red and blue maximum values */
        nPartTwoSum += nGreenMax * nRedMax * nBlueMax;
        
        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Display part a and b answers */
    cout << "Part (a): " << nPartOneSum << endl;

    cout << "Part (b): " << nPartTwoSum << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

