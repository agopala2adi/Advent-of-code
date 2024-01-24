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

    uint64_t max_val = 0;
    uint64_t min_val = 10000000ull;

    vector<uint64_t> nElfVec;
    nElfVec.push_back(0);

    char op, my;

    int64_t nLastIdxNumb = 0;
    int64_t nFirstIdxNumb = 0;

    int64_t nFirstNumber = 0;
    int64_t nLastNumber = 0;

    int64_t nFirstPartSum = 0;
    int64_t nSecondPartSum = 0;

    /* Add spaces so that the total characters is 5 + 1 (NULL); 
     * This is required as we would be checking if the matching hit 5.
     * These space characters are just dummy where we would ignore them and 
     * not bother matching.
     * Also seems like there is no zero */
    char numbers[9][6] = {"one  ", "two  ", "three", "four ", "five ", "six  ", "seven", "eight", "nine "};

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Set the last index of the number to zero so that we can increment */
        nLastIdxNumb = 0;
        /* Set the first index of the number to zero so that we can reduce */
        nFirstIdxNumb = strlen(arr[cnt1]);

        /* Loop through the entire line from start and find for numbers 0-9 */
        for (cnt2 = 0; cnt2 < strlen(arr[cnt1]); cnt2++)
        {
            if (arr[cnt1][cnt2] >= '0' && arr[cnt1][cnt2] <= '9')
            {
                /* Store the digit in the first number variable */
                nFirstNumber = int64_t(arr[cnt1][cnt2]-'0');
                /* Store the index in the first index numb variable */
                nFirstIdxNumb = cnt2;
                break;
            }
        }
        /* Loop through the entire line from end and find for numbers 0-9 */
        for (cnt2 = strlen(arr[cnt1])-1; cnt2 >= 0; cnt2--)
        {
            if (arr[cnt1][cnt2] >= '0' && arr[cnt1][cnt2] <= '9')
            {
                /* Store the last digit in the last number variable */
                nLastNumber = int64_t(arr[cnt1][cnt2]-'0');
                /* Store the index in the last numb variable */
                nLastIdxNumb = cnt2;
                break;
            }
        }

        /* Add nFirstNumber_nLastNumber to first part sum */
        nFirstPartSum += nFirstNumber*10 + nLastNumber;

        /* For the second part loop through all the numbers from 1 to 9
         * Check if the number is present in the input line string
         */
        for (cnt3 = 0; cnt3 < 9; cnt3++)
        {
            int64_t nMatches = 0;
            /* Loop through the whole string plus some 2 charaters because of
             * added two spaces to the numbers text.
             */
            for (cnt2 = 0; cnt2 < strlen(arr[cnt1])+2; cnt2++)
            {
                /* If the current charater is same as the number character, 
                 * increment the matches. If in case of smaller numbers that 
                 * have lesser than 5 character, check for spaces too.
                 */
                if ((arr[cnt1][cnt2] == numbers[cnt3][nMatches]) || (numbers[cnt3][nMatches] == ' '))
                {
                    nMatches++;
                }
                /* This is important as the characters could also have duplicate
                 * letters like "oone", so check for first character.
                 */
                else if (arr[cnt1][cnt2] == numbers[cnt3][0])
                {
                    nMatches = 1;
                }
                /* If not reset matches variable to zero */
                else
                {
                    nMatches = 0;
                }
                /* If found a match of 5 characters stop matching more */
                if (nMatches == 5)
                {
                    break;
                }
            }
            /* If found a match and if the current character is less than 
             * first index numb computed earlier, then update the first index
             * and store the first number = current number in loop + 1
             */
            if ((nMatches == 5) && (cnt2-4) < nFirstIdxNumb)
            {
                nFirstIdxNumb = cnt2-4;
                nFirstNumber = cnt3+1;
            }
        }

        for (cnt3 = 0; cnt3 < 9; cnt3++)
        {
            int64_t nMatches = 0;
            /* Loop through the whole string plus some 2 charaters because of
             * added two spaces to the numbers text.
             */
            for (cnt2 = 0; cnt2 < strlen(arr[cnt1])+2; cnt2++)
            {
                /* If the current charater is same as the number character, 
                 * increment the matches. If in case of smaller numbers that 
                 * have lesser than 5 character, check for spaces too.
                 */
                if ((arr[cnt1][cnt2] == numbers[cnt3][nMatches]) || (numbers[cnt3][nMatches] == ' '))
                {
                    nMatches++;
                }
                /* This is important as the characters could also have duplicate
                 * letters like "oone", so check for first character again.
                 */
                else if (arr[cnt1][cnt2] == numbers[cnt3][0])
                {
                    nMatches = 1;
                }
                /* If not reset matches variable to zero */
                else
                {
                    nMatches = 0;
                }
                /* If found a match and if the current character is more than 
                 * first index numb computed earlier, then update the first index
                 * and store the first number = current number in loop + 1
                 * Do not break like last time as we want the last best number.
                 */
                if (nMatches == 5)
                {
                    if ((cnt2-4) > nLastIdxNumb)
                    {
                        nLastIdxNumb = cnt2-4;
                        nLastNumber = cnt3+1;
                    }
                    /* Reset the matches to zero and start again for the next
                     * match in the same line of input */
                    nMatches = 0;
                    /* Sometimes there could be multiple words in the same line 
                     * that are spaced apart by less than the space characters
                     * of the number, so check for that too. */
                    cnt2 -= 3;
                }
            }
        }

        /* Add the number to second part sum */
        nSecondPartSum += (nFirstNumber*10) + nLastNumber;

        /* Reset first and last number for next line of input */
        nFirstNumber = 0;
        nLastNumber = 0;
        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Display part a and b answers */
    cout << "Part (a): " << nFirstPartSum << endl;

    cout << "Part (b): " << nSecondPartSum << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

