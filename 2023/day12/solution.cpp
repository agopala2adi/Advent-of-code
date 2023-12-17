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

/* Create a hash map for not computing sequences already computed. There are a 
 * lot of them */
unordered_map<string, int64_t> hashMap;

/* Get the number of different combinations for a given string input. 
 * This is a recursive function */
int64_t getDifferentCombinations(string &inpWord, list<int64_t> &nNumber, char prevChar);

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

    /* Read each line from file */
    while (fgets(arr[cnt1], sizeof(arr[cnt1]), fp) != NULL)
    {
        /* Store the input numbers in springsize list */
        list<int64_t> nSpringSize;
        /* Same for part 2 */
        list<int64_t> nSpringSizePart2;
        cnt3 = 0;

        /* Read the row and store all springs (before space in input) */
        for (cnt2 = 0; cnt2 < strlen(arr[cnt1])-1; cnt2++)
        {
            /* If the input has comas, replace them with spaces, so that it 
             * would be easy to split into words */
            if (arr[cnt1][cnt2] == ',')
            {
                arr[cnt1][cnt2] = ' ';
            }
            /* If the input has a space set a flag to stop accumulating springs */
            else if (arr[cnt1][cnt2] == ' ')
            {
                cnt3 = 1;
            }
        }

        /* Split the input string, arr which contains  */
        stringstream iss(arr[cnt1]);

        /* Temporary word */
        string word = "";
        /* Input spring */
        string inpSprings = "";
        /* Input spring for part 2 */
        string inpSpringsPart2 = "";
        /* Input spring stored in reverse for the function */
        string inpSpringsRev = "";
        /* Same for part 2 */
        string inpSpringsPart2Rev = "";

        /* Extract the first word - which is the input springs */
        iss >> inpSprings;

        /* Subsequent extracts would be the input numbers for spring sizes */
        while (iss >> word)
        {
            /* Store them in the spring size list */
            nSpringSize.push_back(atoll(word.c_str()));
        }
        
        /* For part 2, create 5 times the same input spring size */
        for (cnt4 = 0; cnt4 < 5; cnt4++)
        {
            for (auto nNumb : nSpringSize)
            {
                nSpringSizePart2.push_back(nNumb);
            }
        }

        /* For part 2, duplicate the input springs 5 times with a "?" in between */
        inpSpringsPart2 = inpSprings + '?';
        inpSpringsPart2 += inpSprings + '?';
        inpSpringsPart2 += inpSprings + '?';
        inpSpringsPart2 += inpSprings + '?';
        inpSpringsPart2 += inpSprings;

        /* Reverse the part 1 springs */
        for (cnt2 = 0; cnt2 < inpSprings.size(); cnt2++)
        {
            inpSpringsRev.push_back(inpSprings[inpSprings.size()-1-cnt2]);
        }

        /* Get the count for different strings for part 1 */
        cnt5 = getDifferentCombinations(inpSpringsRev, nSpringSize, '.');
        /* Accumulate the sum in part 1 */
        nPartOneSum += cnt5;

        /* Reverse the part 2 springs */
        for (cnt2 = 0; cnt2 < inpSpringsPart2.size(); cnt2++)
        {
            inpSpringsPart2Rev.push_back(inpSpringsPart2[inpSpringsPart2.size()-1-cnt2]);
        }

        /* Get the count for different strings for part 2 */
        cnt5 = getDifferentCombinations(inpSpringsPart2Rev, nSpringSizePart2, '.');
        /* Accumulate the sum in part 1 */
        nPartTwoSum += cnt5;

        /* Increment count to move to next line */
        ++cnt1;
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

/* Get different combinations of input springs recursively.
 * inpWord  - Input springs stored in reverse - for easy pop_back and push_back
 * nNumber  - Input spring sizes list
 * prevChar - Previous character, either a # or a . */
int64_t getDifferentCombinations(string &inpWord, list<int64_t> &nNumber, char prevChar)
{
    /* Temporary counts for loops */
    int64_t cnt1 = 0;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;
    int64_t cnt4 = 0;

    /* Key for hash map */
    string sKey = inpWord;

    /* Get all numbers, spring sizes, convert to character (assuming each 
     * spring size is less than 128) and store into the key string */
    for (int64_t numb : nNumber)
    {
        sKey.push_back(numb);
    }
    /* Store the previous character into the string */
    sKey.push_back(prevChar);

    /* Get the first element of spring size - store into cnt4 */
    if (nNumber.size() > 0)
    {
        auto it = nNumber.begin();
        cnt4 = *it;
    }

    /* Check if this sequence is already there, if there, just return the 
     * value of the key */
    if (hashMap.find(sKey) != hashMap.end())
    {
        return hashMap[sKey];
    }

    /* If the input is a "?", replace it by "#" and then call the recursive
     * function again, then replace by "." and call the recursive function again
     */
    if (inpWord.size() > 0 && inpWord[inpWord.size()-1] == '?')
    {
        inpWord[inpWord.size()-1] = '#';
        cnt2 += getDifferentCombinations(inpWord, nNumber, prevChar);
        inpWord[inpWord.size()-1] = '.';
        cnt2 += getDifferentCombinations(inpWord, nNumber, prevChar);
        inpWord[inpWord.size()-1] = '?';
    }
    /* If the current input spring is zero size and if the input spring size
     * is either zero size of is value zero, add 1 to the sum as we have got
     * a perfect match. Also verify if the previous character is a # as we were
     * adding it earlier */
    else if ((inpWord.size() == 0 && nNumber.size() == 0) ||
             (inpWord.size() == 0 && nNumber.size() == 1 && cnt4 == 0 && prevChar == '#'))
    {
        cnt2 += 1;
    }
    /* If the current input spring size is zero size but the input spring 
     * is a dot, remove the dot and call the recursive function again */
    else if (inpWord.size() > 0 && nNumber.size() == 0 && prevChar == '.' && inpWord[inpWord.size()-1] == '.')
    {
        inpWord.pop_back();
        cnt2 += getDifferentCombinations(inpWord, nNumber, '.');
        inpWord.push_back('.');
    }
    /* If the input spring is zero size, but input spring size is not zero size
     * then return zero, because this was not a match */
    else if (inpWord.size() == 0)
    {
        cnt2 = 0;
    }
    /* If the previous character and current character are both dots (.), then
     * remove the dot and call the recursive function again */
    else if (prevChar == '.' && inpWord[inpWord.size()-1] == '.')
    {
        inpWord.pop_back();
        cnt2 += getDifferentCombinations(inpWord, nNumber, '.');
        inpWord.push_back('.');
    }
    /* If the current input spring is a #, then check if the input spring size
     * has become zero size or zero, if either of the conditions, return false
     * Else, decrement the input spring size and call the recursive function 
     * again */
    else if (inpWord[inpWord.size()-1] == '#')
    {
        inpWord.pop_back();
        if (nNumber.size() == 0)
        {
            cnt2 = 0;
        }
        else
        {
            auto it = nNumber.begin();
            if (*it > 0)
            {
                *it = *it - 1;
                cnt2 += getDifferentCombinations(inpWord, nNumber, '#');
                it = nNumber.begin();
                *it = *it + 1;
            }
            else
            {
                cnt2 = 0;
            }
        }
        inpWord.push_back('#');
    }
    /* If the previous character was a #, and current character is a ".", then
     * check if the input spring size has become zero, if not return false, if
     * true, remove the input spring size and input spring top element and
     * call the recursive function */
    else if (prevChar == '#' && inpWord[inpWord.size()-1] == '.')
    {
        if (nNumber.size() == 0)
        {
            cnt2 = 0;
        }
        else
        {
            auto it = nNumber.begin();
            if (*it == 0)
            {
                nNumber.pop_front();
                inpWord.pop_back();
                cnt2 += getDifferentCombinations(inpWord, nNumber, '.');
                inpWord.push_back('.');
                nNumber.push_front(0);
            }
        }
    }
    /* If these were could not cover all cases, which it should have, print this
     * debug message to capture that */
    else
    {
        cout << "Something else" << endl;
    }

    /* Store the result in the hash map for future use */
    hashMap[sKey] = cnt2;
    /* Return the result */
    return cnt2;
}
