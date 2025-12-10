#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

/* Used for constraint programming */
#include "ortools/sat/cp_model.h"

using namespace std;
using namespace operations_research;
using namespace operations_research::sat;

char arr[2000][10000];

/* Solves a system of linear equations
 * Ax = b
 * Elements of A are in {0,1}
 * Elements of b are >= 0
 * x are integer >= 0
 * Minimising sum of x_j
 */
int solveEquation(vector<vector<int>> &A, vector<int> &b);

int main(void)
{
    auto startTime = chrono::system_clock::now();
    time_t start_time = chrono::system_clock::to_time_t(startTime);

    FILE* fp = fopen("input.txt", "r");

    if (fp == nullptr)
    {
        cerr << "Cannot open input file." << endl;
        return -1;
    }

    cout << "Start Time: " << ctime(&start_time) << endl;

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
    int64_t cnt15 = 0, cnt16 = 0, cnt17 = 0, cnt18 = 0, cnt19 = 0, cnt20 = 0, cnt21 = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* Binary indicator converted to a integer */
    int64_t bIndicator;
    /* 1-D vector to store all the numbers inside each wiring schematic */
    vector<int64_t> vWiringSchematic;

    bitset<32> bsBits;

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

        int64_t nNumbWiring = 0;
        int64_t nJoltageVals = 0;
        bool bJoltageStart = false;

        /* Count the number of wiriting and joltage values
         * This will be given by:
         * Wiring = the number of parantheses
         * Joltage values = 1 + number of commas after the start of '{'
        */
        for (cnt2 = 0; cnt2 < sLine.size(); cnt2++)
        {
            if (sLine[cnt2] == '(')
            {
                ++nNumbWiring;
            }
            else if (sLine[cnt2] == '{')
            {
                bJoltageStart = true;
            }
            else if (bJoltageStart == true && sLine[cnt2] == ',')
            {
                ++nJoltageVals;
            }
        }
        nJoltageVals++;

        /* Split the input line now */
        stringstream ssLine(sLine);
        string segment;

        /* Read the first word = light diagram */
        ssLine >> segment;

        int64_t nLightDiagram = 0;
        for (cnt2 = 1; cnt2 < segment.size(); cnt2++)
        {
            if (segment[cnt2] == '#')
            {
                nLightDiagram = (nLightDiagram | (1 << (cnt2 - 1)));
            }
        }

        /* Store the light diagram into indicator */
        bIndicator = nLightDiagram;
        /* Clear the wiring schematic numbers */
        vWiringSchematic.clear();

        /* Create a 2-D vector with size nJoltageVals x nNumbWiring 
         * This is the A matrix for the equation:
         * Ax = b
         */
        vector<vector<int>> aValues = vector<vector<int>>(nJoltageVals, vector<int>(nNumbWiring, 0));
        /* b vector */
        vector<int> bValues;

        int64_t nWiringNumber = 0;

        /* Now start reading all the wiring schematics */
        while (ssLine >> segment)
        {
            /* If we see a '{' or '}', then break as we do not want to read
             * the joltage values */
            if (segment[0] == '{' || segment[0] == '}')
            {
                break;
            }

            /* Replace ',' , '(', ')' with space to help in extraction of numbers */
            for (cnt2 = 0; cnt2 < segment.size(); cnt2++)
            {
                if (segment[cnt2] == ',' || segment[cnt2] == '(' || segment[cnt2] == ')')
                {
                    segment[cnt2] = ' ';
                }
            }

            /* Temp string for number */
            int64_t nNumber;
            stringstream ssNumbers(segment);

            int64_t nSingleWiringValue = 0;

            /* Now start extracting all the numbers inside a wiring schematic 
             * Start initialising the 2-D vector with 0s and 1s
             * 
             * If number 'k' is present, then set the k'th row and wiring 
             * schematic's number column to 1
             * i.e., aValues[k][nWiringNumber] = 1
            */
            while (ssNumbers >> nNumber)
            {
                aValues[nNumber][nWiringNumber] = 1;
                nSingleWiringValue = (nSingleWiringValue | (1 << nNumber));
            }
            vWiringSchematic.push_back(nSingleWiringValue);
            nWiringNumber++;
        }

        bsBits.reset();

        int64_t nMinButtonPresses = INT64_MAX;

        /* Assumed that the buttons would only need to be pressed at most once
         * So, do a brute force search of all 2^n combinations 
        */
        for (cnt2 = 0; cnt2 < pow(2, vWiringSchematic.size()); cnt2++)
        {
            cnt5 = 0;
            for (cnt3 = 0; cnt3 < bsBits.size(); cnt3++)
            {
                if (bsBits[cnt3] == 1)
                {
                    cnt5 = (cnt5 ^ vWiringSchematic[cnt3]);
                }
            }
            /* If the number after pressing the button matches indicator */
            if (cnt5 == bIndicator)
            {
                /* Count the number of bits set in cnt2 */
                nMinButtonPresses = min(nMinButtonPresses, (int64_t)bsBits.count());
            }

            /* Increment 1 to the bit values 
             * Flip the least significant bit 
             * 
             * If the bit is 1 before flipping, then it becomes 0 after flipping.
             * Run a for loop to find the next 1 bit and flip it to 0
             * 
             * If it becomes 1 after flipping, stop the loop
             * Else, keep flipping the next bit until we find a 1
             */
            bsBits.flip(0);
            for (cnt3 = 0; cnt3 < bsBits.size() - 1; cnt3++)
            {
                if (bsBits[cnt3] == 1)
                {
                    break;
                }
                /* Set the next bit to zero */
                bsBits.reset(cnt3);
                bsBits.flip(cnt3 + 1);
            }
        }

        /* Add the minimum button presses to first part answer */
        nFirstPart += nMinButtonPresses;

        /* Now, coming to the joltage numbers 
         * Replace all ',' with spaces to help in extraction of numbers
        */
        for (cnt2 = 0; cnt2 < segment.size(); cnt2++)
        {
            if (segment[cnt2] == ',' || segment[cnt2] == '{' || segment[cnt2] == '}')
            {
                segment[cnt2] = ' ';
            }
        }

        int64_t nNumber;

        /* Now extract all the b values */
        stringstream ssJoltageNumb(segment);
        while (ssJoltageNumb >> nNumber)
        {
            /* Insert into b values */
            bValues.push_back((int)nNumber);
        }

        /* Solve the equation */
        int nResult = solveEquation(aValues, bValues);

        /* Add the sum to second part answer */
        nSecondPart += (int64_t)nResult;

        /* Increment count */
        ++cnt1;
    }


    /* Display part - 1 and 2 answers */
    cout << "Part (a): " << nFirstPart << endl;
    cout << "Part (b): " << nSecondPart << endl;

    /* Close the file */
    fclose(fp);

    auto endTime = chrono::system_clock::now();
    chrono::duration<double> elapsedSecs = endTime-startTime;
    time_t end_time = chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

/* Helper: derive tight upper bounds for each x_j. */
/* U_j = min b_i over rows where A[i][j] = 1 (else 0). */
static vector<int> TightUpperBounds(const vector<vector<int>>& A,
                                    const vector<int>& b) 
{
    const int m = static_cast<int>(A.size());
    const int n = static_cast<int>(A.empty() ? 0 : A[0].size());
    vector<int> U(n, 0);
    for (int j = 0; j < n; ++j) 
    {
        int min_b = numeric_limits<int>::max();
        bool appears = false;
        for (int i = 0; i < m; ++i) 
        {
            if (A[i][j] == 1) 
            { 
                appears = true; 
                min_b = min(min_b, b[i]); 
            }
        }
        U[j] = appears ? min_b : 0;
    }
    return U;
}

/* Solve the equation Ax = b with integer x >= 0,
 * minimising sum of x_j.
 * Returns the objective value (min of sum of x_j) if feasible, 
 * else exits.
 */
int solveEquation(vector<vector<int>> &A, vector<int> &b) 
{
    const int m = A.size();
    const int n = A.empty() ? 0 : A[0].size();

    /* Quick feasibility check: any all-zero row requires b[i] == 0. */
    for (int i = 0; i < m; ++i) 
    {
        bool has_one = false;
        for (int j = 0; j < n; ++j)
        {
            has_one |= (A[i][j] == 1);
        }
        if (!has_one && b[i] != 0) 
        {
            cerr << "Infeasible: row " << i
                << " has all zeros but b[" << i << "] = " << b[i] << "\n";
            exit(0);
        }
    }

    /* Model */
    CpModelBuilder model;

    /* Decision variables x_j in [0, U_j], integer. */
    vector<int> U = TightUpperBounds(A, b);
    vector<IntVar> x(n);
    for (int j = 0; j < n; ++j) 
    {
        x[j] = model.NewIntVar(Domain(0, U[j])).WithName("x_" + to_string(j));
    }

    /* Equality constraints: sum of selected x_j equals b[i]. */
    for (int i = 0; i < m; ++i) 
    {
        LinearExpr lhs;
        for (int j = 0; j < n; ++j) 
        {
            lhs += x[j] * A[i][j];
        }
        model.AddEquality(lhs, b[i]);
    }

    /* Objective: minimise sum_j x_j */
    LinearExpr sum_x;
    for (int j = 0; j < n; ++j)
    {
        sum_x += x[j];
    }
    model.Minimize(sum_x);

    /* Solve */
    Model sat_model;
    SatParameters params;
    params.set_num_search_workers(8);     /* parallel search */
    params.set_log_search_progress(false); /* silence logs */
    sat_model.Add(NewSatParameters(params));

    const CpSolverResponse resp = SolveCpModel(model.Build(), &sat_model);

    /* Report */
    if (resp.status() == CpSolverStatus::OPTIMAL || resp.status() == CpSolverStatus::FEASIBLE) 
    {
        return resp.objective_value();
    }
    else 
    {
        cerr << "No feasible solution. Status = " << CpSolverStatus_Name(resp.status()) << "\n";
        exit(0);
    }
}
