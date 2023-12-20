#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <algorithm>

using namespace std;

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
                if (lines[i][j] == '*') {
                    vector<int> adjacentNumbers{};
                    if (j > 0 && isdigit(lines[i][j-1])) {
                        int digitSize = 1;
                        while((j-digitSize>0) && isdigit(lines[i][j-(1+digitSize)])) digitSize += 1;
                        adjacentNumbers.push_back(stoi(lines[i].substr(j-(digitSize), digitSize)));
                    }
                    if (j < lineLength-1 && isdigit(lines[i][j+1])) {
                        int digitSize = 1;
                        while(isdigit(lines[i][j+1+digitSize])) digitSize += 1;
                        adjacentNumbers.push_back(stoi(lines[i].substr(j+1, digitSize)));
                    }
                    if (i > 0) {
                        if (isdigit(lines[i-1][j])) {
                            int digitSizeRight = 0;
                            int digitSizeLeft = 0;
                            while((j+digitSizeRight) < lineLength-1 && (lines[i-1][j+1+digitSizeRight])) digitSizeRight += 1;
                            while((j-digitSizeLeft)>0 && isdigit(lines[i-1][j-(1+digitSizeLeft)])) digitSizeLeft += 1;
                            string t = lines[i-1].substr(j-digitSizeLeft, digitSizeLeft+digitSizeRight+1);
                            adjacentNumbers.push_back(stoi(lines[i-1].substr(j-digitSizeLeft, digitSizeLeft+digitSizeRight+1)));
                        } else {
                            if (j > 0 && isdigit(lines[i-1][j-1])) {
                                int digitSize = 1;
                                while((j-digitSize)>0 && isdigit(lines[i-1][j-(1+digitSize)])) digitSize += 1;
                                string t = lines[i-1].substr(j-(digitSize), digitSize+1);
                                adjacentNumbers.push_back(stoi(lines[i-1].substr(j-(digitSize), digitSize+1)));
                            } 
                            if (j < lineLength-1 && isdigit(lines[i-1][j+1])) {
                                int digitSize = 1;
                                while((j+digitSize) < lineLength-1 && isdigit(lines[i-1][j+1+digitSize])) digitSize += 1;
                                adjacentNumbers.push_back(stoi(lines[i-1].substr(j+1, digitSize)));
                            }
                        }
                    }
                    if (i < lines.size()-1) {
                        if (isdigit(lines[i+1][j])) {
                            int digitSizeRight = 0;
                            int digitSizeLeft = 0;
                            while((j+digitSizeRight) < lineLength-1 && isdigit(lines[i+1][j+1+digitSizeRight])) digitSizeRight += 1;
                            while((j-digitSizeLeft) > 0 && isdigit(lines[i+1][j-(1+digitSizeLeft)])) digitSizeLeft += 1;

                            adjacentNumbers.push_back(stoi(lines[i+1].substr(j-digitSizeLeft, digitSizeLeft+digitSizeRight+1)));
                        } else {
                            if (j > 0 && isdigit(lines[i+1][j-1])) {
                                int digitSize = 1;
                                while((j-digitSize) > 0 && isdigit(lines[i+1][j-(1+digitSize)])) digitSize += 1;
                                adjacentNumbers.push_back(stoi(lines[i+1].substr(j-(digitSize), digitSize+1)));
                            } 
                            if (j < lineLength-1 && isdigit(lines[i+1][j+1])) {
                                int digitSize = 1;
                                while((j+digitSize)<lineLength-1 && isdigit(lines[i+1][j+1+digitSize])) digitSize += 1;
                                adjacentNumbers.push_back(stoi(lines[i+1].substr(j+1, digitSize)));
                            }
                        }
                    }
                    if (adjacentNumbers.size() == 2) {
                        sum += (adjacentNumbers[0]*adjacentNumbers[1]);
                    }
                }
            }
        }
        myfile.close();
        cout << sum;
    }

    else cout << "Unable to open file"; 
}