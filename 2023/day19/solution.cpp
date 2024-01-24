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

string s_workflw_name[1000];
vector<string> workflw_expr[1000];
vector<string> workflw_exprName[1000];

bool checkIfApproved(string start_str, int64_t nXMAS[4], int64_t nMaxCnt);
int64_t findMaxCombinations(string start_str, int64_t nMaxCnt, vector<int64_t> nRange);

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

    cnt3 = 0;

    vector<string> workflw_name;
    vector<int64_t> nRange;

    int64_t nXMAS[4];

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        string workflows = arr[cnt1];

        /* If encountering a new line, then increment a flag for identifying
         * the next set of x,m,a,s inputs */
        if (workflows.size() < 3)
        {
            cnt3++;
        }
        /* If we are still parsing the first input */
        else if (cnt3 == 0)
        {
            /* Replace the "{", "}", "," with spaces so that we can extract words  */
            for (cnt2 = 0; cnt2 < workflows.size(); cnt2++)
            {
                if (workflows[cnt2] == '{' || workflows[cnt2] == '}' || workflows[cnt2] == ',')
                {
                    workflows[cnt2] = ' ';
                }
            }

            stringstream iss(workflows);
            string word;

            /* Extract the first input workflow name */
            iss >> word;
            workflw_name.push_back(word);

            /* Store the workflow name in an array of strings too */
            s_workflw_name[workflw_name.size()-1] = word;

            /* Extract next set of words, each having a condition and next workflow */
            while (iss >> word)
            {
                string word2 = word;
                string word3 = "";

                /* Store only the condition in workflow expression -
                 * Each workflow expression index contains those expressions in
                 * that line
                 * Each workflow expression name contains which name the true
                 * expression should point to
                 * So, index 0 of workflow name contains just workflow name
                 * index 0 of workflow expression contains conditions 1, 2,
                 * so on till the last condition
                 * and index 0 of workflow expr name contains workflow names
                 * the workflow expression evaluates true
                 * This would contain one extra expr name as for the last false
                 * evaluation
                 * This continues for other indices as well
                 */
                for (cnt5 = 0; cnt5 < word2.size(); cnt5++)
                {
                    /* Collect till : */
                    if (word2[cnt5] == ':')
                    {
                        workflw_expr[workflw_name.size()-1].push_back(word3);
                        word3 = "";
                    }
                    else
                    {
                        word3 += word2[cnt5];
                    }
                }
                /* Store all the values after : */
                workflw_exprName[workflw_name.size()-1].push_back(word3);
            }
        }
        /* Next set of XMAS inputs */
        else
        {
            /* Replace those characters with space to split with spaces */
            for (cnt2 = 0; cnt2 < workflows.size(); cnt2++)
            {
                if (workflows[cnt2] == '{' || workflows[cnt2] == '}' || workflows[cnt2] == ',')
                {
                    workflows[cnt2] = ' ';
                }
            }

            stringstream iss(workflows);
            string word;

            /* Everything is neatly ordered, store the value of X in xmas[0],
             * M in xmas[1], A in xmas[2] and S in xmas[3] */
            iss >> word;
            word.erase(0, 2);
            nXMAS[0] = atoll(word.c_str());
            iss >> word;
            word.erase(0, 2);
            nXMAS[1] = atoll(word.c_str());
            iss >> word;
            word.erase(0, 2);
            nXMAS[2] = atoll(word.c_str());
            iss >> word;
            word.erase(0, 2);
            nXMAS[3] = atoll(word.c_str());

            /* If the value of XMAS is approved, then add it to part 1 */
            if (checkIfApproved("in", nXMAS, workflw_name.size()) == true)
            {
                nPartOneSum += (nXMAS[0] + nXMAS[1] + nXMAS[2] + nXMAS[3]);
            }
        }

        /* Increment count to move to next line */
        ++cnt1;
    }

    cnt1 = workflw_name.size();

    /* For part2, create a range between 1 and 4000 (both included) for all,
     * of XMAS. After each iteration, the values would be updated and
     * when hit with true approved condition, these range differences would be
     * multiplied.
     *
     * Index[0] is X min, Index[1] is X max
     * Index[2] is M min, Index[3] is M max
     * Index[4] is A min, Index[5] is A max
     * Index[6] is S min, Index[7] is S max
     */

    nRange.push_back(1);
    nRange.push_back(4000);
    nRange.push_back(1);
    nRange.push_back(4000);
    nRange.push_back(1);
    nRange.push_back(4000);
    nRange.push_back(1);
    nRange.push_back(4000);

    /* Get all the sum of the combinations starting with in */
    nPartTwoSum = findMaxCombinations("in", cnt1, nRange);

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

/* Recursive function to check if the value of the string is approved */
bool checkIfApproved(string start_str, int64_t nXMAS[4], int64_t nMaxCnt)
{
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;

    bool result = false;

    /* If the string is just A, return approved */
    if (start_str == "A")
    {
        return true;
    }
    /* If the string is just R, return rejected */
    else if (start_str == "R")
    {
        return false;
    }

    /* Else, search through all workflow names to find the name required */
    for (cnt1 = 0; cnt1 < nMaxCnt; cnt1++)
    {
        if (s_workflw_name[cnt1] == start_str)
        {
            /* If found, iterate through all of its expressions */
            for (cnt2 = 0; cnt2 < workflw_expr[cnt1].size(); cnt2++)
            {
                /* Get the expression in expr */
                string expr = workflw_expr[cnt1][cnt2];
                /* Remove the first two characters from expr */
                string word = expr;
                word.erase(0, 2);
                /* Get the expression's value in integer */
                cnt3 = atoll(word.c_str());

                /* If the expression starts with x, check for the X value using XMAS[0] */
                if (expr[0] == 'x')
                {
                    /* If less than, check if the value is less than */
                    if (expr[1] == '<' && nXMAS[0] < cnt3)
                    {
                        result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
                        break;
                    }
                    /* If greater than, check if the value is greater than */
                    else if (expr[1] == '>' && nXMAS[0] > cnt3)
                    {
                        result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
                        break;
                    }
                    /* If not, check for next expression */
                }
                /* If the expression starts with m, check for the M value using XMAS[1] */
                else if (expr[0] == 'm')
                {
                    /* If less than, check if the value is less than */
                    if (expr[1] == '<' && nXMAS[1] < cnt3)
                    {
                        result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
                        break;
                    }
                    /* If greater than, check if the value is greater than */
                    else if (expr[1] == '>' && nXMAS[1] > cnt3)
                    {
                        result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
                        break;
                    }
                    /* If not, check for next expression */
                }
                /* If the expression starts with a, check for the A value using XMAS[2] */
                else if (expr[0] == 'a')
                {
                    /* If less than, check if the value is less than */
                    if (expr[1] == '<' && nXMAS[2] < cnt3)
                    {
                        result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
                        break;
                    }
                    /* If greater than, check if the value is greater than */
                    else if (expr[1] == '>' && nXMAS[2] > cnt3)
                    {
                        result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
                        break;
                    }
                    /* If not, check for next expression */
                }
                /* If the expression starts with s, check for the S value using XMAS[3] */
                else if (expr[0] == 's')
                {
                    /* If less than, check if the value is less than */
                    if (expr[1] == '<' && nXMAS[3] < cnt3)
                    {
                        result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
                        break;
                    }
                    /* If greater than, check if the value is greater than */
                    else if (expr[1] == '>' && nXMAS[3] > cnt3)
                    {
                        result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
                        break;
                    }
                    /* If not, check for next expression */
                }
                else
                {
                    /* If not, one of X, M, A or S, report error */
                    cout << "Error in input: " << expr << endl;
                }
            }
            /* If none of the expressions are true, execute last expression name */
            if (cnt2 == workflw_expr[cnt1].size())
            {
                result = checkIfApproved(workflw_exprName[cnt1][cnt2], nXMAS, nMaxCnt);
            }
        }
    }

    /* Return the result */
    return result;
}

/* Recursive function to get the product of all maximum combinations */
int64_t findMaxCombinations(string start_str, int64_t nMaxCnt, vector<int64_t> nRange)
{
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;
    int64_t cnt4 = 0;
    int64_t cnt5 = 0;
    int64_t cnt6 = 0;
    int64_t cnt7 = 0;

    /* Store up to 6 ranges for maximum of 6 expressions */
    vector<int64_t> nRange2[6] = {nRange, nRange, nRange, nRange, nRange, nRange};

    /* If approved, return the value of (X_max-X_min)*(M_max-M_min)*(A_max-A_min)*(S_max-S_min) */
    if (start_str == "A")
    {
        cnt3 = (nRange[1] - nRange[0] + 1) * (nRange[3] - nRange[2] + 1) * (nRange[5] - nRange[4] + 1) * (nRange[7] - nRange[6] + 1);
        return cnt3;
    }
    /* If rejected, return zero */
    else if (start_str == "R")
    {
        return 0;
    }

    /* Search for the start string */
    for (cnt1 = 0; cnt1 < nMaxCnt; cnt1++)
    {
        if (s_workflw_name[cnt1] == start_str)
        {
            /* If found, get the expressions of that string */
            for (cnt2 = 0; cnt2 < workflw_expr[cnt1].size(); cnt2++)
            {
                string expr = workflw_expr[cnt1][cnt2];
                string word = expr;
                word.erase(0, 2);
                /* Extract the number from the expression and convert to integer */
                cnt3 = atoll(word.c_str());

                /* If expression is x: */
                if (expr[0] == 'x')
                {
                    /* If expression is less than */
                    if (expr[1] == '<')
                    {
                        /* Update the max value to that expression if more */
                        if (nRange2[cnt2][1] > cnt3-1)
                        {
                            nRange2[cnt2][1] = cnt3-1;
                        }
                        /* Update all other ranges to be compliment as this range
                         * was lesser */
                        for (cnt4 = cnt2+1; cnt4 < workflw_expr[cnt1].size()+1; cnt4++)
                        {
                            if (nRange2[cnt4][0] < cnt3)
                            {
                                nRange2[cnt4][0] = cnt3;
                            }
                        }
                    }
                    /* If expression is greater than */
                    else if (expr[1] == '>')
                    {
                        /* Update the min value to that expression if less */
                        if (nRange2[cnt2][0] < cnt3+1)
                        {
                            nRange2[cnt2][0] = cnt3+1;
                        }
                        /* Update all other ranges to be compliment as this range
                         * was greater */
                        for (cnt4 = cnt2+1; cnt4 < workflw_expr[cnt1].size()+1; cnt4++)
                        {
                            if (nRange2[cnt4][1] > cnt3)
                            {
                                nRange2[cnt4][1] = cnt3;
                            }
                        }
                    }
                }
                /* If expression is m: */
                else if (expr[0] == 'm')
                {
                    /* If expression is less than */
                    if (expr[1] == '<')
                    {
                        /* Update the max value to that expression if more */
                        if (nRange2[cnt2][3] > cnt3-1)
                        {
                            nRange2[cnt2][3] = cnt3-1;
                        }
                        /* Update all other ranges to be compliment as this range
                         * was lesser */
                        for (cnt4 = cnt2+1; cnt4 < workflw_expr[cnt1].size()+1; cnt4++)
                        {
                            if (nRange2[cnt4][2] < cnt3)
                            {
                                nRange2[cnt4][2] = cnt3;
                            }
                        }
                    }
                    /* If expression is more than */
                    else if (expr[1] == '>')
                    {
                        /* Update the min value to that expression if less */
                        if (nRange2[cnt2][2] < cnt3+1)
                        {
                            nRange2[cnt2][2] = cnt3+1;
                        }
                        /* Update all other ranges to be compliment as this range
                         * was greater */
                        for (cnt4 = cnt2+1; cnt4 < workflw_expr[cnt1].size()+1; cnt4++)
                        {
                            if (nRange2[cnt4][3] > cnt3)
                            {
                                nRange2[cnt4][3] = cnt3;
                            }
                        }
                    }
                }
                /* If expression is a: */
                else if (expr[0] == 'a')
                {
                    /* If expression is less than */
                    if (expr[1] == '<')
                    {
                        /* Update the max value to that expression if more */
                        if (nRange2[cnt2][5] > cnt3-1)
                        {
                            nRange2[cnt2][5] = cnt3-1;
                        }
                        /* Update all other ranges to be compliment as this range
                         * was lesser */
                        for (cnt4 = cnt2+1; cnt4 < workflw_expr[cnt1].size()+1; cnt4++)
                        {
                            if (nRange2[cnt4][4] < cnt3)
                            {
                                nRange2[cnt4][4] = cnt3;
                            }
                        }
                    }
                    /* If expression is more than */
                    else if (expr[1] == '>')
                    {
                        /* Update the min value to that expression if less */
                        if (nRange2[cnt2][4] < cnt3+1)
                        {
                            nRange2[cnt2][4] = cnt3+1;
                        }
                        /* Update all other ranges to be compliment as this range
                         * was greater */
                        for (cnt4 = cnt2+1; cnt4 < workflw_expr[cnt1].size()+1; cnt4++)
                        {
                            if (nRange2[cnt4][5] > cnt3)
                            {
                                nRange2[cnt4][5] = cnt3;
                            }
                        }
                    }
                }
                /* If expression is s: */
                else if (expr[0] == 's')
                {
                    /* If expression is less than */
                    if (expr[1] == '<')
                    {
                        /* Update the max value to that expression if more */
                        if (nRange2[cnt2][7] > cnt3-1)
                        {
                            nRange2[cnt2][7] = cnt3-1;
                        }
                        /* Update all other ranges to be compliment as this range
                         * was lesser */
                        for (cnt4 = cnt2+1; cnt4 < workflw_expr[cnt1].size()+1; cnt4++)
                        {
                            if (nRange2[cnt4][6] < cnt3)
                            {
                                nRange2[cnt4][6] = cnt3;
                            }
                        }
                    }
                    /* If expression is more than */
                    else if (expr[1] == '>')
                    {
                        /* Update the min value to that expression if less */
                        if (nRange2[cnt2][6] < cnt3+1)
                        {
                            nRange2[cnt2][6] = cnt3+1;
                        }
                        /* Update all other ranges to be compliment as this range
                         * was greater */
                        for (cnt4 = cnt2+1; cnt4 < workflw_expr[cnt1].size()+1; cnt4++)
                        {
                            if (nRange2[cnt4][7] > cnt3)
                            {
                                nRange2[cnt4][7] = cnt3;
                            }
                        }
                    }
                }

                /* Find the next expression name's max combination */
                cnt5 += findMaxCombinations(workflw_exprName[cnt1][cnt2], nMaxCnt, nRange2[cnt2]);
            }

            /* Find the next expression name's max combination after all expressions */
            cnt5 += findMaxCombinations(workflw_exprName[cnt1][cnt2], nMaxCnt, nRange2[cnt2]);
            break;
        }
    }

    /* Return the sum of all combinations  */
    return cnt5;
}
