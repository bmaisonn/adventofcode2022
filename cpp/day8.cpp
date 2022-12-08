#include <iostream>
#include <fstream>
#include <vector>

#include <algorithm>

using namespace std;

class Matrix {

    public:
        Matrix()
        : data()
        {}

        static const Matrix* from_file(const char* path);

        int Value(int idx, int idy) const ;
        int NbLines() const {return data.size();}
        int NbColumns() const {return data.size() == 0 ? 0 : data[0].size();}
        bool CheckCellVisible(int idx, int idy) const;
        int ComputeViewScore(int idx, int idy) const;

    private:
        vector<string> data;
};

int Matrix::Value(int idx, int idy) const
{
    return (data[idx][idy] - '0');
}

const Matrix* Matrix::from_file(const char* path)
{
    auto m = new Matrix();
    ifstream input_data(path);
    if (input_data.is_open()) {
        string l;
        while (getline(input_data, l)) {
            m->data.push_back(move(l));
        }
    } else {
        cout << "unable to open " << path << endl;
    }
    return m;
}

bool Matrix::CheckCellVisible(int idx, int idy) const {
    int current_value = Value(idx, idy);

    auto curr_row = idx - 1;
    while (curr_row >= 0) {
        if (Value(curr_row, idy) >= current_value)
            break;
        curr_row--;
    }

    if (curr_row < 0)
        return true;

    curr_row = idx + 1;
    while (curr_row < NbLines()) {
        if (Value(curr_row,idy) >= current_value)
            break;
        curr_row++;
    }

    if (curr_row >= NbLines())
        return true;

    auto curr_col = idy - 1;
    while (curr_col >= 0) {
        if (Value(idx, curr_col) >= current_value)
            break;
        curr_col--;
    }

    if (curr_col < 0)
        return true;

    curr_col = idy + 1;
    while (curr_col < NbColumns()) {
        if (Value(idx, curr_col) >= current_value)
            break;
        curr_col++;
    }

    if (curr_col >= NbColumns())
        return true;

    return false;
}

int Matrix::ComputeViewScore(int idx, int idy) const {
    int current_value = Value(idx, idy);
    
    int view_scores[4] =  {0, 0, 0, 0};

    auto curr_row = idx - 1;
    while (curr_row >= 0) {
        view_scores[0]++;
        if (Value(curr_row, idy) >= current_value)
            break;
        curr_row--;
    }

    curr_row = idx + 1;
    while (curr_row < NbLines()) {
        view_scores[1]++;
        if (Value(curr_row, idy) >= current_value)
            break;
        curr_row++;
    }

    auto curr_col = idy - 1;
    while (curr_col >= 0) {
        view_scores[2]++;
        if (Value(idx, curr_col) >= current_value)
            break;
        curr_col--;
    }

    curr_col = idy + 1;
    while (curr_col < NbColumns()) {
        view_scores[3]++;
        if (Value(idx, curr_col) >= current_value)
            break;
        curr_col++;
    }

    return view_scores[0]*view_scores[1]*view_scores[2]*view_scores[3];
}

int main() {
    const char* path = "../day8.txt";

    const Matrix* m = Matrix::from_file(path);

    int nb_trees = 2 * m->NbLines() + 2 * m->NbColumns() - 4;
    int max_score = 0;
    for (int i = 1; i < m->NbLines() - 1 ; i++) {
        for (int j = 1 ; j < m->NbColumns() - 1 ; j++ ) {
            auto score = m->ComputeViewScore(i, j);
            max_score = max(max_score, score);

            if (m->CheckCellVisible(i, j)) {
                nb_trees++;
            }
        }
    }

    cout << "max score : " << max_score << endl;
    cout << "nb trees : " << nb_trees << endl;
}