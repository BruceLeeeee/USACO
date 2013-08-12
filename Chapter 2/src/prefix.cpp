/*
ID: jl39301
PROG: prefix
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

#define SIZE 200010
using namespace std;

int f[SIZE];

void solve(vector<string> &primitives, string &seq, ofstream &fout) {
    for (int i = 0; i < seq.length() + 1; i++)
        f[i] = 0;
    for (int i = 0; i < primitives.size(); i++) {
        int start = seq.size() - primitives[i].length();
        if (start >= 0 && seq.substr(start) == primitives[i]) {
            if (f[start] < primitives[i].length())
                f[start] = primitives[i].length();
        }
    }
    for (int i = seq.length() - 1; i >= 0; i--) {
        int max = 0;
        for (int j = 0; j < primitives.size(); j++)
            if (seq.substr(i, primitives[j].length()) == primitives[j]) {
                int tmp = f[i + primitives[j].length()] + primitives[j].length();
                if (max < tmp)
                    max = tmp;
            }
        f[i] = max;
    }
    fout << f[0] << endl;
}

int main() {
    ofstream fout("prefix.out");
    ifstream fin("prefix.in");
    vector<string> primitives;
    string seq;
    while (true) {
        string str;
        fin >> str;
        if (str == ".")
            break;
        primitives.push_back(str);
    }
    while (true) {
        string str;
        if (getline(fin, str))
            seq += str;
        else
            break;
    }
    //fout << seq << endl;
    solve(primitives, seq, fout);
    return 0;
}
