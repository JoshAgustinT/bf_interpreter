/*
Joshua Tlatelpa-Agustin
9/10/24
bf language interpreter
written for adv compilers course
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int tape_size = 1000000000;
char tape[tape_size];
//Set our position to the middle of tape
int tape_position = tape_size/2; 

int instruction_pointer;

bool debug = false;

void init_tape(){
    for(auto token: tape)
    token = 0;
}

void bf_interpreter(char token){
    if(debug)
    cout <<token;
     switch (token) {
        case '>':
            if(debug)
            cout << "Move the pointer to the right" << endl;
            tape_position++;
            break;
        case '<':
            if(debug)
            cout << "Move the pointer to the left" << endl;
            tape_position--;
            break;
        case '+':
            if(debug)
            cout << "Increment the value at the pointer" << endl;
            tape[tape_position] += 1;
            break;
        case '-':
            if(debug)
            cout << "Decrement the value at the pointer" << endl;
            tape[tape_position] -= 1;
            break;
        case '.':
            if(debug)
            cout << "Output the value at the pointer" << endl;
            cout<< tape[tape_position];
            break;
        case ',':
            if(debug)
            cout << "Input a value and store it at the pointer" << endl;
            char nextByte;
            cin.get(nextByte);
            tape[tape_position] =nextByte;
            break;
        case '[':
            if(debug)
            cout<<" jump to the matching ] instruction if the current value is zero"<<endl;
            break;
        case ']':
            if(debug)
            cout<< "jump to the matching [ instruction if the current value is not zero" <<endl;
            break;
        default:
            break;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout<< "No input file?"<<endl;
        return 1;
    }
    if(argv[2] != NULL && string(argv[2])=="-d"){
        cout << "debug mode enabled."<<endl;
        debug = true;
    }
     ifstream inputFile(argv[1], ios::binary);  // Open file in binary mode
    if (!inputFile) {
        cout << "Couldn't open file: " << argv[1] << endl;
        return 1;
    }
    // Read the file into a vector of chars
    vector<char> fileContents((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    // Close the file
    inputFile.close();

    init_tape();
    
    for (int i = 0; i< fileContents.size(); i++) {    
        char ch = fileContents[i];

        // jump to the matching ] instruction if the current value is zero
        if(ch == '[' ){
            if(tape[tape_position]== 0)
           {
             int count = 1;
             while( count != 0 ){
                i++;
                if(fileContents[i] == '[')
                count++;

                if(fileContents[i] == ']')
                count--;
            }
           }}

        // ]- jump to the matching [ instruction if the current value is not zero
        else if(ch == ']' ){
            if(tape[tape_position]!= 0){
            int count = 1;
             while(count != 0 ){
                i--;
                if(fileContents[i] == ']')
                count++;

                if(fileContents[i] == '[')
                count--;
            }       
            }}
        else 
         bf_interpreter(ch);
    }
    return 0;
}
