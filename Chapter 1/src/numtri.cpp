/*
ID: jl39301
PROG: numtri
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

using namespace std;

#define SIZE 1010

void dfs(int i, int j, int r, int f[SIZE][SIZE], int tri[SIZE][SIZE]) {
    if (i >= r || j > i) {
        f[i][j] = 0;
        return;
    }
    if (f[i + 1][j] == -1)
        dfs(i + 1, j, r, f, tri);
    if (f[i + 1][j + 1] == -1)
        dfs(i + 1, j + 1, r, f, tri);
    f[i][j] = max(f[i + 1][j], f[i + 1][j + 1]) + tri[i][j];
}

int main() {
    ofstream fout("numtri.out");
    ifstream fin("numtri.in");
    int r;
    int tri[SIZE][SIZE];
    int f[SIZE][SIZE];
    fin >> r;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < i + 1; j++)
            fin >> tri[i][j];
    for (int i = 0; i < r; i++)
        for (int j = 0; j < r; j++)
            f[i][j] = -1;
    dfs(0, 0, r, f, tri);
    fout << f[0][0] << endl;
    return 0;
}
