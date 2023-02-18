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
char arr[100][20000];

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

    vector<int64_t> sequence;
    vector<int64_t> sequenceP2;
    vector<int64_t> sequenceCpy;
    vector<int64_t> sequenceCpyP2;

    /* To make each value unique, multiply the index number with a large value
     * and add the number */
    int64_t nMaxIndex = 100000000000000ll;
    int64_t decryptionKey = 811589153ll;

    /* Read every line */
    while (feof(fp) == 0)
    {
        int64_t x;
        int64_t y;
        fscanf(fp, "%" PRId64 "\n",&x);
        if (x == 0)
        {
            /* Store the index of zero */
            cnt9 = cnt1;
        }
        /* Part b, multiply each number with the decryption key */
        y = x * decryptionKey;
        /* If the number is less than zero, store negative value of large
         * number times index plus number */
        if (x < 0)
        {
            x = (int64_t)(((int64_t)-cnt1 * (int64_t)nMaxIndex) + (int64_t)x);
            y = (int64_t)(((int64_t)-cnt1 * (int64_t)nMaxIndex) + (int64_t)y);
        }
        else
        {
            x = (int64_t)((int64_t)cnt1 * (int64_t)nMaxIndex) + (int64_t)x;
            y = (int64_t)((int64_t)cnt1 * (int64_t)nMaxIndex) + (int64_t)y;
        }
        /* Store the result in sequence, create a copy in sequenceCpy */
        sequence.push_back(x);
        sequenceCpy.push_back(x);
        /* Store the part b result in sequenceP2, create a copy in sequenceCpyP2 */
        sequenceP2.push_back(y);
        sequenceCpyP2.push_back(y);
        /* Increment the count */
        ++cnt1;
    }

    /* Loop throught all the numbers */
    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        /* Take the value of the number from the copy */
        cnt3 = sequenceCpy[cnt2];
        /* Find the position where the number is in the original sequence */
        auto it = find(sequence.begin(), sequence.end(), cnt3);
        /* Check if the number is present in the original sequence, it should be present */
        if (it != sequence.end())
        {
            /* Calculate the index by subracting the stating positon */
            cnt4 = it - sequence.begin();
        }

        /* If the number is less than zero, assign nagative */
        if (sequenceCpy[cnt2] < 0)
        {
            /* To get the original number from the large multiplication, find the
             * reminder after dividing by the large number */
            cnt5 = -(-sequence[cnt4] % nMaxIndex);
        }
        else
        {
            /* To get the original number from the large multiplication, find the
             * reminder after dividing by the large number */
            cnt5 = sequence[cnt4] % nMaxIndex;
        }
        /* Store the value temp in cnt7 */
        cnt7 = cnt5;

        /* If the number is lesser than zero, keep adding sequence.size()-1
         * until it becomes greater than zero */
        if (cnt5 < 0)
        {
            cnt6 = (-cnt5) / (sequence.size() - 1) + 1;
            cnt5 += cnt6 * (sequence.size() - 1);
        }

        /* Get the final position where the number has to be placed by adding
         * the number with its current positon */
        cnt6 = cnt4 + cnt5;
        /* Bring the number between 0 and size - 1 */
        if (cnt6 > sequence.size() - 1)
        {
            cnt5 = cnt6 / (sequence.size() - 1);
            cnt6 -= cnt5 * (sequence.size() - 1);
        }
        /* Erase the number and place it in new position */
        sequence.erase(it);
        sequence.insert(sequence.begin() + cnt6, cnt3);
    }

    /* Get the current value where zero is stored (remember, zero is also stored
     * with multiplication factor with its index) */
    cnt3 = sequenceCpy[cnt9];
    /* Get the position where it is in the sequence */
    auto it = find(sequence.begin(), sequence.end(), cnt3);
    /* Get the index where it is in the sequence */
    cnt4 = it - sequence.begin();
    /* Find the value of the number in positon 0 plus 1000 */
    cnt5 = sequence[(cnt4 + 1000) % sequence.size()];
    /* Convet the number to actual number from large number */
    if (cnt5 < 0)
    {
        cnt5 = -(-cnt5 % nMaxIndex);
    }
    else
    {
        cnt5 = cnt5 % nMaxIndex;
    }
    cnt6 = cnt5;
    /* Find the value of the number in positon 0 plus 2000 */
    cnt5 = sequence[(cnt4 + 2000) % sequence.size()];
    /* Convet the number to actual number from large number */
    if (cnt5 < 0)
    {
        cnt5 = -(-cnt5 % nMaxIndex);
    }
    else
    {
        cnt5 = cnt5 % nMaxIndex;
    }
    cnt6 += cnt5;
    /* Find the value of the number in positon 0 plus 3000 */
    cnt5 = sequence[(cnt4 + 3000) % sequence.size()];
    /* Convet the number to actual number from large number */
    if (cnt5 < 0)
    {
        cnt5 = -(-cnt5 % nMaxIndex);
    }
    else
    {
        cnt5 = cnt5 % nMaxIndex;
    }
    cnt6 += cnt5;

    /* Display the value after finding the sum at 1000'th 2000'th and 3000'th positon */
    cout << "Part (a): " << (int64_t)cnt6 << endl;

    /* Run the same loop for 10 iterations */
    for (cnt10 = 0; cnt10 < 10; cnt10++)
    {
        for (cnt2 = 0; cnt2 < cnt1; cnt2++)
        {
            /* Take the value of the number from the copy */
            cnt3 = sequenceCpyP2[cnt2];
            /* Find the position where the number is in the original sequence */
            it = find(sequenceP2.begin(), sequenceP2.end(), cnt3);
            /* Check if the number is present in the original sequence, it should be present */
            if (it != sequenceP2.end())
            {
                /* Calculate the index by subracting the stating positon */
                cnt4 = it - sequenceP2.begin();
            }

            /* If the number is less than zero, assign nagative */
            if (sequenceCpyP2[cnt2] < 0)
            {
                /* To get the original number from the large multiplication, find the
                 * reminder after dividing by the large number */
                cnt5 = -(-sequenceP2[cnt4] % nMaxIndex);
            }
            else
            {
                /* To get the original number from the large multiplication, find the
                 * reminder after dividing by the large number */
                cnt5 = sequenceP2[cnt4] % nMaxIndex;
            }
            /* Store the value temp in cnt7 */
            cnt7 = cnt5;

            /* If the number is lesser than zero, keep adding sequence.size()-1
             * until it becomes greater than zero */
            if (cnt5 < 0)
            {
                cnt6 = (-cnt5) / (sequenceP2.size() - 1) + 1;
                cnt5 += cnt6 * (sequenceP2.size() - 1);
            }

            /* Get the final position where the number has to be placed by adding
             * the number with its current positon */
            cnt6 = cnt4 + cnt5;
            /* Bring the number between 0 and size - 1 */
            if (cnt6 > sequenceP2.size() - 1)
            {
                cnt5 = cnt6 / (sequenceP2.size() - 1);
                cnt6 -= cnt5 * (sequenceP2.size() - 1);
            }
            /* Erase the number and place it in new position */
            sequenceP2.erase(it);
            sequenceP2.insert(sequenceP2.begin() + cnt6, cnt3);
        }
    }

    /* Get the current value where zero is stored (remember, zero is also stored
     * with multiplication factor with its index) */
    cnt3 = sequenceCpyP2[cnt9];
    /* Get the position where it is in the sequence */
    it = find(sequenceP2.begin(), sequenceP2.end(), cnt3);
    /* Get the index where it is in the sequence */
    cnt4 = it - sequenceP2.begin();
    /* Find the value of the number in positon 0 plus 1000 */
    cnt5 = sequenceP2[(cnt4 + 1000) % sequenceP2.size()];
    /* Convet the number to actual number from large number */
    if (cnt5 < 0)
    {
        cnt5 = -(-cnt5 % nMaxIndex);
    }
    else
    {
        cnt5 = cnt5 % nMaxIndex;
    }
    cnt6 = cnt5;
    /* Find the value of the number in positon 0 plus 2000 */
    cnt5 = sequenceP2[(cnt4 + 2000) % sequenceP2.size()];
    /* Convet the number to actual number from large number */
    if (cnt5 < 0)
    {
        cnt5 = -(-cnt5 % nMaxIndex);
    }
    else
    {
        cnt5 = cnt5 % nMaxIndex;
    }
    cnt6 += cnt5;
    /* Find the value of the number in positon 0 plus 3000 */
    cnt5 = sequenceP2[(cnt4 + 3000) % sequenceP2.size()];
    /* Convet the number to actual number from large number */
    if (cnt5 < 0)
    {
        cnt5 = -(-cnt5 % nMaxIndex);
    }
    else
    {
        cnt5 = cnt5 % nMaxIndex;
    }
    cnt6 += cnt5;

    /* Display the value after finding the sum at 1000'th 2000'th and 3000'th positon */
    cout << "Part (b): " << (int64_t)cnt6 << endl;

    fseek(fp, 0L, SEEK_SET);

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

