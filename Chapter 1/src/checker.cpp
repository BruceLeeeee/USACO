/*
ID: jl39301
PROG: checker
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>
#include <algorithm>
#include <cmath>

using namespace std;

bool board[15][15];
bool colUsed[15];
vector<vector<int> > ans;

bool isSafe(int x, int y, int n) {
    int dir[2][2] = {{-1, -1}, {-1, 1}};
    for (int i = 0; i < 2; i++) {
        int dx = dir[i][0];
        int dy = dir[i][1];
        int xTmp = x;
        int yTmp = y;
        while (true) {
            xTmp += dx;
            yTmp += dy;
            if (xTmp < 1 || xTmp > n || yTmp < 1 || yTmp > n)
                break;
            if (board[xTmp][yTmp])
                return false;
        }
    }
    return true;
}

void addSol(int n) {
    vector<int> a;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        if (board[i][j]) {
            a.push_back(j);
            break;
        }
    ans.push_back(a);
}

void backtrack(int row, int n, int &solCount, int firstRowPos, int &middleCount) {
    if (row > n) {
        if (n % 2 == 1 && firstRowPos == n / 2 + 1)
            middleCount++;
        solCount++;
        if (ans.size() < 3)
            addSol(n);
        return;
    }
    if (n != 6 && row == 1) { // prune half the decision tree using symmetry
        int m = n / 2;
        if (n % 2 == 1)
            m++;
        for (int i = 1; i <= m; i++) {
            board[row][i] = true;
            colUsed[i] = true;
            backtrack(row + 1, n, solCount, i, middleCount);
            colUsed[i] = false;
            board[row][i] = false;
        }
    } else {
        for (int i = 1; i <= n; i++)
            if (colUsed[i] == false && isSafe(row, i, n)) {
                board[row][i] = true;
                colUsed[i] = true;
                backtrack(row + 1, n, solCount, firstRowPos, middleCount);
                colUsed[i] = false;
                board[row][i] = false;
            }
    }
}

void output(ofstream &fout, vector<vector<int> > &ans, int &solCount) {
    for (int i = 0; i < ans.size(); i++) {
        vector<int> sol = ans[i];
        fout << sol[0];
        for (int j = 1; j < sol.size(); j++)
            fout << " " << sol[j];
        fout << endl;
    }
    fout << solCount << endl;
}

void init() {
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            board[i][j] = false;
    for (int i = 0; i < 15; i++)
        colUsed[i] = false;
}

int main() {
    ofstream fout("checker.out");
    ifstream fin("checker.in");
    int n;
    int solCount = 0;
    int middleCount = 0;
    fin >> n;
    init();
    backtrack(1, n, solCount, 1, middleCount);
    if (n != 6)
        solCount = solCount * 2 - middleCount;
    output(fout, ans,solCount);
    return 0;
}
