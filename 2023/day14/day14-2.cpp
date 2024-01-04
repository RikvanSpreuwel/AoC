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

struct rockCoordinate {
    int column,row;
    const bool operator==(const rockCoordinate &t) const {
        return column == t.column && row == t.row;
    }
    // const bool operator<(const rockCoordinate &t) const {
        // return !(x == t.x && y ==t.y && z == t.z);
    // }
};

bool sort_north(rockCoordinate r1, rockCoordinate r2) {
    if (r1.column==r2.column) return r1.row < r2.row;
    else return r1.column < r2.column;
}

bool sort_west(rockCoordinate r1, rockCoordinate r2) {
    if (r1.row==r2.row) return r1.column < r2.column;
    else return r1.row < r2.row;
}

bool sort_south(rockCoordinate r1, rockCoordinate r2) {
    if (r1.column==r2.column) return r1.row > r2.row;
    else return r1.column < r2.column;
}

bool sort_east(rockCoordinate r1, rockCoordinate r2) {
    if (r1.row==r2.row) return r1.column > r2.column;
    else return r1.row < r2.row;
}

bool spaceIsFree(char space) {
    return space != 'O' && space != '#';
}

int determineLoad(vector<rockCoordinate> roundRockPositions, int nrRows) {
    int currentLoad = 0;
    for (auto rock : roundRockPositions) currentLoad += (nrRows-rock.row);
    return currentLoad;
}

int main(){
    string line;
    ifstream myfile ("input.txt");

    int totalLoad = 0;
    // [row][column]
    vector<vector<char>> mapOfRocks{}; 

    // x,y positions of the round rocks 
    vector<rockCoordinate> roundRockPositions{};
    if (myfile.is_open())
    {
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            vector<char> mapRow{};
            for (int i=0; i<line.length(); i++) {
                mapRow.push_back(line[i]);
                if (line[i] == 'O') roundRockPositions.push_back(rockCoordinate{i,currentRow});
            }
            mapOfRocks.push_back(mapRow);
            currentRow++;
        }
        myfile.close();      
    }
    else cout << "Unable to open file"; 
    

    int nrRows = mapOfRocks.size();
    int nrColumns = mapOfRocks[0].size();
    
    // history to track to find a cycle of tilting
    vector<vector<rockCoordinate>> roundRockPositionsHistory{};
    roundRockPositionsHistory.push_back(roundRockPositions);
    vector<int> loadsPerCycle{};
    loadsPerCycle.push_back(determineLoad(roundRockPositions, nrRows));
    
    int nrTiltingCyclesPerformed = 0;
    bool cycleFound = false;
    while(!cycleFound) {
        // Roll north
        sort(roundRockPositions.begin(), roundRockPositions.end(), sort_north);
        for (int i=0; i<roundRockPositions.size();i++){
            int nrSpacesMoved = 0;
            while(roundRockPositions[i].row>nrSpacesMoved 
                && spaceIsFree(mapOfRocks[roundRockPositions[i].row-(nrSpacesMoved+1)][roundRockPositions[i].column])) nrSpacesMoved++;

            mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column] = '.'; 
            roundRockPositions[i].row -= nrSpacesMoved;
            mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column] = 'O';   
            
        }

        // Roll west
        sort(roundRockPositions.begin(), roundRockPositions.end(), sort_west);
        for (int i=0; i<roundRockPositions.size();i++){
            int nrSpacesMoved = 0;
            while(roundRockPositions[i].column>nrSpacesMoved 
                && spaceIsFree(mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column-(nrSpacesMoved+1)])) nrSpacesMoved++;

            mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column] = '.'; 
            roundRockPositions[i].column -= nrSpacesMoved;
            mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column] = 'O';   
            
        }

        // Roll south
        sort(roundRockPositions.begin(), roundRockPositions.end(), sort_south);
        for (int i=0; i<roundRockPositions.size();i++){
            int nrSpacesMoved = 0;
            while(roundRockPositions[i].row+nrSpacesMoved<nrRows-1 
                && spaceIsFree(mapOfRocks[roundRockPositions[i].row+(nrSpacesMoved+1)][roundRockPositions[i].column])) nrSpacesMoved++;

            mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column] = '.'; 
            roundRockPositions[i].row += nrSpacesMoved;
            mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column] = 'O';   
            
        }

        // Roll east
        sort(roundRockPositions.begin(), roundRockPositions.end(), sort_east);
        for (int i=0; i<roundRockPositions.size();i++){
            int nrSpacesMoved = 0;
            while(roundRockPositions[i].column+nrSpacesMoved<nrColumns-1
                && spaceIsFree(mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column+(nrSpacesMoved+1)])) nrSpacesMoved++;

            mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column] = '.'; 
            roundRockPositions[i].column += nrSpacesMoved;
            mapOfRocks[roundRockPositions[i].row][roundRockPositions[i].column] = 'O';   
            
        }

        nrTiltingCyclesPerformed++;
        int currentLoad = determineLoad(roundRockPositions, nrRows);
        cout << to_string(nrTiltingCyclesPerformed) << " : " << to_string(currentLoad) << "\n";

        loadsPerCycle.push_back(currentLoad);
        auto found = find(roundRockPositionsHistory.begin(), roundRockPositionsHistory.end(), roundRockPositions); 
        if (found != roundRockPositionsHistory.end()) {
            cycleFound = true;
            // index of the rock positions matching the last list of rock positions
            int index = found - roundRockPositionsHistory.begin(); 
            int cycleLength = nrTiltingCyclesPerformed - index;
            
            // index of the rock positions referring to the positions of the rocks after 10000000000 cycles
            int afterXCycles = ((1000000000-index)%cycleLength)+index;
            int loadAtWantedTimePoint = loadsPerCycle[afterXCycles];
            
            cout << "FOUND!" << "\n";
            cout << index << "\n";
            cout << loadAtWantedTimePoint << "\n";
        }
        roundRockPositionsHistory.push_back(roundRockPositions);
    }
}