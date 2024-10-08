/*
Write a program that produces a simple form letter based on user input. 
Begin by typing the code from 2.1 
i. prompting a user to enter his or her first name and 
ii. writing “Hello, first_name” 
    where first_name is the name entered by the user. Then 
iii. modify your code as follows:
    change the prompt to 
    “Enter the name of the person you want to write to” and 
    change the output to “Dear first_name,”. 
    Don’t forget the comma.
*/


#include <iostream>
using namespace std;

int main()
{
    cout << "Enter the name of the person you want to write to:\n";
    string first_name; // first_name is a variable of type string
    cin >> first_name; // read characters into first_name
    cout << "Dear " << first_name << ",\n";
}