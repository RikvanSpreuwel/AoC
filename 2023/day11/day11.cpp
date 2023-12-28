#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <numeric>
#include <tuple>
using namespace std;


int main()
{
    string line;
    ifstream myfile ("input.txt");
    vector<vector<int>> coordinatesOfGalaxies{};
    vector<bool> isColumnEmpty{};
    vector<int> emptyRowIds{};
    vector<int> emptyColumnIds{};
    int currentRow = 0;

    long long totalShortestPaths = 0;
    if (myfile.is_open())
    {
        bool first = true;
        bool emptyRow = true;
        while ( getline (myfile,line) )
        {
            vector<char> row{};
            for (int i = 0; i<line.length(); i++) {
                row.push_back(line[i]);
                if (first) isColumnEmpty.push_back(line[i]=='.');
                if (line[i]=='#') { emptyRow = false; isColumnEmpty[i]=false; coordinatesOfGalaxies.push_back({i, currentRow}); }
            }

            // keep track of which rows are empty of galaxies
            if (emptyRow) emptyRowIds.push_back(currentRow);
            emptyRow = true;
            currentRow +=1;
            first = false;
        }
        myfile.close();

        // note empty columns
        for (int i=0; i<isColumnEmpty.size(); i++) {
            if (isColumnEmpty[i]) emptyColumnIds.push_back(i);
        }

        // for each galaxy coordinate, add 1 x/y coordinate for each empty column/row with a x/y coordinate smaller 
        // than the galaxy coordinate (i.e., the expansion of the image)
        for (int i = 0; i<coordinatesOfGalaxies.size(); i++) {
            int nrPrecedingEmptyColumns = 0;
            int nrPrecedingEmptyRows = 0;

            for (int j = 0; j<emptyColumnIds.size();j++) {
                if (emptyColumnIds[j] < coordinatesOfGalaxies[i][0]) nrPrecedingEmptyColumns++;
                else break;
            }
            for (int j = 0; j<emptyRowIds.size();j++) {
                if (emptyRowIds[j] < coordinatesOfGalaxies[i][1]) nrPrecedingEmptyRows++;
                else break;
            }
            coordinatesOfGalaxies[i][0] += (nrPrecedingEmptyColumns*999999); //NOTE: change the rightmost value for different expansion sizes
            coordinatesOfGalaxies[i][1] += (nrPrecedingEmptyRows*999999); //NOTE: change the rightmost value for different expansion sizes
        }

        // for each coordinate, calculate the shortest distance with the other coordinates, sum these shortest paths
        for (int i=0; i<coordinatesOfGalaxies.size();i++) {
            for (int j=i+1; j<coordinatesOfGalaxies.size();j++) {
                totalShortestPaths += abs(coordinatesOfGalaxies[i][0] - coordinatesOfGalaxies[j][0]) + abs(coordinatesOfGalaxies[i][1] - coordinatesOfGalaxies[j][1]);
            }
        }
        
        cout << totalShortestPaths;
    }

    else cout << "Unable to open file"; 
}