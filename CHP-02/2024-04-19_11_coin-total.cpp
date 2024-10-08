/*
Write a program that prompts the user to enter some number of pennies
(1-cent coins), nickels (5-cent coins), dimes (10-cent coins), quarters
(25-cent coins), half dollars (50-cent coins), and one-dollar coins (100-
cent coins). Query the user separately for the number of each size coin,
e.g., “How many pennies do you have?” Then your program should
print out something like this:
Click here to view code image
You have 23 pennies.
You have 17 nickels.
You have 14 dimes.
You have 7 quarters.
You have 3 half dollars.
The value of all of your coins is 573 cents.
Make some improvements: if only one of a coin is reported, make the
output grammatically correct, e.g., 14 dimes and 1 dime (not 1 dimes).
Also, report the sum in dollars and cents, i.e., .73 instead of 573 cents.
*/

#include <iostream>
using namespace std;

int main() {
    int penn = 0;
    int nick = 0;
    int dime = 0;
    int quar = 0;
    int hdol = 0;
    int doll = 0;
    bool inputfail = true;

    while(inputfail == true) {
        cout << "How many pennies do you have? ";
        cin >> penn;

        cout << "How many nickels do you have? ";
        cin >> nick;

        cout << "How many dimes do you have? ";
        cin >> dime;

        cout << "How many quarters do you have? ";
        cin >> quar;

        cout << "How many half dollars do you have? ";
        cin >> hdol;

        cout << "How many dollars do you have? ";
        cin >> doll;

        inputfail = cin.fail();
        cin.clear();
        cin.ignore(1000, '\n');
    }

    int total = penn + 5 * nick + 10 * dime + 25 * quar + 50 * hdol + 100 * doll;
    int dollar = total / 100;
    int cents = total - dollar * 100; 
    cout << "The value of all of your coins is " 
        << dollar << " dollar(s) and " << cents << " cent(s).\n";

    return 0;
}