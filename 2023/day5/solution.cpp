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

    /* Store the seeds in this vector */
    vector <int64_t> nSeeds;

    /* Store the destination indices of each step in this vector */
    vector <int64_t> nMapD[10];
    /* Store the source indices of each step in this vector */
    vector <int64_t> nMapS[10];
    /* Store the range indices of each step in this vector */
    vector <int64_t> nMapR[10];

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    /* Start value and end value after each category */
    vector <int64_t> nSeedPair[2];

    /* To store a word for temp purpose */
    string word;

    /* Read the first line */
    fgets(arr[cnt1], sizeof(arr[cnt1]), fp);
    stringstream iss_line1(arr[cnt1]);

    /* Increment line count */
    cnt1++;

    /* Read the first word "seeds:" and ignore it */
    iss_line1 >> word;

    /* Start reading other words which are seed numbers */
    while (iss_line1 >> word)
    {
        /* Read the first number and store it in seeds and begin vectors */
        cnt3 = atoll(word.c_str());
        nSeedPair[0].push_back(cnt3);
        nSeeds.push_back(cnt3);

        /* Read the first number and store it in seeds and end vectors */
        iss_line1 >> word;
        cnt4 = atoll(word.c_str());
        nSeeds.push_back(cnt4);
        nSeedPair[1].push_back(cnt4 + cnt3 - 1);
    }

    /* Start this with negative 1 */
    cnt2 = -1;

    /* Reset word to NULL */
    word = "";

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        stringstream iss(arr[cnt1]);

        /* Read the first word */
        iss >> word;

        /* If the first word's first letter is an alphabet, increment a count to 
         * perform the next set of category */
        if ((word[0] >= 'a' && word[0] <= 'z'))
        {
            ++cnt2;
        }
        /* If not, if it is a number, start storing the three numbers: 
         * (dest, source, range) */
        else if (word.size() > 0)
        {
            nMapD[cnt2].push_back(atoll(word.c_str()));
            iss >> word;
            nMapS[cnt2].push_back(atoll(word.c_str()));
            iss >> word;
            nMapR[cnt2].push_back(atoll(word.c_str()));
        }

        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Increment this to indicate the last category */
    cnt2++;

    /* For each category - Part 1 */
    for (cnt3 = 0; cnt3 < cnt2; cnt3++)
    {
        /* Perform operation for each pair of seeds */
        for (cnt4 = 0; cnt4 < nSeeds.size(); cnt4++)
        {
            /* Check in each category */
            for (cnt5 = 0; cnt5 < nMapS[cnt3].size(); cnt5++)
            {
                /* If between the range (source, source+range) */
                if ((nSeeds[cnt4] >= nMapS[cnt3][cnt5]) && 
                    (nSeeds[cnt4] < (nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5])))
                {
                    /* Update seed value to destination */
                    nSeeds[cnt4] = nSeeds[cnt4] + nMapD[cnt3][cnt5] - nMapS[cnt3][cnt5];
                    break;
                }
            }
        }
    }

    /* Compute the minimum value */
    nPartOneSum = nSeeds[0];

    for (cnt4 = 1; cnt4 < nSeeds.size(); cnt4++)
    {
        /* Compute min */
        if (nPartOneSum > nSeeds[cnt4])
        {
            nPartOneSum = nSeeds[cnt4];
        }
    }

    /* For each category - Part 2 */
    for (cnt3 = 0; cnt3 < cnt2; cnt3++)
    {
        /* Perform operation for each pair of seeds */
        for (cnt4 = 0; cnt4 < nSeedPair[0].size(); cnt4++)
        {
            /* Check in each category */
            for (cnt5 = 0; cnt5 < nMapS[cnt3].size(); cnt5++)
            {
                /* If the operation cannot be performed, skip to next category */
                if ((nMapS[cnt3][cnt5] > nSeedPair[1][cnt4]) || 
                    (nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5] - 1 < nSeedPair[0][cnt4]))
                {
                    continue;
                }
                /* If the pair (pair[0], pair[1]) is between source and source + range -1,
                 * Update both pair[0] and pair[1] to destination values:
                 * (pair[0] + offset, pair[1] + offset) */
                if ((nMapS[cnt3][cnt5] <= nSeedPair[0][cnt4]) && 
                    ((nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5] - 1) >= nSeedPair[1][cnt4]))
                {
                    nSeedPair[0][cnt4] = nSeedPair[0][cnt4] + (nMapD[cnt3][cnt5]) - nMapS[cnt3][cnt5];
                    nSeedPair[1][cnt4] = nSeedPair[1][cnt4] + (nMapD[cnt3][cnt5]) - nMapS[cnt3][cnt5];
                    break;
                }
                /* If the pair (pair[0], pair[1]) is such that, pair[0] is after 
                 * source value but pair[1] is also after destination value, 
                 * then split as: (pair[0] + offset, destination + range-1)
                 * Then, append the missing, i.e., (source + range, pair[1]) to
                 * compute next. */
                else if ((nMapS[cnt3][cnt5] <= nSeedPair[0][cnt4]) && 
                         ((nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5] - 1) < nSeedPair[1][cnt4]))
                {
                    int64_t nBegNumb = nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5];
                    int64_t nEndNumb = nSeedPair[1][cnt4];
                    nSeedPair[0][cnt4] = nSeedPair[0][cnt4] + (nMapD[cnt3][cnt5]) - nMapS[cnt3][cnt5];
                    nSeedPair[1][cnt4] = (nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5] - 1) + (nMapD[cnt3][cnt5]) - nMapS[cnt3][cnt5];
                    nSeedPair[0].push_back(nBegNumb);
                    nSeedPair[1].push_back(nEndNumb);
                    break;
                }
                /* If the pair (pair[0], pair[1]) is such that, pair[0] is before 
                 * source value and pair[1] is also before destination value, 
                 * then split as: (destination, pair[1] + offset)
                 * Then, append the missing, i.e., (pair[0], source-1) to
                 * compute next. */
                else if ((nMapS[cnt3][cnt5] > nSeedPair[0][cnt4]) && 
                         ((nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5] - 1) >= nSeedPair[1][cnt4]))
                {
                    int64_t nBegNumb = nSeedPair[0][cnt4];
                    int64_t nEndNumb = nMapS[cnt3][cnt5] - 1;

                    nSeedPair[0][cnt4] = nMapS[cnt3][cnt5] + (nMapD[cnt3][cnt5]) - nMapS[cnt3][cnt5];
                    nSeedPair[1][cnt4] = nSeedPair[1][cnt4] + (nMapD[cnt3][cnt5]) - nMapS[cnt3][cnt5];
                    nSeedPair[0].push_back(nBegNumb);
                    nSeedPair[1].push_back(nEndNumb);
                    break;
                }
                /* If the pair (pair[0], pair[1]) is such that, pair[0] is before 
                 * source value and pair[1] is after destination value, 
                 * then split as: (destination, destination + range-1)
                 * Then, append the missing, i.e., (pair[0], source-1) and
                 * (source + range, pair[1]) to compute next. */
                else if ((nMapS[cnt3][cnt5] > nSeedPair[0][cnt4]) && 
                         ((nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5] - 1) < nSeedPair[1][cnt4]))
                {
                    int64_t nBegNumb1 = nSeedPair[0][cnt4];
                    int64_t nEndNumb1 = nMapS[cnt3][cnt5] - 1;
                    int64_t nBegNumb2 = nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5];
                    int64_t nEndNumb2 = nSeedPair[1][cnt4];

                    nSeedPair[0][cnt4] = nMapS[cnt3][cnt5] + (nMapD[cnt3][cnt5]) - nMapS[cnt3][cnt5];
                    nSeedPair[1][cnt4] = (nMapS[cnt3][cnt5] + nMapR[cnt3][cnt5] - 1) + (nMapD[cnt3][cnt5]) - nMapS[cnt3][cnt5];
                    nSeedPair[0].push_back(nBegNumb1);
                    nSeedPair[1].push_back(nEndNumb1);
                    nSeedPair[0].push_back(nBegNumb2);
                    nSeedPair[1].push_back(nEndNumb2);
                    break;
                }
            }
        }
    }
    /* Compute the minimum so just use pair[0] as they are the least */
    nPartTwoSum = nSeedPair[0][0];

    for (cnt4 = 1; cnt4 < nSeedPair[0].size(); cnt4++)
    {
        /* Compute min */
        if (nPartTwoSum > nSeedPair[0][cnt4])
        {
            nPartTwoSum = nSeedPair[0][cnt4];
        }
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

