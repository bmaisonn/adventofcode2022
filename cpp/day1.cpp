#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>

using namespace std;

void resolve_part1(ifstream& day1_data) {
    day1_data.seekg(day1_data.beg);
    auto max_elf_count = 0;
    auto curr_sum = 0;
    string line;
    while ( getline(day1_data, line)) {
        size_t line_s = line.size();
        if (line_s > 0) {
            auto val = stoi(line);
            curr_sum += val;
        } else {
            max_elf_count = max(curr_sum, max_elf_count);
            curr_sum = 0;
        }
        
    }
    cout << "part1 result: " << max_elf_count << endl;
}

void insert_count(list<int>& max_elf_counts, int curr_sum) {
    auto it = max_elf_counts.cbegin();
    for (; it != max_elf_counts.cend() ; it++) {
        if (curr_sum < *it) {
            max_elf_counts.insert(it, curr_sum);
            break;
        }
    }
    if (it == max_elf_counts.cend())
        max_elf_counts.push_back(curr_sum);

    if (max_elf_counts.size() > 3)
        max_elf_counts.pop_front();
}

void resolve_part2(ifstream& day1_data) {
    day1_data.seekg(day1_data.beg);

    list<int> max_elf_counts = {0,0,0};
    auto curr_sum = 0;
    string line;
    while (getline(day1_data, line)) {
        size_t line_s = line.size();
        if (line_s > 0) {
            auto val = stoi(line);
            curr_sum += val;
        } else {
            insert_count(max_elf_counts, curr_sum);            
            curr_sum = 0;
        }
    }
    insert_count(max_elf_counts, curr_sum); 

    auto sum = 0;
    for (auto it = max_elf_counts.cbegin() ; it != max_elf_counts.cend(); it++) {
        sum += (*it);
    }
    cout << "part1 result: " << sum << endl;
}

int main()
{
    ifstream day1_data("../py/day1.txt");

    if (day1_data.is_open()) {
        //resolve_part1(day1_data);
        resolve_part2(day1_data);
        day1_data.close();
    } else {
        cout << "unable to open file";
    }
}
