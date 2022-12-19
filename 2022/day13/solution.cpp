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
char arr[10000][1000];

int64_t checkLeftRight(string, string);

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

    vector<int64_t> nElfVec;

    vector<int64_t> leftVals;
    vector<int64_t> rightVals;

    vector<string> allStrings;
    vector<string> allStrings2;

    /* Read every line */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        /* Calculate the total number of lines */
        string leftStr = arr[cnt1];
        if (leftStr.size() > 2)
        {
            /* If the size of a string is more than 2 (with \n and/\r), store
             * into all strings */
            allStrings.push_back(leftStr);
        }
        ++cnt1;
    }

    for (cnt1 = 0; cnt1 < allStrings.size(); cnt1 += 2)
    {
        string leftStr = allStrings[cnt1];
        string rightStr = allStrings[cnt1+1];
        /* Check if the left string is lesser than right string */
        if (checkLeftRight(leftStr, rightStr) == 1)
        {
            cnt7 += (cnt1/2) + 1;
        }
    }

    /* Add [[2]] and [[6]] strings into the list of strings */
    allStrings.push_back("[[2]]");
    allStrings.push_back("[[6]]");

    while (allStrings.size() > 0)
    {
        string leftStr = allStrings[0];
        /* Find the smallest string in the allStrings array */
        for (cnt2 = 1; cnt2 < allStrings.size(); cnt2++)
        {
            string rightStr = allStrings[cnt2];

            if (checkLeftRight(leftStr, rightStr) < 1)
            {
                leftStr = rightStr;
            }
        }

        /* Push the smallest string into the allStrings2 array */
        allStrings2.push_back(leftStr);

        auto it = allStrings.begin();
        /* Remove the smallest string from the array, so that next time, it
        * would not be included */
        for (it = allStrings.begin(); it != allStrings.end(); ++it)
        {
            if (*it == leftStr)
            {
                break;
            }
        }
        allStrings.erase(it);
    }
    /* Value of the product */
    int64_t nValProd = 1;
    for (cnt1 = 0; cnt1 < allStrings2.size(); cnt1++)
    {
        if (allStrings2[cnt1] == "[[2]]" || allStrings2[cnt1] == "[[6]]")
        {
            nValProd *= (cnt1+1);
        }
    }

    /* Display part a */
    cout << "Part (a): " << cnt7 << endl;
    /* Display part b */
    cout << "Part (b): " << nValProd << endl;

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

/* Check if the left string is lower than right string
 * If left is lower than right -> return 1
 * If left is greater than right -> return -1
 * If left is equal to right -> return 0
*/
int64_t checkLeftRight(string leftStr, string rightStr)
{
    string newLeft;
    string newRight;
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;
    int64_t cnt4 = 0;

    if (leftStr.size() == 0 && rightStr.size() != 0)
    {
        /* If left reached zero and right has not reached zero, left is smaller */
        return 1;
    }
    else if (leftStr.size() != 0 && rightStr.size() == 0)
    {
        /* If right reached zero and left has not reached zero, right is smaller */
        return -1;
    }

    /* Loop through all characters in both left and right */
    for (; cnt3 < leftStr.size() && cnt4 < rightStr.size(); cnt3++, cnt4++)
    {
        /* If the left string starts with a "[", accumulate all chars till
         * the corresponding "]" and store that into newLeft
         */
        if (leftStr[cnt3] == '[')
        {
            cnt1 = cnt3 + 1;
            int64_t len = 1;
            while (1)
            {
                if (leftStr[cnt1] == ']')
                {
                    --len;
                }

                if (len == 0)
                {
                    break;
                }
                else
                {
                    newLeft += leftStr[cnt1];
                    if (leftStr[cnt1] == '[')
                    {
                        ++len;
                    }
                }
                ++cnt1;
            }
        }

        /* If the right string starts with a "[", accumulate all chars till
         * the corresponding "]" and store that into newRight
         */
        if (rightStr[cnt4] == '[')
        {
            cnt2 = cnt4+1;
            int64_t len = 1;
            while (1)
            {
                if (rightStr[cnt2] == ']')
                {
                    --len;
                }

                if (len == 0)
                {
                    break;
                }
                else
                {
                    newRight += rightStr[cnt2];
                    if (rightStr[cnt2] == '[')
                    {
                        ++len;
                    }
                }
                ++cnt2;
            }
        }

        /* If either one does gets a "[", then call the function again to
         * solve under "[" and "]"
         */
        if (cnt2 != 0 || cnt1 != 0)
        {
            /* If left string does not have "[", then accumulate all characters
             * until the "," into newLeft */
            if (cnt1 == 0)
            {
                int64_t nCurrLeftIdx = cnt3;
                for (nCurrLeftIdx = cnt3; nCurrLeftIdx < leftStr.size(); nCurrLeftIdx++)
                {
                    if (leftStr[nCurrLeftIdx] == ',')
                    {
                        break;
                    }
                    newLeft += leftStr[nCurrLeftIdx];
                }
                /* Increment the count as the value is already processed */
                cnt1 += nCurrLeftIdx-1;
            }
            /* If right string does not have "[", then accumulate all characters
             * until the "," into newRight */
            if (cnt2 == 0)
            {
                int64_t nCurrRightIdx = cnt4;
                for (nCurrRightIdx = cnt4; nCurrRightIdx < rightStr.size(); nCurrRightIdx++)
                {
                    if (rightStr[nCurrRightIdx] == ',')
                    {
                        break;
                    }
                    newRight += rightStr[nCurrRightIdx];
                }
                /* Increment the count as the value is already processed */
                cnt2 += nCurrRightIdx-1;
            }
            /* Call the function again with newLeft and newRight */
            int64_t check = checkLeftRight(newLeft, newRight);
            if (check != 0)
            {
                return check;
            }

            newLeft = "";
            newRight = "";

            /* Update the count and run the loop again */
            cnt3 = cnt1;
            cnt4 = cnt2;
            cnt1 = 0;
            cnt2 = 0;
        }
        else
        {
            string leftVal;
            string rightVal;

            int64_t numb1 = 0;
            int64_t numb2 = 0;

            /* If the strings do not contain a "[" "]", accumulate all numbers
             * and compare between left and right
            */
            while (leftStr[cnt3] >= '0' && leftStr[cnt3] <= '9')
            {
                leftVal += leftStr[cnt3];
                ++cnt3;
                ++numb1;
            }
            while (rightStr[cnt4] >= '0' && rightStr[cnt4] <= '9')
            {
                rightVal += rightStr[cnt4];
                ++cnt4;
                ++numb2;
            }
            /* If there is a number only in one and not the other, check the logic */
            if ((leftVal.size() == 0 && rightVal.size() != 0) ||
                (leftVal.size() != 0 && rightVal.size() == 0))
            {
                cout << "Error! Check logic" << endl;
                exit(0);
            }
            /* If there is a number in both left and right, check which number
             * is greater */
            if (numb1 > 0)
            {
                if (stoll(rightVal) > stoll(leftVal))
                {
                    return 1;
                }
                else if (stoll(rightVal) < stoll(leftVal))
                {
                    return -1;
                }
            }
        }
    }

    /* If the length of left character is less than the right, (occurs when
     * the right string is fully used and all other chars are same) return left
     * lesser than right
    */
    if (leftStr.size() < rightStr.size())
    {
        return 1;
    }
    /* If the length of right character is less than the left, (occurs when
     * the left string is fully used and all other chars are same) return right
     * lesser than left
    */
    else if (leftStr.size() > rightStr.size())
    {
        return -1;
    }
    /* Else return same */
    else
    {
        return 0;
    }
}

