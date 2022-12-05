#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;

int get_score(char c) {
    if (tolower(c) == c) {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 26 + 1;
    }
}

void resolve_part1() {
    const char* path = "../day3.txt";
    ifstream input_day3(path);

    if (input_day3.is_open()) {
        string line;
        int score = 0;
        while (getline(input_day3, line)) {
            size_t rucksack_size = line.size();

            unordered_map<char, bool> item_map;
            for (size_t i = 0 ; i < rucksack_size ; i++) {
                bool is_part1 = i < rucksack_size/2;
                if (is_part1) {
                    item_map[line[i]] = true;
                } else if (item_map.find(line[i]) != item_map.end()) {
                    score += get_score(line[i]);
                    item_map.erase(line[i]);
                }
            }
        }
        cout << "total score : " << score << endl;
    } else {
        cout << "unable to open : '" << path << "'" << endl;
    }
}

class RuckSackGroup {
    public:
        RuckSackGroup()
        : group()
        , score(0)
        {}

        void add(const string& l) {
            group.insert(l);
            if (group.size() < 3) {
                return;
            }

            unordered_map<char, unordered_set<int>> itemCounter;
            int idx = 0;
            for (auto it = group.cbegin(); it != group.cend(); it++) {
                for (auto i = 0 ; i < it->size() ; i++) {
                    char c = it->at(i);
                    itemCounter[c].insert(idx);
                }
                idx+=1;
            }

            for (auto it = itemCounter.cbegin(); it != itemCounter.cend(); it++) {
                if (it->second.size() == 3) {
                    score += get_score(it->first);
                }
            }

            group.clear();
        }

        int Score() {return score;}
    private:
        set<string> group;
        int score;
};

int main() {
    const char* path = "../day3.txt";
    ifstream input_day3(path);

    if (input_day3.is_open()) {
        string line;
        int score = 0;
        RuckSackGroup sackGroup;
        while (getline(input_day3, line)) {
            sackGroup.add(line);
        }

        cout << sackGroup.Score() << endl;
    }
}