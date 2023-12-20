#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <algorithm>

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
            string currentSubstring = "";
            for (int i = 0; i < line.length(); i++) {
                if (isdigit(line[i])) {
                    numbers.push_back(line[i]);
                    currentSubstring = "";
                } else {
                    currentSubstring = currentSubstring + line[i];
                    if (currentSubstring.length() > 2 && currentSubstring.substr(currentSubstring.length()-3, currentSubstring.length()) == "one")
                        numbers.push_back('1');
                    else if (currentSubstring.length() > 2 && currentSubstring.substr(currentSubstring.length()-3, currentSubstring.length()) == "two")
                        numbers.push_back('2');
                    else if (currentSubstring.length() > 4 && currentSubstring.substr(currentSubstring.length()-5, currentSubstring.length()) == "three")
                        numbers.push_back('3');
                    else if (currentSubstring.length() > 3 && currentSubstring.substr(currentSubstring.length()-4, currentSubstring.length()) == "four")
                        numbers.push_back('4');
                    else if (currentSubstring.length() > 3 && currentSubstring.substr(currentSubstring.length()-4, currentSubstring.length()) == "five")
                        numbers.push_back('5');
                    else if (currentSubstring.length() > 2 && currentSubstring.substr(currentSubstring.length()-3, currentSubstring.length()) == "six")
                        numbers.push_back('6');
                    else if (currentSubstring.length() > 4 && currentSubstring.substr(currentSubstring.length()-5, currentSubstring.length()) == "seven")
                        numbers.push_back('7');
                    else if (currentSubstring.length() > 4 && currentSubstring.substr(currentSubstring.length()-5, currentSubstring.length()) == "eight")
                        numbers.push_back('8'); 
                    else if (currentSubstring.length() > 3 && currentSubstring.substr(currentSubstring.length()-4, currentSubstring.length()) == "nine")
                        numbers.push_back('9');
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