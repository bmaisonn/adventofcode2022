#include <iostream>
#include <fstream>
#include <map>
using namespace std;

// A:Rock
// B:Paper
// C: Scissors
//
// X:Rock
// Y:Paper
// Z:Scissors

map<char, char> LOOSE = {
    {'A', 'Z'},
    {'B', 'X'},
    {'C', 'Y'}
};
map<char, char> WIN = {
    {'A', 'Y'},
    {'B', 'Z'},
    {'C', 'X'}
};

int get_score(char oppenent, char me) {
    auto my_rank = me - 'X'; 
    auto score = my_rank + 1;
    if (WIN[oppenent] == me) {
        score += 6;
    } else if (LOOSE[oppenent] == me) {
        score += 0;
    } else {
        score += 3;
    }
    return score;
}

void resolve_part1(ifstream& input_file) {
    string line;
    auto total_score = 0;
    while (getline(input_file, line)) {
        auto oppenent = line[0];
        auto me = line[2];
        total_score += get_score(oppenent, me);
    }
    cout << total_score << endl;
}

// X:LOOSE
// Y:DRAW
// Z:WIN
int run_game(char oppenent, char event) {
    if (event == 'X') {
        return get_score(oppenent, LOOSE[oppenent]);
    } else if (event == 'Y') {
        auto rank_oppenent = oppenent - 'A';
        return get_score(oppenent, 'X' + rank_oppenent);
    } else {
        return get_score(oppenent, WIN[oppenent]);
    }
}

void resolve_part2(ifstream& input_file) {
    string line;
    auto total_score = 0;
    while (getline(input_file, line)) {
        auto oppenent = line[0];
        auto event = line[2];
        total_score += run_game(oppenent, event);
    }
    cout << total_score << endl;
}

int main() {
    
    ifstream input_file("../day2.txt");

    if (input_file.is_open()) {
        resolve_part2(input_file);
    } else{
        cout << "enable to open the file" << endl;
    }   
}