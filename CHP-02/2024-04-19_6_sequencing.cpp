/*
Write a program that prompts the user to enter three integer values, and
then outputs the values in numerical sequence separated by commas. So,
if the user enters the values 10 4 6, the output should be 4, 6, 10. If two
values are the same, they should just be ordered together. So, the input 4
5 4 should give 4, 4, 5.
*/

#include <iostream>
using namespace std;

int main() {
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;

    bool inputfail = true;
    while(inputfail == true) {
        cout << "Please enter 3 integer values:\n";
        cin >> val1 >> val2 >> val3;
        inputfail = cin.fail();
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if(val1 <= val2 && val1 <= val3) {
        cout << val1 << ' ';
        if (val2 <= val3) cout << val2 << ' ' << val3;
        else cout << val3 << ' ' << val2;
    } 
    else if (val2 <= val3) {
        cout << val2 << ' ';
        if (val1 <= val3) cout << val1 << ' ' << val3;
        else cout << val3 << ' ' << val1;
    }
    else {
        cout << val3 << ' ';
        if (val1 <= val2) cout << val1 << ' ' << val2;
        else cout << val2 << ' ' << val1;
    }
}