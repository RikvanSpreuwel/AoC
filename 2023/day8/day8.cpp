#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
using namespace std;

int main()
{
    string line;
    ifstream myfile ("input.txt");

    int64_t nr_steps = 0;
    string currentLocation = "AAA";
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
                maps[line.substr(0,3)] = {line.substr(7, 3), line.substr(12, 3)};
            }
        }
        myfile.close();

        while (currentLocation != "ZZZ") {
            for (int i=0; i<instructions.length(); i++) {
                if (instructions[i] == 'L') currentLocation = maps[currentLocation][0];
                else currentLocation = maps[currentLocation][1];
                nr_steps++;
                if (currentLocation == "ZZZ") break;
            }
        }

        cout << nr_steps;
    }

    else cout << "Unable to open file"; 
}