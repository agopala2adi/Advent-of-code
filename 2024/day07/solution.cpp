#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[1000];

void modIncrement(char *in, int modulo = 2);


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

    /* Use this to perform an increment, but with modulo N for each "bit" 
     * If the modulo is 2, the increments would be as so:
     * 00000000, 00000001, 00000010, 00000011, 00000100, 00000101, ... 
     * If the modulo is 3, the increments would be as so:
     * 00000000, 00000001, 00000002, 00000010, 00000011, 00000012, ...
     */
    char nBitNumbers[30];


    /* Read each line from file */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        int64_t nTestValue;

        stringstream iss(arr);

        /* Get the test number first and remove the end colon */
        string sTest;
        iss >> sTest;
        sTest.pop_back();

        /* Convert the number from string to integer */
        nTestValue = stoll(sTest);

        /* Store all the numbers after the colon of each line in a vector */
        vector<int64_t> nNumbers;

        string sNumber;

        /* Read the number, convert to integer and store into the vector of numbers */
        while (iss >> sNumber)
        {
            nNumbers.push_back(stoll(sNumber));
        }

        /* Part (a) */

        /* Brute forcing - Number of runs required to run part (a) is 2 ^ (numbers - 1) 
         * Where each bit represents either a + or * operation
         */
        int64_t nNumberOfRuns = pow(2, nNumbers.size()-1);

        /* Reset all bit numbers to zero before starting */
        memset(nBitNumbers, 0, sizeof(nBitNumbers));

        /* Run a for loop for all zeros to all ones -> 2 ^ (numbs - 1) */
        for (cnt2 = 0; cnt2 < nNumberOfRuns; cnt2++)
        {
            int64_t nResult = nNumbers[0];
            /* Apply the operation for each number */
            for (cnt3 = 1; cnt3 < nNumbers.size(); cnt3++)
            {
                /* If the bit is a zero, the operation is add */
                if (nBitNumbers[cnt3-1] == 0)
                {
                    nResult = nResult + nNumbers[cnt3];
                }
                /* If the bit is a one, the operation is mul */
                else
                {
                    nResult = nResult * nNumbers[cnt3];
                }
            }
            /* Check if the result is obtained */
            if (nResult == nTestValue)
            {
                /* If so add the test result value into both parts */
                nFirstPart += nTestValue;
                nSecondPart += nTestValue;
                break;
            }
            /* If result is not obtained as test, do a modulo 2 increment  */ 
            modIncrement(nBitNumbers, 2);
        }

        /* Part (b) */

        if (cnt2 != nNumberOfRuns)
        {
            /* If the number has already been found by part (a), do not do part (b) */
            continue;
        }

        /* Reset all bit numbers to zero before starting */
        memset(nBitNumbers, 0, sizeof(nBitNumbers));

        /* Brute forcing - Number of runs required to run part (a) is 2 ^ (numbers - 1) 
         * Where each bit represents a +, *, or a concatenation operation
         */
        nNumberOfRuns = pow(3, nNumbers.size()-1);
        
        /* Run a for loop for all zeros to all twos -> 3 ^ (numbs - 1) */
        for (cnt2 = 0; cnt2 < nNumberOfRuns; cnt2++)
        {
            int64_t nResult = nNumbers[0];
            /* Apply the operation for each number */
            for (cnt3 = 1; cnt3 < nNumbers.size(); cnt3++)
            {
                /* If the bit is a zero, the operation is add */
                if (nBitNumbers[cnt3-1] == 0)
                {
                    nResult = nResult + nNumbers[cnt3];
                }
                /* If the bit is a one, the operation is mul */
                else if (nBitNumbers[cnt3-1] == 1)
                {
                    nResult = nResult * nNumbers[cnt3];
                }
                /* If the bit is a two, the operation is cat */
                else
                {
                    /* Concat using strings as that is easy */
                    string sCat = to_string(nResult);
                    sCat += to_string(nNumbers[cnt3]);
                    nResult = stoll(sCat);
                }
            }
            /* Check if the result is obtained */
            if (nResult == nTestValue)
            {
                nSecondPart += nTestValue;
                break;
            }
            /* If result is not obtained as test, do a modulo 3 increment  */ 
            modIncrement(nBitNumbers, 3);
        }

        /* Increment count */
        ++cnt1;
    }


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


/**
 * @brief Increments a binary or ternary number represented as an array of characters.
 * 
 * This function increments a number represented as an array of characters (bits) 
 * by 1, considering the number is in binary (modulo 2) or ternary (modulo 3) form.
 * 
 * @param in A character array representing the number to be incremented. 
 *           The array should have at least 30 elements.
 * @param modulo The base of the number system. It should be either 2 (binary) or 3 (ternary).
 * 
 * @note The function assumes that the input array has at least 30 elements.
 *       The function modifies the input array in place.
 */
void modIncrement(char *in, int modulo) 
{
    /* if the modulo was two */
    if (modulo == 2)
    {
        /* Add one from the first bit, if the bit is already a 1, move to a carry bit */
        for (int i = 0; i < 30; ++i)
        {
            /* If the current bit is a zero, make it one and end the loop */
            if (in[i] == 0)
            {
                in[i] = 1;
                break;
            }
            /* If the current bit is a one, make it zero and continue the loop 
             * to add the carry next */
            else
            {
                in[i] = 0;
            }
        }
    }
    /* If the modulo was three */
    else
    {
        /* Add one from the first bit, if the bit is already a 2, move to a carry bit */
        for (int i = 0; i < 30; ++i)
        {
            /* If the current bit is a zero, make it one and end the loop */
            if (in[i] == 0) 
            {
                in[i] = 1;
                break;
            }
            /* Else, add 1 to the result */
            in[i] = in[i] + 1;
            /* If the result is a 3, then make it zero and continue the loop
             * to add the carry next */
            if (in[i] == 3)
            {
                in[i] = 0;
            }
            /* Else break out of the loop */
            else
            {
                break;
            }
        }
    }
}


