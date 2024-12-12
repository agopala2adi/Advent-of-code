#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[10000];

/* x and y co-ordinates of the fence 
 * float - because the fence is considered 0.1 meters away from the plot */
vector<float> xValsFence;
vector<float> yValsFence;

int64_t findPerimeter(vector<string> &sGarden, int64_t nXIdx, int64_t nYIdx, char cRegion);
int64_t findUnique(void);

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
    // To printf uint -> printf("%llu ", fin);

    // String stream: stringstream iss(arr);
    // Store word from string to string iss >> word
    // Display: printf("%s\n",word.c_str());

    // list<string> totalStrings;
    // for (auto it = totalStrings.begin(); it != totalStrings.end(); ++it)
    //     string str = *it;


    int64_t cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0, cnt6 = 0, cnt7 = 0;
    int64_t cnt8 = 0, cnt9 = 0, cnt10 = 0, cnt11 = 0, cnt12 = 0, cnt13 = 0, cnt14 = 0;
    int64_t nPosStartX = 0, nPosStartY = 0, nPosStartXBackup = 0, nPosStartYBackup = 0;

    /* Part (a) and (b) count */
    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    vector<string> sGarden;

    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        /* Read each line and remove the new line characters and store into a vector 
         * of strings */
        sGarden.push_back(arr);
        if (sGarden[cnt1][sGarden[cnt1].size()-1] == '\n' || sGarden[cnt1][sGarden[cnt1].size()-1] == '\r')
        {
            sGarden[cnt1].pop_back();
        }
        if (sGarden[cnt1][sGarden[cnt1].size()-1] == '\n' || sGarden[cnt1][sGarden[cnt1].size()-1] == '\r')
        {
            sGarden[cnt1].pop_back();
        }

        /* Increment count */
        ++cnt1;
    }

    /* For each region */
    for (cnt1 = 0; cnt1 < sGarden.size(); ++cnt1)
    {
        for (cnt2 = 0; cnt2 < sGarden[cnt1].size(); ++cnt2)
        {
            /* If the region is already considered, do not process */
            if (sGarden[cnt1][cnt2] != '-' && sGarden[cnt1][cnt2] != '+')
            {
                /* Find the perimeter of the region */
                int64_t nTotalPerimeter = findPerimeter(sGarden, cnt1, cnt2, sGarden[cnt1][cnt2]);
                int64_t nUniquePerimeter = findUnique();
                int64_t nArea = 0;

                /* Compute area by checking all the marked elemets by - */
                for (cnt4 = 0; cnt4 < sGarden.size(); ++cnt4)
                {
                    for (cnt5 = 0; cnt5 < sGarden[cnt4].size(); ++cnt5)
                    {
                        /* Replace - by + to ensure that they have already been 
                         * considered */
                        if (sGarden[cnt4][cnt5] == '-')
                        {
                            sGarden[cnt4][cnt5] = '+';
                            ++nArea;
                        }
                    }
                }
                nFirstPart += nArea * nTotalPerimeter;
                nSecondPart += nArea * nUniquePerimeter;

                xValsFence.clear();
                yValsFence.clear();
            }
        }
    }

    /* Close the file */
    fclose(fp);


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


/**
 * @brief Recursively finds the perimeter of a region in a garden and marks the boundary with fence coordinates.
 *
 * This function explores the garden matrix to find the perimeter of a specified region. It marks the current
 * position as visited and recursively checks the neighboring cells. If a neighboring cell belongs to the same
 * region, the function continues the search from that cell. If a neighboring cell does not belong to the same
 * region or is out of bounds, it adds the coordinates of the boundary to the fence vectors and increments the
 * perimeter count.
 *
 * @param sGarden A reference to a 2D vector of strings representing the garden.
 * @param nXIdx The x-coordinate (row index) of the current cell.
 * @param nYIdx The y-coordinate (column index) of the current cell.
 * @param cRegion The character representing the region to find the perimeter for.
 * @return The perimeter of the specified region.
 */
int64_t findPerimeter(vector<string> &sGarden, int64_t nXIdx, int64_t nYIdx, char cRegion)
{
    /* Initialise the perimeter to zero */
    int64_t nPerimeter = 0;

    /* Set the current position to a dash '-', to not consider it for a fence */
    sGarden[nXIdx][nYIdx] = '-';

    /* If the next element is the same region, then recursively call this function
     * with the updated co-ordinates (x, y) */
    if (nXIdx > 0 && sGarden[nXIdx-1][nYIdx] == cRegion)
    {
        nPerimeter += findPerimeter(sGarden, nXIdx-1, nYIdx, cRegion);
    }
    /* If the next element is not the same region, then add the x and y co-ordinates
     * to the fence vector
    */
    else if ((nXIdx > 0 && sGarden[nXIdx-1][nYIdx] != '-') || nXIdx <= 0)
    {
        /* Move 0.1 meters away from the current region */
        xValsFence.push_back(nXIdx - 0.1);
        yValsFence.push_back(nYIdx);

        /* Increment the number in perimeter */
        ++nPerimeter;
    }

    /* If the next element is the same region, then recursively call this function
     * with the updated co-ordinates (x, y) */
    if (nXIdx < sGarden.size()-1 && sGarden[nXIdx+1][nYIdx] == cRegion)
    {
        nPerimeter += findPerimeter(sGarden, nXIdx+1, nYIdx, cRegion);
    }
    else if ((nXIdx < sGarden.size()-1 && sGarden[nXIdx+1][nYIdx] != '-') || nXIdx >= sGarden.size()-1)
    {
        /* Move 0.1 meters away from the current region */
        xValsFence.push_back(nXIdx + 0.1);
        yValsFence.push_back(nYIdx);

        /* Increment the number in perimeter */
        ++nPerimeter;
    }

    /* If the next element is the same region, then recursively call this function
     * with the updated co-ordinates (x, y) */
    if (nYIdx > 0 && sGarden[nXIdx][nYIdx-1] == cRegion)
    {
        nPerimeter += findPerimeter(sGarden, nXIdx, nYIdx-1, cRegion);
    }
    else if ((nYIdx > 0 && sGarden[nXIdx][nYIdx-1] != '-') || nYIdx <= 0)
    {
        /* Move 0.1 meters away from the current region */
        xValsFence.push_back(nXIdx);
        yValsFence.push_back(nYIdx-0.1);

        /* Increment the number in perimeter */
        ++nPerimeter;
    }

    /* If the next element is the same region, then recursively call this function
     * with the updated co-ordinates (x, y) */
    if (nYIdx < sGarden[nXIdx].size()-1 && sGarden[nXIdx][nYIdx+1] == cRegion)
    {
        nPerimeter += findPerimeter(sGarden, nXIdx, nYIdx+1, cRegion);
    }
    else if ((nYIdx < sGarden[nXIdx].size()-1 && sGarden[nXIdx][nYIdx+1] != '-') || nYIdx >= sGarden[nXIdx].size()-1)
    {
        /* Move 0.1 meters away from the current region */
        xValsFence.push_back(nXIdx);
        yValsFence.push_back(nYIdx+0.1);

        /* Increment the number in perimeter */
        ++nPerimeter;
    }

    /* Return the perimeter */
    return nPerimeter;
}



/**
 * @brief Finds the number of unique fences in a given set of fence coordinates.
 *
 * This function calculates the number of unique fences by subtracting the number of repeated fences 
 * from the total number of fences. A repeated fence is defined as a fence that is in the same straight 
 * line as another fence, differing by 1 in one coordinate while the other coordinate remains the same.
 *
 * @return int64_t The number of unique fences.
 */
int64_t findUnique(void)
{
    /* Number of unique fences is total number minus repeated 
     * Here, repeated is the fence that is in the same straight line as other fences
     */
    int64_t cnt1 = 0, cnt2 = 0;
    int64_t nPerimeter = 0;
    int64_t nRepeated = 0;

    /* For each fence */
    for (cnt1 = 0; cnt1 < xValsFence.size(); ++cnt1)
    {
        /* Each fence other than already analysed */
        for (cnt2 = cnt1+1; cnt2 < xValsFence.size(); ++cnt2)
        {
            /* Straight line would mean the fence is differing by a 1, but the 
             * other co-ordinate is same 
             * Check all cases. Same x but y differs by 1, same y but x differs by 1
             */
            if ((xValsFence[cnt1] == xValsFence[cnt2]) && abs(yValsFence[cnt1] - yValsFence[cnt2]) == 1)
            {
                ++nRepeated;
            }
            else if (abs(xValsFence[cnt1] - xValsFence[cnt2]) == 1 && (yValsFence[cnt1] == yValsFence[cnt2]))
            {
                ++nRepeated;
            }
        }
    }

    /* Non repeated perimeter is total minus repeated */
    nPerimeter = xValsFence.size() - nRepeated;
    return nPerimeter;
}

