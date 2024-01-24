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

/* A structure to store a given module's connections to all modules */
struct ConnectionsTo
{
    /* Name of the given module (string) */
    string sModuleName;
    /* Names of all modules connected to given module (vec of strings) */
    vector<string> vsConnections;
};

/* A structure to store all modules' connections to a given module */
struct ConnectionsFrom
{
    /* Name of the given module (string) */
    string sModuleName;
    /* Names of all modules connected from the given module (vec of strings) */
    vector<string> vsConnections;
    /* Value of the corresponding module from the given module (vec of int) */
    vector<int64_t> vnValue;
};

/* List of modules to be processed (in a queue) */
list<string> lsProcessString;
/* List of modules' corresponding values to be processed (in same queue) */
list<int64_t> lnProcessState;


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

    /* Connections from flip-flops module to other modules (flip or conj) */
    vector<ConnectionsTo> voFlipFlops;
    /* Connections from conjuctions module to other modules (flip or conj) */
    vector<ConnectionsTo> voConjuctions;
    /* Connections from broadcaster module to other modules (flip or conj) */
    ConnectionsTo oBroadcaster;

    /* Connections of all modules to a given module 
     * This for all modules.
    */
    vector<ConnectionsFrom> voConnectFrom;

    /* State of all modules:
     * 0 - broadcaster 
     * 1 - flip-flop (%) 
     * 2 - conjunction (&) 
    */
    unordered_map<string, int64_t> asStateType;

    /* Value stored by the module - mainly for flip-flops
     * 0 for off or 1 for on
     */
    unordered_map<string, int64_t> asStateValues;

    /* Count of the total number of low pulses sent */
    int64_t nLowCount = 0;
    /* Count of the total number of high pulses sent */
    int64_t nHighCount = 0;

    /* Total number of button presses */
    int64_t nTimes = 0;

    /* Module connected to the module named 'rx' (part 2) */
    string sModuleToRx;
    /* Modules connected to the module, that is connected to module name 'rx' */
    int64_t nModulesToModuleToRx[50] = { 0 };

    /* Loop running */
    bool bRunning = true;

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Read the line */
        stringstream iss(arr[cnt1]);
        string word;

        /* Temporary connection to object */
        ConnectionsTo oOneConnectTo;

        /* Read the first word */
        iss >> word;
        /* Assume it is broadcaster */
        cnt2 = 2;

        /* If the word is broadcaster, store the value of state type to zero
         * for broadcaster, and store its state value to be zero */
        if (word == "broadcaster")
        {
            asStateValues["broadcaster"] = 0;
            asStateType["broadcaster"] = 0;
        }
        /* If the module is a flip-flop, store the type to be one 
         * Store the module name and value of the state to zero */
        else if (word[0] == '%')
        {
            word.erase(0, 1);
            oOneConnectTo.sModuleName = word;
            asStateValues[word] = 0;
            asStateType[word] = 1;
            /* Set local variable to 1 to indicate flip-flip */
            cnt2 = 1;
        }
        /* If the module is a conjunction, store the type to be two 
         * Store the module name and value of the state to zero */
        else if (word[0] == '&')
        {
            word.erase(0, 1);
            oOneConnectTo.sModuleName = (word);
            asStateValues[word] = 0;
            asStateType[word] = 2;
            /* Set local variable to 0 to indicate conjunction */
            cnt2 = 0;
        }
        else
        {
            /* If not the three, display error and exit */
            cout << "Error" << endl;
            return 0;
        }

        /* Read the next word, "->" and ignore */
        iss >> word;

        /* Read the connected words */
        while (iss >> word)
        {
            if (word[word.size()-1] == ',')
            {
                word.pop_back();
            }
            /* Store the connection of the module */
            oOneConnectTo.vsConnections.push_back(word);
        }

        /* If conjunction, store it in conjunctions */
        if (cnt2 == 0)
        {
            voConjuctions.push_back(oOneConnectTo);
        }
        /* If flip-flop, store it in flip-flops */
        else if (cnt2 == 1)
        {
            voFlipFlops.push_back(oOneConnectTo);
        }
        /* Else store it in broadcaster */
        else
        {
            oBroadcaster = oOneConnectTo;
        }

        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Create the connections from vector of objects */

    /* First for broadcaster connected nodes */
    for (cnt2 = 0; cnt2 < oBroadcaster.vsConnections.size(); cnt2++)
    {
        /* Loop through all the existing connection from */
        for (cnt3 = 0; cnt3 < voConnectFrom.size(); cnt3++)
        {
            /* If the module is present already */
            if (voConnectFrom[cnt3].sModuleName == oBroadcaster.vsConnections[cnt2])
            {
                /* Add broadcaster to it as broadcaster is connected to the module */
                voConnectFrom[cnt3].vsConnections.push_back("broadcaster");
                break;
            }
        }
        /* If not already present */
        if (cnt3 == voConnectFrom.size())
        {
            ConnectionsFrom oOneConnectFrom;
            /* Create one object, connect from and add broadcaster and
             * name of the module with one connected to broadcaster */
            oOneConnectFrom.sModuleName = oBroadcaster.vsConnections[cnt2];
            oOneConnectFrom.vsConnections.push_back("broadcaster");
            oOneConnectFrom.vnValue.push_back(0);
            voConnectFrom.push_back(oOneConnectFrom);
        }
    }

    /* Next for all flip-flops, loop through all flip-flops */
    for (cnt2 = 0; cnt2 < voFlipFlops.size(); cnt2++)
    {
        /* For a given flip-flip, loop through all its connections */
        for (cnt3 = 0; cnt3 < voFlipFlops[cnt2].vsConnections.size(); cnt3++)
        {
            /* Check if that flip-flop's connection is already in connect from */
            for (cnt4 = 0; cnt4 < voConnectFrom.size(); cnt4++)
            {
                /* If already present, add the flip-flop module to it */
                if (voConnectFrom[cnt4].sModuleName == voFlipFlops[cnt2].vsConnections[cnt3])
                {
                    voConnectFrom[cnt4].vsConnections.push_back(voFlipFlops[cnt2].sModuleName);
                    voConnectFrom[cnt4].vnValue.push_back(0);
                    break;
                }
            }
            /* If not already present, create a new connection with connectTo 
             * name as flip-flop's connection and connectTo connection as flip-
             * flop's name */
            if (cnt4 == voConnectFrom.size())
            {
                ConnectionsFrom oOneConnectFrom;

                oOneConnectFrom.sModuleName = voFlipFlops[cnt2].vsConnections[cnt3];
                oOneConnectFrom.vsConnections.push_back(voFlipFlops[cnt2].sModuleName);
                oOneConnectFrom.vnValue.push_back(0);

                voConnectFrom.push_back(oOneConnectFrom);
            }
        }
    }

    /* Next for all flip-flops, loop through all conjuctions */
    for (cnt2 = 0; cnt2 < voConjuctions.size(); cnt2++)
    {
        /* For a given conjuction, loop through all its connections */
        for (cnt3 = 0; cnt3 < voConjuctions[cnt2].vsConnections.size(); cnt3++)
        {
            /* Check if that conjuction's connection is already in connect from */
            for (cnt4 = 0; cnt4 < voConnectFrom.size(); cnt4++)
            {
                /* If already present, add the conjunction module to it */
                if (voConnectFrom[cnt4].sModuleName == voConjuctions[cnt2].vsConnections[cnt3])
                {
                    voConnectFrom[cnt4].vsConnections.push_back(voConjuctions[cnt2].sModuleName);
                    voConnectFrom[cnt4].vnValue.push_back(0);
                    break;
                }
            }
            /* If not already present, create a new connection with connectTo 
             * name as conjunction's connection and connectTo connection as
             * conjunction's name */
            if (cnt4 == voConnectFrom.size())
            {
                ConnectionsFrom oOneConnectFrom;

                oOneConnectFrom.sModuleName = voConjuctions[cnt2].vsConnections[cnt3];
                oOneConnectFrom.vsConnections.push_back(voConjuctions[cnt2].sModuleName);
                oOneConnectFrom.vnValue.push_back(0);

                voConnectFrom.push_back(oOneConnectFrom);
            }
        }
    }

    /* Get the input to rx, assumed to be only one. If more than one, re-look
     * at this logic:  
    */
    for (cnt2 = 0; cnt2 < voConnectFrom.size(); cnt2++)
    {
        if (voConnectFrom[cnt2].sModuleName == "rx")
        {
            if (voConnectFrom[cnt2].vsConnections.size() == 1)
            {
                /* Store the module connected to "rx" in module to rx string */
                sModuleToRx = voConnectFrom[cnt2].vsConnections[0];
                break;
            }
            else if (voConnectFrom[cnt2].vsConnections.size() > 1)
            {
                cout << "Cannot compute part 2. Re-look at the logic." << endl;
                return 0;
            }
        }
    }

    /* Reset button pressed times to zero */
    nTimes = 0;
    bRunning = true;

    /* If still running */
    while (bRunning == true)
    {
        /* If the current button pressed is 1000, compute part 1 answer */
        if (nTimes == 1000)
        {
            /* Part 1 sum = low-pulses * high-pulses */
            nPartOneSum = nLowCount*nHighCount;
        }

        /* Increment button pressed times */
        nTimes++;

        /* Increment low count once for broadcaster */
        ++nLowCount;

        /* Send low to all modules connected to broadcaster */
        for (cnt3 = 0; cnt3 < oBroadcaster.vsConnections.size(); cnt3++)
        {
            /* Store module name in queue and its state as zero */
            lsProcessString.push_back(oBroadcaster.vsConnections[cnt3]);
            lnProcessState.push_back(0);
            /* Increment the number of low count */
            ++nLowCount;
        }

        /* If the queue is not empty */
        while (lsProcessString.size() > 0)
        {
            /* If flip-flop, proceed only if zero */
            if (asStateType[lsProcessString.front()] == 1 && lnProcessState.front() == 0)
            {
                /* If the state of the flip-flop was zero, flip to one */
                if (asStateValues[lsProcessString.front()] == 0)
                {
                    asStateValues[lsProcessString.front()] = 1;
                    /* Loop through all the flip-flops and find the flipped 
                     * flip-flop */
                    for (cnt2 = 0; cnt2 < voFlipFlops.size(); cnt2++)
                    {
                        /* After finding: */
                        if (voFlipFlops[cnt2].sModuleName == lsProcessString.front())
                        {
                            /* Loop through all the connections of that flip-flop */
                            for (cnt3 = 0; cnt3 < voFlipFlops[cnt2].vsConnections.size(); cnt3++)
                            {
                                /* Add those connections with state value to the 
                                 * queue */
                                lsProcessString.push_back(voFlipFlops[cnt2].vsConnections[cnt3]);
                                lnProcessState.push_back(1);
                                /* Increment the number of high pulses */
                                ++nHighCount;
                                /* Now, if the connection were to be a conjunction: */
                                if (asStateType[voFlipFlops[cnt2].vsConnections[cnt3]] == 2)
                                {
                                    /* Store the state of the value into all those
                                     * modules connected from that conjunction 
                                     * 
                                     * This is required as the conjunction must
                                     * remember the last pulse sent to it.
                                     */
                                    /* Loop through all the connect from */
                                    for (cnt4 = 0; cnt4 < voConnectFrom.size(); cnt4++)
                                    {
                                        /* If the connect from name is flip-flop's
                                         * connection */
                                        if (voConnectFrom[cnt4].sModuleName == voFlipFlops[cnt2].vsConnections[cnt3])
                                        {
                                            /* Modify the value of the current flip-flop
                                             * name to 1 */
                                            for (cnt5 = 0; cnt5 < voConnectFrom[cnt4].vsConnections.size(); cnt5++)
                                            {
                                                if (voConnectFrom[cnt4].vsConnections[cnt5] == lsProcessString.front())
                                                {
                                                    voConnectFrom[cnt4].vnValue[cnt5] = 1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                /* If the state of the flip-flop was one, flip to zero */
                else
                {
                    asStateValues[lsProcessString.front()] = 0;
                    /* Loop through all the flip-flops and find the flipped 
                     * flip-flop */
                    for (cnt2 = 0; cnt2 < voFlipFlops.size(); cnt2++)
                    {
                        /* After finding: */
                        if (voFlipFlops[cnt2].sModuleName == lsProcessString.front())
                        {
                            /* Loop through all the connections of that flip-flop */
                            for (cnt3 = 0; cnt3 < voFlipFlops[cnt2].vsConnections.size(); cnt3++)
                            {
                                /* Add those connections with state value to the 
                                 * queue */
                                lsProcessString.push_back(voFlipFlops[cnt2].vsConnections[cnt3]);
                                lnProcessState.push_back(0);
                                /* Increment the number of low pulses */
                                ++nLowCount;

                                /* Now, if the connection were to be a conjunction: */
                                if (asStateType[voFlipFlops[cnt2].vsConnections[cnt3]] == 2)
                                {
                                    /* Store the state of the value into all those
                                     * modules connected from that conjunction 
                                     * 
                                     * This is required as the conjunction must
                                     * remember the last pulse sent to it.
                                     */
                                    /* Loop through all the connect from */
                                    for (cnt4 = 0; cnt4 < voConnectFrom.size(); cnt4++)
                                    {
                                        /* If the connect from name is flip-flop's
                                         * connection */
                                        if (voConnectFrom[cnt4].sModuleName == voFlipFlops[cnt2].vsConnections[cnt3])
                                        {
                                            /* Modify the value of the current flip-flop
                                             * name to zero */
                                            for (cnt5 = 0; cnt5 < voConnectFrom[cnt4].vsConnections.size(); cnt5++)
                                            {
                                                if (voConnectFrom[cnt4].vsConnections[cnt5] == lsProcessString.front())
                                                {
                                                    voConnectFrom[cnt4].vnValue[cnt5] = 0;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                /* Remove the module from the queue */
                lsProcessString.pop_front();
                lnProcessState.pop_front();
            }
            /* Flip-flop with one as state, just remove it */
            else if (asStateType[lsProcessString.front()] == 1 && lnProcessState.front() == 1)
            {
                lsProcessString.pop_front();
                lnProcessState.pop_front();
            }
            /* Conjunction */
            else
            {
                /* Loop through all the connect from and find the current 
                 * conjunction */
                for (cnt2 = 0; cnt2 < voConnectFrom.size(); cnt2++)
                {
                    /* After finding the conjunction: */
                    if (voConnectFrom[cnt2].sModuleName == lsProcessString.front())
                    {
                        /* For part 2: if the module to rx is the current 
                         * conjunction: */
                        if (lsProcessString.front() == sModuleToRx)
                        {
                            /* Loop through all the connect from */
                            for (cnt3 = 0; cnt3 < voConnectFrom[cnt2].vsConnections.size(); cnt3++)
                            {
                                /* Check if the current value to it is one */
                                if (voConnectFrom[cnt2].vnValue[cnt3] != 0)
                                {
                                    /* If not already processed */
                                    if (nModulesToModuleToRx[cnt3] == 0)
                                    {
                                        /* Process it by storing the number of 
                                         * times the button was pressed */
                                        nModulesToModuleToRx[cnt3] = nTimes;
                                    }
                                }
                            }

                            /* Loop through all the connect from to check if 
                             * all are processed */
                            for (cnt3 = 0; cnt3 < voConnectFrom[cnt2].vsConnections.size(); cnt3++)
                            {
                                /* If one is not processed, break */
                                if (nModulesToModuleToRx[cnt3] == 0)
                                {
                                    break;
                                }
                            }

                            /* If all are processed */
                            if (cnt3 == voConnectFrom[cnt2].vsConnections.size())
                            {
                                /* Part two answer is the LCM of all the button
                                 * presses stored */
                                nPartTwoSum = nModulesToModuleToRx[0];
                                for (cnt4 = 1; cnt4 < voConnectFrom[cnt2].vsConnections.size(); cnt4++)
                                {
                                    nPartTwoSum = lcm(nPartTwoSum, nModulesToModuleToRx[cnt4]);
                                }
                                /* Stop running the while loop and break */
                                bRunning = false;
                                break;
                            }
                        }

                        /* Check if all connections to that conjunction is one */
                        for (cnt3 = 0; cnt3 < voConnectFrom[cnt2].vsConnections.size(); cnt3++)
                        {
                            /* If, just one connection is a zero, stop by breaking */
                            if (voConnectFrom[cnt2].vnValue[cnt3] == 0)
                            {
                                break;
                            }
                        }
                        /* If all are one, then the current value of the state
                         * is zero */
                        if (cnt3 == voConnectFrom[cnt2].vsConnections.size())
                        {
                            /* Store the state value to be zero */
                            asStateValues[lsProcessString.front()] = 0;

                            /* Loop through all conjunctions and find the current 
                             * conjunction */
                            for (cnt4 = 0; cnt4 < voConjuctions.size(); cnt4++)
                            {
                                /* After finding the current conjunction: */
                                if (voConjuctions[cnt4].sModuleName == lsProcessString.front())
                                {
                                    /* Loop through all its connections */
                                    for (cnt5 = 0; cnt5 < voConjuctions[cnt4].vsConnections.size(); cnt5++)
                                    {
                                        /* Add those connections with state value to the 
                                         * queue */
                                        lsProcessString.push_back(voConjuctions[cnt4].vsConnections[cnt5]);
                                        lnProcessState.push_back(0);
                                        /* Increment the number of low pulses */
                                        ++nLowCount;
                                        /* Now, if the connection were to be a conjunction: */
                                        if (asStateType[voConjuctions[cnt4].vsConnections[cnt5]] == 2)
                                        {
                                            /* Store the state of the value into all those
                                             * modules connected from that conjunction 
                                             * 
                                             * This is required as the conjunction must
                                             * remember the last pulse sent to it.
                                             */
                                            /* Loop through all the connect from */
                                            for (cnt6 = 0; cnt6 < voConnectFrom.size(); cnt6++)
                                            {
                                                /* If the connect from name is conjunction's
                                                 * connection */
                                                if (voConnectFrom[cnt6].sModuleName == voConjuctions[cnt4].vsConnections[cnt5])
                                                {
                                                    /* Modify the value of the current conjunction
                                                     * name to zero */
                                                    for (cnt7 = 0; cnt7 < voConnectFrom[cnt6].vsConnections.size(); cnt7++)
                                                    {
                                                        if (voConnectFrom[cnt6].vsConnections[cnt7] == lsProcessString.front())
                                                        {
                                                            voConnectFrom[cnt6].vnValue[cnt7] = 0;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        /* Else, if at least one is zero, then the current value 
                         * of the state is one */
                        else
                        {
                            /* Store the state value to be zero */
                            asStateValues[lsProcessString.front()] = 1;

                            /* Loop through all conjunctions and find the current 
                             * conjunction */
                            for (cnt4 = 0; cnt4 < voConjuctions.size(); cnt4++)
                            {
                                /* After finding the current conjunction: */
                                if (voConjuctions[cnt4].sModuleName == lsProcessString.front())
                                {
                                    /* Loop through all its connections */
                                    for (cnt5 = 0; cnt5 < voConjuctions[cnt4].vsConnections.size(); cnt5++)
                                    {
                                        /* Add those connections with state value to the 
                                         * queue */
                                        lsProcessString.push_back(voConjuctions[cnt4].vsConnections[cnt5]);
                                        lnProcessState.push_back(1);
                                        /* Increment the number of high pulses */
                                        ++nHighCount;
                                        /* Now, if the connection were to be a conjunction: */
                                        if (asStateType[voConjuctions[cnt4].vsConnections[cnt5]] == 2)
                                        {
                                            /* Store the state of the value into all those
                                             * modules connected from that conjunction 
                                             * 
                                             * This is required as the conjunction must
                                             * remember the last pulse sent to it.
                                             */
                                            /* Loop through all the connect from */
                                            for (cnt6 = 0; cnt6 < voConnectFrom.size(); cnt6++)
                                            {
                                                /* If the connect from name is conjunction's
                                                 * connection */
                                                if (voConnectFrom[cnt6].sModuleName == voConjuctions[cnt4].vsConnections[cnt5])
                                                {
                                                    /* Modify the value of the current conjunction
                                                     * name to one */
                                                    for (cnt7 = 0; cnt7 < voConnectFrom[cnt6].vsConnections.size(); cnt7++)
                                                    {
                                                        if (voConnectFrom[cnt6].vsConnections[cnt7] == lsProcessString.front())
                                                        {
                                                            voConnectFrom[cnt6].vnValue[cnt7] = 1;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                /* Remove the module from the queue */
                lsProcessString.pop_front();
                lnProcessState.pop_front();
            }

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

