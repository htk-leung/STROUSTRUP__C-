#include <iostream>
#include <vector>
using namespace std;


class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

Token get_token();
double expression();
double primary();
double term();
vector<Token> tok;

//------------------------------------------------------------------------------

int main() {

    try {
        while (cin)
            cout << '=' << expression() << '\n';
    }
    catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
    catch (...) {
        cerr << "exception \n";
        return 2;
    }
}

//------------------------------------------------------------------------------

Token get_token()    // read a token from cin
{
    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
        //not yet   case ';':    // for "print"
        //not yet   case 'q':    // for "quit"
        case '(': case ')': case '+': case '-': case '*': case '/':
            return Token(ch);        // let each character represent itself
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
            return Token('8', val);   // let '8' represent "a number"
        }
        default:
            throw runtime_error("Bad token");
    }
}

double expression()
{
    double left = term(); // read and evaluate a Term
    Token t = get_token(); // get the next token
    while (true) {
        switch (t.kind) {   // <<< PROBLEM: when token isn't + / - the whole term is thrown out!
            case '+':
                left += term(); // evaluate Term and add
                t = get_token();
                break;
            case '-':
                left -= term(); // evaluate Term and subtract
                t = get_token();
                break;
            default:
                return left; // finally: no more + or -; return the answer
        }
    }
}

double term()
{
    double left = primary();
    Token t = get_token();
    while (true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = get_token();
                break;
            case '/': {
                double d = primary();
                if (d == 0)
                    throw runtime_error("divide by zero");
                left /= d;
                t = get_token();
                break;
            }
            default:
                return left;
        }
    }
}


double primary()
{
    Token t = get_token();
    switch (t.kind) {
        case '(': { // handle ’(’ expression ’)’ 
            double d = expression();
            t = get_token();
            if (t.kind != ')')
                throw runtime_error("')' expected");
            return d;
        }
        case '8': // we use ’8’ to represent a number
            return t.value; // return the number’s value
        default:
            throw runtime_error("primary expected");
    }
}