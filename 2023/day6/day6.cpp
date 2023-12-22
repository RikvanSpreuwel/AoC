#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string line;
    int64_t total = 1;
    ifstream myfile ("input.txt");
    vector<int> times{};
    vector<int> distances{};
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
                    if (time) times.push_back(stoi(line.substr(i, digitLength)));
                    else if (distance) distances.push_back(stoi(line.substr(i, digitLength)));
                    i += digitLength;
                }
            }
        }
        myfile.close();

        for (int i = 0; i<times.size();i++) {
            int nrWaysToWin = 0;
            for (int j=0; j<times[i];j++) {
                // j = speed
                // times[i]-j = nr milliseconds driving
                if (j*(times[i]-j) > distances[i]) nrWaysToWin++;
            }
            total = total * nrWaysToWin;
        }

        cout << total;
    }

    else cout << "Unable to open file"; 
}