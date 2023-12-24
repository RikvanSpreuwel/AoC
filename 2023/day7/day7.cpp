#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
using namespace std;

enum HandType { fiveOfAKind, fourOfAKind, fullHouse, threeOfAKind, twoPair, onePair, highCard };

HandType mapToHandType(string hand) {
    map<char, int> numberOfOccurrencesPerCard{};
    for (int i=0; i<hand.length(); i++) {
        if (numberOfOccurrencesPerCard.find(hand[i]) == numberOfOccurrencesPerCard.end()) numberOfOccurrencesPerCard[hand[i]] = 1;
        else numberOfOccurrencesPerCard[hand[i]] += 1;
    }
    
    // determine which type of hand is given
    if (numberOfOccurrencesPerCard.size() == 1) return fiveOfAKind;
    else if (numberOfOccurrencesPerCard.size() == 2) {
        // possible: four of a kind or full house
        if (numberOfOccurrencesPerCard[hand[0]] == 3 || numberOfOccurrencesPerCard[hand[0]] == 2) return fullHouse;
        else return fourOfAKind;
    } else if (numberOfOccurrencesPerCard.size() == 3) {
        // possible: three of a kind or two pair
        if (numberOfOccurrencesPerCard[hand[0]] == 3 || numberOfOccurrencesPerCard[hand[1]] == 3 || numberOfOccurrencesPerCard[hand[2]] == 3) return threeOfAKind;
        else return twoPair;
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
                else if (h[i] == 'J') cards.push_back(11);
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