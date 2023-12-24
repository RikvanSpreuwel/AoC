#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
using namespace std;

enum HandType { fiveOfAKind, fourOfAKind, fullHouse, threeOfAKind, twoPair, onePair, highCard };

HandType mapToHandType(string hand) {
    int numberOfJs = 0;
    map<char, int> numberOfOccurrencesPerCard{};
    for (int i=0; i<hand.length(); i++) {
        if (hand[i] == 'J') numberOfJs++;
        else if (numberOfOccurrencesPerCard.find(hand[i]) == numberOfOccurrencesPerCard.end()) numberOfOccurrencesPerCard[hand[i]] = 1;
        else numberOfOccurrencesPerCard[hand[i]] += 1;
    }
    
    // determine which type of hand is given
    if (numberOfOccurrencesPerCard.size() == 1 || numberOfJs == 5) return fiveOfAKind;
    else if (numberOfOccurrencesPerCard.size() == 2) {
        // possible: four of a kind or full house
        if (numberOfJs==1) {
            if (numberOfOccurrencesPerCard[hand[0]] == 3 || numberOfOccurrencesPerCard[hand[1]] == 3) return fourOfAKind;
            else return fullHouse;
        } else if (numberOfJs == 2 || numberOfJs == 3){ // case 1: numberofjs == 3, then two cards occur once, so four of a kind is strongest
            return fourOfAKind; // case 2: one card occurs twice, one occurs once, then + J four of a kind is strongest
        } else {
            if (numberOfOccurrencesPerCard[hand[0]] == 3 || numberOfOccurrencesPerCard[hand[0]] == 2) return fullHouse;
            else return fourOfAKind;
        }
    } else if (numberOfOccurrencesPerCard.size() == 3) {
        // possible: three of a kind or two pair
        if (numberOfJs!=0) { // either a 1/1/2 distribution + 1J, or 1/1/1 distribution + 2J, so three of a kind is strongest
            return threeOfAKind;
        } else {
            if (numberOfOccurrencesPerCard[hand[0]] == 3 || numberOfOccurrencesPerCard[hand[1]] == 3 || numberOfOccurrencesPerCard[hand[2]] == 3) return threeOfAKind;
            else return twoPair;
        }
    }
    else if (numberOfOccurrencesPerCard.size() == 4) return onePair;
    else return highCard;
};

class Hand{
    public:
        string hand;
        vector<int> cards{};
        HandType handType;
        int score;
        Hand(string h, HandType ht, int s) {
            hand = h;
            handType = ht;
            score = s;
            cards = {};
            for (int i=0; i<hand.length(); i++) {
                if (isdigit(h[i])) cards.push_back(stoi(h.substr(i,1)));
                else if (h[i] == 'T') cards.push_back(10);
                else if (h[i] == 'J') cards.push_back(1);
                else if (h[i] == 'Q') cards.push_back(12);
                else if (h[i] == 'K') cards.push_back(13);
                else if (h[i] == 'A') cards.push_back(14);
            }
        }
};



int main()
{
    string line;
    int64_t total = 0;
    ifstream myfile ("input.txt");
    vector<Hand> handsWithScores{};
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            int pos = line.find(" ");
            handsWithScores.push_back(Hand(line.substr(0,pos),  mapToHandType(line.substr(0,pos)), stoi(line.substr(pos, line.length()))));
        }
        myfile.close();

        sort(handsWithScores.begin(), handsWithScores.end(), [](const Hand& h1, const Hand& h2) {
            if (h1.handType != h2.handType) return h1.handType > h2.handType;
            else {
                for (int i=0; i<h1.cards.size(); i++) {
                    if (h1.cards[i] != h2.cards[i]) return h1.cards[i] < h2.cards[i];
                }
            }
        });
        
        for (int i=0; i<handsWithScores.size(); i++) {
            total += (i+1)*handsWithScores[i].score;
        }

        cout << total;
    }

    else cout << "Unable to open file"; 
}