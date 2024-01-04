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

int hashStep(string step) {
    int hash = 0;
    for (int i=0;i<step.length();i++) { hash += int(step[i]); hash = hash*17; hash = hash%256; }
    return hash;
}

int main(){
    string line;
    ifstream myfile ("input.txt");


    int sumOfHashing = 0;
    if (myfile.is_open())
    {
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            int currentStepStartPos = 0;
            for (int i=0; i<line.length(); i++) {
                if (line[i]==',' || i==line.length()-1) {
                    string step = line.substr(currentStepStartPos,i-currentStepStartPos+(i==line.length()-1 ? 1 : 0));
                    sumOfHashing += hashStep(step);
                    currentStepStartPos = i+1;
                }
            }
        }
        myfile.close();      
    }
    else cout << "Unable to open file"; 
    
    cout << sumOfHashing;
}