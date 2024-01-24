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

/* Direction enum - Right, Down, Left, Up */
enum DIRECTION
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};

/* Node structure (class) for storing it into priority queue */
class Node
{
public:
    /* Cost of the node */
    int64_t nCost;
    /* X position (row number) of the node */
    int64_t x_pos;
    /* Y position (column number) of the node */
    int64_t y_pos;
    /* Direction from before of the node */
    DIRECTION eDir;
    /* Number of steps taken in that direction for the node */
    int8_t nSteps;

    /* Constructor for initialising the values */
    Node(int64_t cost, int64_t pos_x, int64_t pos_y, DIRECTION dir, int8_t steps)
        : nCost(cost), x_pos(pos_x), y_pos(pos_y), eDir(dir), nSteps(steps)
    {
        ;
    }
    /* Constructor for initialising zeros */
    Node(void)
        : nCost(0), x_pos(0), y_pos(0), eDir(RIGHT), nSteps(0)
    {
        ;
    }
    /* Comparator operator, < for placing elements in priority queue */
    bool operator<(const Node &newNode) const
    {
        /* Returns true if the second argument's cost is lesser than first */
        return this->nCost > newNode.nCost;
    }
};

/* Not processed nodes as a priority queue */
priority_queue<Node> not_processed;

/* For already processed elements
 * Here, elements are of the form: "dir steps x_val y_val" 
*/
unordered_map<string, int8_t> processed;

/* Temporary nodes for inserting into not-processed queue */
Node oNext;
Node oCurrent;
Node oStart;

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

    vector <string> heatLoss;

    /* X coordinate is vertical and Y coordinate is horizontal */

    /* Last co-ordinate's row position */
    int64_t nEndX;
    /* Last co-ordinate's col position */
    int64_t nEndY;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        string sInpLine = arr[cnt1];

        /* Remove the last new line character(s) */
        if (sInpLine[sInpLine.size()-1] == '\n' || sInpLine[sInpLine.size()-1] == '\r')
        {
            sInpLine.pop_back();
        }
        if (sInpLine[sInpLine.size()-1] == '\n' || sInpLine[sInpLine.size()-1] == '\r')
        {
            sInpLine.pop_back();
        }

        /* Read the matrix and store them in heat loss vector of strings */
        heatLoss.push_back(sInpLine);

        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Store the (X and Y) co-ordinates of the last element of the matrix */
    nEndX = heatLoss.size();
    nEndY = heatLoss[0].size();

    /* For Part 1 */

    /* Assign arbitrary direction to initial direction */
    oStart.eDir = RIGHT;
    /* Set the initial number of steps to zero */
    oStart.nSteps = 0;
    /* Initial (x, y) = 0 */
    oStart.x_pos = 0;
    oStart.y_pos = 0;
    /* Set the initial cost to zero */
    oStart.nCost = 0;

    /* Place the structure into the priority queue */
    not_processed.push(oStart);

    /* As long as there are elements to process in the priority queue */
    while (not_processed.size() > 0)
    {
        /* Get the top value in the priority queue with the least cost */
        oCurrent = not_processed.top();

        /* Remove that from the priority queue */
        not_processed.pop();

        /* Form a string collection of direction, steps, and x and y */
        string sCollection = to_string(oCurrent.eDir) + " " + to_string(oCurrent.nSteps) + " " + to_string(oCurrent.x_pos) + " " + to_string(oCurrent.y_pos);
        if (processed.find(sCollection) != processed.end())
        {
            /* If that collection is already processed, ignore it and continue */
            continue;
        }
        else
        {
            /* Else, include it in processed */
            processed[sCollection] = 1;
        }

        /* If the last co-ordinate is reached, stop and store its cost */
        if (oCurrent.x_pos == nEndX-1 && oCurrent.y_pos == nEndY-1)
        {
            nPartOneSum = oCurrent.nCost;
            break;
        }

        /* If the current direction is right */
        if (oCurrent.eDir == RIGHT)
        {
            /* Check if it can continue moving right */
            if (oCurrent.nSteps < 3 && oCurrent.y_pos < nEndY-1) 
            {
                /* If it can, then continue moving and accumulating cost */
                oNext.nSteps = oCurrent.nSteps + 1;
                oNext.y_pos = oCurrent.y_pos + 1;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = oCurrent.eDir;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move down */
            if (oCurrent.x_pos < nEndX-1)
            {
                /* If it can, set the number of steps to 1, modify the direction,
                 * co-ordinates, and cost.
                 * Add the step's cost into the final cost */
                oNext.nSteps = 1;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos + 1;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = DOWN;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move up */
            if (oCurrent.x_pos > 0)
            {
                /* If it can, set the number of steps to 1, modify the direction,
                 * co-ordinates, and cost.
                 * Add the step's cost into the final cost */
                oNext.nSteps = 1;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos - 1;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = UP;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
        }
        /* If the current direction is down */
        else if (oCurrent.eDir == DOWN)
        {
            /* Check if it can continue moving down */
            if (oCurrent.nSteps < 3 && oCurrent.x_pos < nEndX-1)
            {
                /* If it can, then continue moving and accumulating cost */
                oNext.nSteps = oCurrent.nSteps + 1;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos + 1;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = oCurrent.eDir;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move right */
            if (oCurrent.y_pos < nEndY-1)
            {
                /* If it can, set the number of steps to 1, modify the direction,
                 * co-ordinates, and cost.
                 * Add the step's cost into the final cost */
                oNext.nSteps = 1;
                oNext.y_pos = oCurrent.y_pos + 1;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = RIGHT;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move left */
            if (oCurrent.y_pos > 0)
            {
                /* If it can, set the number of steps to 1, modify the direction,
                 * co-ordinates, and cost.
                 * Add the step's cost into the final cost */
                oNext.nSteps = 1;
                oNext.y_pos = oCurrent.y_pos - 1;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = LEFT;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
        }
        /* If the current direction is left */
        else if (oCurrent.eDir == LEFT)
        {
            /* Check if it can continue moving left */
            if (oCurrent.nSteps < 3 && oCurrent.y_pos > 0)
            {
                /* If it can, then continue moving and accumulating cost */
                oNext.nSteps = oCurrent.nSteps + 1;
                oNext.y_pos = oCurrent.y_pos - 1;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = oCurrent.eDir;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move down */
            if (oCurrent.x_pos < nEndX-1)
            {
                /* If it can, set the number of steps to 1, modify the direction,
                 * co-ordinates, and cost.
                 * Add the step's cost into the final cost */
                oNext.nSteps = 1;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos + 1;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = DOWN;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move up */
            if (oCurrent.x_pos > 0)
            {
                /* If it can, set the number of steps to 1, modify the direction,
                 * co-ordinates, and cost.
                 * Add the step's cost into the final cost */
                oNext.nSteps = 1;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos - 1;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = UP;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
        }
        /* If the current direction is up */
        else if (oCurrent.eDir == UP)
        {
            /* Check if it can continue moving up */
            if (oCurrent.nSteps < 3 && oCurrent.x_pos > 0)
            {
                /* If it can, then continue moving and accumulating cost */
                oNext.nSteps = oCurrent.nSteps + 1;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos - 1;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = oCurrent.eDir;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move right */
            if (oCurrent.y_pos < nEndY-1)
            {
                /* If it can, set the number of steps to 1, modify the direction,
                 * co-ordinates, and cost.
                 * Add the step's cost into the final cost */
                oNext.nSteps = 1;
                oNext.y_pos = oCurrent.y_pos + 1;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = RIGHT;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move left */
            if (oCurrent.y_pos > 0)
            {
                /* If it can, set the number of steps to 1, modify the direction,
                 * co-ordinates, and cost.
                 * Add the step's cost into the final cost */
                oNext.nSteps = 1;
                oNext.y_pos = oCurrent.y_pos - 1;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = LEFT;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
        }
        else
        {
            cout << "Wrong direction " << oCurrent.eDir << endl;
        }
    }

    /* For Part 2 */

    /* Remove all elements from already processed as we would want to process 
     * again */
    processed.clear();
    /* Clear the not processed elements too */
    not_processed = priority_queue<Node>();

    /* Since the initial movement is constraint for right and down, precompute
     * both for 4 steps and add the costs */
    oStart.eDir = RIGHT;
    oStart.nSteps = 4;
    oStart.x_pos = 0;
    oStart.y_pos = 4;
    oStart.nCost = heatLoss[0][1] + heatLoss[0][2] + heatLoss[0][3] + heatLoss[0][4] - 4*'0';
    not_processed.push(oStart);

    oStart.eDir = DOWN;
    oStart.nSteps = 4;
    oStart.x_pos = 4;
    oStart.y_pos = 0;
    oStart.nCost = heatLoss[1][0] + heatLoss[2][0] + heatLoss[3][0] + heatLoss[4][0] - 4*'0';
    not_processed.push(oStart);

    /* As long as there are elements to process in the priority queue */
    while (not_processed.size() > 0)
    {
        /* Get the top value in the priority queue with the least cost */
        oCurrent = not_processed.top();
        /* Remove that from the priority queue */
        not_processed.pop();

        /* Form a string collection of direction, steps, and x and y */
        string sCollection = to_string(oCurrent.eDir) + " " + to_string(oCurrent.nSteps) + " " + to_string(oCurrent.x_pos) + " " + to_string(oCurrent.y_pos);
        if (processed.find(sCollection) != processed.end())
        {
            /* If that collection is already processed, ignore it and continue */
            continue;
        }
        else
        {
            /* Else, include it in processed */
            processed[sCollection] = 1;
        }

        /* If the last co-ordinate is reached, stop and store its cost */
        if (oCurrent.x_pos == nEndX-1 && oCurrent.y_pos == nEndY-1)
        {
            nPartTwoSum = oCurrent.nCost;
            break;
        }

        /* If the current direction is right */
        if (oCurrent.eDir == RIGHT)
        {
            /* Check if it can continue moving right */
            if (oCurrent.nSteps < 10 && oCurrent.y_pos < nEndY-1) 
            {
                /* If it can, then continue moving and accumulating cost */
                oNext.nSteps = oCurrent.nSteps + 1;
                oNext.y_pos = oCurrent.y_pos + 1;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = oCurrent.eDir;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move down by at least 4 blocks */
            if (oCurrent.x_pos < nEndX-4)
            {
                /* If it can, set the number of steps to 4, modify the direction,
                 * co-ordinates, and cost.
                 * Add all the four steps' cost into the final cost */
                oNext.nSteps = 4;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos + 4;
                oNext.nCost = oCurrent.nCost + 
                              (heatLoss[oCurrent.x_pos+1][oCurrent.y_pos] + 
                              heatLoss[oCurrent.x_pos+2][oCurrent.y_pos] +
                              heatLoss[oCurrent.x_pos+3][oCurrent.y_pos] +
                              heatLoss[oCurrent.x_pos+4][oCurrent.y_pos]) - 4*'0';
                oNext.eDir = DOWN;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move up by at least 4 blocks */
            if (oCurrent.x_pos > 3)
            {
                /* If it can, set the number of steps to 4, modify the direction,
                 * co-ordinates, and cost.
                 * Add all the four steps' cost into the final cost */
                oNext.nSteps = 4;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos - 4;
                oNext.nCost = oCurrent.nCost + 
                              (heatLoss[oCurrent.x_pos-1][oCurrent.y_pos] + 
                              heatLoss[oCurrent.x_pos-2][oCurrent.y_pos] +
                              heatLoss[oCurrent.x_pos-3][oCurrent.y_pos] +
                              heatLoss[oCurrent.x_pos-4][oCurrent.y_pos]) - 4*'0';
                oNext.eDir = UP;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
        }
        /* If the current direction is down */
        else if (oCurrent.eDir == DOWN)
        {
            /* Check if it can continue moving down */
            if (oCurrent.nSteps < 10 && oCurrent.x_pos < nEndX-1)
            {
                /* If it can, then continue moving and accumulating cost */
                oNext.nSteps = oCurrent.nSteps + 1;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos + 1;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = oCurrent.eDir;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move right by at least 4 blocks */
            if (oCurrent.y_pos < nEndY-4)
            {
                /* If it can, set the number of steps to 4, modify the direction,
                 * co-ordinates, and cost.
                 * Add all the four steps' cost into the final cost */
                oNext.nSteps = 4;
                oNext.y_pos = oCurrent.y_pos + 4;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + 
                              (heatLoss[oCurrent.x_pos][oCurrent.y_pos+1] + 
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos+2] +
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos+3] +
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos+4]) - 4*'0';
                oNext.eDir = RIGHT;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move left by at least 4 blocks */
            if (oCurrent.y_pos > 3)
            {
                /* If it can, set the number of steps to 4, modify the direction,
                 * co-ordinates, and cost.
                 * Add all the four steps' cost into the final cost */
                oNext.nSteps = 4;
                oNext.y_pos = oCurrent.y_pos - 4;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + 
                              (heatLoss[oCurrent.x_pos][oCurrent.y_pos-1] + 
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos-2] +
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos-3] +
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos-4]) - 4*'0';
                oNext.eDir = LEFT;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
        }
        /* If the current direction is left */
        else if (oCurrent.eDir == LEFT)
        {
            /* Check if it can continue moving left */
            if (oCurrent.nSteps < 10 && oCurrent.y_pos > 0)
            {
                /* If it can, then continue moving and accumulating cost */
                oNext.nSteps = oCurrent.nSteps + 1;
                oNext.y_pos = oCurrent.y_pos - 1;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = oCurrent.eDir;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move down by at least 4 blocks */
            if (oCurrent.x_pos < nEndX-4)
            {
                /* If it can, set the number of steps to 4, modify the direction,
                 * co-ordinates, and cost.
                 * Add all the four steps' cost into the final cost */
                oNext.nSteps = 4;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos + 4;
                oNext.nCost = oCurrent.nCost + 
                              (heatLoss[oCurrent.x_pos+1][oCurrent.y_pos] + 
                              heatLoss[oCurrent.x_pos+2][oCurrent.y_pos] +
                              heatLoss[oCurrent.x_pos+3][oCurrent.y_pos] +
                              heatLoss[oCurrent.x_pos+4][oCurrent.y_pos]) - 4*'0';
                oNext.eDir = DOWN;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move up by at least 4 blocks */
            if (oCurrent.x_pos > 3)
            {
                /* If it can, set the number of steps to 4, modify the direction,
                 * co-ordinates, and cost.
                 * Add all the four steps' cost into the final cost */
                oNext.nSteps = 4;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos - 4;
                oNext.nCost = oCurrent.nCost + 
                              (heatLoss[oCurrent.x_pos-1][oCurrent.y_pos] + 
                              heatLoss[oCurrent.x_pos-2][oCurrent.y_pos] +
                              heatLoss[oCurrent.x_pos-3][oCurrent.y_pos] +
                              heatLoss[oCurrent.x_pos-4][oCurrent.y_pos]) - 4*'0';
                oNext.eDir = UP;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
        }
        /* If the current direction is up */
        else if (oCurrent.eDir == UP)
        {
            /* Check if it can continue moving up */
            if (oCurrent.nSteps < 10 && oCurrent.x_pos > 0)
            {
                /* If it can, then continue moving and accumulating cost */
                oNext.nSteps = oCurrent.nSteps + 1;
                oNext.y_pos = oCurrent.y_pos;
                oNext.x_pos = oCurrent.x_pos - 1;
                oNext.nCost = oCurrent.nCost + heatLoss[oNext.x_pos][oNext.y_pos] - '0';
                oNext.eDir = oCurrent.eDir;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move right by at least 4 blocks */
            if (oCurrent.y_pos < nEndY-4)
            {
                /* If it can, set the number of steps to 4, modify the direction,
                 * co-ordinates, and cost.
                 * Add all the four steps' cost into the final cost */
                oNext.nSteps = 4;
                oNext.y_pos = oCurrent.y_pos + 4;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + 
                              (heatLoss[oCurrent.x_pos][oCurrent.y_pos+1] + 
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos+2] +
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos+3] +
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos+4]) - 4*'0';
                oNext.eDir = RIGHT;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
            /* Check if can move left by at least 4 blocks */
            if (oCurrent.y_pos > 3)
            {
                /* If it can, set the number of steps to 4, modify the direction,
                 * co-ordinates, and cost.
                 * Add all the four steps' cost into the final cost */
                oNext.nSteps = 4;
                oNext.y_pos = oCurrent.y_pos - 4;
                oNext.x_pos = oCurrent.x_pos;
                oNext.nCost = oCurrent.nCost + 
                              (heatLoss[oCurrent.x_pos][oCurrent.y_pos-1] + 
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos-2] +
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos-3] +
                              heatLoss[oCurrent.x_pos][oCurrent.y_pos-4]) - 4*'0';
                oNext.eDir = LEFT;

                /* Finally, place the structure into the priority queue */
                not_processed.push(oNext);
            }
        }
        else
        {
            cout << "Wrong direction " << oCurrent.eDir << endl;
            break;
        }
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

