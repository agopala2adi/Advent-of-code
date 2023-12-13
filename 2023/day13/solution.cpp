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

bool checkRowReflection(vector<string> nRows, int64_t row_no);
bool checkColReflection(vector<string> nRows, int64_t col_no);
int64_t getReflection(vector <string> nRows, int64_t prevSoln);

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

    vector<string> nRows;
    vector<string> nRows2;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* If seeing new line perform the solution */
        if (strlen(arr[cnt1]) < 2)
        {
            /* Calculate reflection summarisation value */
            cnt2 = getReflection(nRows, 0);
            /* Add to part 1 solution */
            nPartOneSum += cnt2;

            /* For part 2, flip each element. Start with columns, then rows */
            for (cnt4 = 0; cnt4 < nRows.size(); cnt4++)
            {
                for (cnt5 = 0; cnt5 < nRows[0].size(); cnt5++)
                {
                    /* Keep a copy of rows into rows2 */
                    nRows2 = nRows;

                    /* Flip (cnt4, cnt5) element */
                    if (nRows[cnt4][cnt5] == '#')
                    {
                        nRows2[cnt4][cnt5] = '.';
                    }
                    else if (nRows[cnt4][cnt5] == '.')
                    {
                        nRows2[cnt4][cnt5] = '#';
                    }
                    /* Get the value of reflection ignoring part 1 solution */
                    cnt3 = getReflection(nRows2, cnt2);
                    /* If the solution is different or not zero, stop computation */
                    if (cnt3 != 0 && cnt2 != cnt3)
                    {
                        break;
                    }
                }
                /* If found, break out of larger loop */
                if (cnt5 != nRows[0].size())
                {
                    break;
                }
            }
            /* If the entire solution is not to be found, then use part 1 solution */
            if (cnt3 == 0)
            {
                cnt3 = cnt2;
            }
            /* Accumulate into part 2 solution */
            nPartTwoSum += cnt3;
            /* Clear the rows to start accumulating new values */
            nRows.clear();
        }
        else
        {
            /* Add the current row into rows */
            nRows.push_back(arr[cnt1]);
            /* Remove the last '\n' character */
            nRows[nRows.size()-1].pop_back();
        }

        /* Increment count to move to next line */
        ++cnt1;
    }
    /* For the last set of input, calculate reflection summarisation value */
    cnt2 = getReflection(nRows, 0);
    /* Add to part 1 solution */
    nPartOneSum += cnt2;

    /* For part 2, flip each element. Start with columns, then rows */
    for (cnt4 = 0; cnt4 < nRows.size(); cnt4++)
    {
        for (cnt5 = 0; cnt5 < nRows[0].size(); cnt5++)
        {
            /* Keep a copy of rows into rows2 */
            nRows2 = nRows;

            /* Flip (cnt4, cnt5) element */
            if (nRows[cnt4][cnt5] == '#')
            {
                nRows2[cnt4][cnt5] = '.';
            }
            else if (nRows[cnt4][cnt5] == '.')
            {
                nRows2[cnt4][cnt5] = '#';
            }
            /* Get the value of reflection ignoring part 1 solution */
            cnt3 = getReflection(nRows2, cnt2);
            /* If the solution is different or not zero, stop computation */
            if (cnt3 != 0 && cnt2 != cnt3)
            {
                break;
            }
        }
        /* If found, break out of larger loop */
        if (cnt5 != nRows[0].size())
        {
            break;
        }
    }
    /* If the entire solution is not to be found, then use part 1 solution */
    if (cnt3 == 0)
    {
        cnt3 = cnt2;
    }
    nPartTwoSum += cnt3;


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


int64_t getReflection(vector <string> nRows, int64_t prev_value)
{
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;

    cnt1 = nRows[0].size();

    /* Check row wise reflections first */
    for (cnt2 = 1; cnt2 < nRows.size(); cnt2++)
    {
        /* If row reflection is present and if the value is different from
         * previous value, stop the loop and return the answer */
        if (checkRowReflection(nRows, cnt2))
        {
            cnt3 = cnt2*100;
            if (prev_value != cnt3)
            {
                break;
            }
        }
    }

    /* If no reflection in rows, try columns */
    if (cnt2 == nRows.size())
    {
        for (cnt2 = 1; cnt2 < cnt1; cnt2++)
        {
            /* If column reflection is present and if the value is different from
             * previous value, stop the loop and return the answer */
            if (checkColReflection(nRows, cnt2))
            {
                cnt3 = cnt2;
                if (prev_value != cnt3)
                {
                    break;
                }
            }
        }
    }

    return cnt3;

}

/* Check if the row reflection along with row_no is present */
bool checkRowReflection(vector<string> nRows, int64_t row_no)
{
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;

    /* Compute the minimum value of rows above the line of reflection and rows
     * after the line of reflection */
    cnt2 = min(int64_t(nRows.size())-row_no, row_no);

    /* Check if row before is same as row after */
    for (cnt1 = 0; cnt1 < cnt2; cnt1++)
    {
        for (cnt3 = 0; cnt3 < nRows[0].size(); cnt3++)
        {
            if (nRows[row_no-cnt1-1][cnt3] != nRows[row_no+cnt1][cnt3])
            {
                return false;
            }
        }
    }

    return true;
}

/* Check if the column reflection along with col_no is present */
bool checkColReflection(vector<string> nRows, int64_t col_no)
{
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;

    /* Compute the minimum value of rows above the line of reflection and rows
     * after the line of reflection */
    cnt2 = min(int64_t(nRows[0].size())-col_no, col_no);

    /* Check if col left is same as col right */
    for (cnt1 = 0; cnt1 < cnt2; cnt1++)
    {
        for (cnt3 = 0; cnt3 < nRows.size(); cnt3++)
        {
            if (nRows[cnt3][col_no-cnt1-1] != nRows[cnt3][col_no+cnt1])
            {
                return false;
            }
        }
    }

    return true;
}
