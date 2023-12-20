#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<numeric>

using namespace std;

int main()
{
    string line;
    vector<string> lines{};
    int64_t sum = 0;
    int currentCardNumber = 0;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            lines.push_back(line);
        }
        int nrCards = lines.size();
        vector<int> amountOfCardsPerCard(nrCards, 1);

        for (auto & line : lines) {
            currentCardNumber += 1;
            int pos = line.find(":");
            line = line.substr(pos+1, line.length()); // +1 also removes the whitespcae

            bool crossedSeperator = false;
            vector<int> winningNumbers{};
            vector<int> myNumbers{};
            int nrMatches = 0;
            for (int i = 0; i< line.length(); i++) {
                if (line[i] == '|') crossedSeperator = true;
                if (isdigit(line[i])) {
                    string digit = "";
                    while (isdigit(line[i+digit.length()]))
                        digit = digit + line[i+digit.length()];
                    if (!crossedSeperator) winningNumbers.push_back(stoi(digit));
                    else if (find(winningNumbers.begin(), winningNumbers.end(), stoi(digit)) != winningNumbers.end()) {
                        nrMatches += 1;
                    }
                    i += digit.length()-1;
                }
            }
            for (int i = 0; i < nrMatches; i++) {
                if (currentCardNumber + i < nrCards)
                    amountOfCardsPerCard[currentCardNumber+i] += amountOfCardsPerCard[currentCardNumber-1];
            }
        }
        for (int i=0; i<nrCards; i++) sum += amountOfCardsPerCard[i];
        myfile.close();
        cout << sum;
    }

    else cout << "Unable to open file"; 
}