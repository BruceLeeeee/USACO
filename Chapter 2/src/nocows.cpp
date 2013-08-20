/*
ID: jl39301
PROG: nocows
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

#define MODULO 9901
#define SIZE1 210
#define SIZE2 110

using namespace std;

void solve(int N, int K, ofstream &fout) {
    int f[SIZE1][SIZE2];
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= N; i += 2)
        for (int j = 1; j <= K; j++)
            if (i == 1)
                f[i][j] = 1;
            else {
                f[i][j] = 0;
                for (int k = 1; k <= i - 2; k += 2) {
                    f[i][j] += f[k][j - 1] * f[i - 1 - k][j - 1] % MODULO;
                    f[i][j] %= MODULO;
                }
            }
    fout << (f[N][K] - f[N][K - 1] + MODULO) % MODULO << endl;
}

int main() {
    ofstream fout("nocows.out");
    ifstream fin("nocows.in");
    int N, K;
    fin >> N >> K;
    solve(N, K, fout);
    return 0;
}
