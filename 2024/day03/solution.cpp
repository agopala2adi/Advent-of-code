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

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    bool bEnabled = true;

    /* Read each line from file */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        string instruction(arr);

        for (cnt2 = 0; cnt2 < instruction.size(); ++cnt2)
        {
            /* Check if the instruction contains the combination "mul(" */
            if (instruction[cnt2] == 'm' && instruction[cnt2+1] == 'u' && instruction[cnt2+2] == 'l' && instruction[cnt2+3] == '(')
            {
                /* Skip the count by 4 to move past "mul(" */
                cnt2 += 4;

                /* To store the first and second numbers as strings */
                string sFirstNumb, sSecondNumb;

                /* Accumulate all the characters that are between 0 and 9 to get 
                 * the first number */
                while (instruction[cnt2] >= '0' && instruction[cnt2] <= '9')
                {
                    sFirstNumb += instruction[cnt2];
                    cnt2++;
                }
                /* Check if the next character after the number is a comma */
                if (instruction[cnt2] != ',')
                {
                    /* Else, skip accumulation */
                    continue;
                }
                cnt2++;
                /* Accumulate all the characters that are between 0 and 9 to get 
                 * the second number  */
                while (instruction[cnt2] >= '0' && instruction[cnt2] <= '9')
                {
                    sSecondNumb += instruction[cnt2];
                    cnt2++;
                }
                /* Check if the next char after the second number is a close 
                 * parenthesis */
                if (instruction[cnt2] != ')')
                {
                    /* Else, skip accumulation */
                    continue;
                }

                /* Multiply the numbers after converting to ints and add to res */
                nFirstPart += (stoll(sFirstNumb) * stoll(sSecondNumb));

                /* If the multiplication is enabled by seeing a do(), 
                 * add the result to the part b of the problem */
                if (bEnabled)
                {
                    nSecondPart += (stoll(sFirstNumb) * stoll(sSecondNumb));
                }
            }
            /* Check if you read a don't() */
            else if (instruction[cnt2] == 'd' && 
                     instruction[cnt2+1] == 'o' && 
                     instruction[cnt2+2] == 'n' && 
                     instruction[cnt2+3] == '\'' && 
                     instruction[cnt2+4] == 't' && 
                     instruction[cnt2+5] == '(' && 
                     instruction[cnt2+6] == ')')
            {
                /* Disable for part (b) */
                bEnabled = false;
                cnt2 += 6;
            }
            /* Check if you read a do() */
            else if (instruction[cnt2] == 'd' && 
                     instruction[cnt2+1] == 'o' && 
                     instruction[cnt2+2] == '(' && 
                     instruction[cnt2+3] == ')')
            {
                /* Enable for part (b) */
                bEnabled = true;
                cnt2 += 3;
            }
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

