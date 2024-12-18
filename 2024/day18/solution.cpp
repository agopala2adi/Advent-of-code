#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;


char arr[10000];

int64_t nArrCost[1000][1000] = {0};

/* Direction enum - Right, Down, Left, Up */
enum DIRECTION
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};

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

        Node *parent;

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
unordered_map<string, int64_t> processed;

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
    // To printf uint -> printf("%llu ", fin);

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
    string nSecondPart;

    /* Max size of array */
    const int64_t nMaxSize = 71;

    /* Array to store the map */
    int8_t vsMap[nMaxSize][nMaxSize];

    /* List of bytes - coordinates*/
    vector<pair<int, int>> nBytesList;

    /* Read each line */
    while (feof(fp) == 0)
    {
        int64_t xPoint;
        int64_t yPoint;

        /* Read the coordinates of x and y */
        fscanf(fp, "%ld,%ld", &xPoint, &yPoint);

        /* Store into the vector */
        nBytesList.push_back(make_pair(xPoint, yPoint));

        /* Increment count */
        ++cnt1;
    }

    /* Start co-ordinates */
    int64_t nStartX = 0;
    int64_t nStartY = 0;

    /* End co-ordinates */
    int64_t nEndX = nMaxSize-1;
    int64_t nEndY = nMaxSize-1;

    /* Start the count with 1024 as we know that it would work from part (a) */
    for (cnt1 = 1024; cnt1 < nBytesList.size(); cnt1++)
    {
        /* Number of bytes to set is given by the current iteration number */
        int64_t nNumberOfBytes = cnt1+1;

        /* A flag to check if the maze comes out */
        bool bMazeWorked = false;
        /* To be processed data */
        not_processed = priority_queue<Node>();
        /* Processed data */
        processed = unordered_map<string, int64_t>();

        /* Start the direction with right and set all the costs to zero */
        oStart.eDir = RIGHT;
        oStart.nSteps = 0;
        oStart.x_pos = nStartX;
        oStart.y_pos = nStartY;
        oStart.nCost = 0;
        oStart.parent = nullptr;

        /* Store the current start to be processed */
        not_processed.push(oStart);

        /* Set all co-ordinates to dot to begin with */
        for (cnt2 = 0; cnt2 < nMaxSize; cnt2++)
        {
            for (cnt3 = 0; cnt3 < nMaxSize; cnt3++)
            {
                vsMap[cnt2][cnt3] = '.';
            }
        }

        /* Set the first n bytes as hashes */
        for (cnt2 = 0; cnt2 < nNumberOfBytes; cnt2++)
        {
            vsMap[nBytesList[cnt2].second][nBytesList[cnt2].first] = '#';
        }

        /* Until processing all locations */
        while (not_processed.size() > 0)
        {
            /* Get the top value in the priority queue with the least cost */
            oCurrent = not_processed.top();

            /* Remove that from the priority queue */
            not_processed.pop();

            /* Create a unique collection given by the direction, and position and 
            * check if this combination has already repeated 
            * If not add that into the unordered map (hash map)
            */
            string sCollection = to_string(oCurrent.eDir) + " " + to_string(oCurrent.x_pos) + " " + to_string(oCurrent.y_pos);

            if (processed.find(sCollection) != processed.end())
            {
                /* If that collection is already processed, ignore it and continue */
                continue;
            }
            else
            {
                /* Else, add it into processed */
                processed[sCollection] = 1;
            }

            /* If the dest. co-ordinate is reached, stop and store its cost */
            if (oCurrent.x_pos == nEndX && oCurrent.y_pos == nEndY)
            {
                /* If found the last destination node, store the cost into part (a) */
                if (cnt1 == 1024)
                {
                    nFirstPart = oCurrent.nCost;
                }
                bMazeWorked = true;

                break;
            }

            /* If the current direction is moving towards the right */
            if (oCurrent.eDir == RIGHT)
            {
                /* Check if it can move right */
                if (oCurrent.x_pos+1 < nMaxSize && vsMap[oCurrent.y_pos][oCurrent.x_pos+1] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos+1;
                    oNext.y_pos = oCurrent.y_pos;
                    oNext.eDir = RIGHT;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
                /* Check if it can move up */
                if (oCurrent.y_pos-1 >= 0 && vsMap[oCurrent.y_pos-1][oCurrent.x_pos] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos;
                    oNext.y_pos = oCurrent.y_pos-1;
                    oNext.eDir = UP;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
                /* Check if it can move down */
                if (oCurrent.y_pos+1 < nMaxSize && vsMap[oCurrent.y_pos+1][oCurrent.x_pos] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos;
                    oNext.y_pos = oCurrent.y_pos+1;
                    oNext.eDir = DOWN;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
            }
            /* If the current direction is moving towards the up */
            else if (oCurrent.eDir == UP)
            {
                /* Check if it can move right */
                if (oCurrent.x_pos+1 < nMaxSize && vsMap[oCurrent.y_pos][oCurrent.x_pos+1] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos+1;
                    oNext.y_pos = oCurrent.y_pos;
                    oNext.eDir = RIGHT;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
                /* Check if it can move up */
                if (oCurrent.y_pos-1 >= 0 && vsMap[oCurrent.y_pos-1][oCurrent.x_pos] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos;
                    oNext.y_pos = oCurrent.y_pos-1;
                    oNext.eDir = UP;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
                /* Check if it can move down */
                if (oCurrent.x_pos-1 >= 0 && vsMap[oCurrent.y_pos][oCurrent.x_pos-1] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos-1;
                    oNext.y_pos = oCurrent.y_pos;
                    oNext.eDir = LEFT;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }

            }
            /* If the current direction is moving towards down */
            else if (oCurrent.eDir == DOWN)
            {
                /* Check if it can move right */
                if (oCurrent.x_pos+1 < nMaxSize && vsMap[oCurrent.y_pos][oCurrent.x_pos+1] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos+1;
                    oNext.y_pos = oCurrent.y_pos;
                    oNext.eDir = RIGHT;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
                /* Check if it can move up */
                if (oCurrent.y_pos+1 < nMaxSize && vsMap[oCurrent.y_pos+1][oCurrent.x_pos] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos;
                    oNext.y_pos = oCurrent.y_pos+1;
                    oNext.eDir = DOWN;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
                /* Check if it can move down */
                if (oCurrent.x_pos-1 >= 0 && vsMap[oCurrent.y_pos][oCurrent.x_pos-1] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos-1;
                    oNext.y_pos = oCurrent.y_pos;
                    oNext.eDir = LEFT;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }


            }
            /* If the current direction is moving towards left */
            else if (oCurrent.eDir == LEFT)
            {
                /* Check if it can move right */
                if (oCurrent.y_pos+1 < nMaxSize && vsMap[oCurrent.y_pos+1][oCurrent.x_pos] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos;
                    oNext.y_pos = oCurrent.y_pos+1;
                    oNext.eDir = DOWN;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
                /* Check if it can move up */
                if (oCurrent.y_pos-1 >= 0 && vsMap[oCurrent.y_pos-1][oCurrent.x_pos] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos;
                    oNext.y_pos = oCurrent.y_pos-1;
                    oNext.eDir = UP;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }
                /* Check if it can move down */
                if (oCurrent.x_pos-1 >= 0 && vsMap[oCurrent.y_pos][oCurrent.x_pos-1] != '#')
                {
                    /* If yes, create another node with cost greater by 1 */
                    oNext.x_pos = oCurrent.x_pos-1;
                    oNext.y_pos = oCurrent.y_pos;
                    oNext.eDir = LEFT;
                    oNext.nCost = oCurrent.nCost+1;
                    oNext.parent = new Node(oCurrent);

                    /* Put it into the priority queue */
                    not_processed.push(oNext);
                }

            }
            else
            {
                cout << "Wrong direction " << oCurrent.eDir << endl;
                return -1;
            }
        }

        /* If the current maze does not work, stop there and store the co-ordinates */
        if (bMazeWorked == false)
        {
            nSecondPart = to_string(nBytesList[cnt1].first) + "," + to_string(nBytesList[cnt1].second);
            break;
        }
    }

    /* Close the file */
    fclose(fp);

    /* Display part a and b answers */
    cout << "Part (b): " << nFirstPart << endl;
    cout << "Part (b): " << nSecondPart << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

