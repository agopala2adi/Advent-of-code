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

    int64_t mavXYCord = 0;
    const int64_t nYCordMax = 10000000ll;

    int64_t nPartOneSum = 0;
    int64_t nPartTwoSum = 0;

    vector <int64_t> nPos[3]; 
    vector <int64_t> nVel[3]; 

    /* Read each line from file */
    while (feof(fp) == 0)
    {
        int64_t x, y, z; 
        int64_t mx, my, mz; 
        fscanf(fp, "%" PRId64 ", %" PRId64 ", %" PRId64 " @ %" PRId64 ", %" PRId64 ", %" PRId64, &x, &y, &z, &mx, &my, &mz);

        nPos[0].push_back(x);
        nPos[1].push_back(y);
        nPos[2].push_back(z);

        nVel[0].push_back(mx);
        nVel[1].push_back(my);
        nVel[2].push_back(mz);

        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Remove the last element as there is a bug that includes it twice */
    nPos[0].pop_back();
    nPos[1].pop_back();
    nPos[2].pop_back();
    nVel[0].pop_back();
    nVel[1].pop_back();
    nVel[2].pop_back();

    /* Minimum value to consider */
    const double x_min = (double)200000000000000;
    /* Maximum value to consider */
    const double x_max = (double)400000000000000;

    /* For all pair of inputs */
    for (cnt2 = 0; cnt2 < (int64_t)nPos[0].size(); cnt2++)
    {
        /* For the pair */
        for (cnt3 = cnt2+1; cnt3 < (int64_t)nPos[0].size(); cnt3++)
        {
            /* Compute the slope of the line, y/x for first line */
            double m_slope1 = (double)nVel[1][cnt2] / (double)nVel[0][cnt2];
            /* Compute the slope of the line, y/x for second line */
            double m_slope2 = (double)nVel[1][cnt3] / (double)nVel[0][cnt3];

            /* Get the value of x and y for the two lines, 1 and 2 */
            double x1 = (double)nPos[0][cnt2];
            double x2 = (double)nPos[0][cnt3];
            double y1 = (double)nPos[1][cnt2];
            double y2 = (double)nPos[1][cnt3];

            /* If the slopes are same, do not compute the solution */
            if (m_slope1 == m_slope2)
            {
                continue;
            }

            /* Compute the X point of intersection */
            double x_val = ((y1 - y2) + ((x2 * m_slope2) - (x1*m_slope1))) / (m_slope2 - m_slope1);
            /* Substitute and Compute the Y point of intersection */
            double y_val = y1 + (x_val * m_slope1 - x1 * m_slope1);

            /* If x and y are between the values */
            if (x_val >= x_min && x_val <= x_max && y_val >= x_min && y_val <= x_max)
            {
                /* And it is in the future */
                if (((x_val >= x1 && nVel[0][cnt2] > 0) || (x_val <= x1 && nVel[0][cnt2] < 0)) && 
                    ((x_val >= x2 && nVel[0][cnt3] > 0) || (x_val <= x2 && nVel[0][cnt3] < 0)))
                {
                    /* Increment the value of part 1 sum */
                    ++nPartOneSum;
                }
            }
        }
    }

    /* For part2: */

    /* Store the final result here */
    long double valArrFinal[6] = {(long double)0};

    /* Keep checking until the answer becomes exact for three eqns */
    for (cnt7 = 0; cnt7 < (int64_t)nPos[0].size()-2; cnt7++)
    {
        long double p0x = (long double)nPos[0][0+cnt7];
        long double p1x = (long double)nPos[0][1+cnt7];
        long double p2x = (long double)nPos[0][2+cnt7];

        long double p0y = (long double)nPos[1][0+cnt7];
        long double p1y = (long double)nPos[1][1+cnt7];
        long double p2y = (long double)nPos[1][2+cnt7];

        long double p0z = (long double)nPos[2][0+cnt7];
        long double p1z = (long double)nPos[2][1+cnt7];
        long double p2z = (long double)nPos[2][2+cnt7];


        long double v0x = (long double)nVel[0][0+cnt7];
        long double v1x = (long double)nVel[0][1+cnt7];
        long double v2x = (long double)nVel[0][2+cnt7];

        long double v0y = (long double)nVel[1][0+cnt7];
        long double v1y = (long double)nVel[1][1+cnt7];
        long double v2y = (long double)nVel[1][2+cnt7];

        long double v0z = (long double)nVel[2][0+cnt7];
        long double v1z = (long double)nVel[2][1+cnt7];
        long double v2z = (long double)nVel[2][2+cnt7];

        /* Use this to store the system of linear equations in this order:
         * (p_x, p_y, p_z, v_x, v_y, v_z, constant) 
         * (  0,   1,   2,   3,   4,   5,   6)
         */
        long double linearEqn6[6][7] = {(long double)0};
        /* Keep a copy for verification purposes */
        long double linearEqn6Cpy[6][7] = {(long double)0};

        /*
         * Launch stone from point p at a velocity v:
         * Let p be the point at time t = 0, p = (p_x*i_hat + p_y*j_hat + p_z*k_hat)
         * and let v be the velocity, v = (v_x*i_hat + v_y*j_hat + v_z*k_hat)
         * 
         * Then for any hailstone i, with initial position p_i and velocity,
         * v_i and after some time t_i, 
         * 
         * =>      (p + t_i*v) = (p_i + t_i*v_i)
         * =>        (p - p_i) = t_i*(v_i - v)
         * => (p - p_i) cross (v_i - v) = 0
         *              (by taking the cross product of (v_i - v) on both sides)
         * => (p * v_i) - (p_i * v_i) - (p * v) + (p_i * v) = 0
         * Here, p * v are independent of index i, they can be removed by taking
         * difference between any two inputs i.
         * (p, v are vector unknowns, v_i and p_i known vectors and t_i is scalar)
         * 
         * => (p * v_0) - (p_0 * v_0) - (p * v) + (p_0 * v) = 0 and
         * => (p * v_1) - (p_1 * v_1) - (p * v) + (p_1 * v) = 0
         * 
         * Difference:
         * 
         * => (p * (v_0 - v_1)) - ((p_0 * v_0) - (p_1 * v_1)) + (v * (p_1 - p_0)) = 0    ... (i)
         * Similarly for 0 and 2:
         * 
         * => (p * (v_0 - v_2)) - ((p_0 * v_0) - (p_2 * v_2)) + (v * (p_2 - p_0)) = 0    ... (ii)
         * 
         * 
         * Solve eqn., (i) and (ii) for a system of 6 linear equations to get
         * p and v.
         */

        /* For 0-1 i_hat */
        linearEqn6[0][0] = (long double)0;
        linearEqn6[0][1] = v0z-v1z;
        linearEqn6[0][2] = -(v0y-v1y);
        linearEqn6[0][3] = (long double)0;
        linearEqn6[0][4] = p1z-p0z;
        linearEqn6[0][5] = -(p1y-p0y);
        linearEqn6[0][6] = -(long double)((int64_t)((int64_t)p1y*(int64_t)v1z) - 
                                          (int64_t)((int64_t)p1z*(int64_t)v1y) - 
                                          (int64_t)((int64_t)p0y*(int64_t)v0z) + 
                                          (int64_t)((int64_t)p0z*(int64_t)v0y));

        /* For 0-2 i_hat */
        linearEqn6[1][0] = (long double)0;
        linearEqn6[1][1] = v0z-v2z;
        linearEqn6[1][2] = -(v0y-v2y);
        linearEqn6[1][3] = (long double)0;
        linearEqn6[1][4] = p2z-p0z;
        linearEqn6[1][5] = -(p2y-p0y);
        linearEqn6[1][6] = -(long double)((int64_t)((int64_t)p2y*(int64_t)v2z) - 
                                          (int64_t)((int64_t)p2z*(int64_t)v2y) - 
                                          (int64_t)((int64_t)p0y*(int64_t)v0z) + 
                                          (int64_t)((int64_t)p0z*(int64_t)v0y));


        /* For 0-1 j_hat */
        linearEqn6[2][0] = -(v0z-v1z);
        linearEqn6[2][1] = (long double)0;
        linearEqn6[2][2] = (v0x-v1x);
        linearEqn6[2][3] = -(p1z-p0z);
        linearEqn6[2][4] = (long double)0;
        linearEqn6[2][5] = (p1x-p0x);
        linearEqn6[2][6] = -(long double)((int64_t)((int64_t)p1z*(int64_t)v1x) - 
                                          (int64_t)((int64_t)p1x*(int64_t)v1z) - 
                                          (int64_t)((int64_t)p0z*(int64_t)v0x) + 
                                          (int64_t)((int64_t)p0x*(int64_t)v0z));

        /* For 0-2 j_hat */
        linearEqn6[3][0] = -(v0z-v2z);
        linearEqn6[3][1] = (long double)0;
        linearEqn6[3][2] = (v0x-v2x);
        linearEqn6[3][3] = -(p2z-p0z);
        linearEqn6[3][4] = (long double)0;
        linearEqn6[3][5] = (p2x-p0x);
        linearEqn6[3][6] = -(long double)((int64_t)((int64_t)p2z*(int64_t)v2x) - 
                                          (int64_t)((int64_t)p2x*(int64_t)v2z) - 
                                          (int64_t)((int64_t)p0z*(int64_t)v0x) + 
                                          (int64_t)((int64_t)p0x*(int64_t)v0z));


        /* For 0-1 k_hat */
        linearEqn6[4][0] = (v0y-v1y);
        linearEqn6[4][1] = -(v0x-v1x);
        linearEqn6[4][2] = (long double)0;
        linearEqn6[4][3] = (p1y-p0y);
        linearEqn6[4][4] = -(p1x-p0x);
        linearEqn6[4][5] = (long double)0;
        linearEqn6[4][6] = -(long double)((int64_t)((int64_t)p1x*(int64_t)v1y) - 
                                          (int64_t)((int64_t)p1y*(int64_t)v1x) - 
                                          (int64_t)((int64_t)p0x*(int64_t)v0y) + 
                                          (int64_t)((int64_t)p0y*(int64_t)v0x));

        /* For 0-2 k_hat */
        linearEqn6[5][0] = (v0y-v2y);
        linearEqn6[5][1] = -(v0x-v2x);
        linearEqn6[5][2] = (long double)0;
        linearEqn6[5][3] = (p2y-p0y);
        linearEqn6[5][4] = -(p2x-p0x);
        linearEqn6[5][5] = (long double)0;
        linearEqn6[5][6] = -(long double)((int64_t)((int64_t)p2x*(int64_t)v2y) - 
                                          (int64_t)((int64_t)p2y*(int64_t)v2x) - 
                                          (int64_t)((int64_t)p0x*(int64_t)v0y) + 
                                          (int64_t)((int64_t)p0y*(int64_t)v0x));

        for (cnt1 = 0; cnt1 < 6; cnt1++)
        {
            for (cnt2 = 0; cnt2 < 7; cnt2++)
            {
                linearEqn6Cpy[cnt1][cnt2] = linearEqn6[cnt1][cnt2];
            }
        }

        /* Solve the system of linear equations using Gauss-Jordan elimination Method */

        /* For each row of input */
        for (cnt1 = 0; cnt1 < 5; cnt1++)
        {
            /* Check if pivot is zero */
            if (linearEqn6[cnt1][cnt1] == 0)
            {
                /* If the pivot is zero, swap with a non-zero pivot row */
                for (cnt2 = cnt1+1; cnt2 < 6; cnt2++)
                {
                    if (linearEqn6[cnt2][cnt1] != 0)
                    {
                        for (cnt3 = 0; cnt3 < 7; cnt3++)
                        {
                            swap(linearEqn6[cnt1][cnt3], linearEqn6[cnt2][cnt3]);
                        }
                        break;
                    }
                }
            }

            /* Get the value of 1/pivot */
            long double pivot = (long double)1 / linearEqn6[cnt1][cnt1];

            /* Multiply the row with 1/pivot */
            for (cnt2 = 0; cnt2 < 7; cnt2++)
            {
                linearEqn6[cnt1][cnt2] = linearEqn6[cnt1][cnt2] * pivot;
            }

            /* Make the pivot column below pivot zero by subtracting the pivot 
             * row */
            for (cnt2 = cnt1+1; cnt2 < 6; cnt2++)
            {
                long double fScale = linearEqn6[cnt2][cnt1];

                for (cnt3 = 0; cnt3 < 7; cnt3++)
                {
                    linearEqn6[cnt2][cnt3] = (linearEqn6[cnt2][cnt3]) - (fScale*linearEqn6[cnt1][cnt3]);
                }
            }
        }

        /* Store the value answer, unknowns here */
        long double valArrAns[6] = {(long double)0};

        /* Find the value of the unknowns using back substitution */
        for (cnt1 = 0; cnt1 < 6; cnt1++)
        {
            long double pivot = (long double)1/linearEqn6[5-cnt1][5-cnt1];
            long double fConst = linearEqn6[5-cnt1][6];
            for (cnt2 = 0; cnt2 < cnt1; cnt2++)
            {
                long double fTemp = valArrAns[5-cnt2];
                fConst -= fTemp*linearEqn6[5-cnt1][5-cnt2];
            }
            valArrAns[5-cnt1] = pivot * fConst;
        }

        /* Validate if the answer is correct for the given inputs
         * This may be done multiple times due to floating point precision
         * problems.
         */
        for (cnt3 = 0; cnt3 < 6; cnt3++)
        {
            int64_t val_cur = -(int64_t)linearEqn6Cpy[cnt3][6];

            for (cnt2 = 0; cnt2 < 6; cnt2++)
            {
                val_cur += (int64_t)valArrAns[cnt2]*(int64_t)linearEqn6Cpy[cnt3][cnt2];
            }
            if (val_cur != 0)
            {
                break;
            }
        }
        /* If the answer is correct for all 6 equations, stop processing inputs */
        if (cnt3 == 6)
        {
            for (cnt2 = 0; cnt2 < 6; cnt2++)
            {
                valArrFinal[cnt2] = (int64_t)valArrAns[cnt2];
            }
            break;
        }
    }

    /* Get the sum of x, y and z components of p */
    nPartTwoSum = (int64_t)valArrFinal[0] + (int64_t)valArrFinal[1] + (int64_t)valArrFinal[2];

    /* Display part b answer */
    cout << "Part (a): " << nPartOneSum << endl;
    cout << "Part (b): " << nPartTwoSum << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

