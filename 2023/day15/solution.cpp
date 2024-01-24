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

char arr2[100000];

int64_t computeHash(string word, bool fullWord);

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

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    /* Lens label inside each of 256 boxes */
    vector <string> nLensLabel[256];
    /* Lens value inside each of 256 boxes */
    vector <int64_t> nLensValue[256];

    /* Read each line from file */
    while (fgets(arr2, sizeof(arr2), fp) != NULL)
    {
        /* Store the input string from arr2 */
        string inputStr = arr2;

        /* Replace all ',' with spaces so that it would be easy to split */
        for (cnt2 = 0; cnt2 < inputStr.size()-1; cnt2++)
        {
            if (inputStr[cnt2] == ',')
            {
                inputStr[cnt2] = ' ';
            }
        }

        stringstream iss(inputStr);
        string word;

        /* Split each word */
        while (iss >> word)
        {
            /* Compute the hash of the whole word for part 1 */
            cnt2 = computeHash(word, true);
            nPartOneSum += cnt2;

            /* Compute the hash of the label only to get the box number */
            cnt2 = computeHash(word, false);

            string label = "";
            for (cnt4 = 0; word[cnt4] != '-' && word[cnt4] != '='; cnt4++)
            {
                label += word[cnt4];
            }
            /* If the lens needs to be removed */
            if (word[word.size()-1] == '-')
            {
                /* Find the lens with that label */
                for (cnt4 = 0; cnt4 < nLensLabel[cnt2].size(); cnt4++)
                {
                    if (label == nLensLabel[cnt2][cnt4])
                    {
                        /* Remove both lens and the focal length */
                        nLensLabel[cnt2].erase(nLensLabel[cnt2].begin()+cnt4);
                        nLensValue[cnt2].erase(nLensValue[cnt2].begin()+cnt4);
                    }
                }
            }
            /* If a lens needs to be updated or added */
            else
            {
                /* Get the value of focal length */
                int64_t nFocalLength = word[word.size()-1]-'0';

                /* Check if the lens is already present */
                for (cnt4 = 0; cnt4 < nLensLabel[cnt2].size(); cnt4++)
                {
                    /* If already present, update the focal length */
                    if (label == nLensLabel[cnt2][cnt4])
                    {
                        nLensValue[cnt2][cnt4] = nFocalLength;
                        break;
                    }
                }
                /* If not present, add the lens into the correct box */
                if (cnt4 == nLensLabel[cnt2].size())
                {
                    nLensLabel[cnt2].push_back(label);
                    nLensValue[cnt2].push_back(nFocalLength);
                }
            }
        }

        /* Increment count to move to next line */
        ++cnt1;
    }


    /* Compute the focusing power */
    for (cnt5 = 0; cnt5 < 256; cnt5++)
    {
        // cout << cnt5 << " " << nLensLabel[cnt5].size() << endl;
        for (cnt4 = 0; cnt4 < nLensLabel[cnt5].size(); cnt4++)
        {
            nPartTwoSum += (cnt5 + 1) * (cnt4 + 1) * nLensValue[cnt5][cnt4];
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

/* Compute the hash of full word or just the label */
int64_t computeHash(string word, bool fullWord)
{
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;

    if (fullWord == true)
    {
        for (cnt1 = 0; cnt1 < word.size(); cnt1++)
        {
            /* Hash = (prev_hash + ASCII*17) MOD 256  */
            cnt2 = ((cnt2 + int64_t(word[cnt1])) * 17) % 256;
        }
    }
    else
    {
        for (cnt1 = 0; word[cnt1] != '-' && word[cnt1] != '='; cnt1++)
        {
            /* Hash = (prev_hash + ASCII*17) MOD 256  */
            cnt2 = ((cnt2 + int64_t(word[cnt1])) * 17) % 256;
        }
    }
    return cnt2;
}
