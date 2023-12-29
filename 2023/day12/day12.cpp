#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <numeric>
#include <tuple>
using namespace std;

int recurse(string condition, string currentCondition, int currentGroupsSize, vector<int> groupSizesGiven, vector<int> currentGroupSizes, int nrOfArrangements) {
    if (currentCondition.length() == condition.length()) {
        if (currentCondition[currentCondition.length()-1] == '#') {
            // find group size, add to current group sizes
            int groupSize = 1;
            while (currentCondition[currentCondition.length()-1-groupSize] == '#') groupSize++;
            currentGroupSizes.push_back(groupSize);
        } 
        if (currentGroupSizes.size() == groupSizesGiven.size() && currentGroupSizes.back() == groupSizesGiven.back()) 
            return nrOfArrangements+1;
        else return nrOfArrangements;
    } else {
        if (condition[currentCondition.length()] == '?') {
            // option 1, we consider ? as a .
            vector<int> currentGroupSizesCopy = currentGroupSizes;
            if (currentGroupsSize != 0) currentGroupSizesCopy.push_back(currentGroupsSize);
            if (currentGroupSizesCopy.size() == 0 || (currentGroupSizesCopy.size() <= groupSizesGiven.size() && currentGroupSizesCopy.back() == groupSizesGiven[currentGroupSizesCopy.size()-1])) 
                nrOfArrangements = recurse(condition, currentCondition+'.', 0, groupSizesGiven, currentGroupSizesCopy, nrOfArrangements);
            
            // option 2, we consider ? as a #
            if (currentGroupsSize+1 <= groupSizesGiven[currentGroupSizes.size()])
                return recurse(condition, currentCondition+'#', currentGroupsSize+1, groupSizesGiven, currentGroupSizes, nrOfArrangements);
        } else if (condition[currentCondition.length()] == '.') {
            if (currentGroupsSize != 0) currentGroupSizes.push_back(currentGroupsSize);
            if (currentGroupSizes.size() == 0 || (currentGroupSizes.size() <= groupSizesGiven.size() && currentGroupSizes.back() == groupSizesGiven[currentGroupSizes.size()-1])) 
                return recurse(condition, currentCondition+'.', 0, groupSizesGiven, currentGroupSizes, nrOfArrangements);
            else return nrOfArrangements;
        } else if (condition[currentCondition.length()] == '#') {
            if (currentGroupsSize+1 <= groupSizesGiven[currentGroupSizes.size()])
                return recurse(condition, currentCondition+'#', currentGroupsSize+1, groupSizesGiven, currentGroupSizes, nrOfArrangements);
        }
    }
    return nrOfArrangements;
}

int main()
{
    string line;
    ifstream myfile ("input.txt");
    vector<string> springConditions{};

    long long totalArrangements = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            springConditions.push_back(line);
        }
        myfile.close();


        for (auto springCondition : springConditions) {
            int posSpace = springCondition.find(" ");
            
            string condition = springCondition.substr(0, posSpace);
            vector<int> missingInfoLocations{};
            for (int i=0; i<condition.length(); i++) {
                if (condition[i]=='?') missingInfoLocations.push_back(i);
            }

            vector<int> groupSizesGiven{};
            for (int i=posSpace+1; i<springCondition.length(); i++) {
                if (isdigit(springCondition[i])) {
                    int digitLength = 1;
                    while(isdigit(springCondition[i+digitLength])) digitLength++;
                    groupSizesGiven.push_back(stoi(springCondition.substr(i, digitLength)));
                    i = i+digitLength;
                }
            }

            totalArrangements += recurse(condition, "", 0, groupSizesGiven, {}, 0);

        }

        cout << totalArrangements;
    }

    else cout << "Unable to open file"; 
}