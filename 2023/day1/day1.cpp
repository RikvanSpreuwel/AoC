#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string line;
    string number = "";
    int64_t total = 0;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<char> numbers{}; 
            for (int i = 0; i < line.length(); i++) {
                if (isdigit(line[i])) {
                    numbers.push_back(line[i]);
                }
            }
            // add first
            number = numbers[0];
            // add last
            number = number + numbers[numbers.size()-1];

            cout << number + "\n";
            //convert and add to total
            total = total + stoi(number);
        }
        myfile.close();
        cout << total;
    }

    else cout << "Unable to open file"; 
}