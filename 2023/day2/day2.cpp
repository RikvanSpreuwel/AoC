#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <algorithm>

using namespace std;
int main()
{
    string line;
    int64_t currentGame = 0;
    int64_t possibleGamesCount = 0;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            bool possible = true;
            string currentAmount = ""; // current amount of a color
            currentGame += 1;

            int pos = line.find(":");
            line = line.substr(pos+1, line.length()); // +1 also removes the whitespcae

            string currentSubstring = "";
            for (int i = 0; i < line.length(); i++) {
                currentSubstring = currentSubstring + line[i];
                if (isdigit(currentSubstring[currentSubstring.length()-1])) {
                    currentAmount = currentAmount + currentSubstring[currentSubstring.length()-1];
                } else if (currentSubstring.length() > 2 && currentSubstring.substr(currentSubstring.length()-3, currentSubstring.length()) == "red"){
                    if (stoi(currentAmount) > 12) { possible = false; break; }
                    currentAmount = "";
                    currentSubstring = "";
                } else if (currentSubstring.length() > 3 && currentSubstring.substr(currentSubstring.length()-4, currentSubstring.length()) == "blue"){
                    if (stoi(currentAmount) > 14) { possible = false; break; }
                    currentAmount = "";
                    currentSubstring = "";
                } else if (currentSubstring.length() > 4 && currentSubstring.substr(currentSubstring.length()-5, currentSubstring.length()) == "green"){
                    if (stoi(currentAmount) > 13) { possible = false; break; }
                    currentAmount = "";
                    currentSubstring = "";
                }
            }
            if (possible) possibleGamesCount += currentGame;
        }
        myfile.close();
        cout << possibleGamesCount;
    }

    else cout << "Unable to open file"; 
}