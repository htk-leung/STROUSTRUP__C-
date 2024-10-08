#include <iostream>
#include <vector>
using namespace std;


class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token()    // make a Token from a char
        :kind('x'), value(0) { }
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

class Token_stream {
public:
    Token get(); // get a Token (get() is defined in §5.8.2)
    void putback(Token t); // put a Token back
private:
    bool full = false; // is there a Token in the buffer?
    Token buffer; // putback() saves its token here
};

Token_stream ts;

Token get_token();
double expression();
double primary();
double term();
vector<Token> tok;

//------------------------------------------------------------------------------

int main() {
    try{
        while (cin)
            cout << expression() << '\n';
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


double expression() {
    double left = term(); // read and evaluate a Term
    Token t = ts.get(); // get the next Token from the Token stream
    while (true) {
        switch (t.kind) {
            case '+':
                left += term(); // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term(); // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.putback(t); // put t back into the token stream
                return left; // finally: no more + or -; return the answer
        }
    }
}

double term() {
    double left = primary();
    Token t = ts.get(); // get the next Token from the Token stream
    while (true) {
        switch (t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/': {
                double d = primary();
                if (d == 0)
                    throw runtime_error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            default:
                ts.putback(t); // put t back into the Token stream
                return left;
        }
    }
}


double primary(){
    Token t = ts.get();
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

void Token_stream::putback(Token t){
    if (full)
        throw runtime_error("putback() into a full buffer");
    buffer = t; // copy t to buffer
    full = true; // buffer is now full
}

Token Token_stream::get(){
    if (full) { // do we already have a Token ready?
        full = false; // remove Token from buffer
        return buffer;
    }
    char ch = 0;
    if (!(cin >> ch)) // note that >> skips whitespace (space, newline, tab, etc.)
        throw runtime_error("no input");
    switch (ch) {
        case ';': // for "print"
        case 'q': // for "quit"
        case '(': case ')': case '+': case '-': case '*': case '/':
            return Token{ch}; // let each character represent itself
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':{
            cin.putback(ch); // put digit back into the input stream
            double val = 0;
            cin >> val; // read a floating-point number
            return Token{'8',val}; // let ’8’ represent "a number"
        }
        default:
            throw runtime_error("Bad token");
    }
}