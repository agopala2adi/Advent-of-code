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

int64_t getTypeKind(string card, bool bJackIsJoker = false);
bool isGreater(char a, char b, bool bJackIsJoker = false);

int main(void)
{
    auto startTime = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startTime);

    /* NOTE: REMOVE THE LAST LINE FROM INPUT AS THERE IS A BUG THAT READS THE 
     * LAST LINE TWICE */

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

    /* To store the 5 letter card */
    vector<string> cards;
    /* To store the bid value of corresponding card */
    vector<int64_t> bid;
    /* To get the cards in descending order of value - Part 1 */
    vector<string> card_value_part1[7];
    /* To get the cards in descending order of value - Part 2 */
    vector<string> card_value_part2[7];

    /* NOTE: REMOVE THE LAST LINE FROM INPUT AS THERE IS A BUG THAT READS THE 
     * LAST LINE TWICE */

    /* Read each line from file */
    while (feof(fp) == 0)
    {
        /* Read the current 5 char card and the bid amount */
        char card_char[7];
        fscanf(fp, "%s %ld", card_char, &cnt2);

        /* Store the card in the cards list */
        cards.push_back(card_char);
        /* Store the bid value of the card in the bid list */
        bid.push_back(cnt2);

        /* Increment count to move to next line */
        ++cnt1;
    }

    /* Sort the cards as per "type":
     * Index 0: Store cards of type five of a kind 
     * Index 1: Store cards of type four of kind, so on 
     * Index 6: Store cards of type high card */
    for (cnt2 = 0; cnt2 < cnt1; cnt2++)
    {
        /* Part 1 - Jack is jack */
        card_value_part1[getTypeKind(cards[cnt2], false)].push_back(cards[cnt2]);
        /* Part 1 - Jack is joker */
        card_value_part2[getTypeKind(cards[cnt2], true)].push_back(cards[cnt2]);
    }


    /* For all type index from strongest to weakest - Part 1 */
    for (cnt2 = 0; cnt2 < 7; cnt2++)
    {
        /* Perform bubble sort */
        for (cnt3 = 0; cnt3 + 1 < card_value_part1[cnt2].size(); cnt3++)
        {
            for (cnt4 = 0; cnt4 + cnt3 + 1 < card_value_part1[cnt2].size(); cnt4++)
            {
                cnt5 = 0;
                /* Keep ignoring if same both are of the characters */
                while (card_value_part1[cnt2][cnt4][cnt5] == card_value_part1[cnt2][cnt4+1][cnt5])
                {
                    cnt5++;
                }
                /* If first number is lesser than second number, swap - for descending order sort */
                if (isGreater(card_value_part1[cnt2][cnt4][cnt5], card_value_part1[cnt2][cnt4+1][cnt5], false) == false)
                {
                    string temp_card = card_value_part1[cnt2][cnt4];
                    card_value_part1[cnt2][cnt4] = card_value_part1[cnt2][cnt4+1];
                    card_value_part1[cnt2][cnt4+1] = temp_card;
                }
            }
        }
    }

    /* For all type index from strongest to weakest - Part 2 */
    for (cnt2 = 0; cnt2 < 7; cnt2++)
    {
        /* Perform bubble sort */
        for (cnt3 = 0; cnt3 + 1 < card_value_part2[cnt2].size(); cnt3++)
        {
            for (cnt4 = 0; cnt4 + cnt3 + 1 < card_value_part2[cnt2].size(); cnt4++)
            {
                cnt5 = 0;
                /* Keep ignoring if same both are of the characters */
                while (card_value_part2[cnt2][cnt4][cnt5] == card_value_part2[cnt2][cnt4+1][cnt5])
                {
                    cnt5++;
                }
                /* If first number is lesser than second number, swap - for descending order sort */
                if (isGreater(card_value_part2[cnt2][cnt4][cnt5], card_value_part2[cnt2][cnt4+1][cnt5], true) == false)
                {
                    string temp_card = card_value_part2[cnt2][cnt4];
                    card_value_part2[cnt2][cnt4] = card_value_part2[cnt2][cnt4+1];
                    card_value_part2[cnt2][cnt4+1] = temp_card;
                }
            }
        }
    }

    /* Assign rank highest to the first element and keep decreasing the rank  */
    cnt7 = cards.size();

    /* For all types */
    for (cnt2 = 0; cnt2 < 7; cnt2++)
    {
        for (cnt3 = 0; cnt3 < card_value_part1[cnt2].size(); cnt3++)
        {
            auto it = std::find(cards.begin(), cards.end(), card_value_part1[cnt2][cnt3]);
            /* Store the sum in part 1: bid value * rank */
            nPartOneSum += cnt7 * bid[it-cards.begin()];
            cnt7--;
        }
    }


    /* Assign rank highest to the first element and keep decreasing the rank  */
    cnt7 = cards.size();

    /* For all types */
    for (cnt2 = 0; cnt2 < 7; cnt2++)
    {
        for (cnt3 = 0; cnt3 < card_value_part2[cnt2].size(); cnt3++)
        {
            auto it = std::find(cards.begin(), cards.end(), card_value_part2[cnt2][cnt3]);
            /* Store the sum in part 2: bid value * rank */
            nPartTwoSum += cnt7 * bid[it-cards.begin()];
            cnt7--;
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

/* Returns the type of kind of a given card */
int64_t getTypeKind(string card, bool bJackIsJoker)
{
    vector <int64_t> cnt1;
    int64_t cnt2 = 0;
    int64_t cnt3 = 0;
    int64_t card_j = 0;

    /* For all different characters in a card, store the initial value to zero */
    for (cnt2 = 0; cnt2 < 15; cnt2++)
    {
        cnt1.push_back(0);
    }

    /* For all different characters, start storing the sum in every index:
     * index 0 would have the number of A's
     * index 1 would have the number of K's so on till
     * index 11 would have the number of 2's 
     * index 12 would have number of Jacks/Jokers */
    for (cnt2 = 0; cnt2 < card.size(); cnt2++)
    {
        if (card[cnt2] == 'A')
        {
            cnt1[0]++;
        }
        else if (card[cnt2] == 'K')
        {
            cnt1[1]++;
        }
        else if (card[cnt2] == 'Q')
        {
            cnt1[2]++;
        }
        else if (card[cnt2] == 'J')
        {
            card_j++;
            if (bJackIsJoker == false)
            {
                cnt1[12]++;
            }
        }
        else if (card[cnt2] == 'T')
        {
            cnt1[3]++;
        }
        else if (card[cnt2] == '9')
        {
            cnt1[4]++;
        }
        else if (card[cnt2] == '8')
        {
            cnt1[5]++;
        }
        else if (card[cnt2] == '7')
        {
            cnt1[6]++;
        }
        else if (card[cnt2] == '6')
        {
            cnt1[7]++;
        }
        else if (card[cnt2] == '5')
        {
            cnt1[8]++;
        }
        else if (card[cnt2] == '4')
        {
            cnt1[9]++;
        }
        else if (card[cnt2] == '3')
        {
            cnt1[10]++;
        }
        else if (card[cnt2] == '2')
        {
            cnt1[11]++;
        }
        else
        {
            cout << "something wrong: " << card[cnt2] << endl;
        }
    }

    /* Sort the numbers in descending order to get the type */
    sort(cnt1.begin(), cnt1.end(), greater<int64_t>());

    /* If the card is a joker, add the count to index zero */
    if (bJackIsJoker == true)
    {
        cnt1[0] += card_j;
    }

    /* Five of a kind */
    if (cnt1[0] == 5)
    {
        return 0;
    }
    /* Four of a kind */
    else if (cnt1[0] == 4)
    {
        return 1;
    }
    /* Full house */
    else if (cnt1[0] == 3 && cnt1[1] == 2)
    {
        return 2;
    }
    /* Three of a kind */
    else if (cnt1[0] == 3 && cnt1[1] == 1)
    {
        return 3;
    }
    /* Two pair */
    else if (cnt1[0] == 2 && cnt1[1] == 2)
    {
        return 4;
    }
    /* One pair */
    else if (cnt1[0] == 2)
    {
        return 5;
    }
    /* High card */
    else 
    {
        return 6;
    }
}

/* To get which character in the card is greater */
bool isGreater(char a, char b, bool bJackIsJoker)
{
    /* If jack is joker, J is the least value card */
    if (bJackIsJoker == true)
    {
        if (a == 'A')
        {
            return true;
        }
        else if (a == 'K')
        {
            if (b == 'A')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (a == 'Q')
        {
            if (b == 'A' || b == 'K')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (a == 'J')
        {
            return false;
        }
        else if (b == 'J')
        {
            return true;
        }
        else if (a == 'T')
        {
            if (b == 'A' || b == 'K' || b == 'Q')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (a == '9')
        {
            if (b == 'A' || b == 'K' || b == 'Q' || b == 'T')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (a > b)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    /* If jack is jack, J's value is in between Q and T */
    else
    {
        if (a == 'A')
        {
            return true;
        }
        else if (a == 'K')
        {
            if (b == 'A')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (a == 'Q')
        {
            if (b == 'A' || b == 'K')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (a == 'J')
        {
            if (b == 'A' || b == 'K' || b == 'Q')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (a == 'T')
        {
            if (b == 'A' || b == 'K' || b == 'Q' || b == 'J')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (a == '9')
        {
            if (b == 'A' || b == 'K' || b == 'Q' || b == 'T' || b == 'J')
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        /* For number cards */
        else if (a > b)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
}

