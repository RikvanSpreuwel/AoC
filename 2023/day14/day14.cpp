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

int main()
{
    string line;
    ifstream myfile ("input.txt");

    int totalLoad = 0;
    vector<vector<char>> mapOfRocks{}; 

    // the initial locations of the round rocks in columns, ordered by row location (vector = column, ints in vector = row number)
    vector<vector<int>> roundRocksPerColumn{};
    if (myfile.is_open())
    {
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            vector<char> mapRow{};
            for (int i=0; i<line.length(); i++) {
                mapRow.push_back(line[i]);
                if (currentRow == 0) roundRocksPerColumn.push_back({});
                if (line[i] == 'O') roundRocksPerColumn[i].push_back(currentRow);
            }
            mapOfRocks.push_back(mapRow);
            currentRow++;
        }
        myfile.close();

        int nrRows = mapOfRocks.size();
        
        for (int i=0; i<roundRocksPerColumn.size();i++){
            for (int j=0; j<roundRocksPerColumn[i].size();j++) {
                while(roundRocksPerColumn[i][j]>0 &&
                    mapOfRocks[roundRocksPerColumn[i][j]-1][i] != 'O' && mapOfRocks[roundRocksPerColumn[i][j]-1][i] != '#') {
                        mapOfRocks[roundRocksPerColumn[i][j]][i] = '.';
                        roundRocksPerColumn[i][j] = roundRocksPerColumn[i][j]-1;
                        mapOfRocks[roundRocksPerColumn[i][j]][i] = 'O';
                }
                totalLoad += nrRows - roundRocksPerColumn[i][j];
            }
        }

        cout << totalLoad;
    }

    else cout << "Unable to open file"; 
}