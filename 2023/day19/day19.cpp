#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct part {
    int x, m, a, s;
    // part(int x, int m, int a, int s) {
    //     x = x;
    //     m = m;
    //     a = a;
    //     s = s;
    // }
};

struct rule {
    char var;
    char op;
    int val;
    string dest;
    bool emptyRule;
    bool checkRule(part p) {
        if (emptyRule) return true;
        if (var == 'x') return op == '<' ? p.x < val : p.x > val; 
        if (var == 'm') return op == '<' ? p.m < val : p.m > val; 
        if (var == 'a') return op == '<' ? p.a < val : p.a > val; 
        if (var == 's') return op == '<' ? p.s < val : p.s > val; 
    }
};

part extractPart(string line) {
    part p = {0,0,0,0};
    for (int i=1; i<line.length(); i++) {
        char var = line[i];
        if (var == '}') break;
        if (var != 'x' && var != 'm' && var != 'a' && var != 's') throw ("var should be one of the variable of a part");
        
        int digitLength = 1;
        while (isdigit(line[i+2+digitLength])) digitLength++;
        int val = stoi(line.substr(i+2, digitLength));
        
        if (var == 'x') p.x = val;
        else if (var == 'm') p.m = val;
        else if (var == 'a') p.a = val;
        else if (var == 's') p.s = val;
        i += 2+digitLength;
    }
    return p;
}

vector<rule> extractRules(string line) {
    vector<rule> result{};
    for (int i = line.find('{')+1; i < line.length(); i++) {
        if ((line[i] == 'x' || line[i] == 'm' || line[i] == 'a' || line[i] == 's') && (line[i+1] == '<' || line[i+1] == '>')) {
            char var = line[i];
            char op = line[i+1];
            
            int digitLength = 1;
            while (isdigit(line[i+2+digitLength])) digitLength++;
            int val = stoi(line.substr(i+2, digitLength));

            int destLength = 1;
            while (line[i+3+digitLength+destLength] != ',') destLength++;
            string dest = line.substr(i+3+digitLength, destLength);

            result.push_back({var, op, val, dest, false});
            i += 3+digitLength+destLength;
        } else if (line[i] != '}'){
            int destLength = 1;
            while (line[i+destLength] != '}') destLength++;
            string dest = line.substr(i, destLength);

            result.push_back({' ', ' ', 0, dest, true});
            break;
        }
    }

    return result;
}

int main(){
    string line;
    ifstream myfile ("input.txt");

    // all workflows used to determine if parts are Accepted or Rejected
    map<string, vector<rule>> workflows{};

    // lists of Accepted and Rejected parts
    vector<part> accepted{};
    vector<part> rejected{};

    // Read grid from input file
    if (myfile.is_open())
    {
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            if (line[0] == '{'){
                part current = extractPart(line);

                // all workflows come first, so we can now determine where to put the part
                string dest = "in";
                while (!(dest == "A" || dest == "R")) {
                    for (int i = 0; i < workflows[dest].size(); i++) {
                        if (workflows[dest][i].checkRule(current)) {
                            dest = workflows[dest][i].dest;
                            break;
                        }
                    }
                }
                if (dest == "A") accepted.push_back(current);
                else rejected.push_back(current);
            } else if (line[0] != '\n') {
                string workFlowIdentifier = line.substr(0, line.find('{'));
                vector<rule> rules = extractRules(line);
                workflows[workFlowIdentifier] = rules;
            }
        }
        myfile.close();      
    }
    else cout << "Unable to open file"; 
    
    int accepted_sum = 0;
    for (auto p : accepted) {
        accepted_sum += p.x + p.m + p.a +p.s;
    }
    printf("part 1: %lld", accepted_sum);
    // printf("\npart 2: %lld \n", nr_interior_points_p2 + nr_boundary_points_p2);
}