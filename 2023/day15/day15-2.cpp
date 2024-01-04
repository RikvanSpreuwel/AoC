#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int hashString(string step) {
    int hash = 0;
    for (int i=0;i<step.length();i++) { hash += int(step[i]); hash = hash*17; hash = hash%256; }
    return hash;
}

struct Step{
    string label;
    int focalLength;
    const bool operator==(const Step &s) const {
        return label==s.label;
    }
};

bool stepLabelEquals(Step s1, Step s2) {
    return s1.label == s2.label;
}

int main(){
    string line;
    ifstream myfile ("input.txt");
    vector<Step> boxes[256];

    int totalFocusingPower = 0;
    if (myfile.is_open())
    {
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            int currentStepStartPos = 0;
            int currentOperationPos = 0;
            for (int i=0; i<line.length(); i++) {
                if (line[i]=='-' || line[i]=='=') currentOperationPos = i-currentStepStartPos;
                if (line[i]==',' || i==line.length()-1) {
                    string step = line.substr(currentStepStartPos,i-currentStepStartPos+(i==line.length()-1 ? 1 : 0));
                    currentStepStartPos = i+1;
                    string label = step.substr(0,currentOperationPos);
                    int box = hashString(label);
                    if (step[currentOperationPos] == '-') {
                        auto it = find(boxes[box].begin(), boxes[box].end(), Step{label,0});
                        if (it != boxes[box].end()) {
                            boxes[box].erase(it);
                        }
                    } else {
                        auto it = find(boxes[box].begin(), boxes[box].end(), Step{label,0});
                        if (it != boxes[box].end()) {
                            int focalLength = stoi(step.substr(currentOperationPos+1, 1));
                            boxes[box][it-boxes[box].begin()].focalLength = focalLength;
                        } else {
                            int focalLength = stoi(step.substr(currentOperationPos+1, 1));
                            boxes[box].push_back(Step{label,focalLength});
                        }
                    }
                }
            }
        }
        myfile.close();      
    }
    else cout << "Unable to open file"; 
    
    for (int i = 0; i<256; i++) {
        int lens_position = 1;
        for (auto it = boxes[i].begin(); it != boxes[i].end(); it++){
            totalFocusingPower += (1+i)*(lens_position)*(it->focalLength);
            lens_position++;
        }
    }
    cout << totalFocusingPower;
}