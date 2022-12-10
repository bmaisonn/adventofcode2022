#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef pair<int, int> Point;
const int ROPE_SIZE = 10;

struct pair_hash {
    inline std::size_t operator()(const Point & v) const {
        return v.first*31+v.second;
    }
};
typedef unordered_set<Point, pair_hash> VisitedPath;
// R 4
// U 4
// L 3
// D 1
// R 4
// D 1
// L 5
// R 2

class RopeSimulator {
    public:
        RopeSimulator()
        : visited()
        {
            visited.insert(knots[0]);
        }
    
    public:
        void move(char direction, int count);

    public:
        const VisitedPath& TailPath() const {return visited;};

    private:
        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();

        bool AreAdjacent(Point& ref, Point& knot);
        void AdjustKnotPosition(Point& ref, Point& knot);

    private:
        Point knots[ROPE_SIZE];
        VisitedPath visited;
};

void RopeSimulator::AdjustKnotPosition(Point& ref, Point& knot)
{
    cout << "H:" << ref.first << "," << ref.second << endl;
    auto x_diff = knot.first - ref.first;
    if (x_diff <= -1)
        knot.first++;
    else if (x_diff >= 1)
        knot.first--;
    
    auto y_diff = knot.second - ref.second;
    if (y_diff <= -1)
        knot.second++;
    else if (y_diff >= 1)
        knot.second--;
    
    cout << "T:" << knot.first << "," << knot.second << endl;
}

bool RopeSimulator::AreAdjacent(Point& ref, Point& knot) {
    // compute the distance between two points
    auto x_diff = abs(knot.first - ref.first);
    auto y_diff = abs(knot.second - ref.second);
    return x_diff <= 1 and y_diff <= 1;
}

void RopeSimulator::move(char direction, int count) {
    for (auto i = 0 ; i < count ; i++) {
        switch (direction) {
            case 'R':
                moveRight();
                break;
            case 'L':
                moveLeft();
                break;
            case 'U':
                moveUp();
                break;
            case 'D':
                moveDown();
                break;
        } 
        
        for (auto i = 1 ; i < ROPE_SIZE ; i++) {
            if (!AreAdjacent(knots[i], knots[i-1]))
                AdjustKnotPosition(knots[i-1], knots[i]);

            if (i == ROPE_SIZE - 1)
                visited.insert(knots[i]);
        }
    }
}

void RopeSimulator::moveRight() {
    knots[0].first++;
}
void RopeSimulator::moveLeft() {
    knots[0].first--;
}
void RopeSimulator::moveUp() {
    knots[0].second++;
}
void RopeSimulator::moveDown() {
    knots[0].second--;
}

int main() {
    const char* path = "../day9.txt";

    ifstream data(path);
    if (data.is_open()) {
        string l;

        RopeSimulator s;
        while (getline(data, l)) {
            char direction = l[0];
            int count = stoi(l.substr(2));
            s.move(direction, count);
        }

        cout << s.TailPath().size() << endl;

    } else {
        cout << "Unable to open " << path << endl;
    }
}