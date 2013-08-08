/*
ID: jl39301
PROG: hamming
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

string toBinary(int num, int b) {
    string result;
    while (true) {
        if (num == 0)
            break;
        int r = num % 2;
        if (r == 1)
            result += "1";
        else
            result += "0";
        num /= 2;
    }
    while (true) {
        if (result.size() >= b)
            break;
        result += "0";
    }
    return result;
}

int hDist(int num1, int num2, int b) {
    string str1 = toBinary(num1, b);
    string str2 = toBinary(num2, b);
    int count = 0;
    for (int i = 0; i < b; i++)
        if (str1[i] != str2[i])
            count++;
    return count;
}

bool satisfy(vector<int> &ans, int num, int b, int d) {
    for (int i = 0; i < ans.size(); i++)
        if (hDist(ans[i], num, b) < d)
            return false;
    return true;
}

void output(vector<int> &ans, ofstream &fout) {
    for (int i = 0; i < ans.size(); i++) {
        if (i % 10 != 0)
            fout << " ";
        fout << ans[i];
        if (i % 10 == 9 || i == ans.size() - 1)
            fout << endl;
    }
}

void dfs(int curr, int max, int n, int b, int d, vector<int> &ans, bool &found, ofstream &fout) {
    if (found)
        return;
    if (ans.size() == n) {
        found = true;
        output(ans, fout);
        return;
    }
    for (int i = curr + 1; i < max; i++)
        if (satisfy(ans, i, b, d)) {
            ans.push_back(i);
            dfs(i, max, n, b, d, ans, found, fout);
            ans.pop_back();
        }
}

int main() {
    ofstream fout("hamming.out");
    ifstream fin("hamming.in");
    int n, b, d;
    fin >> n >> b >> d;
    vector<int> ans;
    bool found = false;
    ans.push_back(0);
    dfs(0, (int)pow(2, b), n, b, d, ans, found, fout);
    return 0;
}
