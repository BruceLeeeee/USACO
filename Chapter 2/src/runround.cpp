/*
ID: jl39301
PROG: runround
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

#define ull unsigned long long

using namespace std;

ull toNum(string str) {
    ull num = 0;
    for (int i = 0; i < str.size(); i++) {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

bool isRunaround(string str) {
    bool flag[str.size()];
    for (int i = 0; i < str.size(); i++)
        flag[i] = false;
    int curr = 0;
    int next;
    int len = str.length();
    int touchCount = 0;
    while (true) {
        int count = str[curr] - '0';
        next = (curr + count) % len;
        touchCount++;
        if (str[next] == str[curr])
            return false;
        if (next == 0 && touchCount == len)
            return true;
        if (flag[next] == false)
            flag[next] = true;
        else
            return false;
        curr = next;
    }
}

void dfs(string &soFar, string &rest, int len, int m, ofstream &fout, bool &found) {
    if (found)
        return;
    if (soFar.length() == len) {
        ull num = toNum(soFar);
        if (num > m && isRunaround(soFar)) {
            fout << num << endl;
            found = true;
            return;
        }
    }
    for (int i = 0; i < rest.size(); i++) {
        string soFarTmp = soFar;
        string restTmp = rest;
        restTmp.erase(i, 1);
        soFarTmp += rest[i];
        dfs(soFarTmp, restTmp, len, m, fout, found);
    }
}

int numLen(int num) {
    int len = 1;
    while (true) {
        num /= 10;
        if (num == 0)
            break;
        len++;
    }
    return len;
}

void solve(int m, ofstream &fout) {
    bool found = false;
    int mLen = numLen(m);
    for (int l = mLen; l <= 9; l++) {
        string rest = "123456789";
        string soFar = "";
        dfs(soFar, rest, l, m, fout, found);
    }
}

int main() {
    ofstream fout("runround.out");
    ifstream fin("runround.in");
    int m;
    fin >> m;
    solve(m, fout);
    return 0;
}
