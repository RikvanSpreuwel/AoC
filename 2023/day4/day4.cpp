#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string line;
    int64_t sum = 0;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            int pos = line.find(":");
            line = line.substr(pos+1, line.length()); // +1 also removes the whitespcae

            bool crossedSeperator = false;
            vector<int> winningNumbers{};
            vector<int> myNumbers{};
            int worthNess = 0;
            for (int i = 0; i< line.length(); i++) {
                if (line[i] == '|') crossedSeperator = true;
                if (isdigit(line[i])) {
                    string digit = "";
                    while (isdigit(line[i+digit.length()]))
                        digit = digit + line[i+digit.length()];
                    if (!crossedSeperator) winningNumbers.push_back(stoi(digit));
                    else if (find(winningNumbers.begin(), winningNumbers.end(), stoi(digit)) != winningNumbers.end()) {
                        if (worthNess == 0) worthNess = 1;
                        else worthNess = worthNess*2;
                    }
                    i += digit.length()-1;
                }
            }
            sum += worthNess;
        }
        
        myfile.close();
        cout << sum;
    }

    else cout << "Unable to open file"; 
}