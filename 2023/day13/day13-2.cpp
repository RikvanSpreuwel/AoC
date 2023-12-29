#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <numeric>
#include <tuple>
#include <math.h>
using namespace std;

// from: https://www.geeksforgeeks.org/program-to-find-whether-a-given-number-is-power-of-2/
bool isPowerOfTwo(int n)
{
    if (n == 0)
        return false;
 
    return (ceil(log2(n)) == floor(log2(n)));
}

bool exactlyOneBitDiffers(int bitmask1, int bitmask2) {
    return isPowerOfTwo(abs(bitmask1^bitmask2));
}

// convert patterns to bitmasks?
int main()
{
    string line;
    ifstream myfile ("input.txt");

    int summary = 0;
    
    vector<vector<int>> patternsRowsBitmasks{};
    vector<vector<int>> patternsColumnsBitmasks{};
    if (myfile.is_open())
    {
        vector<int> currentPatternRows{};
        vector<int> currentPatternColumns{};
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            if (line == "") {
                patternsRowsBitmasks.push_back(currentPatternRows);
                patternsColumnsBitmasks.push_back(currentPatternColumns);
                currentPatternRows = {};
                currentPatternColumns = {};
                currentRow = 0;
            } else {
                currentPatternRows.push_back(0);
                for (int i=0; i<line.length(); i++) {
                    if (currentRow == 0) currentPatternColumns.push_back(0);
                    if (line[i] == '#') { currentPatternColumns[i] += pow(2, currentRow); currentPatternRows[currentRow] += pow(2, i); }
                }
                currentRow++;
            }
        }
        
        patternsRowsBitmasks.push_back(currentPatternRows);
        patternsColumnsBitmasks.push_back(currentPatternColumns);
        myfile.close();

        for (int i=0; i<patternsRowsBitmasks.size(); i++) {
            // check rows
            for (int j=0;j<patternsRowsBitmasks[i].size()-1;j++) {
                if (patternsRowsBitmasks[i][j] == patternsRowsBitmasks[i][j+1]) { 
                    // same as before, but now we consider a single smudge, no smudge found means no valid reflection
                    bool changedASmudge = false;
                    int up = j-1;
                    int down = j+2;
                    bool reflectionFound = true;
                    while (up >=0 && down <patternsRowsBitmasks[i].size()) {
                        if (patternsRowsBitmasks[i][up] != patternsRowsBitmasks[i][down]) { 
                            if (!changedASmudge && exactlyOneBitDiffers(patternsRowsBitmasks[i][up], patternsRowsBitmasks[i][down])) changedASmudge = true;
                            else { reflectionFound = false; break; }
                        }
                        up--;
                        down++;
                    }
                    if (reflectionFound && changedASmudge) { summary += (100*(j+1)); break; } // add to sum, break
                } else if (exactlyOneBitDiffers(patternsRowsBitmasks[i][j], patternsRowsBitmasks[i][j+1])) { 
                    // second case, two rows almost match, fixing the smudge here may also reveal a valid reflection
                    int up = j-1;
                    int down = j+2;
                    bool reflectionFound = true;
                    while (up >=0 && down <patternsRowsBitmasks[i].size()) {
                        if (patternsRowsBitmasks[i][up] != patternsRowsBitmasks[i][down]) { reflectionFound = false; break; }
                        up--;
                        down++;
                    }
                    if (reflectionFound) { summary += (100*(j+1)); break; } // add to sum, break
                }
            }

            // if not found, check columns
            for (int j=0;j<patternsColumnsBitmasks[i].size()-1;j++) {
                if (patternsColumnsBitmasks[i][j] == patternsColumnsBitmasks[i][j+1]) {
                    // same as before, but now we consider a single smudge, no smudge found means no valid reflection
                    bool changedASmudge = false;
                    int left = j-1;
                    int right = j+2;
                    bool reflectionFound = true;
                    while (left >=0 && right <patternsColumnsBitmasks[i].size()) {
                        if (patternsColumnsBitmasks[i][left] != patternsColumnsBitmasks[i][right]) { 
                            if (!changedASmudge && exactlyOneBitDiffers(patternsColumnsBitmasks[i][left], patternsColumnsBitmasks[i][right])) changedASmudge = true;
                            else { reflectionFound = false; break; }
                        }
                        left--;
                        right++;
                    }
                    if (reflectionFound && changedASmudge) { summary += (j+1); break; } // add to sum, break
                } else if (exactlyOneBitDiffers(patternsColumnsBitmasks[i][j], patternsColumnsBitmasks[i][j+1])) {
                    // second case, two columns almost match, fixing the smudge here may also reveal a valid reflection
                    int left = j-1;
                    int right = j+2;
                    bool reflectionFound = true;
                    while (left >=0 && right <patternsColumnsBitmasks[i].size()) {
                        if (patternsColumnsBitmasks[i][left] != patternsColumnsBitmasks[i][right]) { reflectionFound = false; break; }
                        left--;
                        right++;
                    }
                    if (reflectionFound) { summary += (j+1); break; } // add to sum, break
                }
            }
        }
        // for (auto pattern : patterns) {
        //     // check for matching rows
        //     for (int i=0; i<pattern.size(); i++) {
        //         for (int j=0; j<pattern[0].length(); j++) {

        //         }
        //     }
        // }

        // for (auto springCondition : springConditions) {
        //     int posSpace = springCondition.find(" ");
            
        //     string condition = springCondition.substr(0, posSpace);
        //     vector<int> missingInfoLocations{};
        //     for (int i=0; i<condition.length(); i++) {
        //         if (condition[i]=='?') missingInfoLocations.push_back(i);
        //     }

        //     vector<int> groupSizesGiven{};
        //     for (int i=posSpace+1; i<springCondition.length(); i++) {
        //         if (isdigit(springCondition[i])) {
        //             int digitLength = 1;
        //             while(isdigit(springCondition[i+digitLength])) digitLength++;
        //             groupSizesGiven.push_back(stoi(springCondition.substr(i, digitLength)));
        //             i = i+digitLength;
        //         }
        //     }

        //     totalArrangements += recurse(condition, "", 0, groupSizesGiven, {}, 0);

        // }

        cout << summary;
    }

    else cout << "Unable to open file"; 
}