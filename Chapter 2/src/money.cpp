/*
ID: jl39301
PROG: money
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
#include <cstring>

#define SIZE1 10010
#define SIZE2 30
#define ll long long

using namespace std;

ll f[SIZE2][SIZE1];

void dp(int v, int n, vector<int> &coins) {
    for (int i = 0; i < v; i++)
        for (int j = 1; j <= n; j++) {
            if (i != 0)
                f[i][j] = f[i-1][j];
            if (j - coins[i] >= 0)
                f[i][j] += f[i][j - coins[i]];
        }
}

void init(int v, int n) {
    for (int i = 0; i < v; i++)
        for (int j = 0; j <= n; j++)
            if (j == 0)
                f[i][j] = 1;
            else
                f[i][j] = 0;
}

int main() {
    ofstream fout("money.out");
    ifstream fin("money.in");
    int v, n;
    vector<int> coins;
    fin >> v >> n;
    coins.assign(v, 0);
    for (int i = 0; i < v; i++)
        fin >> coins[i];
    init(v, n);
    dp(v, n, coins);
    fout << f[v - 1][n] << endl;
    return 0;
}
