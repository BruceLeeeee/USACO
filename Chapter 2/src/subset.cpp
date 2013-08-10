/*
ID: jl39301
PROG: subset
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

#define SIZE 40

using namespace std;

unsigned f[SIZE][SIZE * (1 + SIZE) / 4];

int main() {
    ofstream fout("subset.out");
    ifstream fin("subset.in");
    int n;
    fin >> n;
    memset(f, 0, sizeof(f));
    f[1][0] = f[1][1] = 1;
    f[2][0] = f[2][1] = f[2][2] = f[2][3] = 1;
    if (n * (1 + n) % 4 != 0) {
        fout << 0 << endl;
    } else {
        for (int i = 3; i <= n; i++)
            for (int lSum = 0; lSum <= n * (1 + n) / 4; lSum++)
                f[i][lSum] = f[i - 1][lSum - i] + f[i - 1][lSum];
        fout << f[n][n * (1 + n) / 4] / 2 << endl;
    }
    return 0;
}
