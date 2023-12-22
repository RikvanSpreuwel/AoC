#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string line;
    int64_t total = 0;
    ifstream myfile ("input.txt");
    vector<string> times{};
    vector<string> distances{};
    if (myfile.is_open())
    {
        int currentList = -1;
        bool skipNext = false;
        bool first = true;
        while ( getline (myfile,line) )
        {
            bool time = false;
            bool distance = false;
            if (line.find("Time") != string::npos) {
                time = true;
            } else if (line.find("Distance") != string::npos) {
                distance = true;
            }
            for (int i = 0; i<line.length(); i++) {
                if (isdigit(line[i])){
                    int digitLength = 1;
                    while (isdigit(line[i+digitLength])) digitLength++;
                    if (time) times.push_back(line.substr(i, digitLength));
                    else if (distance) distances.push_back(line.substr(i, digitLength));
                    i += digitLength;
                }
            }
        }
        myfile.close();

        string totalRaceTime = "";
        string totalDistanceToBeat = "";
        for (int i = 0; i<times.size();i++) {
            totalRaceTime += times[i];
            totalDistanceToBeat += distances[i];
        }

        for (long long i=0; i<stoll(totalRaceTime); i++) {
            if (i*(stoll(totalRaceTime)-i) > stoll(totalDistanceToBeat)) total += 1;
        }

        cout << total;
    }

    else cout << "Unable to open file"; 
}