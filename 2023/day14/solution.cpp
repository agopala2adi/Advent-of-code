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

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    vector <string> nInputRocks;
    vector <string> nFirstInput;
    vector <string> nInputRocksAfterMin;

    int64_t nRunMin = 1000ll;
    int64_t nTotalRun = 1000000000ll; 

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Read inputs and store into input rocks */
        nInputRocks.push_back(arr[cnt1]);
        /* Remove the last '\n' */
        nInputRocks[nInputRocks.size()-1].pop_back();
        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Start count with zero */
    cnt9 = 0;
    while (cnt9 < nTotalRun)
    {
        /* Increment count */
        cnt9++;
        /* North roll */
        for (cnt2 = 0; cnt2 < nInputRocks[0].size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < nInputRocks.size()-1; cnt3++)
            {
                if (nInputRocks[cnt3][cnt2] == '.')
                {
                    for (cnt4 = cnt3+1; cnt4 < nInputRocks.size(); cnt4++)
                    {
                        if (nInputRocks[cnt4][cnt2] == 'O')
                        {
                            nInputRocks[cnt4][cnt2] = '.';
                            nInputRocks[cnt3][cnt2] = 'O'; 
                            break;
                        }
                        else if (nInputRocks[cnt4][cnt2] == '#')
                        {
                            break;
                        }
                    }
                }
            }
        }
        /* Store the input for part 1 */ 
        if (nFirstInput.size() == 0)
        {
            nFirstInput = nInputRocks;
        }
        /* West roll */
        for (cnt2 = 0; cnt2 < nInputRocks.size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < nInputRocks[0].size()-1; cnt3++)
            {
                if (nInputRocks[cnt2][cnt3] == '.')
                {
                    for (cnt4 = cnt3+1; cnt4 < nInputRocks[0].size(); cnt4++)
                    {
                        if (nInputRocks[cnt2][cnt4] == 'O')
                        {
                            nInputRocks[cnt2][cnt4] = '.';
                            nInputRocks[cnt2][cnt3] = 'O'; 
                            break;
                        }
                        else if (nInputRocks[cnt2][cnt4] == '#')
                        {
                            break;
                        }
                    }
                }
            }
        }
        /* South roll */
        for (cnt2 = nInputRocks[0].size()-1; cnt2 >= 0; cnt2--)
        {
            for (cnt3 = nInputRocks.size()-1; cnt3 > 0; cnt3--)
            {
                if (nInputRocks[cnt3][cnt2] == '.')
                {
                    for (cnt4 = cnt3-1; cnt4 >= 0; cnt4--)
                    {
                        if (nInputRocks[cnt4][cnt2] == 'O')
                        {
                            nInputRocks[cnt4][cnt2] = '.';
                            nInputRocks[cnt3][cnt2] = 'O'; 
                            break;
                        }
                        else if (nInputRocks[cnt4][cnt2] == '#')
                        {
                            break;
                        }
                    }
                }
            }
        }
        /* East roll */
        for (cnt2 = nInputRocks.size()-1; cnt2 >= 0; cnt2--)
        {
            for (cnt3 = nInputRocks[0].size()-1; cnt3 > 0; cnt3--)
            {
                if (nInputRocks[cnt2][cnt3] == '.')
                {
                    for (cnt4 = cnt3-1; cnt4 >= 0; cnt4--)
                    {
                        if (nInputRocks[cnt2][cnt4] == 'O')
                        {
                            nInputRocks[cnt2][cnt4] = '.';
                            nInputRocks[cnt2][cnt3] = 'O'; 
                            break;
                        }
                        else if (nInputRocks[cnt2][cnt4] == '#')
                        {
                            break;
                        }
                    }
                }
            }
        }

        /* Once the current count reaches the minimum run count, store the value
         * of current input state into input after min variable */
        if (cnt9 == nRunMin)
        {
            nInputRocksAfterMin = nInputRocks;
        }
        /* Once we have crossed the minimum run, if the current input value has 
         * reached the input after min again, then break out of main loop */
        else if (cnt9 > nRunMin)
        {
            /* Compare if current input is same as input after min run */
            for (cnt5 = 0; cnt5 < nInputRocks.size(); cnt5++)
            {
                if (nInputRocksAfterMin[cnt5] != nInputRocks[cnt5])
                {
                    break;
                }
            }
            /* If same, store the difference between current inp and run min */
            if (cnt5 == nInputRocks.size())
            {
                cnt10 = cnt9-nRunMin;
                break;
            }
        }
    }

    /* Find the differential amount which it needs to run */
    cnt9 = (nTotalRun - nRunMin) % cnt10;

    /* Run only differential amount again */
    while (cnt9 > 0)
    {
        cnt9--;
        /* North roll */
        for (cnt2 = 0; cnt2 < nInputRocks[0].size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < nInputRocks.size()-1; cnt3++)
            {
                if (nInputRocks[cnt3][cnt2] == '.')
                {
                    for (cnt4 = cnt3+1; cnt4 < nInputRocks.size(); cnt4++)
                    {
                        if (nInputRocks[cnt4][cnt2] == 'O')
                        {
                            nInputRocks[cnt4][cnt2] = '.';
                            nInputRocks[cnt3][cnt2] = 'O'; 
                            break;
                        }
                        else if (nInputRocks[cnt4][cnt2] == '#')
                        {
                            break;
                        }
                    }
                }
            }
        }
        /* West roll */
        for (cnt2 = 0; cnt2 < nInputRocks.size(); cnt2++)
        {
            for (cnt3 = 0; cnt3 < nInputRocks[0].size()-1; cnt3++)
            {
                if (nInputRocks[cnt2][cnt3] == '.')
                {
                    for (cnt4 = cnt3+1; cnt4 < nInputRocks[0].size(); cnt4++)
                    {
                        if (nInputRocks[cnt2][cnt4] == 'O')
                        {
                            nInputRocks[cnt2][cnt4] = '.';
                            nInputRocks[cnt2][cnt3] = 'O'; 
                            break;
                        }
                        else if (nInputRocks[cnt2][cnt4] == '#')
                        {
                            break;
                        }
                    }
                }
            }
        }
        /* South roll */
        for (cnt2 = nInputRocks[0].size()-1; cnt2 >= 0; cnt2--)
        {
            for (cnt3 = nInputRocks.size()-1; cnt3 > 0; cnt3--)
            {
                if (nInputRocks[cnt3][cnt2] == '.')
                {
                    for (cnt4 = cnt3-1; cnt4 >= 0; cnt4--)
                    {
                        if (nInputRocks[cnt4][cnt2] == 'O')
                        {
                            nInputRocks[cnt4][cnt2] = '.';
                            nInputRocks[cnt3][cnt2] = 'O'; 
                            break;
                        }
                        else if (nInputRocks[cnt4][cnt2] == '#')
                        {
                            break;
                        }
                    }
                }
            }
        }
        /* East roll */
        for (cnt2 = nInputRocks.size()-1; cnt2 >= 0; cnt2--)
        {
            for (cnt3 = nInputRocks[0].size()-1; cnt3 > 0; cnt3--)
            {
                if (nInputRocks[cnt2][cnt3] == '.')
                {
                    for (cnt4 = cnt3-1; cnt4 >= 0; cnt4--)
                    {
                        if (nInputRocks[cnt2][cnt4] == 'O')
                        {
                            nInputRocks[cnt2][cnt4] = '.';
                            nInputRocks[cnt2][cnt3] = 'O'; 
                            break;
                        }
                        else if (nInputRocks[cnt2][cnt4] == '#')
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    /* Compute the count - Part 1 */
    cnt7 = cnt1;
    for (cnt5 = 0; cnt5 < nInputRocks.size(); cnt5++)
    {
        for (cnt6 = 0; cnt6 < nInputRocks[0].size(); cnt6++)
        {
            if (nFirstInput[cnt5][cnt6] == 'O')
            {
                nPartOneSum += cnt7;
            }
        }
        cnt7--;
    }

    /* Compute the count - Part 2 */
    cnt7 = cnt1;
    for (cnt5 = 0; cnt5 < nInputRocks.size(); cnt5++)
    {
        for (cnt6 = 0; cnt6 < nInputRocks[0].size(); cnt6++)
        {
            if (nInputRocks[cnt5][cnt6] == 'O')
            {
                nPartTwoSum += cnt7;
            }
        }
        cnt7--;
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

