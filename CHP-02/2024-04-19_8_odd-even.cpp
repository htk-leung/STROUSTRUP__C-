/*
Write a program to test an integer value to determine if it is odd or even.
As always, make sure your output is clear and complete. In other words,
don’t just output yes or no. Your output should stand alone, like The
value 4 is an even number.
*/

#include <iostream>
using namespace std;

int main() {
    int val = 0;
    bool inputfail = true;

    while(inputfail == true) {
        cout << "Please enter an integer to check if it is odd or even:\n";
        cin >> val;

        inputfail = cin.fail();
        cin.clear();
        cin.ignore(1000, '\n');
    }

    int remainder = val % 2;
    cout << val << " is an " 
        << ((remainder == 1) ? "odd" : "even") << " number.\n";

    return 0;
}