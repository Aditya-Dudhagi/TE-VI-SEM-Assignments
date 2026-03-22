#include <bits/stdc++.h>
using namespace std;

class NQueen {
public:
    int n;
    vector<vector<int>> matrix;
    vector<vector<int>> ans;

    NQueen(int x) {
        n = x;
        matrix = vector<vector<int>>(n, vector<int>(n, 0));
    }

    bool isSafe(int row, int col) {

        // Check column
        for(int i = 0; i < row; i++) {
            if(matrix[i][col]) return false;
        }

        // Check left diagonal
        for(int i=row-1, j=col-1; i>=0 && j>=0; i--, j--) {
            if(matrix[i][j]) return false;
        }

        // Check right diagonal
        for(int i=row-1, j=col+1; i>=0 && j<n; i--, j++) {
            if(matrix[i][j]) return false;
        }

        return true;
    }

    void placeQueen(int row) {
        if(row == n) {
            vector<int> temp;
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                    if(matrix[i][j]) {
                        temp.push_back(j+1);
                    }
                }
            }
            ans.push_back(temp);
            return;
        }

        for(int col=0; col<n; col++) {
            if(isSafe(row, col)) {
                matrix[row][col] = 1;
                placeQueen(row + 1);
                matrix[row][col] = 0; // backtrack
            }
        }
    }

    void displayQueens() {
        if(ans.empty()) {
            cout << "No solution found\n";
            return;
        }

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(ans[0][i] == j+1)
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter no. of queens: ";
    cin >> n;

    NQueen q1(n);
    q1.placeQueen(0);   // Solve
    q1.displayQueens(); // Display first solution

    return 0;
}