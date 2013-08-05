/*
ID: jl39301
PROG: holstein
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

#define SIZE1 30
#define SIZE2 1010

using namespace std;

struct feed {
    int vitamins[SIZE1];
};

bool satisfy(int v, int vitamins[SIZE1], vector<feed> &feeds, vector<int> &soFar) {
    int had[SIZE1];

    memset(had, 0, sizeof(had));
    for (int i = 0; i < soFar.size(); i++)
        for (int j = 0; j < v; j++)
            had[j] += feeds[soFar[i]].vitamins[j];
    for (int i = 0; i < v; i++)
        if (vitamins[i] > had[i])
            return false;
    return true;
}

void dfs(int i, int v, int g, int vitamins[SIZE1], vector<feed> &feeds, vector<int> &soFar, vector<int> &ans) {
    if (i == g) {
        if (satisfy(v, vitamins, feeds, soFar)) {
            if (ans.size() == 0)
                ans = soFar;
            else if (ans.size() > soFar.size())
                ans = soFar;
        }
        return;
    }
    soFar.push_back(i);
    dfs(i + 1, v, g, vitamins, feeds, soFar, ans);
    soFar.pop_back();
    dfs(i + 1, v, g, vitamins, feeds, soFar, ans);
}

void output(vector<int> &ans, ofstream &fout) {
    fout << ans.size();
    for (int i = 0; i < ans.size(); i++)
        fout << " " << ans[i] + 1;
    fout << endl;
}

int main() {
    ofstream fout("holstein.out");
    ifstream fin("holstein.in");
    int v, g;
    int vitamins[SIZE1];
    vector<feed> feeds;
    vector<int> ans;
    vector<int> soFar;
    fin >> v;
    for (int i = 0; i < v; i++)
        fin >> vitamins[i];
    fin >> g;
    for (int i = 0; i < g; i++) {
        feed f;
        for (int j = 0; j < v; j++)
            fin >> f.vitamins[j];
        feeds.push_back(f);
    }
    dfs(0, v, g, vitamins, feeds, soFar, ans);
    output(ans, fout);
    return 0;
}
