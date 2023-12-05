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
    cout << "Start Time: " << std::ctime(&start_time) << endl;

    FILE* fp = fopen("input.txt", "r");

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

    int64_t nLines = 0;

    /* The number of copies for each card */
    int64_t nCardCopies[500];

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Set copies to 1 initially */
        nCardCopies[cnt1] = 1;
        /* Increment count to move to next line */
        ++cnt1;
    }
    nLines = cnt1;


    /* Now read each file */
    for (cnt1 = 0; cnt1 < nLines; cnt1++)
    {
        stringstream iss(arr[cnt1]);
        string word;
        vector<int64_t> vsWinners;
        vector<int64_t> vsMine;
        int64_t nWinners = 0;

        /* Read the first and second word - card and number - not relevant */
        iss >> word;
        iss >> word;

        /* Read all winner cards */
        while ((iss >> word) && word != "|")
        {
            /* Store them in winners list */
            vsWinners.push_back(atoi(word.c_str()));
        }
        /* After that, read all of my cards */
        while ((iss >> word))
        {
            /* Store them in my card list */
            vsMine.push_back(atoi(word.c_str()));
        }
        nWinners = 0;

        /* Run a double loop for all of my number list, check if there is a number 
         * in the winner list*/
        for (cnt2 = 0; cnt2 < vsMine.size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < vsWinners.size(); cnt3++)
            {
                /* If there is a card, increment winners */
                if (vsMine[cnt2] == vsWinners[cnt3])
                {
                    ++nWinners;
                    break;
                }
            }
        }
        /* Increment part 1 sum with 2^(winners-1) */
        if (nWinners > 0)
        {
            nPartOneSum += 1 << (nWinners - 1);
        }

        /* For part 2, increment the index of the games that are won */
        for (cnt2 = 0; cnt2 < nWinners; cnt2++)
        {
            /* Sanity to not go out of bounds */
            if (cnt2 + cnt1 + 1 < nLines)
            {
                /* Add the value of current cards as those many games will
                 * be played */
                nCardCopies[cnt2+cnt1+1] += nCardCopies[cnt1];
            }
        }

    }

    /* Count the total number of cards for each game */
    for (cnt2 = 0; cnt2 < nLines; cnt2++)
    {
        nPartTwoSum += nCardCopies[cnt2];
    }


    /* Display part a and b answers */
    cout << "Part (a): " << nPartOneSum << endl;

    cout << "Part (b): " << nPartTwoSum << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

