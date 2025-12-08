#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

char arr[1000][10000];

class coordinate
{
    public:
        int64_t x, y, z;
        coordinate(int64_t a, int64_t b, int64_t c)
        {
            x = a;
            y = b;
            z = c;
        }
        coordinate()
        {
            x = 0;
            y = 0;
            z = 0;
        }
        
        int64_t getDistanceSquared(coordinate& other)
        {
            return (x - other.x) * (x - other.x) +
                   (y - other.y) * (y - other.y) +
                   (z - other.z) * (z - other.z);
        }

        bool operator==(const coordinate& other) const
        {
            return (x == other.x &&
                    y == other.y &&
                    z == other.z);
        }
};

class connections
{
    public:
        coordinate c1;
        coordinate c2;

        int64_t distanceSquared;

        connections()
        {
            c1 = coordinate();
            c2 = coordinate();
        }

        connections(coordinate& coord1, coordinate& coord2)
        {
            c1 = coord1;
            c2 = coord2;
            distanceSquared = c1.getDistanceSquared(c2);
        }

        bool operator<(const connections& other) const
        {
            return other.distanceSquared < distanceSquared;
        }

        bool operator>(const connections& other) const
        {
            return other.distanceSquared > distanceSquared;
        }
};

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

    /* Vector to store all coordinates */
    vector<coordinate> vCoordinates;

    /* Priority queue to store all connections between coordinates 
     * This would contain two coordinates and the distance squared between them 
     * The queue would automatically sort based on the distance squared (least)
    */
    priority_queue<connections> vConnections;

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

        /* The coordinates are of the form x,y,z */
        sscanf(arr[cnt1], "%ld,%ld,%ld", &cnt2, &cnt3, &cnt4);

        /* Add that into the vector of coordinates */
        vCoordinates.push_back(coordinate(cnt2, cnt3, cnt4));

        /* Increment count */
        ++cnt1;
    }

    /* Get every combination of coordinate with every other coordinate */
    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        for (cnt3 = cnt2 + 1; cnt3 < cnt1; cnt3++)
        {
            /* Store the distance squared between the coordinate and every other 
             * coordinate into a priority queue */
            vConnections.push(connections(vCoordinates[cnt2], vCoordinates[cnt3]));
        }
    }

    /* Get the lowest distance connections first */
    connections topConnection = vConnections.top();
    vConnections.pop();

    /* Get the two coordinates */
    string sLowestIdx1 = to_string(topConnection.c1.x) + "," + to_string(topConnection.c1.y) + "," + to_string(topConnection.c1.z);
    string sLowestIdx2 = to_string(topConnection.c2.x) + "," + to_string(topConnection.c2.y) + "," + to_string(topConnection.c2.z);

    unordered_set<string> uset;
    uset.insert(sLowestIdx1);
    uset.insert(sLowestIdx2);

    /* Use a vector of sets to store the coordinates and distances 
     * Each set would represent a group of connected coordinates
     * When a new connection is found, it would be added to a new set (vector)
     * If it connects two different sets, those sets would be merged
    */
    vector<unordered_set<string>> vAllDistances;

    /* Insert the inital two set of coordinates */
    vAllDistances.push_back(uset);

    /* Maximum distance found so far */
    int64_t nMaxDist = 0;

    /* Total number of connections */
    int64_t nConnections = 0;

    while (true)
    {
        /* Increment total connections */
        ++nConnections;

        /* If the total connections reach 1000, execute part - 1 */
        if (nConnections == 1000)
        {
            /* Get highest three numbers */
            vector <int64_t> vTopSizes;
            /* Insert the sizes of all sets into a vector */
            for (cnt2 = 0; cnt2 < vAllDistances.size(); cnt2++)
            {
                vTopSizes.push_back(vAllDistances[cnt2].size());
            }
            /* Sort the vector in descending order */
            sort(vTopSizes.begin(), vTopSizes.end(), greater<int64_t>());
            /* Calculate part - 1 answer */
            nFirstPart = vTopSizes[0] * vTopSizes[1] * vTopSizes[2];
        }

        /* Get the top connection from the priority queue */
        topConnection = vConnections.top();
        vConnections.pop();

        /* Get the two coordinates */
        sLowestIdx1 = to_string(topConnection.c1.x) + "," + to_string(topConnection.c1.y) + "," + to_string(topConnection.c1.z);
        sLowestIdx2 = to_string(topConnection.c2.x) + "," + to_string(topConnection.c2.y) + "," + to_string(topConnection.c2.z);

        /* Find if the coordinates are already in any set */
        int64_t nFoundConnection = -1;

        /* Check each set to see if it contains either of the coordinates */
        for (cnt2 = 0; cnt2 < vAllDistances.size(); cnt2++)
        {
            /* If either coordinate is found in the set, insert both coordinates */
            if (vAllDistances[cnt2].find(sLowestIdx1) != vAllDistances[cnt2].end() ||
                vAllDistances[cnt2].find(sLowestIdx2) != vAllDistances[cnt2].end())
            {
                vAllDistances[cnt2].insert(sLowestIdx1);
                vAllDistances[cnt2].insert(sLowestIdx2);
                nFoundConnection = cnt2;
                break;
            }
        }

        /* If no set contains either coordinate, create a new set */
        if (nFoundConnection == -1)
        {
            /* Create a new set for the new connection */
            unordered_set<string> usetNew;
            /* Insert the two coordinates into the new set */
            usetNew.insert(sLowestIdx1);
            usetNew.insert(sLowestIdx2);
            /* Add the new set into the vector of sets */
            vAllDistances.push_back(usetNew);
            continue;
        }

        /* Merge sets if the new connection connects two different sets */
        for (cnt2 = 0; cnt2 < vAllDistances.size(); cnt2++)
        {
            /* If the current set is not the one where the connection was found */
            if (cnt2 != nFoundConnection)
            {
                /* If either coordinate is found in the current set */
                if (vAllDistances[cnt2].find(sLowestIdx1) != vAllDistances[cnt2].end() ||
                    vAllDistances[cnt2].find(sLowestIdx2) != vAllDistances[cnt2].end())
                {
                    /* Merge the current set into the found connection set */
                    for (const auto& str : vAllDistances[cnt2])
                    {
                        /* Insert each element from the current set into the 
                         * found connection set */
                        vAllDistances[nFoundConnection].insert(str);
                    }
                    /* Remove the current set from the vector */
                    vAllDistances.erase(vAllDistances.begin() + cnt2);
                    /* Decrement cnt2 to account for the removed set */
                    cnt2--;
                }
            }
        }

        /* Update the maximum distance found so far */
        for (cnt2 = 0; cnt2 < vAllDistances.size(); cnt2++)
        {
            nMaxDist = max(nMaxDist, (int64_t)vAllDistances[cnt2].size());
        }

        /* If the maximum distance equals the total number of coordinates, 
         * all coordinates are connected */
        if (nMaxDist == cnt1)
        {
            /* Calculate part - 2 answer 
             * Multiply the x coordinates of the two coordinates in the last 
             * connection
            */
            nSecondPart = topConnection.c1.x * topConnection.c2.x;
            break;
        }
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
