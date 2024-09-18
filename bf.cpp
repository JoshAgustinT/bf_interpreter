/*
Joshua Tlatelpa-Agustin
9/10/24
bf language interpreter
written for adv compilers course
last edit - 9/17/24
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
using namespace std;

const int tape_size = 10000;
char tape[tape_size];
int tape_position = tape_size / 2; // Set our position to the middle of tape

vector<char> program_file;

bool debug = false;
bool profiler_mode = false;
bool verbose_output = false;

int count_greaterthan = 0;
int count_lessthan = 0;
int count_plus = 0;
int count_minus = 0;
int count_period = 0;
int count_comma = 0;
int count_leftbracket = 0;
int count_rightbracket = 0;

// index, count
map<int, int> loop_index_dict;
// loop string, count
map<string, int> loop_string_dict;

void init_tape()
{
    for (auto token : tape)
        token = 0;
}

int bf_interpreter(char token, int i)
{

    if (debug)
        cout << token;

    switch (token)
    {
    case '>':
        if (profiler_mode)
            count_greaterthan++;

        tape_position++;
        break;
    case '<':
        if (profiler_mode)
            count_lessthan++;

        tape_position--;
        break;
    case '+':
        if (profiler_mode)
            count_plus++;

        tape[tape_position] += 1;
        break;
    case '-':
        if (profiler_mode)
            count_minus++;

        tape[tape_position] -= 1;
        break;
    case '.':

        if (profiler_mode)
            count_period++;

        cout << tape[tape_position];
        break;
    case ',':

        if (profiler_mode)
            count_comma++;

        char nextByte;
        cin.get(nextByte);
        tape[tape_position] = nextByte;
        break;
    case '[':
        if (profiler_mode)
            count_leftbracket++;

        if (tape[tape_position] == 0)
        {

            int count = 1;
            while (count != 0)
            {
                i++;
                if (program_file[i] == '[')
                    count++;

                if (program_file[i] == ']')
                    count--;
            }
            i--; // go back one, since the interpreter for loop will i++;
        }
        // we're going into the loop, ie +1 use of this loop
        else
        {
            if (profiler_mode)
            {
                // adding count to loop_index_dict
                if (loop_index_dict.find(i) != loop_index_dict.end())
                    loop_index_dict[i] = loop_index_dict[i] + 1;
                else
                    loop_index_dict[i] = 1;
            }
        }

        break;
    case ']':

        if (tape[tape_position] != 0)
        {
            int count = 1;
            while (count != 0)
            {
                i--;
                if (program_file[i] == ']')
                    count++;

                if (program_file[i] == '[')
                    count--;
            };
            i--; // go back one, since the interpreter for loop will i++;
        }

        if (profiler_mode)
            count_rightbracket++;

        break;
    default:
        // non bf instruction, so we ignore
        break;
    } // end switch

    return i;
}

/*
Returns associated loop with given index of [
ie, [*.>><], given program index of [, will return [*.>><]
*/
string get_loop_string(int program_index)
{
    string sb = ""; // sb short for stringbuilder :]
    if (program_file[program_index] == '[')
    {
        sb += "[";
        int count = 1;
        while (count != 0)
        {
            program_index++;

            if (program_file[program_index] == '[')
                count++;

            if (program_file[program_index] == ']')
                count--;

            switch (program_file[program_index])
            {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']':
                // Code for handling valid characters
                sb += program_file[program_index];
                break;
            default:
                // Code for invalid character or do nothing
                // sb += program_file[program_index];
                break;
            }
        }

        return sb;
    }

    cout << "couldn't find '[' in get_loop_string(), wrong index?? ";
    return nullptr;
}

/*
Checks if input string is a simple loop
*/
bool is_simple_loop(string loop_string)
{
    bool answer = true;
    int net_cell_change = 0;
    int net_loop_cell_value = 0;
    // iterate over body of loop ie -> [...]
    for (int i = 1; i < loop_string.length() - 1; i++)
    {
        char token = loop_string[i];

        if (token == ',')
        {
            answer = false;
            break;
        }
        if (token == '.')
        {
            answer = false;
            break;
        }
        if (token == '[')
        {
            answer = false;
            break;
        }
        if (token == ']')
        {
            answer = false;
            break;
        }
        if (token == '<')
            net_cell_change--;
        if (token == '>')
            net_cell_change++;

        if (token == '+')
        {
            if (net_cell_change == 0)
            {
                net_loop_cell_value++;
            }
        }
        if (token == '-')
        {
            if (net_cell_change == 0)
            {
                net_loop_cell_value--;
            }
        }

    } // end for loop

    if (net_cell_change != 0)
        answer = false;

    if (abs(net_loop_cell_value) != 0 && abs(net_loop_cell_value) != 1)
        answer = false;

    return answer;
}

/*
print a vector list of pair<string,int> in order with some formatting
*/
void print_vector_string_int_pair(vector<std::pair<std::string, int>> vector_list)
{

    int count = 0;
    int max_string_size = 40;

    for (const auto &pair : vector_list)
    {
        string loop_string = pair.first;
        int string_count = pair.second;

        if (!verbose_output && loop_string.length() > max_string_size)
        {
            loop_string = pair.first.substr(0, max_string_size);
            loop_string += " ??? [verbose=off]";
        }

        std::cout << "[" << count << "] ";
        std::cout << loop_string << " : " << string_count << std::endl;
        count++;
    }
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cout << "No input file?" << endl;
        return 1;
    }

    //set flags
    for (int i = 0; i < argc; i++)
    {
        string flag = argv[i];
        if (flag == "-d")
            debug = true;
        if (flag == "-p")
            profiler_mode = true;
        if (flag == "-v")
            verbose_output = true;
    }

    ifstream inputFile(argv[1]); // Open file
    if (!inputFile)
    {
        cout << "Couldn't open file: " << argv[1] << endl;
        return 1;
    }
    // Read the file into a vector of chars
    program_file.assign((istreambuf_iterator<char>(inputFile)),
                        istreambuf_iterator<char>()); 
    // Close the file
    inputFile.close();
    //set 0's to tape
    init_tape();

    //begin our interpreter loop
    for (int i = 0; i < program_file.size(); i++)
    {
        char ch = program_file[i];
        i = bf_interpreter(ch, i);

    } 

    cout << endl;
    cout << endl;
    cout << "BF PROGRAM TERMINATED CORRECTLY." << endl;

    if (profiler_mode)
    {
        cout << endl;
        cout << "INSTRUCTION COUNT" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << " > : " << count_greaterthan << endl;
        cout << " < : " << count_lessthan << endl;
        cout << " + : " << count_plus << endl;
        cout << " - : " << count_minus << endl;
        cout << " . : " << count_period << endl;
        cout << " , : " << count_comma << endl;
        cout << " [ : " << count_leftbracket << endl;
        cout << " ] : " << count_rightbracket << endl;

        // Accumulate our loop count results
        for (const auto &pair : loop_index_dict)
        {
            // pair.first- index of loop
            // pair.second- count of times it executed
            string loop_string = get_loop_string(pair.first);

            // adding count to loop_index_dict
            if (loop_string_dict.find(loop_string) != loop_string_dict.end())
                loop_string_dict[loop_string] = loop_string_dict[loop_string] + pair.second;
            else
                loop_string_dict[loop_string] = pair.second;
        }

        std::vector<std::pair<std::string, int>> simple_loop_list;
        std::vector<std::pair<std::string, int>> other_loop_list;
        // Add our loops to one of two lists
        for (const auto &pair : loop_string_dict)
        {
            // pair.first = string of the loop
            if (is_simple_loop(pair.first))
                simple_loop_list.push_back(pair);
            else
                other_loop_list.push_back(pair);
        }
        // sort the lists based on count
        std::sort(simple_loop_list.begin(), simple_loop_list.end(),
                  [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
                  {
                      return a.second > b.second; // For descending order
                  });
        std::sort(other_loop_list.begin(), other_loop_list.end(),
                  [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
                  {
                      return a.second > b.second; // For descending order
                  });

        cout << endl;

        cout << "SIMPLE LOOP COUNT" << endl;
        cout << "--------------------------------------------------" << endl;

        print_vector_string_int_pair(simple_loop_list);
        cout << endl;

        cout << "OTHER LOOP COUNT" << endl;
        cout << "--------------------------------------------------" << endl;
        print_vector_string_int_pair(other_loop_list);

    } // end if profiler mode

} // end main()
