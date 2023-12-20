#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <algorithm>

using namespace std;
int main()
{
    string line;
    int64_t total = 0;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            int64_t maxRed = 0;
            int64_t maxBlue = 0;
            int64_t maxGreen = 0;
            string currentAmount = ""; // current amount of a color

            int pos = line.find(":");
            line = line.substr(pos+1, line.length()); // +1 also removes the whitespcae

            string currentSubstring = "";
            for (int i = 0; i < line.length(); i++) {
                currentSubstring = currentSubstring + line[i];
                if (isdigit(currentSubstring[currentSubstring.length()-1])) {
                    currentAmount = currentAmount + currentSubstring[currentSubstring.length()-1];
                } else if (currentSubstring.length() > 2 && currentSubstring.substr(currentSubstring.length()-3, currentSubstring.length()) == "red"){
                    if (stoi(currentAmount) > maxRed) maxRed = stoi(currentAmount); 
                    currentAmount = "";
                    currentSubstring = "";
                } else if (currentSubstring.length() > 3 && currentSubstring.substr(currentSubstring.length()-4, currentSubstring.length()) == "blue"){
                    if (stoi(currentAmount) > maxBlue) maxBlue = stoi(currentAmount);
                    currentAmount = "";
                    currentSubstring = "";
                } else if (currentSubstring.length() > 4 && currentSubstring.substr(currentSubstring.length()-5, currentSubstring.length()) == "green"){
                    if (stoi(currentAmount) > maxGreen) maxGreen = stoi(currentAmount);
                    currentAmount = "";
                    currentSubstring = "";
                }
            }
            total += (maxRed * maxBlue * maxGreen);
        }
        myfile.close();
        cout << total;
    }

    else cout << "Unable to open file"; 
}