/*
Write a program that prompts the user to enter two integer values. Store
these values in int variables named val1 and val2. Write your program to
determine the smaller, larger, sum, difference, product, and ratio of
these values and report them to the user.
*/


#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int val1, val2;
    bool inputfail = true;

    while(inputfail == true) { // as long as input fails continue
        cout << "Please enter 2 numbers :\n";
        cin >> val1 >> val2;
        inputfail = cin.fail();
        cin.clear();
        cin.ignore(1000, '\n');
    }
    
    cout << "smaller number is " << ((val1 <= val2) ? val1 : val2) << endl
        << "larger number is " << ((val1 >= val2) ? val1 : val2) << endl
        << "sum is " << val1 + val2 << endl
        << "difference is " << abs(val1 - val2) << endl
        << "product is " << val1 * val2 << endl
        << "ratio is " << val1 / val2 << endl;

    return 0;
}