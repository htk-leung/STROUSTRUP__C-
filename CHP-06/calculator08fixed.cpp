
/*
Given:
- calculator08buggy.cpp
Improvements:
- used cin.get instead of cin to account for spaces
- differential treatment for '\n' and ' '
- new line when only input is ';;;;;;;'
- multiple inputs
- fmod(): account for rounding errors when answer should be 0
*/

#include "std_lib_facilities.h"

//-----------------------------------------------------------------------
// define Token as temp storage of input chars
struct Token {
	char kind;
	double value;
	string name;
    Token() :kind(0) { } // default constructor
	Token(char ch) :kind(ch), value(0) { } // constructor with kind input
	Token(char ch, double val) :kind(ch), value(val) { } // constructor for char & double
    Token(char ch, string n) :kind{ch}, name{n} { } // added ability to initialize with string
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }
	void ignore(char c); // ignore input in stream up to char c + correction, missing 'c'
};

// define t.kind with chars
const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char space = 'X';
const char endline = '\n';

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin.get(ch); // <<< where cin is stuck at at the end of the line
	switch (ch) {
		case '\n':
			return Token(endline);
		case ' ':
		case ';':
			return Token(print);
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
            return Token(ch);
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':{	
            cin.unget();
            double val;
            cin >> val;
            return Token(number, val);
		}
        default:
            if (isalpha(ch)) {
                string s;
                s += ch;
                while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) 
                    s += ch; // logic error: added '+'
                cin.unget();
                if (s == "let") 
                    return Token(let);
                if (s == "quit") 
                    return Token(quit); // logic error: changed 'name' to 'quit'
                return Token(name, s);
            }
            error("Bad token");
	}
	return Token(ch);
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

//-----------------------------------------------------------------------
// variable struct to store and access values with a name

struct Variable { 
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) 
            return names[i].value;
	error("get: undefined name " + s);
	return 0;
}

void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name " + s);
}

bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

//-----------------------------------------------------------------------
// parsing input from stream

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
        case '(': {	
			double d = expression();
            t = ts.get();
            if (t.kind != ')') 
				error("')' expected"); // logic fix (2): change '(' to ')'
			return d; // logic fix (1): missing break + return value to term()
        }
        case '-':
            return -primary();
        case number:
            return t.value;
        case name:
            return get_value(t.name);
        default:
            error("primary expected");
	}
	return 0;
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/': {	
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%': { // missing function for %
			double d = primary();
			if (d == 0)
				error("%:divide by zero");
			left = fmod(left, d);
			if (left < 1e-10) 	// account for rounding errors when answer should be 0
				left = 0;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

//-----------------------------------------------------------------------
// creation and storage of new variables

double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') 
        error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) 
        error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') 
        error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

//-----------------------------------------------------------------------
// what to do after error is thrown

void clean_up_mess()
{
	ts.ignore(print);
}

void remove_print(Token t)
{
	while(t.kind == print)		
		t= ts.get();			// added 't ='
}

//-----------------------------------------------------------------------
// calculator function

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while (true) {
		try {
			cout << prompt;
			Token t = ts.get();
			if (t.kind == print) 		// get rid of extra ;;;;;;		
				remove_print(t);			
			if (t.kind == quit) return;
			while (t.kind != endline) {		// added while loop to account for multiple input
				ts.unget(t);
				cout << result << statement() << endl;
				t = ts.get();
				if (t.kind == print)		
					remove_print(t);
			}
		}
		catch (exception& e) {
			cerr << e.what() << endl;
			clean_up_mess();
		}
	}
}

int main()

try {
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}