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

/* For more information see day 17, 2023 */

class Node
{
public:
    int64_t nElement;
    int64_t nCost;

    Node(int64_t elem, int64_t cost)
        :nElement(elem), nCost(cost)
    {
        ;
    }

    Node(void)
    {
        ;
    }

    bool operator<(const Node &newNode) const
    {
        return this->nCost > newNode.nCost;
    }
};

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

    const int64_t nMaxCost = 999999999999ll;

    vector<pair<int64_t, int64_t>> nCostMatrix[500];
    vector<int64_t> nCostFromStart(500, nMaxCost);
    priority_queue<Node> nToProcess;
    Node nStart;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        stringstream iss(arr[cnt1]);
        string word;

        cnt3 = 0;

        while (iss >> word)
        {
            cnt2 = atoll(word.c_str());
            if (cnt2 == 0)
            {
                cnt2 = nMaxCost;
            }
            else
            {
                nCostMatrix[cnt1].push_back(make_pair(cnt3, cnt2));
            }
            cnt3++;
        }

        /* Increment count to move to next line */
        ++cnt1;
    }

    nStart.nCost = 0;
    nStart.nElement = 0;

    nToProcess.push(nStart);
    nCostFromStart[0] = 0;

    while (nToProcess.size() > 0)
    {
        Node nCurrent = nToProcess.top();
        nToProcess.pop();
        int64_t nElement = nCurrent.nElement;
        int64_t nCost = nCurrent.nCost;

        cout << "Element: " << nElement << endl;
        cout << "Cost: " << nCost << endl;

        for (cnt2 = 0; cnt2 < nCostMatrix[nElement].size(); cnt2++)
        {
            int64_t nNextElement = nCostMatrix[nElement][cnt2].first;
            int64_t nNextCost = nCostMatrix[nElement][cnt2].second;
            if (nCostFromStart[nNextElement] > nCostFromStart[nElement] + nNextCost)
            {
                Node nNext;
                nCostFromStart[nNextElement] = nCostFromStart[nElement] + nNextCost;

                nNext.nCost = nCostFromStart[nNextElement];
                nNext.nElement = nNextElement;
                nToProcess.push(nNext);
            }
        }
    }

    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        cout << nCostFromStart[cnt2] << endl;
    }

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

