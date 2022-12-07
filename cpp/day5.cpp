#include <iostream>
#include <fstream>
#include <vector>
#include <list>


using namespace std;

//     [D]    
// [N] [C]    
// [Z] [M] [P]
//  1   2   3 

// move 1 from 2 to 1
// move 3 from 1 to 3
// move 2 from 2 to 1
// move 1 from 1 to 2

class CratesStacks {
    public:
        CratesStacks(const list<string>& stack_list);

        void move9000(int nbCrates, int fromStack, int toStack);
        void move9001(int nbCrates, int fromStack, int toStack);
        void showStacks();

    private:
        vector<list<char>> stacks;
};


CratesStacks::CratesStacks(const list<string>& stack_list) {
    auto it = stack_list.cbegin();
    while (it != stack_list.cend() and next(it) != stack_list.cend()) {
        const string& line = *it;
        size_t l_size = line.size();
        size_t cursor = 1;
        int idx = 0;
        while (cursor < l_size) {
            if (line[cursor] != ' ')
                {
                if (stacks.size() < idx + 1)
                    stacks.resize(idx + 1);
                stacks[idx].push_front(line[cursor]);
                }
            idx++;
            cursor += 4;
        }
        it++;
    }
}

void CratesStacks::move9000(int nbCrates, int fromStack, int toStack)
{
    while (nbCrates > 0){
        char back = stacks[fromStack-1].back();
        stacks[fromStack-1].pop_back();
        stacks[toStack-1].push_back(back);
        nbCrates--;
    }
}

void CratesStacks::move9001(int nbCrates, int fromStack, int toStack)
{
    list<char> intermediate_stack;
    while (nbCrates > 0) {
        char back = stacks[fromStack-1].back();
        stacks[fromStack-1].pop_back();
        intermediate_stack.push_front(back);
        nbCrates--;
    }
    for (auto el : intermediate_stack) {
        stacks[toStack-1].push_back(el);
    }
}

void CratesStacks::showStacks()
{
    for (auto currL : stacks) {
        cout << currL.back() << endl;
    }
}

void load_stack_list(ifstream& input_data, list<string>& stack_list) {
    string line;
    while (getline(input_data, line)) {
        size_t l_size = line.size();
        if (l_size == 0)
            break;
        stack_list.push_back(line);
    }
}


int main() {
    const char* path = "../day5.txt";
    ifstream input_data(path);
    if (input_data.is_open()) {
        list<string> stack_list;
        load_stack_list(input_data, stack_list);
        auto stacks = CratesStacks(stack_list);

        string line;
        while (getline(input_data, line)) {
            const string from = " from ";
            const string move = "move ";
            const string to = " to ";
            size_t pos_from = line.find(from);
            size_t pos_to = line.find(to);

            string nbCrates = line.substr(move.length(), pos_from - move.length());
            string fromStack = line.substr(pos_from + from.length(), pos_to - pos_from - from.length());
            string toStack = line.substr(pos_to+to.length(), line.size() - pos_to - to.length());
            stacks.move9001(stoi(nbCrates), stoi(fromStack), stoi(toStack));
        }

        stacks.showStacks();
    } else {
        cout << "failed to open " << path << endl;
    }
}