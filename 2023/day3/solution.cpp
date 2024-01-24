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

    int64_t mavXYCord = 0;
    const int64_t nYCordMax = 10000000ll;

    vector<int64_t> vXYCord;
    vector<int64_t> numbers;

    int64_t nPartOneSoln = 0;
    int64_t nPartTwoSoln = 0;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Get the length of one line and exclude the new line characters (\r and \n) */
    for (cnt2 = 0; cnt2 < strlen(arr[0]); cnt2++)
    {
        if (arr[0][cnt2] == '\n' || arr[0][cnt2] == '\r')
        {
            break;
        }
    }

    /* Loop through all lines */
    for (cnt3 = 0; cnt3 < cnt1; cnt3++)
    {
        /* Loop through each character in a given line */
        for (cnt4 = 0; cnt4 < cnt2; cnt4++)
        {
            /* Store the number in a string */
            string number;
            /* Flag to set if it is a part number */
            bool bIsPartNumb = false;
            /* Flag to set if it is a gear */
            bool bIsGear = false;

            /* To store the second number adjacent to gear '*' */
            int64_t nSecondNumber = 0;

            /* If the first character is between 0 to 9, accumulate all digits
             * to form a number */
            if (arr[cnt3][cnt4] >= '0' && arr[cnt3][cnt4] <= '9')
            {
                /* "cnt5" would hold the y-index of the last digit */
                cnt5 = cnt4;
                while(arr[cnt3][cnt5] >= '0' && arr[cnt3][cnt5] <= '9')
                {
                    number += arr[cnt3][cnt5];
                    cnt5++;
                }

                /* If we are at least one row down */
                if (cnt3 > 0)
                {
                    /* Check if the top row has a non dot '.' */
                    for (cnt6 = cnt4; cnt6 < cnt5; cnt6++)
                    {
                        /* If found a non-dot */
                        if (arr[cnt3-1][cnt6] != '.')
                        {
                            /* Check if this non-dot is a second word by searching
                             * through the list of stored co-ordinates */
                            auto it = std::find(vXYCord.begin(), 
                                                vXYCord.end(), 
                                                (cnt3-1)*nYCordMax + cnt6);

                            /* If the co-ordinate is already there, that means
                             * there was a number before that shares the same 
                             * gear and find that number that was adjacent to 
                             * the gear */
                            if (it != vXYCord.end())
                            {
                                /* The number would be the same index as the 
                                 * co-ordinate */
                                nSecondNumber = numbers[it - vXYCord.begin()];
                                bIsGear = true;
                            }
                            else
                            {
                                /* If there is no co-ordinate, save the 
                                 * co-ordinate (x*y_max, y) for later use */
                                vXYCord.push_back((cnt3-1)*nYCordMax+cnt6);
                                /* Also store the number that was adjacent to 
                                 * the gear */
                                numbers.push_back(atoll(number.c_str()));
                            }

                            /* Set the part number to be true as the number
                             * has a gear adjacent to it */
                            bIsPartNumb = true;
                            break;
                        }
                    }
                }
                /* If we are not in the last row */
                if (cnt3 < cnt1-1)
                {
                    /* Check if the next row has a non dot '.' */
                    for (cnt6 = cnt4; cnt6 < cnt5; cnt6++)
                    {
                        /* If found a non-dot */
                        if (arr[cnt3+1][cnt6] != '.')
                        {
                            /* Check if this non-dot is a second word by searching
                             * through the list of stored co-ordinates */
                            auto it = std::find(vXYCord.begin(), 
                                                vXYCord.end(), 
                                                (cnt3+1)*nYCordMax + cnt6);

                            /* If the co-ordinate is already there, that means
                             * there was a number before that shares the same 
                             * gear and find that number that was adjacent to 
                             * the gear */
                            if (it != vXYCord.end())
                            {
                                /* The number would be the same index as the 
                                 * co-ordinate */
                                nSecondNumber = numbers[it - vXYCord.begin()];
                                /* Set is gear to true */
                                bIsGear = true;
                            }
                            else
                            {
                                /* If there is no co-ordinate, save the 
                                 * co-ordinate (x*y_max, y) for later use */
                                vXYCord.push_back((cnt3+1)*nYCordMax+cnt6);
                                /* Also store the number that was adjacent to 
                                 * the gear */
                                numbers.push_back(atoll(number.c_str()));
                            }

                            /* Set the part number to be true as the number
                             * has a gear adjacent to it */
                            bIsPartNumb = true;
                            break;
                        }
                    }
                }
                /* If we are not in the first column and the column before is 
                 * not a dot */
                if (cnt4 > 0 && arr[cnt3][cnt4-1] != '.')
                {
                    /* Check if this non-dot is a second word by searching
                     * through the list of stored co-ordinates */
                    auto it = std::find(vXYCord.begin(), vXYCord.end(), (cnt3)*nYCordMax + (cnt4-1));

                    /* If the co-ordinate is already there, that means there was
                     * a number before that shares the same gear and find that 
                     * number that was adjacent to the gear */
                    if (it != vXYCord.end())
                    {
                        /* The number would be the same index as the co-ordinate */
                        nSecondNumber = numbers[it - vXYCord.begin()];
                        /* Set is gear to true */
                        bIsGear = true;
                    }
                    else
                    {
                        /* If there is no co-ordinate, save the co-ordinate
                         * (x*y_max, y) for later use */
                        vXYCord.push_back((cnt3)*nYCordMax+cnt4-1);
                        /* Also store the number that was adjacent to the gear */
                        numbers.push_back(atoll(number.c_str()));
                    }
                    /* Set the part number to be true as the number has a gear 
                     * adjacent to it */
                    bIsPartNumb = true;
                }
                /* If we are not in the last column and the column next is 
                 * not a dot */
                if (cnt5 < cnt2 && arr[cnt3][cnt5] != '.')
                {
                    /* Check if this non-dot is a second word by searching
                     * through the list of stored co-ordinates */
                    auto it = std::find(vXYCord.begin(), vXYCord.end(), (cnt3)*nYCordMax + cnt5);

                    /* If the co-ordinate is already there, that means there was
                     * a number before that shares the same gear and find that 
                     * number that was adjacent to the gear */
                    if (it != vXYCord.end())
                    {
                        /* The number would be the same index as the co-ordinate */
                        nSecondNumber = numbers[it - vXYCord.begin()];
                        /* Set is gear to true */
                        bIsGear = true;
                    }
                    else
                    {
                        /* If there is no co-ordinate, save the co-ordinate
                         * (x*y_max, y) for later use */
                        vXYCord.push_back((cnt3)*nYCordMax+cnt5);
                        /* Also store the number that was adjacent to the gear */
                        numbers.push_back(atoll(number.c_str()));
                    }
                    /* Set the part number to be true as the number has a gear 
                     * adjacent to it */
                    bIsPartNumb = true;
                }
                /* If we are not in the first column and first row and the cell 
                 * north-west is not a dot */
                if (cnt4 > 0 && cnt3 > 0 && arr[cnt3-1][cnt4-1] != '.')
                {
                    /* Check if this non-dot is a second word by searching
                     * through the list of stored co-ordinates */
                    auto it = std::find(vXYCord.begin(), vXYCord.end(), (cnt3-1)*nYCordMax + (cnt4-1));

                    /* If the co-ordinate is already there, that means there was
                     * a number before that shares the same gear and find that 
                     * number that was adjacent to the gear */
                    if (it != vXYCord.end())
                    {
                        /* The number would be the same index as the co-ordinate */
                        nSecondNumber = numbers[it - vXYCord.begin()];
                        /* Set is gear to true */
                        bIsGear = true;
                    }
                    else
                    {
                        /* If there is no co-ordinate, save the co-ordinate
                         * (x*y_max, y) for later use */
                        vXYCord.push_back((cnt3-1)*nYCordMax+cnt4-1);
                        /* Also store the number that was adjacent to the gear */
                        numbers.push_back(atoll(number.c_str()));
                    }
                    /* Set the part number to be true as the number has a gear 
                     * adjacent to it */
                    bIsPartNumb = true;
                }
                /* If we are not in the first column and last row and the cell 
                 * south-west is not a dot */
                if (cnt4 > 0 && cnt3 < cnt1-1 && arr[cnt3+1][cnt4-1] != '.')
                {
                    /* Check if this non-dot is a second word by searching
                     * through the list of stored co-ordinates */
                    auto it = std::find(vXYCord.begin(), vXYCord.end(), (cnt3+1)*nYCordMax + (cnt4-1));

                    /* If the co-ordinate is already there, that means there was
                     * a number before that shares the same gear and find that 
                     * number that was adjacent to the gear */
                    if (it != vXYCord.end())
                    {
                        /* The number would be the same index as the co-ordinate */
                        nSecondNumber = numbers[it - vXYCord.begin()];
                        /* Set is gear to true */
                        bIsGear = true;
                    }
                    else
                    {
                        /* If there is no co-ordinate, save the co-ordinate
                         * (x*y_max, y) for later use */
                        vXYCord.push_back((cnt3+1)*nYCordMax+cnt4-1);
                        /* Also store the number that was adjacent to the gear */
                        numbers.push_back(atoll(number.c_str()));
                    }
                    /* Set the part number to be true as the number has a gear 
                     * adjacent to it */
                    bIsPartNumb = true;
                }
                /* If we are not in the last column and first row and the cell 
                 * north-east is not a dot */
                if (cnt5 < cnt2 && cnt3 > 0 && arr[cnt3-1][cnt5] != '.')
                {
                    /* Check if this non-dot is a second word by searching
                     * through the list of stored co-ordinates */
                    auto it = std::find(vXYCord.begin(), vXYCord.end(), (cnt3-1)*nYCordMax + cnt5);

                    /* If the co-ordinate is already there, that means there was
                     * a number before that shares the same gear and find that 
                     * number that was adjacent to the gear */
                    if (it != vXYCord.end())
                    {
                        /* The number would be the same index as the co-ordinate */
                        nSecondNumber = numbers[it - vXYCord.begin()];
                        /* Set is gear to true */
                        bIsGear = true;
                    }
                    else
                    {
                        /* If there is no co-ordinate, save the co-ordinate
                         * (x*y_max, y) for later use */
                        vXYCord.push_back((cnt3-1)*nYCordMax+cnt5);
                        /* Also store the number that was adjacent to the gear */
                        numbers.push_back(atoll(number.c_str()));
                    }
                    /* Set the part number to be true as the number has a gear 
                     * adjacent to it */
                    bIsPartNumb = true;
                }
                /* If we are not in the last column and last row and the cell 
                 * south-east is not a dot */
                if (cnt5 < cnt2 && cnt3 < cnt1-1 && arr[cnt3+1][cnt5] != '.')
                {
                    /* Check if this non-dot is a second word by searching
                     * through the list of stored co-ordinates */
                    auto it = std::find(vXYCord.begin(), vXYCord.end(), (cnt3+1)*nYCordMax + cnt5);

                    /* If the co-ordinate is already there, that means there was
                     * a number before that shares the same gear and find that 
                     * number that was adjacent to the gear */
                    if (it != vXYCord.end())
                    {
                        /* The number would be the same index as the co-ordinate */
                        nSecondNumber = numbers[it - vXYCord.begin()];
                        /* Set is gear to true */
                        bIsGear = true;
                    }
                    else
                    {
                        /* If there is no co-ordinate, save the co-ordinate
                         * (x*y_max, y) for later use */
                        vXYCord.push_back((cnt3+1)*nYCordMax+cnt5);
                        /* Also store the number that was adjacent to the gear */
                        numbers.push_back(atoll(number.c_str()));
                    }
                    /* Set the part number to be true as the number has a gear 
                     * adjacent to it */
                    bIsPartNumb = true;
                }
                /* Move the count to the end of the number-1 */
                cnt4 = cnt5-1;
            }
            /* If it is a part number, add the number to part 1's solution */
            if (bIsPartNumb == true)
            {
                nPartOneSoln += atoll(number.c_str());
            }
            /* If it is a gear, multiply number with the previous number 
             * (second number) and add it to part two's solution */
            if (bIsGear == true)
            {
                nPartTwoSoln += (atoll(number.c_str()) * nSecondNumber);
            }
        }
    }

    /* Display part a and b answers */
    cout << "Part (a): " << nPartOneSoln << endl;

    cout << "Part (b): " << nPartTwoSoln << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

