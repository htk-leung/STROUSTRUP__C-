/*

Get the “repeated word detection program” to run. 
Test it with the sentence

She she laughed "he he he!" because what he did did not look 
very very good good.

How many repeated words were there? Why? 
What is the definition of word used here? 
What is the definition of repeated word? 
(For example, is She she a repetition?)

>> She she is NOT a repetition
>> good good. is NOT a repetition
>> "he != he != he!" therefore not counted either!

result: only "did" and "very" are counted

*/

#include <string>
#include <iostream>
using namespace std;

/*
int main()
{
    string previous;                    // previous word; initialized to ""
    string current;                     // current word
    while (cin >> current) {            // read a stream of words
        if (previous == current) {      // check if the word is the same as last
            cout << "repeated word: " 
                << current 
                << '\n';
        }
        previous = current;
    }
}
*/

int main()
{
    string previous;                    // previous word; initialized to ""
    string current;                     // current word
    string prevrep;                     // previous repeated word
    int rep = 0;

    while (cin >> current) {            // read a stream of words
        if (previous == current && previous != prevrep) {
            rep++;
            cout << "repeated word " << rep << ": "
                << current << endl;
        }
        previous = current;
    }
}