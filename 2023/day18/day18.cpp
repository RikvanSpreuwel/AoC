#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct coordinate {
    long long x,y;
};

coordinate computeNextVertex(char direction, coordinate previousCoordinate, long long distance) {
    if (direction == 'R') { 
        return {previousCoordinate.x+distance, previousCoordinate.y}; 
    } else if (direction == 'L') {
        return {previousCoordinate.x-distance, previousCoordinate.y};
    } else if (direction == 'D') {
        return {previousCoordinate.x, previousCoordinate.y+distance};
    } else if (direction == 'U') {
        return {previousCoordinate.x, previousCoordinate.y-distance};
    }
}

long long computeArea(vector<coordinate> boundary_vertices) {
    long long area_size = 0;
    // Compute 2*areaSize using the shoelace formula: https://en.wikipedia.org/wiki/Shoelace_formula
    for (int i=0; i<boundary_vertices.size(); i++) {
        if (i == boundary_vertices.size()-1) { // final coordinate should be used with first coordinate
            area_size += ((boundary_vertices[i].x * boundary_vertices[0].y) - (boundary_vertices[i].y * boundary_vertices[0].x));
        } else {
            area_size += ((boundary_vertices[i].x * boundary_vertices[i+1].y) - (boundary_vertices[i].y * boundary_vertices[i+1].x));
        }
    }
    // divide by half to obtain area size
    return area_size / 2;
}

// Solved using the Picks theorem https://en.wikipedia.org/wiki/Pick's_theorem 
// and shoelace formula https://en.wikipedia.org/wiki/Shoelace_formula
int main(){
    string line;
    ifstream myfile ("input.txt");

    vector<coordinate> boundary_vertices_p1{};
    vector<coordinate> boundary_vertices_p2{};
    boundary_vertices_p1.push_back({0,0});
    boundary_vertices_p2.push_back({0,0});
    int c_b_points = 1;
    long long nr_boundary_points_p1 = 0;
    long long nr_boundary_points_p2 = 0;

    // Read grid from input file
    if (myfile.is_open())
    {
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            char direction = line[0];
            int digit_length = 1;
            while (isdigit(line[2+digit_length])) digit_length++;
            int distance = stoi(line.substr(2, digit_length));
            nr_boundary_points_p1 += distance;

            boundary_vertices_p1.push_back(computeNextVertex(direction, boundary_vertices_p1[c_b_points-1], distance));
            
            string hex_color = line.substr(2+digit_length+3, 6);
            distance = stoi(hex_color.substr(0,5), 0, 16);
            nr_boundary_points_p2 += distance;
            direction = hex_color[5] == '0' ? 'R' : hex_color[5] == '1' ? 'D' : hex_color[5] == '2' ? 'L' : 'U';
            boundary_vertices_p2.push_back(computeNextVertex(direction, boundary_vertices_p2[c_b_points-1], distance));
            
            c_b_points++;
        }
        myfile.close();      
    }
    else cout << "Unable to open file"; 
    
    long long area_size_p1 = computeArea(boundary_vertices_p1);
    long long area_size_p2 = computeArea(boundary_vertices_p2);

    // Compute the number of internal points using picks theorem https://en.wikipedia.org/wiki/Pick's_theorem/
    // area = nr_interior_points + nr_boundary_points_p1 - 1
    long long nr_interior_points_p1 = area_size_p1 - nr_boundary_points_p1/2 + 1;
    long long nr_interior_points_p2 = area_size_p2 - nr_boundary_points_p2/2 + 1;

    printf("part 1: %lld", nr_interior_points_p1 + nr_boundary_points_p1);
    printf("\npart 2: %lld \n", nr_interior_points_p2 + nr_boundary_points_p2);
}