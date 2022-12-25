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
char arr[10000][20000];

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

    int64_t x_pos = 0;
    int64_t y_pos = -1;

    /* Total sum in decimal */
    int64_t nValueSum = 0;

    /* Multiplier */
    int64_t nMultipler = 1;

    /* Read every line */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        /* Read the line into a string (value in SNAFU) */
        string value5 = arr[cnt1];
        /* Remove the last "\n" */
        value5.pop_back();
        /* Value in decimal */
        int64_t nValue10 = 0;
        nMultipler = 1;

        /* Read each digit of SNAFU number from its units place */
        for (cnt2 = value5.size()-1; cnt2 >= 0; cnt2--)
        {
            /* Read the character of SNAFU in the current place */
            char number = value5[cnt2];
            /* If the number is a -, subtract a value of current multiplier from
             * the decimal result */
            if (number == '-')
            {
                nValue10 -= nMultipler;
            }
            /* Else if the number if a double -, "=", subtract twice the value of
             * currnt multiplier from the current result */
            else if (number == '=')
            {
                nValue10 -= 2 * nMultipler;
            }
            /* If the number is a 0, 1, or 2, add the result times its multiplier */
            else
            {
                nValue10 += nMultipler * (number - '0');
            }
            /* Shift the multiplier by 5*/
            nMultipler = nMultipler * 5;
        }
        /* Add the current line sum to the total */
        nValueSum += nValue10;
        /* Increment the count */
        ++cnt1;
    }

    vector<int64_t> nNosIn5;

    /* Create a maximum of 100 digits in SNAFU result */
    for (cnt2 = 0; cnt2 < 100; cnt2++)
    {
        nNosIn5.push_back(0);
    }
    cnt2 = 0;

    /* Until the value in decimal is zero, continue this */
    while (nValueSum > 0)
    {
        /* Extract the reminder when number is divided by 5 */
        int64_t nTensPlace = nValueSum % 5;

        /* If the reminder is greater than 2 */
        if (nTensPlace > 2)
        {
            /* increment the next digit to the left */
            nNosIn5[cnt2+1]++;
            /* If the number is a 3, subtract two from the current digit
             * else if the number is 4, subtract one from the current digit */
            if (nTensPlace == 3)
            {
                nNosIn5[cnt2]--;
                nNosIn5[cnt2]--;
            }
            else if (nTensPlace == 4)
            {
                nNosIn5[cnt2]--;
            }
        }
        else
        {
            /* If the number the lesser than or equal to 2, add the number
             * to the current digit */
            nNosIn5[cnt2] += nTensPlace;
            /* It could happen that the value after adding 2 is greater than 2
             * This is because the value in current place could have been
             * incremented in the previous iteration */
            if (nNosIn5[cnt2] == 3)
            {
                /* If the value is three, increment the left digit and set
                 * the current digit to -2 (giving you 5-2 = 3) */
                nNosIn5[cnt2+1]++;
                nNosIn5[cnt2] = -2;
            }
        }
        /* Divide the number by 5 */
        nValueSum /= 5;
        cnt2++;
    }

    /* To not display starting zeros */
    int64_t startingZero = 1;
    cout << "Part (a): ";

    while (cnt2 >= 0)
    {
        /* If the number is a zero and is a starting zero, don't display it */
        if (startingZero == 1 && nNosIn5[cnt2] == 0)
        {
            cnt2--;
            continue;
        }
        /* Reset starting zero, to indicate that the number is no longer zero */
        startingZero = 0;
        /* If the number is -1, display "-" */
        if (nNosIn5[cnt2] == -1)
        {
            cout << "-";
        }
        /* If the number is a -2, display a "=" */
        else if (nNosIn5[cnt2] == -2)
        {
            cout << "=";
        }
        /* If not both, display the number directly */
        else
        {
            cout << nNosIn5[cnt2];
        }
        /* Decrement the count */
        cnt2--;
    }
    cout << endl;

    fseek(fp, 0L, SEEK_SET);

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}


