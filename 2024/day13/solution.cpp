#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[10000];

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
    // To printf uint -> printf("%llu ", fin);

    // String stream: stringstream iss(arr);
    // Store word from string to string iss >> word
    // Display: printf("%s\n",word.c_str());

    // list<string> totalStrings;
    // for (auto it = totalStrings.begin(); it != totalStrings.end(); ++it)
    //     string str = *it;


    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int64_t nPosStartX = 0, nPosStartY = 0, nPosStartXBackup = 0, nPosStartYBackup = 0;

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    int64_t nButtonAX;
    int64_t nButtonAY;

    int64_t nButtonBX;
    int64_t nButtonBY;

    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        stringstream iss(arr);
        string word;

        iss >> word;

        /* If the word is a button */
        if (word == "Button")
        {
            iss >> word;

            /* Check if it a A or a B */
            if (word == "A:")
            {
                /* Read x count and y count and store into  */
                iss >> word;
                sscanf(word.c_str(), "X+%" PRId64 ",", &cnt2);
                nButtonAX = cnt2;

                iss >> word;
                sscanf(word.c_str(), "Y+%" PRId64 "", &cnt3);
                nButtonAY = (cnt3);
            }

            else if (word == "B:")
            {
                /* Read x count and y count */
                iss >> word;
                sscanf(word.c_str(), "X+%" PRId64 ",", &cnt2);
                nButtonBX = (cnt2);

                iss >> word;
                sscanf(word.c_str(), "Y+%" PRId64 "", &cnt3);
                nButtonBY = (cnt3);
            }

        }
        else if (word == "Prize:")
        {
            /* If the text is prize, do computation */

            int64_t xPrize = 0, yPrize = 0;
            iss >> word;
            sscanf(word.c_str(), "X=%ld,", &xPrize);

            iss >> word;
            sscanf(word.c_str(), "Y=%ld", &yPrize);

            int64_t equ1x = 0, equ1y = 0, equ2x = 0, equ2y = 0;
            int64_t cons1 = 0, cons2 = 0;

            long double yVal = 0, xVal = 0;
            int64_t yValInt = 0, xValInt = 0;

            /*
             * Construct an equation for the button A and button B
             * For example - 
             *  Button A: X+94, Y+34
             *  Button B: X+22, Y+67
             *  Prize: X=8400, Y=5400
             * 
             * Equation 1: 94x + 22y = 8400
             * Equation 2: 34x + 67y = 5400
             * 
             * Cross multiplying to make x coefficient same:
             * 
             * Equation 1: 34*(94x + 22y) = 34*8400
             * Equation 2: 94*(34x + 67y) = 94*5400
             * 
             * Subtract equation2 from equation1 to get the value of y
             * Then to get the value of x, substitute the value of y in equation1
            */

            equ1x = nButtonAY * nButtonAX;
            equ1y = nButtonAY * nButtonBX;

            equ2x = nButtonAX * nButtonAY;
            equ2y = nButtonAX * nButtonBY;

            cons1 = nButtonAY * xPrize;
            cons2 = nButtonAX * yPrize;

            /* Do not handle the case where the lines are parallel or intersecting 
             * For that the y values are same for the same x values 
            */
            if (equ1y != equ2y && equ1x == equ2x)
            {
                /* Convert them into long double as the equations can get very large */
                yVal = (long double)(cons1 - cons2) / (long double)(equ1y - equ2y);
                xVal = (long double)(cons1 - (equ1y * yVal)) / (long double)equ1x;

                /* Round it off to the nearest integer and check if they are same */
                yValInt = (int64_t)yVal;
                xValInt = (int64_t)xVal;

                /* If they are same, add the cost to part (a) */
                if ((long double)yValInt == yVal && (long double)xValInt == xVal)
                {
                    nFirstPart += (yValInt * 1 + xValInt * 3);
                }
            }

            /* Do the same for part (b) but increment by 10000000000000 */
            xPrize += 10000000000000;
            yPrize += 10000000000000;

            cons1 = nButtonAY * xPrize;
            cons2 = nButtonAX * yPrize;

            if (equ1y == equ2y || equ1x != equ2x)
            {
                /* Do not handle the case where the lines are parallel or intersecting */
                continue;
            }


            /* Convert them into long double as the equations can get very large */
            yVal = (long double)(cons1 - cons2) / (long double)(equ1y - equ2y);
            xVal = (long double)(cons1 - (equ1y * yVal)) / (long double)equ1x;

            /* Round it off to the nearest integer and check if they are same */
            yValInt = (int64_t)yVal;
            xValInt = (int64_t)xVal;

            /* If they are same, add the cost to part (b) */
            if ((long double)yValInt == yVal && (long double)xValInt == xVal)
            {
                nSecondPart += (yValInt * 1 + xValInt * 3);
            }

        }

        /* Increment count */
        ++cnt1;
    }

    /* Close the file */
    fclose(fp);


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

