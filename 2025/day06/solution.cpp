#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

// #include <sstream>

using namespace std;

char arr[1000][10000];


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

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    vector<int64_t> nNumbers[100];
    vector<string> sLines;
    vector<char> cOperations;
    vector<int64_t> nSpaceIdx;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Read a line from the file */
        string sLine = arr[cnt1];

        /* Remove newline character */
        if (sLine.back() == '\n' || sLine.back() == '\r')
        {
            sLine.pop_back();
        }
        if (sLine.back() == '\n' || sLine.back() == '\r')
        {
            sLine.pop_back();
        }

        /* If we have not reached the last line yet: */
        if (sLine[0] != '*' && sLine[0] != '+')
        {
            /* Store it in the lines vector with a leading space
             * This space is required to compute the last number's 
             * calculation at the end of part 2
             */
            sLines.push_back(" " + sLine);

            stringstream iss(sLine);

            int64_t nNumber = 0;

            while (iss >> nNumber)
            {
                nNumbers[cnt1].push_back(nNumber);
            }
        }
        /* If we see the last line: */
        else
        {
            stringstream iss(sLine);
            char operation;

            /* Part - 1 */

            /* Collect all the operations */
            while (iss >> operation)
            {
                /* Place them in a operations vector */
                cOperations.push_back(operation);
            }

            /* For each operation + / *, perform calculation */
            for (cnt2 = 0; cnt2 < cOperations.size(); cnt2++)
            {
                int64_t nIndividualOperRes = 0;
                /* If the operation is a + */
                if (cOperations[cnt2] == '+')
                {
                    nIndividualOperRes = 0;
                    /* add all the values in a column */
                    for (cnt3 = 0; cnt3 < cnt1; cnt3++)
                    {
                        nIndividualOperRes += nNumbers[cnt3][cnt2];
                    }
                }
                /* If the operation is a * */
                else if (cOperations[cnt2] == '*')
                {
                    nIndividualOperRes = 1;
                    /* multiply all the values in a column */
                    for (cnt3 = 0; cnt3 < cnt1; cnt3++)
                    {
                        nIndividualOperRes *= nNumbers[cnt3][cnt2];
                    }
                }
                else
                {
                    /* empty else */
                }

                /* Add the results into the first part sum */
                nFirstPart += nIndividualOperRes;
            }

            /* Part - 2 */

            /* Compute the maximum character length */
            int64_t nMaxSize = sLines[0].size();

            /* Get the line with maximum character length */
            for (cnt2 = 0; cnt2 < sLines.size(); cnt2++)
            {
                if (sLines[cnt2].size() > nMaxSize)
                {
                    nMaxSize = sLines[cnt2].size();
                }
            }

            /* Pad spaces at the end to the lines which are smaller
             * than the maximum character length line
             */
            for (cnt2 = 0; cnt2 < sLines.size(); cnt2++)
            {
                if (sLines[cnt2].size() < nMaxSize)
                {
                    int64_t nDiff = nMaxSize - sLines[cnt2].size();
                    for (cnt3 = 0; cnt3 < nDiff; cnt3++)
                    {
                        sLines[cnt2] += " ";
                    }
                }
            }

            /* Find the indices that have spaces by all the lines.
             *
             * This would help us in separating the numbers 
            */
            for (cnt2 = 0; cnt2 < sLines[0].size(); cnt2++)
            {
                for (cnt3 = 0; cnt3 < sLines.size(); cnt3++)
                {
                    if (sLines[cnt3][cnt2] != ' ')
                    {
                        break;
                    }
                }

                /* Store the indices into a vector */
                if (cnt3 == sLines.size())
                {
                    nSpaceIdx.push_back(cnt2);
                }
            }

            /* Reverse the indices storing spaces and operations as it is 
             * required to go from reverse order 
            */
            reverse(nSpaceIdx.begin(), nSpaceIdx.end());
            reverse(cOperations.begin(), cOperations.end());

            /* For each column, accumulate the number result */
            vector<int64_t> nColNumbers;

            /* Keep track of the current space index */
            cnt4 = 0;

            /* Iterate over each character position in the lines from the end */
            for (cnt2 = sLines[0].size()-1; cnt2 >= 0; cnt2--)
            {
                int64_t nNumber = 0;

                /* If we have reached a space index */
                if (cnt2 == nSpaceIdx[cnt4])
                {
                    /* Perform the operation */
                    if (cOperations[cnt4] == '+')
                    {
                        cnt7 = 0;
                        /* Sum all the column numbers */
                        for (cnt3 = 0; cnt3 < nColNumbers.size(); cnt3++)
                        {
                            cnt7 += nColNumbers[cnt3];
                        }
                        /* Add to the second part result */
                        nSecondPart += cnt7;
                    }
                    else if (cOperations[cnt4] == '*')
                    {
                        cnt7 = 1;
                        /* Multiply all the column numbers */
                        for (cnt3 = 0; cnt3 < nColNumbers.size(); cnt3++)
                        {
                            cnt7 *= nColNumbers[cnt3];
                        }
                        /* Add to the second part result */
                        nSecondPart += cnt7;
                    }

                    /* Clear the column numbers for next operation */
                    nColNumbers.clear();
                    /* Move to the next space index */
                    cnt4++;

                    continue;
                }

                /* Extract the number at the current character position */
                for (cnt3 = 0; cnt3 < sLines.size(); cnt3++)
                {
                    /* skip if the character is a space*/
                    if (sLines[cnt3][cnt2] == ' ')
                    {
                        continue;
                    }
                    else
                    {
                        /* Build the number 
                         * Convert char to digit and accumulate
                        */
                        nNumber = nNumber * 10 + (sLines[cnt3][cnt2] - '0');
                    }
                }
                /* Store the built number into the column numbers vector */
                nColNumbers.push_back(nNumber);
            }
        }

        /* Increment count */
        ++cnt1;
    }

    /* Display part a and b answers */
    cout << "Part (a): " << nFirstPart << endl;

    cout << "Part (b): " << nSecondPart << endl;

    /* Close the file */
    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

