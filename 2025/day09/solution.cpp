#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[2000][10000];

class PointPairs
{
    public:
        pair<int64_t, int64_t> coord1;
        pair<int64_t, int64_t> coord2;

        int64_t nArea;

        PointPairs(pair<int64_t, int64_t> a, pair<int64_t, int64_t> b)
        {
            coord1 = a;
            coord2 = b;

            nArea = (abs(coord1.first - coord2.first)+1) *
                    (abs(coord1.second - coord2.second)+1);
        }
        PointPairs()
        {
            coord1 = make_pair(0, 0);
            coord2 = make_pair(0, 0);

            nArea = 0;
        }

        bool operator<(const PointPairs& other) const
        {
            return other.nArea > nArea;
        }
};

/* A priority queue for PointPairs to automatically sort the points as per
 * decreasing order of coordPairs between the two points 
 */
priority_queue<PointPairs> pqPointPair;
/* A collection of all point lines
 */
vector<PointPairs> vPointPair;
/* All lines containing the same x coordinate */
vector<PointPairs> vSameX;
/* All lines containing the same y coordinate */
vector<PointPairs> vSameY;


/* Function to check if a coordinate lies on the line joining the point pairs 
 * Returns true if point is on the line, false otherwise
 */
bool checkIfOnLine(pair<int64_t, int64_t> coord)
{
    /* Check in same x coordinate first */
    for (const auto& coordPairs : vSameX)
    {
        /* For this, the x coordinate must match and the y coordinate of the point
         * must lie between the y coordinates of the point pairs */
        if ((coordPairs.coord1.first == coord.first) && 
            (coord.second <= max(coordPairs.coord1.second, coordPairs.coord2.second)) &&
            (coord.second >= min(coordPairs.coord1.second, coordPairs.coord2.second)))
        {
            return true;
        }
    }

    /* Else, check in same y coordinate next */
    for (const auto& coordPairs : vSameY)
    {
        /* For this, the y coordinate must match and the x coordinate of the point
         * must lie between the x coordinates of the point pairs */
        if ((coordPairs.coord1.second == coord.second) &&
            (coord.first <= max(coordPairs.coord1.first, coordPairs.coord2.first)) &&
            (coord.first >= min(coordPairs.coord1.first, coordPairs.coord2.first)))
        {
            return true;
        }
    }

    /* If not found in either, return false */
    return false;
}

/* Function to check if a coordinate lies inside the polygon formed by the point 
 * pairs.
 *
 * Returns true if point is inside, false otherwise
 */
bool checkIfInside(pair<int64_t, int64_t> coord)
{
    /* Temp loop variables */
    int64_t nRayCuts = 0;

    /* If we see an edge while computing the ray tracing, we cannot determine
     * it correctly, so we just move to a different direction */
    bool bIfFoundEdge = false;

    /* Start by looking at all the polygon edges to the right of the point, that
     * cuts through the point. 
     * If there are odd number of cuts, then we conclude that the point is inside the
     * polygon. Or else, then point is outside the polygon.
     * 
     * However, while we look right, if we see the polygon's edge, we cannot 
     * determine correctly, so we break out and try a different direction
     */
    for (const auto& coordPairs : vSameX)
    {
        /* For looking at the perpendicular lines that are right of the point,
         * We look at the points that have the same x coordinate 
         * If we do not find a line, we simply look at other lines
         */
        if (coordPairs.coord1.first < coord.first)
        {
            continue;
        }
        /* If we find a line that is to the right of the point */
        if (coordPairs.coord1.first > coord.first)
        {
            /* If the point lies exactly on the polygon edge */
            if (coord.second == max(coordPairs.coord1.second, coordPairs.coord2.second) ||
                coord.second == min(coordPairs.coord1.second, coordPairs.coord2.second))
            {
                /* We set the flag and break out */
                bIfFoundEdge = true;
                break;
            }
            /* Else, if the point lies between the y coordinates of the polygon 
             * edge, we increment a count */
            else if (coord.second <= max(coordPairs.coord1.second, coordPairs.coord2.second) &&
                     coord.second >= min(coordPairs.coord1.second, coordPairs.coord2.second))
            {
                ++nRayCuts;
            }
        }
    }

    /* After checking all lines to the right, if we did not find an edge */
    if (bIfFoundEdge == false)
    {
        /* If the number of ray cuts is odd, point is inside */
        if (nRayCuts % 2 == 1)
        {
            return true;
        }
        /* Else, point is outside */
        else
        {
            return false;
        }
    }

    /* Reset variables for checking in other directions */
    bIfFoundEdge = false;
    nRayCuts = 0;

    /* Now, look at all polygon edges to the left of the point */
    for (const auto& coordPairs : vSameX)
    {
        /* For looking at the perpendicular lines that are left of the point,
         * We look at the points that have the same x coordinate 
         * If we do not find a line that is left, we simply look at other lines
         */
        if (coordPairs.coord1.first > coord.first)
        {
            continue;
        }
        /* If we find a line that is to the left of the point */
        if (coordPairs.coord1.first < coord.first)
        {
            /* If the point lies exactly on the polygon edge */
            if (coord.second == max(coordPairs.coord1.second, coordPairs.coord2.second) ||
                coord.second == min(coordPairs.coord1.second, coordPairs.coord2.second))
            {
                /* We set the flag and break out */
                bIfFoundEdge = true;
                break;
            }
            /* Else, if the point lies between the y coordinates of the polygon 
             * edge, we increment a count */
            else if (coord.second <= max(coordPairs.coord1.second, coordPairs.coord2.second) &&
                     coord.second >= min(coordPairs.coord1.second, coordPairs.coord2.second))
            {
                ++nRayCuts;
            }
        }

    }
    /* After checking all lines to the left, if we did not find an edge */
    if (bIfFoundEdge == false)
    {
        /* If the number of ray cuts is odd, point is inside */
        if (nRayCuts % 2 == 1)
        {
            return true;
        }
        /* Else, point is outside */
        else
        {
            return false;
        }
    }

    /* Reset variables for checking in other directions */
    bIfFoundEdge = false;
    /* Reset the count of ray cuts */
    nRayCuts = 0;

    /* Now, look at all polygon edges below the point */
    for (const auto& coordPairs : vSameY)
    {
        /* For looking at the horizontal lines that are below the point,
         * We look at the lines that have the same y coordinate but below the 
         * point to test. 
         * If we do not find a line, we simply look at other lines
         */
        if (coordPairs.coord1.second < coord.second)
        {
            continue;
        }
        /* If we find a line that is below the point */
        if (coordPairs.coord1.second > coord.second)
        {
            /* If the point lies exactly on the polygon edge */
            if (coord.first == max(coordPairs.coord1.first, coordPairs.coord2.first) ||
                coord.first == min(coordPairs.coord1.first, coordPairs.coord2.first))
            {
                /* We set the flag and break out */
                bIfFoundEdge = true;
                break;
            }
            /* Else, if the point lies between the x coordinates of the polygon 
             * edge, we increment a count */
            else if (coord.first <= max(coordPairs.coord1.first, coordPairs.coord2.first) &&
                     coord.first >= min(coordPairs.coord1.first, coordPairs.coord2.first))
            {
                ++nRayCuts;
            }
        }
    }

    /* After checking all lines below, if we did not find an edge */
    if (bIfFoundEdge == false)
    {
        /* If the number of ray cuts is odd, point is inside */
        if (nRayCuts % 2 == 1)
        {
            return true;
        }
        /* Else, point is outside */
        else
        {
            return false;
        }
    }

    /* Reset variables for checking in other directions */
    bIfFoundEdge = false;
    nRayCuts = 0;

    /* Now, look at all polygon edges above the point */
    for (const auto& coordPairs : vSameY)
    {
        /* For looking at the horizontal lines that are above the point,
         * We look at the lines that have the same y coordinate but above the 
         * point to test. 
         * If we do not find a line, we simply look at other lines
         */
        if (coordPairs.coord1.second > coord.second)
        {
            continue;
        }
        /* If we find a line that is above the point */
        if (coordPairs.coord1.second < coord.second)
        {
            /* If the point lies exactly on the polygon edge */
            if (coord.first == max(coordPairs.coord1.first, coordPairs.coord2.first) ||
                coord.first == min(coordPairs.coord1.first, coordPairs.coord2.first))
            {
                /* We set the flag and break out */
                bIfFoundEdge = true;
                break;
            }
            /* Else, if the point lies between the x coordinates of the polygon 
             * edge, we increment a count */
            else if (coord.first <= max(coordPairs.coord1.first, coordPairs.coord2.first) &&
                     coord.first >= min(coordPairs.coord1.first, coordPairs.coord2.first))
            {
                ++nRayCuts;
            }
        }
    }

    /* After checking all lines above, if we did not find an edge */
    if (bIfFoundEdge == false)
    {
        if (nRayCuts % 2 == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /* If we found an edge in all four directions, we cannot determine if the 
     * point is inside or outside the polygon 
     */
    cout << "Unable to determine if point is inside polygon" << endl;
    exit(-1);
}

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
    int64_t cnt15 = 0, cnt16 = 0, cnt17 = 0, cnt18 = 0, cnt19 = 0, cnt20 = 0, cnt21 = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    int64_t nFirstPart = 0;
    int64_t nSecondPart = 0;

    /* Vector to store all coordinates */
    vector<pair<int64_t, int64_t>> vCoordinates;

    /* Previous coordinate to help form the polygon */
    pair<int64_t, int64_t> coordPrev;

    /* Initialize previous coordinate */
    coordPrev.first = -1;
    coordPrev.second = -1;

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

        sscanf(arr[cnt1], "%ld,%ld", &cnt2, &cnt3);
        /* Store the coordinate */
        vCoordinates.push_back(make_pair(cnt2, cnt3));

        /* If previous coordinate is valid, form a point pair */
        if (cnt1 > 0)
        {
            /* Store the point pair */
            vPointPair.push_back(PointPairs(make_pair(coordPrev.first, coordPrev.second), make_pair(cnt2, cnt3)));
        }
        /* Update previous coordinate */
        coordPrev = make_pair(cnt2, cnt3);

        /* Increment count */
        ++cnt1;
    }

    /* Finally, connect the last coordinate to the first coordinate to 
     * complete the polygon
     */
    vPointPair.push_back(PointPairs(make_pair(coordPrev.first, coordPrev.second), vCoordinates[0]));

    /* Store all point pairs in the priority queue for processing */
    for (cnt2 = 0; cnt2 < vCoordinates.size(); cnt2++)
    {
        for (cnt3 = cnt2 + 1; cnt3 < vCoordinates.size(); cnt3++)
        {
            /* The priority queue stores the every coordinate with every other
             * coordinate of the polygon in the order of highest area first */
            pqPointPair.push(PointPairs(vCoordinates[cnt2], vCoordinates[cnt3]));
        }
    }

    /* Calculate and display part 1 answer */
    nFirstPart = pqPointPair.top().nArea;
    cout << "Part (a): " << nFirstPart << endl;

    /* Create a same x coordinate lines and same y coordinate lines */
    for (cnt2 = 0; cnt2 < vPointPair.size(); cnt2++)
    {
        /* If the point pair has the same x coordinate */
        if (vPointPair[cnt2].coord1.first == vPointPair[cnt2].coord2.first)
        {
            vSameX.push_back(vPointPair[cnt2]);
        }
        /* If the point pair has the same y coordinate */
        else if (vPointPair[cnt2].coord1.second == vPointPair[cnt2].coord2.second)
        {
            vSameY.push_back(vPointPair[cnt2]);
        }
    }

    /* Now, process each point pair from the priority queue */
    while (!pqPointPair.empty())
    {
        /* Get the top area point pair */
        PointPairs topPointPair = pqPointPair.top();
        pqPointPair.pop();

        /* Get the two other diagonal co-ordinates of the rectangle */
        pair<int64_t, int64_t> coord1 = make_pair(topPointPair.coord1.first, topPointPair.coord2.second);
        pair<int64_t, int64_t> coord2 = make_pair(topPointPair.coord2.first, topPointPair.coord1.second);

        /* First check if the other two diagonal coordinates are on the line or inside */
        if ((checkIfOnLine(coord1) == true || checkIfInside(coord1) == true) &&
            (checkIfOnLine(coord2) == true || checkIfInside(coord2) == true))
        {
            /* Now, check all four sides (perimeter) of the rectangle formed by the 
             * point pairs to see if all points on the sides are either
             * on the line or inside the polygon
             */
            /* Start with freezing x coordinate to min x:
             * min(x1, x2) : min(y1, y2) to max(y1, y2)
             */
            cnt3 = min(topPointPair.coord1.first, topPointPair.coord2.first);
            for (cnt2 = min(topPointPair.coord1.second, topPointPair.coord2.second);
                 cnt2 <= max(topPointPair.coord1.second, topPointPair.coord2.second);
                 cnt2++)
            {
                /* Check if they are present */
                if (checkIfOnLine(make_pair(cnt3, cnt2)) == false && 
                    checkIfInside(make_pair(cnt3, cnt2)) == false)
                {
                    break;
                }
            }
            /* If not, check move to the next point pair */
            if (cnt2 < (max(topPointPair.coord1.second, topPointPair.coord2.second) + 1))
            {
                continue;
            }

            /* Next, freeze x coordinate to max x:
             * max(x1, x2) : min(y1, y2) to max(y1, y2)
             */
            cnt3 = max(topPointPair.coord1.first, topPointPair.coord2.first);
            for (cnt2 = min(topPointPair.coord1.second, topPointPair.coord2.second);
                 cnt2 <= max(topPointPair.coord1.second, topPointPair.coord2.second);
                 cnt2++)
            {
                /* Check if they are present */
                if (checkIfOnLine(make_pair(cnt3, cnt2)) == false && 
                    checkIfInside(make_pair(cnt3, cnt2)) == false)
                {
                    break;
                }
            }
            /* If not, check move to the next point pair */
            if (cnt2 < (max(topPointPair.coord1.second, topPointPair.coord2.second) + 1))
            {
                continue;
            }

            /* Next, freeze y coordinate to min y:
             * min(y1, y2) : min(x1, x2) to max(x1, x2)
             */
            cnt3 = min(topPointPair.coord1.second, topPointPair.coord2.second);
            for (cnt2 = min(topPointPair.coord1.first, topPointPair.coord2.first);
                 cnt2 <= max(topPointPair.coord1.first, topPointPair.coord2.first);
                 cnt2++)
            {
                /* Check if they are present */
                if (checkIfOnLine(make_pair(cnt2, cnt3)) == false && 
                    checkIfInside(make_pair(cnt2, cnt3)) == false)
                {
                    break;
                }
            }
            /* If not, check move to the next point pair */
            if (cnt2 < (max(topPointPair.coord1.first, topPointPair.coord2.first) + 1))
            {
                continue;
            }

            /* Finally, freeze y coordinate to max y:
             * max(y1, y2) : min(x1, x2) to max(x1, x2)
             */
            cnt3 = max(topPointPair.coord1.second, topPointPair.coord2.second);
            for (cnt2 = min(topPointPair.coord1.first, topPointPair.coord2.first);
                 cnt2 <= max(topPointPair.coord1.first, topPointPair.coord2.first);
                 cnt2++)
            {
                /* Check if they are present */
                if (checkIfOnLine(make_pair(cnt2, cnt3)) == false && 
                    checkIfInside(make_pair(cnt2, cnt3)) == false)
                {
                    break;
                }
            }
            /* If not, check move to the next point pair */
            if (cnt2 < (max(topPointPair.coord1.first, topPointPair.coord2.first) + 1))
            {
                continue;
            }

            /* If we reach here, it means all four sides are either on the line
             * or inside the polygon
             * So, we have our answer for part b
             */
            nSecondPart = topPointPair.nArea;
            break;
        }

    }

    /* Display part - 2 answer */
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
