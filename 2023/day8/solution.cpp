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

int64_t gcd(int64_t a, int64_t b);
int64_t lcm(int64_t a, int64_t b);

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

    string sInstruction;

    /* Input node */
    vector <string> asInputNode;
    /* Left node to input */
    vector <string> asLeftNode;
    /* Right node to input */
    vector <string> asRightNode;

    /* Starting node string for part 1 */
    string sStartNodePart1;
    /* Starting nodes' indices for part 1 */
    int64_t nStartNodeIdxPart1;

    /* Starting node strings for part 2 */
    vector<string> asStartNodePart2;
    /* Starting nodes' indices for part 2 */
    vector<int64_t> anStartNodeIdxPart2;

    /* Left and right index of the node
     * [0] -> input node's left node index where it occurs in input node
     * [1] -> input node's right node index where it occurs in input node*/
    vector<int64_t> anNodeLeftRightIdx[2];

    vector <int64_t> nCountNode;

    stringstream iss;

    /* Read the first line for sInstructions */
    fgets(arr[cnt1], sizeof(arr[cnt1]), fp);
    iss.str(arr[cnt1]);
    iss >> sInstruction;
    cnt1++;

    /* Read extra new line and ignore */
    fgets(arr[cnt1], sizeof(arr[cnt1]), fp);
    cnt1++;

    /* Current count for the index */
    cnt2 = 0;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        iss.str(arr[cnt1]);
        string word;

        /* Extract input node */
        iss >> word;
        asInputNode.push_back(word);

        /* If the last character is 'A' store it in part2's  */
        if (word[word.size()-1] == 'A')
        {
            if (word == "AAA")
            {
                sStartNodePart1 = word;
                nStartNodeIdxPart1 = cnt2;
            }
            asStartNodePart2.push_back(word);
            anStartNodeIdxPart2.push_back(cnt2);
        }

        /* Extract "=" and ignore */
        iss >> word;

        /* Extract the left node and remove "(" and "," */
        iss >> word;
        word.erase(0, 1);
        word.erase(word.size()-1);
        /* Store it into the list of left nodes */
        asLeftNode.push_back(word);

        /* Extract the right node and remove ")" */
        iss >> word;
        word.erase(word.size()-1);
        /* Store it into the list of right nodes */
        asRightNode.push_back(word);

        /* Increment count to move to next line */
        ++cnt1;
        /* Increment count for index */
        ++cnt2;
    }


    /* For all input nodes */
    for (cnt2 = 0; cnt2 < asInputNode.size(); cnt2++)
    {
        for (cnt3 = 0; cnt3 < asInputNode.size(); cnt3++)
        {
            /* Find where in the input the left node's index is present */
            if (asLeftNode[cnt2] == asInputNode[cnt3])
            {
                /* Store the index in the left i.e., [0] */
                anNodeLeftRightIdx[0].push_back(cnt3);
            }
            /* Find where in the input the right node's index is present */
            if (asRightNode[cnt2] == asInputNode[cnt3])
            {
                /* Store the index in the right i.e., [1] */
                anNodeLeftRightIdx[1].push_back(cnt3);
            }
        }
    }

    /* After how many iterations the node becomes "ZZZ" */
    cnt7 = 0;
    /* Modulo for getting the instruction */
    cnt3 = 0;
    /* Set part one to zero */
    nPartOneSum = 0;

    while (true)
    {
        /* If right instruction */
        if (sInstruction[cnt3] == 'R')
        {
            int64_t nIdx = nStartNodeIdxPart1;
            /* Check if the right node of the current node is "ZZZ" */
            if (asInputNode[anNodeLeftRightIdx[1][nIdx]] == "ZZZ")
            {
                /* Store interation number into part 1 and exit */
                nPartOneSum = cnt7+1;
                break;
            }
            /* Else, make the current node as its right node */
            nStartNodeIdxPart1 = anNodeLeftRightIdx[1][nIdx];
        }
        /* If left instruction */
        else if (sInstruction[cnt3] == 'L')
        {
            int64_t nIdx = nStartNodeIdxPart1;
            /* Check if the left node of the current node is "ZZZ" */
            if (asInputNode[anNodeLeftRightIdx[0][nIdx]] == "ZZZ")
            {
                /* Store interation number into part 1 and exit */
                nPartOneSum = cnt7+1;
                break;
            }
            /* Else, make the current node as its left node */
            nStartNodeIdxPart1 = anNodeLeftRightIdx[0][nIdx];
        }
        /* Increment interation count */
        ++cnt7;
        ++cnt3;

        /* Loop around for getting next instruction */
        if (cnt3 >= sInstruction.size())
        {
            cnt3 -= sInstruction.size();
        }
    }

    /* Count value for each node for part 2 - initialise with zero*/
    for (cnt2 = 0; cnt2 < asStartNodePart2.size(); cnt2++)
    {
        nCountNode.push_back(0);
    }

    /* After how many iterations the node's last character becomes "Z" */
    cnt7 = 0;
    /* Initialise part two to 1 */
    nPartTwoSum = 1;

    /* For all starting nodes, i.e., nodes that end with "A" */
    for (cnt2 = 0; cnt2 < asStartNodePart2.size(); cnt2++)
    {
        /* Initialise count and index for this starting node */
        cnt3 = 0;
        cnt7 = 0;
        while (true)
        {
            /* If right instruction */
            if (sInstruction[cnt3] == 'R')
            {
                int64_t nIdx = anStartNodeIdxPart2[cnt2];
                /* Check if the right node of the current node ends with a "Z" */
                if (asInputNode[anNodeLeftRightIdx[1][nIdx]][2] == 'Z')
                {
                    /* Store interation number into part 1 and exit */
                    nCountNode[cnt2] = cnt7+1;
                    break;
                }
                /* Else, make the current node as its right node */
                anStartNodeIdxPart2[cnt2] = anNodeLeftRightIdx[1][nIdx];
            }
            /* If left instruction */
            else if (sInstruction[cnt3] == 'L')
            {
                int64_t nIdx = anStartNodeIdxPart2[cnt2];
                /* Check if the left node of the current node ends with a "Z" */
                if (asInputNode[anNodeLeftRightIdx[0][nIdx]][2] == 'Z')
                {
                    /* Store interation number into part 1 and exit */
                    nCountNode[cnt2] = cnt7+1;
                    break;
                }
                /* Else, make the current node as its left node */
                anStartNodeIdxPart2[cnt2] = anNodeLeftRightIdx[0][nIdx];
            }
            /* Increment interation count */
            ++cnt7;
            ++cnt3;

            /* Loop around for getting next instruction */
            if (cnt3 >= sInstruction.size())
            {
                cnt3 -= sInstruction.size();
            }
        }

        /* Finally for the sum, get the LCM of all the individual counts */
        nPartTwoSum = lcm(nPartTwoSum, nCountNode[cnt2]);
    }

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


/* Get the GCD of the numbers, a and b */
int64_t gcd(int64_t a, int64_t b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

/* Get the LCM of the numbers, a and b */
int64_t lcm(int64_t a, int64_t b)
{
    return (a / gcd(a, b)) * b;
}

