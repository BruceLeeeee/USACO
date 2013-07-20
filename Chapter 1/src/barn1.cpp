/*
ID: jl39301
PROG: barn1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;



int main() {
    ofstream fout("barn1.out");
    ifstream fin("barn1.in");
    int m, s, c;
    int max;
    int min;
    int ans;

    fin >> m >> s >> c;
    if (m >= c) {
        fout << c << endl;
        return 0;
    }

    vector<int> stalls(c);
    vector<int> gaps(c - 1);
    for (int i = 0; i < c; i++)
        fin >> stalls[i];
    sort(stalls.begin(), stalls.end());
    min = stalls[0];
    max = stalls[stalls.size() - 1];
    for (int i = 1; i < stalls.size(); i++)
        gaps[i - 1] = stalls[i] - stalls[i - 1];
    sort(gaps.begin(), gaps.end());
    ans = max - min + 1;
    for (int i = 0; i < m - 1; i++)
        ans -= gaps[gaps.size() - 1 - i] - 1;
    fout << ans << endl;
    return 0;
}
