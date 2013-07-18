/*
ID: jl39301
PROG: palsquare
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

string convert(int num, int base) {
    stack<char> s;
    string res = "";

    while (num != 0) {
        int r = num % base;
        num /= base;
        if (r >= 10)
            s.push(r - 10 + 'A');
        else
            s.push('0' + r);
    }

    while (!s.empty()) {
        res += s.top();
        s.pop();
    }
    return res;
}

bool isPalin(string &str) {
    for (int i = 0; i < str.length() / 2; i++)
        if (str[i] != str[str.length() - 1 - i])
            return false;
    return true;
}

void solve(int base, ofstream &fout) {
    int square;
    string numInBase;
    string squareInBase;

    for (int i = 1; i <= 300; i++) {
        square = i * i;
        squareInBase = convert(square, base);
        if (isPalin(squareInBase)) {
            numInBase = convert(i, base);
            fout << numInBase << " " << squareInBase << endl;
        }
    }
}

int main() {
    ofstream fout("palsquare.out");
    ifstream fin("palsquare.in");
    int base;

    fin >> base;
    solve(base, fout);
    return 0;
}
