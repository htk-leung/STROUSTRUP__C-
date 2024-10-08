
/* e.g. 1
int a = 7; // an int variable
const double cd = 8.7; // a double-precision floating-point constant
double sqrt(double); // a function taking a double argument and returning a double result
vector<Token> v; // a vector-of-Tokens variable
*/

#include <iostream> // we find the declaration of cout in here
using namespace std;

int f(int i);

int main()
{
    int i = 7;
    cout << f(i) << '\n';
}