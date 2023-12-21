#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Triple 
{ 
   long long x, y, z; 
}; 

struct Tuple 
{
    long long x, y;
};

vector<vector<Triple>> maps{{},{},{},{},{},{},{}};

vector<Tuple> resursiveLocationsFinder(vector<Tuple> locations, Tuple currentRange, int mapToUse) {
    if (mapToUse < 7) {
        vector<Triple> currentMapping{};
        for (auto & currentMapping : maps[mapToUse]) {
            if (currentRange.x >= currentMapping.y && currentRange.x+currentRange.y-1 < currentMapping.y+currentMapping.z) { //  -----  mapping 
                return resursiveLocationsFinder(locations, {currentMapping.x+(currentRange.x-currentMapping.y),              //   ---   currentrange
                    currentRange.y}, mapToUse+1); 
            } else if (currentRange.x >= currentMapping.y && currentRange.x < currentMapping.y+currentMapping.z) {                      //  ----- mapping
                vector<Tuple> tempLocations1 = resursiveLocationsFinder(locations, {currentMapping.x+(currentRange.x-currentMapping.y), //     ---- currentrange
                    (currentMapping.y+currentMapping.z)-currentRange.x}, mapToUse+1);                                    
                vector<Tuple> tempLocations2 = resursiveLocationsFinder(locations, {currentMapping.y+currentMapping.z, 
                    currentRange.y-(currentMapping.y+currentMapping.z-currentRange.x)}, mapToUse);
                locations.insert(locations.end(), tempLocations1.begin(), tempLocations1.end());
                locations.insert(locations.end(), tempLocations2.begin(), tempLocations2.end());
                return locations;
            } else if (currentRange.x+currentRange.y-1 >= currentMapping.y && currentRange.x+currentRange.y-1 < currentMapping.y+currentMapping.z) {   //  ----- mapping
                vector<Tuple> tempLocations1 = resursiveLocationsFinder(locations, {currentMapping.x,                                                  // ---- currentrange
                    (currentRange.x+currentRange.y-1)-currentMapping.y}, mapToUse+1);                                    
                vector<Tuple> tempLocations2 = resursiveLocationsFinder(locations, {currentRange.x, currentMapping.y-currentRange.x-1},
                    mapToUse);
                locations.insert(locations.end(), tempLocations1.begin(), tempLocations1.end());
                locations.insert(locations.end(), tempLocations2.begin(), tempLocations2.end());
                return locations;                                                                                                            
            } else if (currentRange.x < currentMapping.y && currentRange.x+currentRange.y-1 > currentMapping.y+currentMapping.z) {                   //  ----- mapping
                vector<Tuple> tempLocations1 = resursiveLocationsFinder(locations, {currentRange.x, currentMapping.y-currentRange.x-1}, mapToUse);   // ------- currenrangge
                vector<Tuple> tempLocations2 = resursiveLocationsFinder(locations, {currentMapping.x, currentMapping.z}, mapToUse+1);
                vector<Tuple> tempLocations3 = resursiveLocationsFinder(locations, {currentMapping.y+currentMapping.z+1,
                    currentRange.y-((currentMapping.y+currentMapping.z)-currentRange.x)}, mapToUse);
                locations.insert(locations.end(), tempLocations1.begin(), tempLocations1.end());
                locations.insert(locations.end(), tempLocations2.begin(), tempLocations2.end());
                locations.insert(locations.end(), tempLocations3.begin(), tempLocations3.end());
                return locations;
            }
        }    
        return resursiveLocationsFinder(locations, currentRange, mapToUse+1);                                                                                                            
    }
    locations.push_back(currentRange);
    return locations;
}

int main()
{
    string line;
    int64_t sum = 0;
    ifstream myfile ("input.txt");
    vector<Tuple> seeds{};
    long long minLocation = LLONG_MAX;

    if (myfile.is_open())
    {
        int currentList = -1;
        bool skipNext = false;
        bool first = true;
        while ( getline (myfile,line) )
        {
            if (first) { // Read all initial seed ranges
                int pos = line.find(":");
                line = line.substr(pos+1, line.length()); // +1 also removes the whitespcae
                Tuple seedRange = {0,0};
                bool firstSeedRangeTupleValue = true;
                for (int i = 0; i<line.length(); i++) {
                    if (isdigit(line[i])){
                        int digitLength = 1;
                        while (isdigit(line[i+digitLength])) digitLength++;
                        if (firstSeedRangeTupleValue) { seedRange.x = stoll(line.substr(i, digitLength)); firstSeedRangeTupleValue = false; }
                        else { 
                            seedRange.y = stoll(line.substr(i, digitLength)); 
                            seeds.push_back(seedRange); 
                            firstSeedRangeTupleValue = true; 
                        }
                        i += digitLength;
                    }
                }
                first = false;
            } else { // read all maps
                if (skipNext) { skipNext = false; continue; }
                if (line == "") {
                    skipNext = true;
                    currentList += 1;
                    continue;
                }

                Triple current = {0, 0, 0};
                int currentVal = 0;
                for (int i =0; i < line.length(); i++) {
                    if (isdigit(line[i])){
                        int digitLength = 1;
                        while (isdigit(line[i+digitLength])) digitLength++;
                        if (currentVal == 0) { current.x = stoll(line.substr(i, digitLength)); currentVal++; }
                        else if (currentVal == 1) { current.y = stoll(line.substr(i, digitLength)); currentVal++; }
                        else { current.z = stoll(line.substr(i, digitLength)); currentVal++; }
                        i += digitLength;
                    }
                }
                maps[currentList].push_back(current);
            }
        }

        // for each seed range find the locations (consisting of one or more ranges of locations)
        Tuple seedRange;
        vector<Tuple> locations{};
        for (auto & seedRange : seeds) {
            vector<Tuple> tempLocations = resursiveLocationsFinder({}, seedRange, 0);
            locations.insert(locations.end(), tempLocations.begin(), tempLocations.end());
        }
        
        // select the location range with the lowest starting location
        for (auto & seedRange : locations) {
            if (seedRange.x < minLocation) minLocation = seedRange.x;
        }

        myfile.close();
        cout << minLocation;
    }

    else cout << "Unable to open file"; 
}