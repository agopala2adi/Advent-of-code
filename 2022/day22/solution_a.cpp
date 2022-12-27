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

    int64_t max_val = 0;
    int64_t min_val = 10000000ull;

    vector <string> forestMap;
    vector <int64_t> mapNumbers;
    vector <char> mapDirs;

    int64_t currposX;
    int64_t currposY;

    /* Read every line */
    while (fgets(arr[cnt1], sizeof(arr[0]), fp) != NULL)
    {
        /* If the line is not any of space, dot, hash or new-line break from reading */
        if (arr[cnt1][0] != ' ' && arr[cnt1][0] != '.' && arr[cnt1][0] != '#' && arr[cnt1][0] != '\n')
        {
            break;
        }
        /* Store the value of current line into a vector of strings */
        string sMap = arr[cnt1];
        if (sMap[sMap.size() - 1] == '\n')
        {
            sMap.pop_back();
        }
        forestMap.push_back(sMap);
        cnt1++;
    }

    /* If the last line is a new-line, remove it from the vector of strings */
    if (forestMap[forestMap.size()-1].size() == 0)
    {
        forestMap.pop_back();
    }

    /* Current instruction, movement is stored into instruction string */
    string instruction = arr[cnt1];
    /* Placeholder to concatinate and store the number in the instruction */
    string instNumb;

    /* Iterate through each char in instruction */
    for (cnt2 = 0; cnt2 < instruction.size(); cnt2++)
    {
        /* If the inctruction is not an R or an L, keep accumulating the number */
        if (instruction[cnt2] != 'R' && instruction[cnt2] != 'L')
        {
            instNumb = instNumb + instruction[cnt2];
        }
        /* If the char is an "R" or an "L" stop accumulating and store store
         * the value of number into mapNumbers vector. Store the direction,
         * "R" or "L" into another vector, mapDirs */
        else
        {
            mapNumbers.push_back(stoll(instNumb));
            mapDirs.push_back(instruction[cnt2]);
            instNumb = "";
        }
    }
    /* Place the last number that was accumulated but not added */
    mapNumbers.push_back(stoll(instNumb));

    /* Calculate the maxumum number of columns of the input */
    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        if (max_val < forestMap[cnt2].size())
        {
            max_val = forestMap[cnt2].size();
        }
    }

    /* If a line has less than max_val columns, add spaces to fill up to
     * max_val number of columns */
    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        if (max_val > forestMap[cnt2].size())
        {
            cnt3 = max_val - forestMap[cnt2].size();
            string spaces = forestMap[cnt2];
            for (cnt4 = 0; cnt4 < cnt3; cnt4++)
            {
                spaces = spaces + " ";
            }
            forestMap[cnt2] = spaces;
        }
    }

    /* Get the position of the first dot in the first row "." */
    for (cnt2 = 0; cnt2 < max_val; cnt2++)
    {
        if (forestMap[0][cnt2] != ' ' && forestMap[0][cnt2] != '#')
        {
            break;
        }
    }
    /* Mark that as the current X co-ordinate */
    currposX = cnt2;
    /* Y co-ordinate is a zero as there this is the first row */
    currposY = 0;

    /* Let the dir be as follows: right = 0, down = 1, left = 2, and up = 3 */
    int64_t nCurrDir = 0;

    /* Iterate through all the instructions */
    for (cnt2 = 0; cnt2 < mapNumbers.size(); cnt2++)
    {
        /* Store the movement number in cnt5 */
        cnt5 = mapNumbers[cnt2];

        /* If the currDir = 0 (right) */
        if (nCurrDir == 0)
        {
            /* Count of how many steps are taken */
            cnt3 = 0;
            while (1)
            {
                /* Keep moving cnt5 distance until either the x co-ordinate runs
                 * out of space or you have hit a "#" or space */
                while (currposX+1 < max_val && forestMap[currposY][currposX+1] == '.' && cnt3 < cnt5)
                {
                    ++cnt3;
                    /* Increment X co-ordinate to check for the next value */
                    ++currposX;
                }
                /* If the whole count has been reached, stop moving */
                if (cnt3 == cnt5)
                {
                    break;
                }
                /* If the next value is a "#", reached a wall, stop moving */
                if (currposX + 1 < max_val && forestMap[currposY][currposX+1] == '#')
                {
                    break;
                }
                /* If reached the end of line or a space */
                if (currposX+1 >= max_val || forestMap[currposY][currposX+1] == ' ')
                {
                    /* Find the next value that is not a space in the current line */
                    for (cnt4 = -1; forestMap[currposY][cnt4+1] == ' '; cnt4++);
                    /* If at least one value is not a space and has not reached
                     * a "#" at the beginning after space, that is the X co-ord */
                    if (cnt4 >= 0 && forestMap[currposY][cnt4+1] != '#')
                    {
                        currposX = cnt4+1;
                    }
                    /* Not a singla value is moved (no space), but the first
                     * index is a dot that is the current X co-ord */
                    else if (cnt4 == -1 && forestMap[currposY][0] == '.')
                    {
                        currposX = 0;
                    }
                    /* If reached a brick wall, stop moving */
                    else
                    {
                        break;
                    }
                }
                ++cnt3;
            }
        }
        /* If the currDir = 1 (down) */
        else if (nCurrDir == 1)
        {
            /* Count of how many steps are taken */
            cnt3 = 0;
            while (1)
            {
                /* Keep moving cnt5 distance until either the y co-ordinate runs
                 * out of space or you have hit a "#" or space */
                while (currposY+1 < forestMap.size() && forestMap[currposY+1][currposX] == '.' && cnt3 < cnt5)
                {
                    ++cnt3;
                    /* Increment Y co-ordinate to check for the next value */
                    ++currposY;
                }
                /* If the whole count has been reached, stop moving */
                if (cnt3 == cnt5)
                {
                    break;
                }
                /* If the next value is a "#", reached a wall, stop moving */
                if (currposY + 1 < forestMap.size() && forestMap[currposY+1][currposX] == '#')
                {
                    break;
                }
                /* If reached the end of line or a space */
                if (currposY+1 >= forestMap.size() || forestMap[currposY+1][currposX] == ' ')
                {
                    /* Find the next value that is not a space in the current line */
                    for (cnt4 = -1; forestMap[cnt4+1][currposX] == ' '; cnt4++);
                    /* If at least one value is not a space and has not reached
                     * a "#" at the beginning after space, that is the Y co-ord */
                    if (cnt4 >= 0 && forestMap[cnt4+1][currposX] != '#')
                    {
                        currposY = cnt4+1;
                    }
                    /* Not a singla value is moved (no space), but the first
                     * index is a dot that is the current Y co-ord */
                    else if (cnt4 == -1 && forestMap[0][currposX] == '.')
                    {
                        currposY = 0;
                    }
                    /* If reached a brick wall, stop moving */
                    else
                    {
                        break;
                    }
                }
                ++cnt3;
            }
        }
        /* If the currDir = 2 (left) */
        else if (nCurrDir == 2)
        {
            cnt3 = 0;
            while (1)
            {
                /* Keep moving cnt5 distance until either the x co-ordinate becomes
                 * zero or you have hit a "#" or space */
                while (currposX-1 >= 0 && forestMap[currposY][currposX-1] == '.' && cnt3 < cnt5)
                {
                    ++cnt3;
                    /* Decrement X co-ordinate to check for the next value */
                    --currposX;
                }
                /* If the whole count has been reached, stop moving */
                if (cnt3 == cnt5)
                {
                    break;
                }
                /* If the next value is a "#", reached a wall, stop moving */
                if (currposX > 0 && forestMap[currposY][currposX-1] == '#')
                {
                    break;
                }
                /* If reached the beginning of line or a space */
                if (currposX-1 < 0 || forestMap[currposY][currposX-1] == ' ')
                {
                    /* Find the next value that is not a space in the current line
                     * Start from the end */
                    for (cnt4 = max_val; forestMap[currposY][cnt4-1] == ' '; cnt4--);
                    /* If at least one value is not a space and has not reached
                     * a "#" at the end after space, that is the X co-ord */
                    if (cnt4 < max_val && forestMap[currposY][cnt4-1] != '#')
                    {
                        currposX = cnt4-1;
                    }
                    /* Not a singla value is moved (no space), but the last
                     * index is a dot, then that is the current X co-ord */
                    else if (cnt4 == max_val && forestMap[currposY][max_val-1] == '.')
                    {
                        currposX = max_val-1;
                    }
                    /* If reached a brick wall, stop moving */
                    else
                    {
                        break;
                    }
                }
                ++cnt3;
            }
        }
        /* If the currDir = 3 (up) */
        else if (nCurrDir == 3)
        {
            cnt3 = 0;
            while (1)
            {
                /* Keep moving cnt5 distance until either the y co-ordinate becomes
                 * zero or you have hit a "#" or space */
                while (currposY-1 >= 0 && forestMap[currposY-1][currposX] == '.' && cnt3 < cnt5)
                {
                    ++cnt3;
                    /* Decrement X co-ordinate to check for the next value */
                    --currposY;
                }
                /* If the whole count has been reached, stop moving */
                if (cnt3 == cnt5)
                {
                    break;
                }
                /* If the next value is a "#", reached a wall, stop moving */
                if (currposY > 0 && forestMap[currposY-1][currposX] == '#')
                {
                    break;
                }
                /* If reached the beginning of line or a space */
                if (forestMap[forestMap.size()-1][currposX] == '#')
                {
                    break;
                }
                if (currposY-1 < 0 || forestMap[currposY-1][currposX] == ' ')
                {
                    /* Find the next value that is not a space in the current line
                     * Start from the end */
                    for (cnt4 = forestMap.size(); forestMap[cnt4-1][currposX] == ' '; cnt4--);
                    /* If at least one value is not a space and has not reached
                     * a "#" at the end after space, that is the Y co-ord */
                    if (cnt4 < forestMap.size() && forestMap[cnt4-1][currposX] != '#')
                    {
                        currposY = cnt4-1;
                    }
                    /* Not a singla value is moved (no space), but the last
                     * index is a dot, then that is the current X co-ord */
                    else if (cnt4 == forestMap.size() && forestMap[forestMap.size()-1][currposX] == '.')
                    {
                        currposY = forestMap.size()-1;
                    }
                    /* If reached a brick wall, stop moving */
                    else
                    {
                        break;
                    }
                }
                ++cnt3;
            }
        }

        /* Read the direction now
         * Note: Place a check to avoid the index, cnt2 going beyond number of
         * directions */
        if (cnt2 < mapDirs.size())
        {
            /* If the direction is right, circ increment currDir */
            if (mapDirs[cnt2] == 'R')
            {
                nCurrDir = (nCurrDir + 1) % 4;
            }
            /* If the direction is left, circ decrement currDir */
            else if (mapDirs[cnt2] == 'L')
            {
                nCurrDir = (nCurrDir + 3) % 4;
            }
        }
    }

    /* Print the value of (Y * 1000 + X * 4 + currDir) */
    cout << "Part (a): " << (currposY + 1)* 1000 + (currposX + 1) * 4 + nCurrDir << endl;

    fseek(fp, 0L, SEEK_SET);

    fclose(fp);

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

