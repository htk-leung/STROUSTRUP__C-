/*
Run this program with a variety of inputs:

    Small values (e.g., 2 and 3).
    Large values (larger than 127, larger than 1000).
    Negative values.
    56, 89, and 128.
    Non-integer values (e.g., 56.9 and 56.2).

You’ll find that many inputs produce “unreasonable” results when converted. 
Basically, we are trying to put a gallon into a pint pot 
(about 4 liters into a 500ml glass).
*/

/*
results:

1   : nothing for char
40  : char = (
70  : char = F
122 : char = z
126 : char = ~
128 : c == -128???
*/


#include <iostream>
using namespace std;

int main()
{
    double d = 0;
    while (cin>>d) {        // repeat the statements below as long as we type in numbers
        int i = d;          // try to squeeze a floating-point value into an integer value
        char c = i;         // try to squeeze an integer into a char
        cout << "d==" << d  // the original double
        << "\ni=="<< i       // double converted to int
        << "\nc==" << int(c)      // int value of char
        << "\nchar(" << c << ")\n";  // the char
    }

}