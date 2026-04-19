#include <bits/stdc++.h>
using namespace std;

class Matrix {
public:
    vector<vector<int>> mat;
    int x, y;
    int g, h, f;
    Matrix* parent;

    Matrix(vector<vector<int>> m, int g_val, Matrix* p = nullptr) {
        mat = m;
        g = g_val;
        parent = p;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (mat[i][j] == 0) {
                    x = i;
                    y = j;
                }

        h = heuristic();
        f = g + h;
    }

    vector<vector<int>> goal = {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}
    };

  
    int heuristic() {
        int misplaced = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mat[i][j] != 0) {
                    if (mat[i][j] != goal[i][j]) {
                        misplaced++;
                    }
                }
            }
        }
        return misplaced;
    }

    bool isGoal() {
        return mat == goal;
    }

    void print() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mat[i][j] == 0) cout << "  ";
                else cout << mat[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

struct cmp {
    bool operator()(const Matrix* a, const Matrix* b) {
        return a->f > b->f;
    }
};

void printPath(Matrix* node) {
    if (!node) return;
    printPath(node->parent);

    node->print();
    cout << "  g = " << node->g 
         << "   h = " << node->h 
         << "   f = " << node->f << "\n"
         << "------------------------\n";
}

int main() {
    vector<vector<int>> start = {
        {2, 8, 3},
        {1, 6, 4},
        {7, 0, 5}
    };

    priority_queue<Matrix*, vector<Matrix*>, cmp> pq;
    set<vector<vector<int>>> visited;

    Matrix* startNode = new Matrix(start, 0);
    pq.push(startNode);

    cout << "Starting state:\n";
    startNode->print();
    cout << "  g = " << startNode->g 
         << "   h = " << startNode->h 
         << "   f = " << startNode->f << "\n\n";

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    int step = 0;

    while (!pq.empty()) {
        Matrix* cur = pq.top();
        pq.pop();

        step++;
        cout << "Step " << step << " - Expanding node  (f = " << cur->f << ")\n";
        cur->print();
        cout << "  g(n) = " << cur->g 
             << "   h(n) = " << cur->h 
             << "   f(n) = " << cur->f << "\n\n";

        if (cur->isGoal()) {
            cout << "========== SOLUTION FOUND ==========\n\n";
            cout << "Path from start to goal:\n\n";
            printPath(cur);
            cout << "\nTotal moves = " << cur->g << "\n";
            return 0;
        }

        if (visited.count(cur->mat)) continue;
        visited.insert(cur->mat);

        for (int d = 0; d < 4; d++) {
            int nx = cur->x + dx[d];
            int ny = cur->y + dy[d];

            if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                auto newMat = cur->mat;
                swap(newMat[cur->x][cur->y], newMat[nx][ny]);

                if (visited.find(newMat) == visited.end()) {
                    Matrix* child = new Matrix(newMat, cur->g + 1, cur);
                    pq.push(child);
                }
            }
        }
    }

    cout << "No solution found.\n";
    return 0;
}