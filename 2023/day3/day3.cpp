#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <algorithm>

using namespace std;
bool is_symbol(char c) {
    if (!isdigit(c) && c != '.')//c == '!' || c == '@' || c =='#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '-' || c == '=' || c == '+' || c == '/')
        return true; //!isdigit(c) && c != '.'
    else return false;
}

int main()
{
    string line;
    int lineLength = 0;
    vector<string> lines{}; 
    int64_t sum = 0;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            lines.push_back(line);
        }
        lineLength = lines[0].length();
        for (int i = 0; i < lines.size(); i++) {
            for (int j = 0; j < lineLength; j++) {
                if (isdigit(lines[i][j])) {
                    bool hasAdjacentSymbol = false;
                    if (j > 0 && is_symbol(lines[i][j-1])) hasAdjacentSymbol = true;
                    if (j < lineLength-1 && is_symbol(lines[i][j+1])) hasAdjacentSymbol = true;
                    if (i > 0 && hasAdjacentSymbol == false) {
                        // check row above
                        if (j > 0 && is_symbol(lines[i-1][j-1])) hasAdjacentSymbol = true;
                        if (is_symbol(lines[i-1][j])) hasAdjacentSymbol = true;
                        if (j < lineLength-1 && is_symbol(lines[i-1][j+1])) hasAdjacentSymbol = true;
                    }
                    if (i < lines.size()-1 && hasAdjacentSymbol == false) {
                        // check row above
                        if (j > 0 && is_symbol(lines[i+1][j-1])) hasAdjacentSymbol = true;
                        if (is_symbol(lines[i+1][j])) hasAdjacentSymbol = true;
                        if (j < lineLength-1 && is_symbol(lines[i+1][j+1])) hasAdjacentSymbol = true;
                    }

                    int digitSize = 1;
                    while (isdigit(lines[i][j+digitSize])) {
                        if (j+digitSize < lineLength-1) { 
                            if (hasAdjacentSymbol == false && is_symbol(lines[i][j+digitSize+1])) hasAdjacentSymbol = true; 
                            if (hasAdjacentSymbol == false && i > 0 && is_symbol(lines[i-1][j+digitSize+1])) hasAdjacentSymbol = true;
                            if (hasAdjacentSymbol == false && i < lines.size()-1 && is_symbol(lines[i+1][j+digitSize+1])) hasAdjacentSymbol = true;
                        }
                        digitSize += 1;
                    }
                    if (hasAdjacentSymbol == true) {
                        string t = lines[i].substr(j, digitSize);
                        sum += stoi(lines[i].substr(j, digitSize));
                    }
                    
                    j = j+digitSize;
                }
            }
        }
        myfile.close();
        cout << sum;
    }

    else cout << "Unable to open file"; 
}