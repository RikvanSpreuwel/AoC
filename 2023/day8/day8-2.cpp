#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <numeric>
using namespace std;

bool allEndWithZ(vector<string> locations) {
    for (int i=0; i<locations.size();i++){
        if (locations[i].substr(2,3) != "Z") return false;
    }
    return true;
}

int64_t lcm(int64_t first, int64_t second) {
    int64_t result = first;
    while (result % first != 0 || result % second != 0) {
        result += first;
    }
    return result;
}

int main()
{
    string line;
    ifstream myfile ("input.txt");

    int64_t nr_steps_needed = 1;
    vector<string> currentLocations{};
    string instructions = "";
    map<string, vector<string>> maps{};
    if (myfile.is_open())
    {
        bool firstLine = true;
        bool firstMap = true;
        while ( getline (myfile,line) )
        {
            if (firstLine) {instructions = line; firstLine=false;}
            else if (line != ""){
                if (line.substr(2,1) == "A") currentLocations.push_back(line.substr(0,3));
                maps[line.substr(0,3)] = {line.substr(7, 3), line.substr(12, 3)};
            }
        }
        myfile.close();


        for (int i=0; i<currentLocations.size(); i++) {
            int64_t nr_steps_loop = 0;
            while (currentLocations[i][2] != 'Z' || nr_steps_loop % instructions.length() != 0) {
                if (instructions[nr_steps_loop%instructions.length()] == 'L') currentLocations[i] = maps[currentLocations[i]][0];
                else currentLocations[i] = maps[currentLocations[i]][1];
                nr_steps_loop++;
            }

            string state = currentLocations[i];
            for (int64_t j=0; j<nr_steps_loop; j++) {
                if (instructions[j%instructions.length()] == 'L') currentLocations[i] = maps[currentLocations[i]][0];
                else currentLocations[i] = maps[currentLocations[i]][1];
            }
            if (state != currentLocations[i]) throw runtime_error(":(");

            nr_steps_needed = lcm(nr_steps_needed, nr_steps_loop);
        }

        cout << nr_steps_needed;
    }

    else cout << "Unable to open file"; 
}