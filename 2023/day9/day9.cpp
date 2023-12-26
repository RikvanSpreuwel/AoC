#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <numeric>
using namespace std;

int main()
{
    string line;
    ifstream myfile ("input.txt");

    int64_t sum = 0;
    vector<vector<int>> sequences{};
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<int> sequence{};
            for (int i=0; i<line.length();i++) {
                if (isdigit(line[i])) {
                    int digitLength = 1;
                    while (isdigit(line[i+digitLength])) digitLength++;
                    sequence.push_back(stoi(line.substr(i,digitLength)));
                    i+=digitLength;
                } else if (line[i] == '-') {
                    int digitLength = 0;
                    while (isdigit(line[i+1+digitLength])) digitLength++;
                    sequence.push_back(0-stoi(line.substr(i+1,digitLength)));
                    i+=digitLength;
                }
            }
            sequences.push_back(sequence);
        }
        myfile.close();

        for (auto sequence : sequences) {
            vector<vector<int>> subsequences{};
            subsequences.push_back(sequence);
            vector<int> currentSequence{};
            bool next=true;
            while(next){
                next = false;
                int currentElement = subsequences.back()[0];
                for (int i=1; i<subsequences.back().size();i++) {
                    int newElement = subsequences.back()[i]-currentElement;
                    currentElement = subsequences.back()[i];
                    currentSequence.push_back(newElement);
                    if (currentElement != 0) next=true;
                }
                subsequences.push_back(currentSequence);
                currentSequence = {};
            }
            int newSequenceValue = 0;
            for (auto subsequence : subsequences) {
                newSequenceValue += subsequence.back();
            }
            sum += newSequenceValue;
        }

        cout << sum;
    }

    else cout << "Unable to open file"; 
}