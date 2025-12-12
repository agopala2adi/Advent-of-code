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

/* Create a data type that can hold a device and its connections */
class Device
{
    public:
        /* Device name */
        string sStart;
        /* Connections from this device to other devices */
        vector<string> sConnections;

};

/* Map to hold all devices and their connections 
 * We use a hash map to quickly get the device by its name */
unordered_map<string, Device> devices;

/* Map to hold already searched device paths and their counts */
unordered_map<string, int64_t> devicePaths;

/* Function to search device paths from start to end device 
 * Returns the count of distinct paths
 * Uses DFS and memoization to store already computed paths
*/
int64_t searchDevice(string sStartDevice, string sEndDevice);

int64_t nTotalCount = 0;

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

        /* Split the line into words */
        stringstream ssLine(sLine);
        string sStart;

        /* Read the start device */
        ssLine >> sStart;
        sStart.pop_back(); /* remove the colon */

        /* Initialize the device in the map */
        devices[sStart].sStart = sStart;

        /* Read all connections from this device */
        string sConn;
        while (ssLine >> sConn)
        {
            /* Push all its connections */
            devices[sStart].sConnections.push_back(sConn);
        }

        /* Increment count */
        ++cnt1;
    }


    /* For part - 1, we go from "you" to "out" */
    nFirstPart = searchDevice("you", "out");
    /* Clear the already computed paths as we do not want it to affect subsequent
     * searches */
    devicePaths.clear();

    /* For part - 2, we go from "svr" to "out" via two possible paths:
     * 1. svr -> fft -> dac -> out
     * 2. svr -> dac -> fft -> out
     * We compute both paths and add them up for the final result 
     * 
     * Total number of combinations to reach svr -> fft -> dac -> out =
     *   (number of paths from svr to fft) * (number of paths from fft to dac) *
     *   (number of paths from dac to out) 
     * 
     * Total number of combinations to reach svr -> dac -> fft -> out =
     *   (number of paths from svr to dac) * (number of paths from dac to fft) *
     *   (number of paths from fft to out)
     */

    /* From "svr" to "fft" */
    int64_t nSvrToFft = searchDevice("svr", "fft");
    devicePaths.clear();

    /* From "fft" to "dac" */
    int64_t nFftToDac = searchDevice("fft", "dac");
    devicePaths.clear();

    /* From "dac" to "out" */
    int64_t nDacToOut = searchDevice("dac", "out");
    devicePaths.clear();

    /* Total combinations for svr -> fft -> dac -> out 
     * Is the product of all three path counts
    */
    int64_t nSvrToFftToDacToOut = nSvrToFft * nFftToDac * nDacToOut;

    /* From "svr" to "dac" */
    int64_t nSvrToDac = searchDevice("svr", "dac");
    devicePaths.clear();

    /* From "dac" to "fft" */
    int64_t nDacToFft = searchDevice("dac", "fft");
    devicePaths.clear();

    /* From "fft" to "out" */
    int64_t nFftToOut = searchDevice("fft", "out");
    devicePaths.clear();

    /* Total combinations for svr -> dac -> fft -> out 
     * Is the product of all three path counts
    */
    int64_t nSvrToDacToFftToOut = nSvrToDac * nDacToFft * nFftToOut;

    /* Final total combinations for part - 2 */
    nSecondPart = nSvrToFftToDacToOut + nSvrToDacToFftToOut;

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

/* Function to search device paths from start to end device 
 * Returns the count of distinct paths
 * Uses DFS and memoization to store already computed paths
*/
int64_t searchDevice(string sStartDevice, string sEndDevice) 
{
    int64_t nConnCount = 0;

    for (const auto& sConn : devices[sStartDevice].sConnections)
    {
        /* If already computed, use the stored value */
        if (devicePaths.find(sConn) != devicePaths.end())
        {
            /* Add the stored count to the connection count */
            nConnCount += devicePaths[sConn];
            continue;
        }
        /* If the connection is the end device, we found a path */
        if (sConn == sEndDevice)
        {
            /* Found a path to the end device */
            devicePaths[sStartDevice] = 1;
            return 1;
        }
        else
        {
            /* Else, search further down this connection */
            nConnCount += searchDevice(sConn, sEndDevice);
        }
    }

    /* Store the computed path count for this start device */
    devicePaths[sStartDevice] = nConnCount;
    return nConnCount;
}

