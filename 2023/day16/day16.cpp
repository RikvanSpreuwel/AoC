#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

enum Direction {
    Left, Right, Up, Down
};

struct gridCel {
    char celContent;
    bool energized = false;
    // for each cell we keep track of each direction that is explored
    // if a direction has been explored before, it can be skipped when repeated
    bool left, right, up, down = false;
    gridCel(char content) {
        celContent = content;
    }
};

vector<vector<gridCel>> grid{};

// Check if this direction was already explored in this cell
bool directionAlreadyExplored(gridCel cel, Direction direction) {
    if (direction == Right && cel.right) return true;
    if (direction == Left && cel.left) return true;
    if (direction == Up && cel.up) return true;
    if (direction == Down && cel.down) return true;
    return false;
}

// check if the next step moves the beam out of the grid
bool beamOutOfGrid(int rowId, int columnId, Direction direction) {
    if (columnId < 0 || rowId < 0 || columnId >= grid[0].size() || rowId >= grid.size()) return true;
    return false;
}

void exploreBeam(int rowId, int columnId, Direction direction) {
    if (!beamOutOfGrid(rowId, columnId, direction) && !directionAlreadyExplored(grid[rowId][columnId], direction)) {
        grid[rowId][columnId].energized = true;
        if (direction == Right) {
            grid[rowId][columnId].right = true;
            if (grid[rowId][columnId].celContent == '.' || grid[rowId][columnId].celContent == '-') {
                exploreBeam(rowId, columnId+1, Right);
            } else if (grid[rowId][columnId].celContent == '/') {
                exploreBeam(rowId-1, columnId, Up);
            } else if (grid[rowId][columnId].celContent == '\\') {
                exploreBeam(rowId+1, columnId, Down);
            } else if (grid[rowId][columnId].celContent == '|') {
                exploreBeam(rowId-1, columnId, Up);
                exploreBeam(rowId+1, columnId, Down);
            }
        } else if (direction == Left) {
            grid[rowId][columnId].left = true;
            if (grid[rowId][columnId].celContent == '.' || grid[rowId][columnId].celContent == '-') {
                exploreBeam(rowId, columnId-1, Left);
            } else if (grid[rowId][columnId].celContent == '/') {
                exploreBeam(rowId+1, columnId, Down);
            } else if (grid[rowId][columnId].celContent == '\\') {
                exploreBeam(rowId-1, columnId, Up);
            } else if (grid[rowId][columnId].celContent == '|') {
                exploreBeam(rowId-1, columnId, Up);
                exploreBeam(rowId+1, columnId, Down);
            }
        } else if (direction == Up) {
            grid[rowId][columnId].up = true;
            if (grid[rowId][columnId].celContent == '.' || grid[rowId][columnId].celContent == '|') {
                exploreBeam(rowId-1, columnId, Up);
            } else if (grid[rowId][columnId].celContent == '/') {
                exploreBeam(rowId, columnId+1, Right);
            } else if (grid[rowId][columnId].celContent == '\\') {
                exploreBeam(rowId, columnId-1, Left);
            } else if (grid[rowId][columnId].celContent == '-') {
                exploreBeam(rowId, columnId+1, Right);
                exploreBeam(rowId, columnId-1, Left);
            }
        } else if (direction == Down) {
            grid[rowId][columnId].down = true;
            if (grid[rowId][columnId].celContent == '.' || grid[rowId][columnId].celContent == '|') {
                exploreBeam(rowId+1, columnId, Down);
            } else if (grid[rowId][columnId].celContent == '/') {
                exploreBeam(rowId, columnId-1, Left);
            } else if (grid[rowId][columnId].celContent == '\\') {
                exploreBeam(rowId, columnId+1, Right);
            } else if (grid[rowId][columnId].celContent == '-') {
                exploreBeam(rowId, columnId+1, Right);
                exploreBeam(rowId, columnId-1, Left);
            }
        }
    }
}


// Store the grid, then recursively process each beam from a gridCel perspective
// and store for each gridCel which direction has already been explored,
// thereby avoiding the redundant processing of the same beam multiple times
int main(){
    string line;
    ifstream myfile ("input.txt");

    int nrCellsEnergized = 0;
    
    // Read grid from input file
    if (myfile.is_open())
    {
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            vector<gridCel> gridRow{};
            for (int i=0; i<line.length(); i++) {
                gridRow.push_back(gridCel(line[i]));
            }
            grid.push_back(gridRow);
        }
        myfile.close();      
    }
    else cout << "Unable to open file"; 
    
    // starting from top-left going right, recursively go through the grid
    // Keeping track of which direction has already been explored
    exploreBeam(0,0, Right);

    // iterate over all cells of the grid once, counting the number of energized grids
    for (auto row : grid) {
        for (auto cel : row) {
            if (cel.energized) nrCellsEnergized++;
        }
    }
    cout << nrCellsEnergized;
}