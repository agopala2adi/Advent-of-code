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

/* Store the map of the maze */
vector<string> map_puzzle;
/* Part 1: Get the longest path using recursion */
int64_t moveMapPuzzle(int64_t x_val, int64_t y_val, int64_t nDir, int64_t nCount);
/* Part 2: Get the longest path using recursion */
int64_t moveMapPuzzle2(int64_t x_val, int64_t y_val, int64_t nDir, int64_t nCount, vector<bitset<200>> vMoved);

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

    int64_t mavXYCord = 0;
    const int64_t nYCordMax = 10000000ll;

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    vector<bitset<200>> nMoved;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Store the input map maze in map puzzle */
        map_puzzle.push_back(arr[cnt1]);
        /* Remove new line characters */
        map_puzzle[map_puzzle.size()-1].pop_back();

        /* Store zero (part 2) for the path already visited */
        nMoved.push_back(0);

        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Get the first starting point */
    for (cnt2 = 0; cnt2 < map_puzzle[0].size(); cnt2++)
    {
        if (map_puzzle[0][cnt2] == '.')
        {
            break;
        }
    }

    /* Get part one answer, subtract one as we would ignore the first step */
    nPartOneSum = moveMapPuzzle(0, cnt2, 2, 0) -1;

    /* Display part a answer */
    cout << "Part (a): " << nPartOneSum << endl;

    /* For part2, replace all arrows with dots */
    for (cnt2 = 0; cnt2 < map_puzzle.size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < map_puzzle[0].size(); cnt3++)
        {
            if (map_puzzle[cnt2][cnt3] != '#')
            {
                map_puzzle[cnt2][cnt3] = '.';
            }
        }
    }
    /* Get the first starting point again */
    for (cnt2 = 0; cnt2 < map_puzzle[0].size(); cnt2++)
    {
        if (map_puzzle[0][cnt2] == '.')
        {
            break;
        }
    }
    /* Get part two answer, subtract one as we would ignore the first step */
    nPartTwoSum = moveMapPuzzle2(0, cnt2, 2, 0, nMoved)-1;

    /* Display part b answer */
    cout << "Part (b): " << nPartTwoSum << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}


/* Recursive function to compute the maximum steps taken for part 1, with arrows */
int64_t moveMapPuzzle(int64_t x_val, int64_t y_val, int64_t nDir, int64_t nCount)
{
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;
    int64_t cnt4 = 0;

    /* If we have hit the last row, return the count accumulated till now */
    if (x_val == map_puzzle.size()-1)
    {
        return nCount;
    }

    /* Keep moving the values inside until there is no way to move */
    while (true)
    {
        /* Increment the count */
        nCount++;

        /* If the direction of movement is up: */
        if (nDir == 0)
        {
            /* At a time, due to arrows, it can only go maximum two directions */
            if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' || map_puzzle[x_val-1][y_val] == '^'))
            {
                if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' || map_puzzle[x_val][y_val-1] == '<'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val-1, 3, nCount);
                    cnt2 = moveMapPuzzle(x_val-1, y_val, nDir, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' || map_puzzle[x_val][y_val+1] == '>'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val+1, 1, nCount);
                    cnt2 = moveMapPuzzle(x_val-1, y_val, nDir, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    x_val--;
                }
            }
            else if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' || map_puzzle[x_val][y_val-1] == '<'))
            {
                if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' || map_puzzle[x_val][y_val+1] == '>'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val+1, 1, nCount);
                    cnt2 = moveMapPuzzle(x_val, y_val-1, 3, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    y_val--;
                    nDir = 3;
                }
            }
            else if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' || map_puzzle[x_val][y_val+1] == '>'))
            {
                /* If can do only one, just continue in this loop only, 
                 * avoid calling recursive function */
                y_val++;
                nDir = 1;
            }
            else
            {
                /* If cannot move at all, return zero as we could not reach the end */
                return 0;
            }
        }
        /* If the direction of movement is right: */
        else if (nDir == 1)
        {
            if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' || map_puzzle[x_val][y_val+1] == '>'))
            {
                if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' || map_puzzle[x_val+1][y_val] == 'v'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val+1, 1, nCount);
                    cnt2 = moveMapPuzzle(x_val+1, y_val, 2, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' || map_puzzle[x_val-1][y_val] == '^'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val+1, 1, nCount);
                    cnt2 = moveMapPuzzle(x_val-1, y_val, 0, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    y_val++;
                    nDir = 1;
                }
            }
            else if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' || map_puzzle[x_val+1][y_val] == 'v'))
            {
                if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' || map_puzzle[x_val-1][y_val] == '^'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val-1, y_val, 0, nCount);
                    cnt2 = moveMapPuzzle(x_val+1, y_val, 2, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    x_val++;
                    nDir = 2;
                }
            }
            else if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' || map_puzzle[x_val-1][y_val] == '^'))
            {
                /* If can do only one, just continue in this loop only, 
                 * avoid calling recursive function */
                x_val--;
                nDir = 0;
            }
        }
        /* If the direction of movement is down: */
        else if (nDir == 2)
        {
            if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' || map_puzzle[x_val+1][y_val] == 'v'))
            {
                if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' || map_puzzle[x_val][y_val-1] == '<'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val-1, 3, nCount);
                    cnt2 = moveMapPuzzle(x_val+1, y_val, nDir, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' || map_puzzle[x_val][y_val+1] == '>'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val+1, 1, nCount);
                    cnt2 = moveMapPuzzle(x_val+1, y_val, nDir, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    x_val++;
                }
            }
            else if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' || map_puzzle[x_val][y_val-1] == '<'))
            {
                if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' || map_puzzle[x_val][y_val+1] == '>'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val+1, 1, nCount);
                    cnt2 = moveMapPuzzle(x_val, y_val-1, 3, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    y_val--;
                    nDir = 3;
                }
            }
            else if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' || map_puzzle[x_val][y_val+1] == '>'))
            {
                /* If can do only one, just continue in this loop only, 
                 * avoid calling recursive function */
                y_val++;
                nDir = 1;
            }
            else if (x_val == map_puzzle.size()-1)
            {
                /* If we have reached the end of the line, exit */
                break;
            }
        }
        /* If the direction of movement is left: */
        else if (nDir == 3)
        {
            if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' || map_puzzle[x_val][y_val-1] == '>'))
            {
                if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' || map_puzzle[x_val+1][y_val] == 'v'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val-1, 3, nCount);
                    cnt2 = moveMapPuzzle(x_val+1, y_val, 2, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' || map_puzzle[x_val-1][y_val] == '^'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val, y_val-1, 3, nCount);
                    cnt2 = moveMapPuzzle(x_val-1, y_val, 0, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    y_val--;
                    nDir = 3;
                }
            }
            else if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' || map_puzzle[x_val+1][y_val] == 'v'))
            {
                if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' || map_puzzle[x_val-1][y_val] == '^'))
                {
                    /* If can do both directions, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle(x_val-1, y_val, 0, nCount);
                    cnt2 = moveMapPuzzle(x_val+1, y_val, 2, nCount);
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    x_val++;
                    nDir = 2;
                }
            }
            else if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' || map_puzzle[x_val-1][y_val] == '^'))
            {
                /* If can do only one, just continue in this loop only, 
                 * avoid calling recursive function */
                x_val--;
                nDir = 0;
            }
            else
            {
                /* If cannot move at all, return zero as we could not reach the end */
                return 0;
            }
        }
        else if (x_val == map_puzzle.size()-1)
        {
            /* If we have reached the end of the line, exit */
            break;
        }
        else
        {
            /* If cannot move at all, return zero as we could not reach the end */
            return 0;
        }
    }

    return nCount;
}



/* Recursive function to compute the maximum steps taken for part 2, without arrows */
int64_t moveMapPuzzle2(int64_t x_val, int64_t y_val, int64_t nDir, int64_t nCount, vector<bitset<200>> vMoved)
{
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;
    int64_t cnt4 = 0;

    /* If we have hit the last row, return the count accumulated till now */
    if (x_val == map_puzzle.size()-1)
    {
        return nCount;
    }

    /* Keep moving the values inside until there is no way to move */
    while (true)
    {
        /* Increment the count */
        nCount++;
        /* Keep track of all values moved */
        vMoved[x_val][y_val] = 1;
        /* If the direction of movement is up: */
        if (nDir == 0)
        {
            /* Check if it can continue moving up */
            if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
            {
                /* Also check if it can move left and right */
                if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' && vMoved[x_val][y_val-1] == 0))
                {
                    if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
                    {
                        /* If can do all three, move to those locations and call 
                         * the recursive function again */
                        cnt1 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                        cnt2 = moveMapPuzzle2(x_val-1, y_val, nDir, nCount, vMoved);
                        cnt3 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                        /* Get the maximum value of the three and quit */
                        nCount = max(max(cnt1, cnt2), cnt3);
                        break;
                    }
                    else
                    {
                        /* If can do just two, move to those locations and call 
                         * the recursive function again */
                        cnt1 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                        cnt2 = moveMapPuzzle2(x_val-1, y_val, nDir, nCount, vMoved);
                        /* Get the maximum value of the two and quit */
                        nCount = max(cnt1, cnt2);
                        break;
                    }
                }
                else if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
                {
                    /* If can do just two, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                    cnt2 = moveMapPuzzle2(x_val-1, y_val, nDir, nCount, vMoved);
                    /* Get the maximum value of the two and quit */
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    x_val--;
                }
            }
            else if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' && vMoved[x_val][y_val-1] == 0))
            {
                if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
                {
                    /* If can do just two, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                    cnt2 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                    /* Get the maximum value of the two and quit */
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    y_val--;
                    nDir = 3;
                }
            }
            /* If can do only one, just continue in this loop only, 
             * avoid calling recursive function */
            else if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
            {
                y_val++;
                nDir = 1;
            }
            /* If cannot move at all, return zero as we could not reach the end */
            else
            {
                return 0;
            }
        }
        /* If direction is right: */
        else if (nDir == 1)
        {
            /* Check if it can continue moving right */
            if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
            {
                if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' && vMoved[x_val+1][y_val] == 0))
                {
                    if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
                    {
                        /* If can do all three, move to those locations and call 
                         * the recursive function again */
                        cnt1 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                        cnt2 = moveMapPuzzle2(x_val+1, y_val, 2, nCount, vMoved);
                        cnt3 = moveMapPuzzle2(x_val-1, y_val, 0, nCount, vMoved);
                        /* Get the maximum value of the three and quit */
                        nCount = max(max(cnt1, cnt2), cnt3);
                        break;
                    }
                    else
                    {
                        /* If can do just two, move to those locations and call 
                        * the recursive function again */
                        cnt1 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                        cnt2 = moveMapPuzzle2(x_val+1, y_val, 2, nCount, vMoved);
                        /* Get the maximum value of the two and quit */
                        nCount = max(cnt1, cnt2);
                        break;
                    }
                }
                else if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
                {
                    /* If can do just two, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                    cnt2 = moveMapPuzzle2(x_val-1, y_val, 0, nCount, vMoved);
                    /* Get the maximum value of the two and quit */
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    y_val++;
                    nDir = 1;
                }
            }
            else if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' && vMoved[x_val+1][y_val] == 0))
            {
                if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
                {
                    /* If can do just two, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle2(x_val-1, y_val, 0, nCount, vMoved);
                    cnt2 = moveMapPuzzle2(x_val+1, y_val, 2, nCount, vMoved);
                    /* Get the maximum value of the two and quit */
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    x_val++;
                    nDir = 2;
                }
            }
            else if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
            {
                /* If can do only one, just continue in this loop only, 
                 * avoid calling recursive function */
                x_val--;
                nDir = 0;
            }
            else
            {
                /* If cannot move at all, return zero as we could not reach the end */
                return 0;
            }
        }
        /* If direction is down: */
        else if (nDir == 2)
        {
            /* Check if it can continue moving down */
            if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' && vMoved[x_val+1][y_val] == 0))
            {
                if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' && vMoved[x_val][y_val-1] == 0))
                {
                    if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
                    {
                        /* If can do all three, move to those locations and call 
                         * the recursive function again */
                        cnt1 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                        cnt2 = moveMapPuzzle2(x_val+1, y_val, nDir, nCount, vMoved);
                        cnt3 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                        /* Get the maximum value of the three and quit */
                        nCount = max(max(cnt1, cnt2), cnt3);
                        break;
                    }
                    else
                    {
                        /* If can do just two, move to those locations and call 
                         * the recursive function again */
                        cnt1 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                        cnt2 = moveMapPuzzle2(x_val+1, y_val, nDir, nCount, vMoved);
                        /* Get the maximum value of the two and quit */
                        nCount = max(cnt1, cnt2);
                        break;
                    }
                }
                else if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
                {
                    /* If can do just two, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                    cnt2 = moveMapPuzzle2(x_val+1, y_val, nDir, nCount, vMoved);
                    /* Get the maximum value of the two and quit */
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    x_val++;
                }
            }
            else if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' && vMoved[x_val][y_val-1] == 0))
            {
                if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
                {
                    /* If can do just two, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle2(x_val, y_val+1, 1, nCount, vMoved);
                    cnt2 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                    /* Get the maximum value of the two and quit */
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    y_val--;
                    nDir = 3;
                }
            }
            else if (y_val < map_puzzle[0].size()-1 && (map_puzzle[x_val][y_val+1] == '.' && vMoved[x_val][y_val+1] == 0))
            {
                /* If can do only one, just continue in this loop only, 
                 * avoid calling recursive function */
                y_val++;
                nDir = 1;
            }
            else if (x_val == map_puzzle.size()-1)
            {
                /* If we have reached the end of the line, exit */
                break;
            }
            else
            {
                /* If cannot move at all, return zero as we could not reach the end */
                return 0;
            }
        }
        /* If direction is left: */
        else if (nDir == 3)
        {
            /* Check if it can continue moving left */
            if (y_val > 0 && (map_puzzle[x_val][y_val-1] == '.' && vMoved[x_val][y_val-1] == 0))
            {
                if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' && vMoved[x_val+1][y_val] == 0))
                {
                    if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
                    {
                        /* If can do all three, move to those locations and call 
                         * the recursive function again */
                        cnt1 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                        cnt2 = moveMapPuzzle2(x_val+1, y_val, 2, nCount, vMoved);
                        cnt3 = moveMapPuzzle2(x_val-1, y_val, 0, nCount, vMoved);
                        /* Get the maximum value of the three and quit */
                        nCount = max(max(cnt1, cnt2), cnt3);
                        break;
                    }
                    else
                    {
                        /* If can do just two, move to those locations and call 
                         * the recursive function again */
                        cnt1 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                        cnt2 = moveMapPuzzle2(x_val+1, y_val, 2, nCount, vMoved);
                        /* Get the maximum value of the two and quit */
                        nCount = max(cnt1, cnt2);
                        break;
                    }
                }
                else if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
                {
                    /* If can do just two, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle2(x_val, y_val-1, 3, nCount, vMoved);
                    cnt2 = moveMapPuzzle2(x_val-1, y_val, 0, nCount, vMoved);
                    /* Get the maximum value of the two and quit */
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    y_val--;
                    nDir = 3;
                }
            }
            else if (x_val < map_puzzle.size()-1 && (map_puzzle[x_val+1][y_val] == '.' && vMoved[x_val+1][y_val] == 0))
            {
                if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
                {
                    /* If can do just two, move to those locations and call 
                     * the recursive function again */
                    cnt1 = moveMapPuzzle2(x_val-1, y_val, 0, nCount, vMoved);
                    cnt2 = moveMapPuzzle2(x_val+1, y_val, 2, nCount, vMoved);
                    /* Get the maximum value of the two and quit */
                    nCount = max(cnt1, cnt2);
                    break;
                }
                else
                {
                    /* If can do only one, just continue in this loop only, 
                     * avoid calling recursive function */
                    x_val++;
                    nDir = 2;
                }
            }
            else if (x_val > 0 && (map_puzzle[x_val-1][y_val] == '.' && vMoved[x_val-1][y_val] == 0))
            {
                /* If can do only one, just continue in this loop only, 
                 * avoid calling recursive function */
                x_val--;
                nDir = 0;
            }
            else
            {
                /* If cannot move at all, return zero as we could not reach the end */
                return 0;
            }
        }
        else if (x_val == map_puzzle.size()-1)
        {
            /* If we have reached the end of the line, exit */
            break;
        }
        else
        {
            /* If cannot move at all, return zero as we could not reach the end */
            return 0;
        }
    }

    return nCount;
}

