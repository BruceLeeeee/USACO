/*
ID: jl39301
PROG: zerosum
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

void parse(string &str, vector<int> &operands, vector<char> &optrs) {
    int i = 0;
    int num = 0;

    while (true) {
        if (i >= str.length())
            break;
        if (str[i] == '+' || str[i] == '-') {
            operands.push_back(num);
            num = 0;
            optrs.push_back(str[i]);
        } else if (str[i] != ' '){
            num *= 10;
            num += str[i] - '0';
        }
        i++;
    }
    operands.push_back(num);
}

int sum(string &str) {
    vector<int> operands;
    vector<char> optrs;
    parse(str, operands, optrs);

    int s = operands[0];
    for (int i = 0; i < optrs.size(); i++)
        if (optrs[i] == '+')
            s += operands[i + 1];
        else
            s -= operands[i + 1];
    return s;
}

void dfs(string soFar, int i, int n, vector<string> &ans) {
    if (i == n) {
        if (sum(soFar) == 0)
            ans.push_back(soFar);
        return;
    }
    char optrs[] = {' ', '+', '-'};
    for (int j = 0; j < 3; j++) {
        string next = soFar;
        char ch;
        ch = optrs[j];
        if (i != n)
            next += ch;
        ch = '1' + i - 0;
        next += ch;
        dfs(next, i + 1, n, ans);
    }
}

void output(vector<string> &ans, ofstream &fout) {
    for (int i = 0; i < ans.size(); i++)
        fout << ans[i] << endl;
}

int main() {
    ofstream fout("zerosum.out");
    ifstream fin("zerosum.in");
    int n;
    vector<string> ans;
    fin >> n;
    dfs("1", 1, n, ans);
    sort(ans.begin(), ans.end());
    output(ans, fout);
    return 0;
}
