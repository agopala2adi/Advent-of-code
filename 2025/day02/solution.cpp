#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[100000];

/*
 * Function to check if the number is valid as per the given conditions
 * nNo: Number to be checked
 * nPart: 1 for part a, 2 for part b
 * Returns: 0 if valid, else returns the number itself
*/
int64_t checkValidNo(int64_t nNo, int64_t nPart)
{
    /* Convert number to string */
    string strNo = to_string(nNo);
    int64_t cnt1 = 0, cnt2 = 0;

    if (nPart == 1)
    {
        /* For first part, the number would be always valid if it has odd
         * number of digits */
        if (strNo.size() % 2 != 0)
        {
            return 0;
        }
        /* Check if the first half of the number matches the second half */
        for (cnt1 = 0; cnt1 < strNo.size()/2; cnt1++)
        {
            /* Return zero if found validity, i.e., not same */
            if (strNo[cnt1] != strNo[cnt1 + strNo.size()/2])
            {
                return 0;
            }
        }
        /* Else, return the number */
        return nNo;
    }
    else
    {
        /* For second part, split the number into substrings with length from one  
         * to half the number's length */
        for (cnt1 = 1; cnt1 < strNo.size()/2+1; cnt1++)
        {
            string firstNumb;
            
            /* If the number cannot be divided into cnt1 number of parts, move 
             * to the next */
            if ((strNo.size()/cnt1) * cnt1 != strNo.size())
            {
                continue;
            }

            /* Check if the number is repeated version of the first part number
             * Example, 12121212 */
            firstNumb = strNo.substr(0, cnt1);

            /* Iterate through all parts and compare with the first part */
            for (cnt2 = 1; cnt2 < strNo.size()/cnt1; cnt2++)
            {
                /* Create sub strings for comparisions */
                if (firstNumb != strNo.substr(cnt2*cnt1, cnt1))
                {
                    /* If not true, immediately break and check for the next 
                     * length */
                    break;
                }
            }

            /* If it works for all numbers, then then it is invalid and return the number */
            if (cnt2 == strNo.size()/cnt1)
            {
                return nNo;
            }
            else
            {
                continue;
            }
        }
        /* If checked for all substrings, then return zero as it is valid */
        return 0;
    }
}



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

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    int64_t nDial = 50;

    char sLine[100];

    /* Read each line from file */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        string lineStr = string(arr);
        /* Read the input and convert that to a string type */
        for (cnt1 = 0; cnt1 < lineStr.size(); ++cnt1)
        {
            /* Replace all , and - with spaces sot that we can use
             * stringstream for number extraction */
            if (lineStr[cnt1] == ',' || lineStr[cnt1] == '-')
            {
                lineStr[cnt1] = ' ';
            }
        }

        stringstream iss(lineStr);

        /* Read first and second numbers, convert that to integer */
        while (iss >> sLine)
        {
            int64_t nStartNo = atoll(sLine);
            iss >> sLine;
            int64_t nEndNo = atoll(sLine);

            /* Iterage through all numbers, a brute force way */
            for (cnt2 = nStartNo; cnt2 <= nEndNo; ++cnt2)
            {
                /* Check if the number is valid by calling the function */
                cnt3 = checkValidNo(cnt2, 1);
                /* If valid, the function returns zero, if invalid, returns 
                 * the number itself */
                nFirstPart += cnt3;
                /* Every invalid number obtained in first part is an invalid
                 * number for second part as well */
                nSecondPart += cnt3;
                if (cnt3 == 0)
                {
                    /* Else, additionally check for validity */
                    cnt3 = checkValidNo(cnt2, 2);
                    nSecondPart += cnt3;
                }
            }
        }


        /* Increment count */
        ++cnt1;
    }


    /* Display part a and b answers */
    cout << "Part (a): " << nFirstPart << endl;

    cout << "Part (b): " << nSecondPart << endl;

    /* Close the file */
    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

