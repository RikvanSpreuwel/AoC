#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <numeric>
#include <tuple>
using namespace std;


vector<vector<int>> getNextCoordinate(vector<int> currentCoordinate, vector<int> previousCoordinate, vector<string> map) {
    vector<vector<int>> connectedPoints{};
    if (map[currentCoordinate[1]][currentCoordinate[0]] == '|') 
        connectedPoints = {{currentCoordinate[0], currentCoordinate[1]-1},{currentCoordinate[0], currentCoordinate[1]+1}};
    else if (map[currentCoordinate[1]][currentCoordinate[0]] == '-')
        connectedPoints = {{currentCoordinate[0]-1, currentCoordinate[1]},{currentCoordinate[0]+1, currentCoordinate[1]}};
    else if (map[currentCoordinate[1]][currentCoordinate[0]] == 'L')
        connectedPoints = {{currentCoordinate[0], currentCoordinate[1]-1},{currentCoordinate[0]+1, currentCoordinate[1]}};
    else if (map[currentCoordinate[1]][currentCoordinate[0]] == 'J')
        connectedPoints = {{currentCoordinate[0], currentCoordinate[1]-1},{currentCoordinate[0]-1, currentCoordinate[1]}};
    else if (map[currentCoordinate[1]][currentCoordinate[0]] == '7')
        connectedPoints = {{currentCoordinate[0], currentCoordinate[1]+1},{currentCoordinate[0]-1, currentCoordinate[1]}};
    else if (map[currentCoordinate[1]][currentCoordinate[0]] == 'F')
        connectedPoints = {{currentCoordinate[0], currentCoordinate[1]+1},{currentCoordinate[0]+1, currentCoordinate[1]}};
        
    // we return the successor that is not hte previous coordinate
    if (connectedPoints[0][0] == previousCoordinate[0] && connectedPoints[0][1] == previousCoordinate[1]) return {connectedPoints[1], currentCoordinate};
    else return {connectedPoints[0], currentCoordinate};
}

int main()
{
    string line;
    ifstream myfile ("input.txt");
    vector<string> map{};
    int startPosX = -1;
    int startPosY = -1;
    if (myfile.is_open())
    {
        int linePosStart = 0;
        while ( getline (myfile,line) )
        {
            map.push_back(line);
            if (startPosX == -1 || startPosY == -1) {
                for (int i=0;i<line.length();i++) {
                    if (line[i] == 'S') { startPosX = i; startPosY = linePosStart; }
                }
                linePosStart+=1;
            }
        }
        myfile.close();
        vector<vector<int>> secondStepStartingPositions{};
        
        // find starting directions (both ways) -- order -- left/right/top/bottom
        if (startPosX > 0 && (map[startPosY][startPosX-1] == '-' || map[startPosY][startPosX-1] == 'L' || map[startPosY][startPosX-1] == 'F')) secondStepStartingPositions.push_back({startPosX-1, startPosY});
        if (startPosX < map[0].length()-1 && (map[startPosY][startPosX+1] == '-' || map[startPosY][startPosX+1] == 'J' || map[startPosY][startPosX+1] == '7')) secondStepStartingPositions.push_back({startPosX+1, startPosY});
        if (startPosY > 0 && (map[startPosY-1][startPosX] == '|' || map[startPosY-1][startPosX] == '7' || map[startPosY-1][startPosX] == 'F')) secondStepStartingPositions.push_back({startPosX, startPosY-1});
        if (startPosY < map.size()-1 && (map[startPosY+1][startPosX] == '|' || map[startPosY+1][startPosX] == 'L' || map[startPosY+1][startPosX] == 'J')) secondStepStartingPositions.push_back({startPosX, startPosY+1});
        
        vector<vector<int>> routings{}; // 0: first way, 1: second way, 2: first way previous coordinates, 3: second way previous coordinates
        routings.push_back({secondStepStartingPositions[0][0],secondStepStartingPositions[0][1]});
        routings.push_back({secondStepStartingPositions[1][0],secondStepStartingPositions[1][1]});
        routings.push_back({startPosX, startPosY});
        routings.push_back({startPosX, startPosY});
        int nrSteps = 1;
        while (routings[0][0] != routings[1][0] || routings[0][1] != routings[1][1]) {
            vector<vector<int>> results = getNextCoordinate(routings[0], routings[2], map);
            routings[0] = results[0];
            routings[2] = results[1];
            results = getNextCoordinate(routings[1], routings[3], map);
            routings[1] = results[0];
            routings[3] = results[1];
            nrSteps += 1;
        }

        cout << nrSteps;
    }

    else cout << "Unable to open file"; 
}