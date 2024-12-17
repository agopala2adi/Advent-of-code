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

/**
 * @brief Executes a series of instructions on given registers and returns a vector of results.
 * 
 * This function processes a vector of instructions and performs operations on three registers (A, B, and C).
 * The instructions are processed sequentially, and the function supports various opcodes to manipulate the registers.
 * 
 * @param nInstructions A vector of int64_t containing the instructions to be executed.
 * @param nRegisterA Initial value of register A.
 * @param nRegisterB Initial value of register B.
 * @param nRegisterC Initial value of register C.
 * @return A vector of int64_t containing the results of specific instructions.
 * 
 * The supported opcodes and their operations are:
 * - Opcode 0: Divide register A by 2 raised to the power of the operand.
 * - Opcode 1: XOR register B with the operand.
 * - Opcode 2: Set register B to the operand modulo 8.
 * - Opcode 3: Jump to the instruction at the operand index if register A is not zero.
 * - Opcode 4: XOR register B with register C.
 * - Opcode 5: Push the operand modulo 8 to the result vector.
 * - Opcode 6: Set register B to register A divided by 2 raised to the power of the operand.
 * - Opcode 7: Set register C to register A divided by 2 raised to the power of the operand.
 * 
 * If an invalid instruction is encountered, the function prints "Invalid" and returns the results collected so far.
 */
vector<int64_t> RunInstructions(vector<int64_t> &nInstructions, int64_t nRegisterA, int64_t nRegisterB, int64_t nRegisterC)
{
    int64_t cnt1 = 0;
    vector <int64_t> nRetVect; 

    /* For all instructions */
    for (cnt1 = 0; cnt1 < nInstructions.size(); cnt1++)
    {
        /* If the opcode 0 */
        if (nInstructions[cnt1] == 0)
        {
            /* If the operand is less than 4, take immediate value */
            if (nInstructions[cnt1+1] <= 3)
            {
                /* Update is as registerA = registerA / (2 ^ operand)*/
                nRegisterA /= (1 << nInstructions[cnt1+1]);
            }
            else if (nInstructions[cnt1+1] == 4)
            {
                /* Update is as registerA = registerA / (2 ^ registerA)*/
                nRegisterA /= (1 << nRegisterA);
            }
            else if (nInstructions[cnt1+1] == 5)
            {
                /* Update is as registerA = registerA / (2 ^ nRegisterB)*/
                nRegisterA /= (1 << nRegisterB);
            }
            else if (nInstructions[cnt1+1] == 6)
            {
                /* Update is as registerA = registerA / (2 ^ nRegisterC)*/
                nRegisterA /= (1 << nRegisterC);
            }
            else
            {
                /* Invalid instruction */
                cout << "Invalid" << endl;
                return nRetVect;
            }
            cnt1++;
        }
        /* If the opcode 1 */
        else if (nInstructions[cnt1] == 1)
        {
            /* Update it as registerB = registerB XOR operand */
            nRegisterB ^= (nInstructions[cnt1+1]);
            cnt1++;
        }
        /* If the opcode 2 */
        else if (nInstructions[cnt1] == 2)
        {
            /* If the operand is less than 4, take immediate value */
            if (nInstructions[cnt1+1] <= 3)
            {
                /* Update it as registerB = operand % 8 */
                nRegisterB = (nInstructions[cnt1+1]) % 8;
            }
            else if (nInstructions[cnt1+1] == 4)
            {
                /* Update it as registerB = registerA % 8 */
                nRegisterB = (nRegisterA) % 8;
            }
            else if (nInstructions[cnt1+1] == 5)
            {
                /* Update it as registerB = registerB % 8 */
                nRegisterB = (nRegisterB) % 8;
            }
            else if (nInstructions[cnt1+1] == 6)
            {
                /* Update it as registerB = registerC % 8 */
                nRegisterB = (nRegisterC) % 8;
            }
            else
            {
                /* Invalid instruction */
                cout << "Invalid" << endl;
                return nRetVect;
            }
            cnt1++;
        }
        /* If the opcode 3 */
        else if (nInstructions[cnt1] == 3)
        {
            /* If registerA is not zero, then jump to the instruction */
            if (nRegisterA != 0)
            {
                cnt1 = nInstructions[cnt1+1]-1;
                continue;
            }
            cnt1++;
        }
        /* If the opcode 4 */
        else if (nInstructions[cnt1] == 4)
        {
            /* Update it as registerB = registerB XOR registerC */
            nRegisterB ^= nRegisterC;
            cnt1++;
        }
        /* If the opcode 5 */
        else if (nInstructions[cnt1] == 5)
        {
            /* If the operand is less than 4, take immediate value */
            if (nInstructions[cnt1+1] <= 3)
            {
                nRetVect.push_back((nInstructions[cnt1+1]) % 8);
            }
            else if (nInstructions[cnt1+1] == 4)
            {
                nRetVect.push_back((nRegisterA) % 8);
            }
            else if (nInstructions[cnt1+1] == 5)
            {
                nRetVect.push_back((nRegisterB) % 8);
            }
            else if (nInstructions[cnt1+1] == 6)
            {
                nRetVect.push_back((nRegisterC) % 8);
            }
            else
            {
                /* Invalid instruction */
                cout << "Invalid" << endl;
                return nRetVect;
            }
            cnt1++;
        }
        /* If the opcode 6 */
        else if (nInstructions[cnt1] == 6)
        {
            /* If the operand is less than 4, take immediate value */
            if (nInstructions[cnt1+1] <= 3)
            {
                /* Update it as registerB = registerA / (2 ^ operand) */
                nRegisterB = nRegisterA/(1 << nInstructions[cnt1+1]);
            }
            else if (nInstructions[cnt1+1] == 4)
            {
                /* Update it as registerB = registerA / (2 ^ registerA) */
                nRegisterB = nRegisterA/(1 << nRegisterA);
            }
            else if (nInstructions[cnt1+1] == 5)
            {
                /* Update it as registerB = registerA / (2 ^ registerB) */
                nRegisterB = nRegisterA/(1 << nRegisterB);
            }
            else if (nInstructions[cnt1+1] == 6)
            {
                /* Update it as registerB = registerA / (2 ^ registerC) */
                nRegisterB = nRegisterA/(1 << nRegisterC);
            }
            else
            {
                /* Invalid instruction */
                cout << "Invalid" << endl;
                return nRetVect;
            }
            cnt1++;
        }
        /* If the opcode 7 */
        else if (nInstructions[cnt1] == 7)
        {
            /* If the operand is less than 4, take immediate value */
            if (nInstructions[cnt1+1] <= 3)
            {
                /* Update it as registerC = registerA / (2 ^ operand) */
                nRegisterC = nRegisterA/(1 << nInstructions[cnt1+1]);
            }
            else if (nInstructions[cnt1+1] == 4)
            {
                /* Update it as registerC = registerA / (2 ^ registerA) */
                nRegisterC = nRegisterA/(1 << nRegisterA);
            }
            else if (nInstructions[cnt1+1] == 5)
            {
                /* Update it as registerC = registerA / (2 ^ registerB) */
                nRegisterC = nRegisterA/(1 << nRegisterB);
            }
            else if (nInstructions[cnt1+1] == 6)
            {
                /* Update it as registerC = registerA / (2 ^ registerC) */
                nRegisterC = nRegisterA/(1 << nRegisterC);
            }
            else
            {
                /* Invalid instruction */
                cout << "Invalid" << endl;
                return nRetVect;
            }
            cnt1++;
        }
    }

    return nRetVect;

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

    string nFirstPart = "";
    int64_t nSecondPart = 0;

    int64_t nRegisterA;
    int64_t nRegisterB;
    int64_t nRegisterBCopy;
    int64_t nRegisterC;
    int64_t nRegisterCCopy;

    vector<int64_t> nInstructions;


    /* Read each line */
    while (fgets(arr, sizeof(arr), fp) != NULL)
    {
        stringstream iss(arr);

        string sWord;

        /* Read the first input word */
        iss >> sWord;

        /* If the first input word is a register, then store the value into the
         * corresponding register */
        if (sWord == "Register")
        {
            iss >> sWord;
            if (sWord == "A:")
            {
                iss >> sWord;
                nRegisterA = stoll(sWord);
            }
            else if (sWord == "B:")
            {
                iss >> sWord;
                nRegisterB = stoll(sWord);
                nRegisterBCopy = nRegisterB;
            }
            else if (sWord == "C:")
            {
                iss >> sWord;
                nRegisterC = stoll(sWord);
                nRegisterCCopy = nRegisterC;
            }
        }
        /* If the first word is a program, the store the next numbers in instruction */
        else if (sWord == "Program:")
        {
            iss >> sWord;

            /* Replace all commas with space to split by space */
            for (int i = 0; i < sWord.size(); i++)
            {
                if (sWord[i] == ',')
                {
                    sWord[i] = ' ';
                }
            }
            stringstream iss2(sWord);
            string sInstrs;
            while (iss2 >> sInstrs)
            {
                nInstructions.push_back(stoll(sInstrs));
            }
        }
        /* Increment count */
        ++cnt1;
    }

    /* Part (a) */

    vector <int64_t> vPart1Soln = RunInstructions(nInstructions, nRegisterA, nRegisterB, nRegisterC);

    for (cnt1 = 0; cnt1 < vPart1Soln.size(); cnt1++)
    {
        nFirstPart += to_string(vPart1Soln[cnt1]) + ",";
    }

    /* Remove the ending comma if present */
    if (nFirstPart[nFirstPart.size()-1] == ',')
    {
        nFirstPart.pop_back();
    }

    /* Display part a answer */
    cout << "Part (a): " << nFirstPart << endl;

    /* Make a list of all possible solutions */
    list<int64_t> nSolutionList;

    /* Insert a zero to begin with */
    nSolutionList.push_back(0);
    
    /* Build one number at a time from the end and do it until building all numbers
     * in the instruction */
    for (cnt1 = 0; cnt1 < nInstructions.size(); cnt1++)
    {
        /* Create a list of possible solution locally for verification */
        list<int64_t> nSolnListLocal;
        /* Run a loop for 8 times, for the current number as the number cannot 
         * exceed 8 */
        for (cnt2 = 0; cnt2 < 8; cnt2++)
        {
            /* For all solution check if it can meet the next test criteria */
            for (auto it = nSolutionList.begin(); it != nSolutionList.end(); it++)
            {
                /* At each step build a number that is 8 times previous + a test */
                int64_t nCurrSolnTest = ((*it) << 3) + cnt2;

                /* Check the local outputs */
                vector<int64_t> nLocalOuts = RunInstructions(nInstructions, nCurrSolnTest, 0, 0);
                /* Consider the outputs than have at least that many numbers as we want to check
                 * in the current iteration */
                if (nLocalOuts.size() > cnt1)
                {
                    /* Verify if the outputs are correctly matching all the 
                     * instructions from the end */
                    for (cnt3 = 0; cnt3 < nLocalOuts.size(); cnt3++)
                    {
                        if (nInstructions[nInstructions.size()-nLocalOuts.size()+cnt3] != nLocalOuts[cnt3])
                        {
                            break;
                        }
                    }
                    /* If it does, add it into the list */
                    if (nLocalOuts.size() == cnt3)
                    {
                        nSolnListLocal.push_back(nCurrSolnTest);
                    }
                }
            }
        }
        /* Make a global solution list equal to local for the next iteration */
        nSolutionList = nSolnListLocal;
    }

    /* Find the min value of all the lists */
    nSecondPart = *(nSolutionList.begin());

    for (auto it = nSolutionList.begin(); it != nSolutionList.end(); it++)
    {
        nSecondPart = min(nSecondPart, *it);
    }

    /* Close the file */
    fclose(fp);

    /* Display part b answer */
    cout << "Part (b): " << nSecondPart << endl;

    auto endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecs = endTime-startTime;
    std::time_t end_time = std::chrono::system_clock::to_time_t(endTime);
    cout << "\nEnd time: " << std::ctime(&end_time);
    cout << "Elapsed time: " << elapsedSecs.count() << " seconds\n";

    return 0;
}

