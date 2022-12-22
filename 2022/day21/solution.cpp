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

/* List of monkeys in a string */
vector<string> monkeys;
/* Operation performed by the monkey:
 * index0 - index of monkey operand 1
 * index1 - (+,-,*,/)
 * index2 - index of monkey operand 2
 */
vector<int64_t> monkeyOper[3];
/* Computation result of a particular monkey */
unordered_map<int64_t, int64_t> monkeyNumber;

/* Recursive function to compute the result of a monkey */
int64_t getMonkkeyNumber(string monkeyName);

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

    /* Read every line */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        /* Split the line into multiple words */
        stringstream iss(arr[cnt1]);
        string word;
        string monkeyName;

        /* Extract first word */
        iss >> monkeyName;

        /* If the last character of the first word is a ":", remove it */
        if (monkeyName[monkeyName.size()-1] == ':')
        {
            monkeyName.pop_back();
        }
        /* Store the word into monkeys list */
        monkeys.push_back(monkeyName);
        /* Identify the index of "humn" */
        if (monkeyName == "humn")
        {
            /* Store this index into cnt3 */
            cnt3 = cnt1;
        }

        /* Read the second word */
        iss >> word;
        /* If the second word is a number, convert string to a number and
         * store it into the monkeyNumber array */
        if (word[0] >= '0' && word[0] <= '9')
        {
            monkeyNumber[cnt1] = stoll(word);
        }
        /* Else store -1, as -1 is not a number in the input */
        else
        {
            monkeyNumber[cnt1] = -1;
        }
        /* Increment the count */
        ++cnt1;
    }
    fseek(fp, 0L, SEEK_SET);

    /* Store the copy of number of lines */
    cnt2 = cnt1;
    cnt1 = 0;

    /* Run the loop once again */
    for (cnt1 = 0; cnt1 < cnt2; cnt1++)
    {
        /* Split the line into multiple words */
        stringstream iss(arr[cnt1]);
        string word;
        string monkeyName;

        /* Extract first word: Ignore */
        iss >> monkeyName;

        /* Extract second word */
        iss >> word;
        /* If the second word is a number, store -1 in the operation as no
         * operation is required */
        if (word[0] >= '0' && word[0] <= '9')
        {
            monkeyOper[0].push_back(-1);
            monkeyOper[1].push_back(-1);
            monkeyOper[2].push_back(-1);
        }
        else
        {
            /* If the second word is a monkey, store the index of the monkey in
             * the first operation */
            auto it = find(monkeys.begin(), monkeys.end(), word);
            monkeyOper[0].push_back(it - monkeys.begin());
            if (monkeyName == "root:")
            {
                /* If the monkey is root, store the index of root's first operation
                 * monkey's index into cnt4 */
                cnt4 = it - monkeys.begin();
            }
            /* Extract the third word */
            iss >> word;
            /* The third word is an operation: If the operation is (+, -, *, /)
             * store (0, 1, 2, 3) into the second operation respectively*/
            if (word == "+")
            {
                monkeyOper[1].push_back(0);
            }
            else if (word == "-")
            {
                monkeyOper[1].push_back(1);
            }
            else if (word == "*")
            {
                monkeyOper[1].push_back(2);
            }
            else if (word == "/")
            {
                monkeyOper[1].push_back(3);
            }
            /* Extract the fourth word */
            iss >> word;
            /* Find the index of the fourth word monkey */
            it = find(monkeys.begin(), monkeys.end(), word);
            /* Store the index into the third operation array */
            monkeyOper[2].push_back(it - monkeys.begin());
            if (monkeyName == "root:")
            {
                /* If the monkey is root, store the index of root's 2nd operation
                 * monkey's index into cnt5 */
                cnt5 = it - monkeys.begin();
            }
        }
    }

    /* Display the calculation result of monkey "root" */
    cout << "Part (a): " << getMonkkeyNumber("root") << endl;

    /* Large value into cnt11: Use this to do a variable step-size search search
     */
    cnt11 = 1000000000000;

    /* Start the count with zero */
    cnt2 = 0;
    while (1)
    {
        /* Assign the value into monkey with "humn", i.e., cnt3 */
        monkeyNumber[cnt3] = cnt2;
        for (cnt6 = 0; cnt6 < cnt1; cnt6++)
        {
            /* Reset all monkeys that do not have a number to begin with */
            if (monkeyOper[0][cnt6] != -1)
            {
                monkeyNumber[cnt6] = -1;
            }
        }
        /* Get the final calculation result of root's first monkey */
        cnt8 = getMonkkeyNumber(monkeys[cnt4]);
        /* Get the final calculation result of root's second monkey */
        cnt7 = getMonkkeyNumber(monkeys[cnt5]);
        /* If the result is equal quit from computation */
        if (cnt7 == cnt8)
        {
            break;
        }
        else
        {
            /* If the second result is larger than first, we have an over shoot
             */
            if ((cnt7 - cnt8) > 0)
            {
                /* Subtract the index from previously incremented step-size */
                cnt2 -= cnt11;
                if (cnt11 > 10)
                {
                    /* Fine tune the step size by dividing it by 10 */
                    cnt11 /= 10;
                }
                /* If the step size goes below 10, or becomes close to zero,
                 * equate the step size to one, making future increments to index
                 * equal to 1 */
                else
                {
                    cnt11 = 1;
                }
            }
            else
            {
                /* If we are not there yet, increment the index by the step-size */
                cnt2 += cnt11;
            }
        }
    }

    /* Display the value of the current index */
    cout << "Part (b): " << cnt2 << endl;

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

/* Recursive function to compute the result of a monkey */
int64_t getMonkkeyNumber(string monkeyName)
{
    /* First find the index of the monkey */
    auto it = find(monkeys.begin(), monkeys.end(), monkeyName);
    int64_t nIdx;

    /* If the index is within the list of monkeys */
    if (it != monkeys.end())
    {
        /* Convert iteration, it to index, nIdx */
        nIdx = it - monkeys.begin();
        /* If the monkey already has a number assigned to it, return the number */
        if (monkeyNumber[nIdx] != -1)
        {
            return monkeyNumber[nIdx];
        }
        else
        {
            /* If no, check what operation the monkey does */
            if (monkeyOper[1][nIdx] == 0)
            {
                /* If addition, add the results of monkey1 and monkey2 */
                monkeyNumber[nIdx] = (getMonkkeyNumber(monkeys[monkeyOper[0][nIdx]]) + getMonkkeyNumber(monkeys[monkeyOper[2][nIdx]]));
            }
            else if (monkeyOper[1][nIdx] == 1)
            {
                /* If subtraction, subtract the result of monkey2 from result of monkey1 */
                monkeyNumber[nIdx] = (getMonkkeyNumber(monkeys[monkeyOper[0][nIdx]]) - getMonkkeyNumber(monkeys[monkeyOper[2][nIdx]]));
            }
            else if (monkeyOper[1][nIdx] == 2)
            {
                /* If multiplication, multiply the results of monkey1 and monkey2 */
                monkeyNumber[nIdx] = (getMonkkeyNumber(monkeys[monkeyOper[0][nIdx]]) * getMonkkeyNumber(monkeys[monkeyOper[2][nIdx]]));
            }
            else if (monkeyOper[1][nIdx] == 3)
            {
                /* If division, compute monkey1's result over monkey2's result */
                monkeyNumber[nIdx] = (getMonkkeyNumber(monkeys[monkeyOper[0][nIdx]]) / getMonkkeyNumber(monkeys[monkeyOper[2][nIdx]]));
            }
            return monkeyNumber[nIdx];
        }
    }
    return 0;
}
