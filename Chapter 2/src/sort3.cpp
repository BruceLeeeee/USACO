/*
ID: jl39301
PROG: sort3
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
#include <queue>

using namespace std;

void solve(vector<int> &keys, ofstream &fout) {
    vector<int> sortedKeys;
    vector<int> pos(keys.size());
    int ans = 0;
    int part1End = -1;
    int part2End = -1;
    sortedKeys = keys;
    sort(sortedKeys.begin(), sortedKeys.end());
    for (int i = 0; i < sortedKeys.size(); i++) {
        if (sortedKeys[i] == 2 && part1End == -1)
            part1End = i - 1;
        if (sortedKeys[i] == 3 && part2End == -1)
            part2End = i - 1;
    }
    for (int i = 0; i < keys.size(); i++) {
        if (i <= part1End)
            pos[i] = 1;
        else if (i > part1End && i <= part2End)
            pos[i] = 2;
        else
            pos[i] = 3;
    }
    for (int i = 0; i < keys.size(); i++)
        for (int j = i + 1; j < keys.size(); j++)
            if (keys[i] != pos[i] && keys[j] != pos[j] && keys[i] == pos[j] && keys[j] == pos[i]) {
                ans++;
                swap(keys[i], keys[j]);
            }
    for (int i = 0; i <= part1End; i++)
        if (keys[i] != pos[i])
            ans += 2;
    fout << ans << endl;
}

int main() {
    ofstream fout("sort3.out");
    ifstream fin("sort3.in");
    int n;
    vector<int> keys;
    fin >> n;
    for (int i = 0; i < n; i++) {
        int key;
        fin >> key;
        keys.push_back(key);
    }
    solve(keys, fout);
    return 0;
}
