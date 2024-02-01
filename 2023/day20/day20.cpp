#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>

using namespace std;


struct pulse {
    string source, target;
    bool low;
};


// list of pulses ordered on when they were sent
deque<pulse> pulses{};

class Module {
    public:
        string module_name;
        vector<string> destinations;
        Module(string n="", vector<string> d={}) { 
            module_name = n;
            destinations = d;
        };
        
    virtual void addInputModule(string name) {}
    virtual void handlePulse(pulse p) { 
        for (auto dest : destinations) {
            pulses.push_back({module_name, dest, true});
        }
    }
};

class FlipFlop: public Module {
    public: 
        bool on;
        FlipFlop(string n="", vector<string> d={}) : Module{n, d} {
            on = false;
        };
    void handlePulse(pulse p) override {
        if (p.low) {
            if (on) {
                on = false;
                for (auto dest : destinations) {
                    pulses.push_back({module_name, dest, true});
                }
            } else {
                on = true;
                for (auto dest : destinations) {
                    pulses.push_back({module_name, dest, false});
                }
            }
        }
    }
};

class Conjunction: public Module {
    public: 
        map<string, bool> pulse_per_input{}; // true == low, false == high
        Conjunction(string n="", vector<string> d={}) : Module{n, d} { 
            pulse_per_input = {};
        };
    
    void addInputModule(string name) { pulse_per_input[name] = true; }
    
    bool pulseMemoryAllHigh(){
        for (auto item : pulse_per_input) {
            if (item.second) return false;
        }
        return true;
    }

    void handlePulse(pulse p) override {
        if (p.low) {
            pulse_per_input[p.source] = true;
        } else {
            pulse_per_input[p.source] = false;
        }

        bool sendHigh = pulseMemoryAllHigh();
        for (auto dest : destinations) {
            if (sendHigh) pulses.push_back({module_name, dest, true});
            else pulses.push_back({module_name, dest, false});
        }
    }
};
vector<string> get_destinations(string line, int startingPoint) {
    vector<string> destinations{};
    for (int i = startingPoint; i<line.length(); i++) {
        destinations.push_back(line.substr(i, 2));
        i+=3;
    }
    return destinations;
}


int main(){
    string line;
    ifstream myfile ("input.txt");

    // map of modules with module_names as keys
    map<string, FlipFlop> flipFlopModules{};
    map<string, Conjunction> conjunctionModules{};
    Module broadcaster;

    int totalNrLowPulsesSent = 0;
    int totalNrHighPulsesSent = 0;

    if (myfile.is_open())
    {
        int currentRow = 0;
        while ( getline (myfile,line) )
        {   
            if (line[0] == '%') { // flip flop

                string name = line.substr(1, 2);
                vector<string> destinations = get_destinations(line, 7);
                flipFlopModules[name] = FlipFlop(name, destinations);
            } else if (line[0] == '&') { // conjunction
                string name = line.substr(1, 2);
                vector<string> destinations = get_destinations(line, 7);
                conjunctionModules[name] = Conjunction(name, destinations);
            } else { // broadcaster
                vector<string> destinations = get_destinations(line, 15);
                broadcaster = Module("broadcaster", destinations);
            }
        }
        myfile.close();      
    }
    else cout << "Unable to open file"; 
    

    // for each module, check if any of the distinations are conjunction modules, 
    // if so, add module name to conjunction module's input list
    for (auto item : flipFlopModules) {
        for (string destination : item.second.destinations) {
            if (conjunctionModules.find(destination) != conjunctionModules.end())
                conjunctionModules[destination].addInputModule(item.first);
        }
    }
    for (auto item : conjunctionModules) {
        for (string destination : item.second.destinations) {
            if (conjunctionModules.find(destination) != conjunctionModules.end())
                conjunctionModules[destination].addInputModule(item.first);
        }
    }

    for (int i=0; i<1000; i++) {
        pulses.push_back({"", "broadcaster", true});
        while (pulses.size()>0) {
            pulse current = pulses.front();
            pulses.pop_front();
            if (current.low) totalNrLowPulsesSent++;
            else totalNrHighPulsesSent++;
            if (flipFlopModules.find(current.target) != flipFlopModules.end()) flipFlopModules[current.target].handlePulse(current);
            else if (conjunctionModules.find(current.target) != conjunctionModules.end()) conjunctionModules[current.target].handlePulse(current);
            else if (current.target == "broadcaster") broadcaster.handlePulse(current);
        }
    }
    
    printf("part 1: %lld", totalNrHighPulsesSent*totalNrLowPulsesSent);
    // Part 2 skipped
}