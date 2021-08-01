//
// Created by Vikash Gilja on 4/21/20.
//

#include<fstream>
#include<strstream>
#include<iostream>

using namespace std;

// Open two files and compare, tokens should match on all lines
// return 0 if true, 1 otherwise
int main(int argc, const char * argv[]) {
    if (argc != 3) return 1;  // line_level_token_match file1 file2

    ifstream file1;
    ifstream file2;

    file1.open(argv[1]);
    file2.open(argv[2]);

    if (!file1.is_open() || !file2.is_open()) return 2;  // a file (or two) didn't open

    string line1, line2;
    while (!file1.eof() && !file2.eof()) {  // if both files have another line, iterate
        getline(file1, line1);
        getline(file2, line2);
        istrstream line_stream1(line1.c_str()), line_stream2(line2.c_str());
        string word1, word2;
        while (!line_stream1.eof() && !line_stream2.eof()) { // if both lines have another word, iterate
            line_stream1 >> word1;
            line_stream2 >> word2;
            if (word1 != word2) 
            {   
                cout << "Token Mismatch" << endl;
                cout << "Line from 1: " << line1 << endl;
                cout << "Line from 2: " << line2 << endl;
                return 3; // word mismatch!
            }
        }
        
        line_stream1 >> ws;  // Consume potential whitespace at the end of lines
        line_stream2 >> ws;
        if (!line_stream1.eof() || !line_stream2.eof()) 
        {   
            cout << "Token Count Mismatch" << endl;
            cout << "Line from 1: " << line1 << endl;
            cout << "Line from 2: " << line2 << endl;
            return 4; // lines do not have the same # of tokens
        }
    }
    if(!file1.eof() || !file2.eof()) 
    {
        cout << "The number of lines is incorrect" << endl;
        return 5; // files do not have the same # of lines
    }
    return 0;
}
