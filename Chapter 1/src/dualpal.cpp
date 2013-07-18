/*
ID: jl39301
PROG: dualpal
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

bool isDualpal(int num) {
    string numInBase;
    int count = 0;

    for (int base = 2; base <= 10; base++) {
        numInBase = convert(num, base);
        if (isPalin(numInBase))
            count++;
        if (count >= 2)
            return true;
    }
    return false;
}

void solve(int n, int s, ofstream &fout) {
    int i = s + 1;
    int count = 0;

    while (true) {
        if (isDualpal(i)) {
            count++;
            fout << i << endl;
        }
        i++;
        if (count == n)
            break;
    }
}

int main() {
    ofstream fout("dualpal.out");
    ifstream fin("dualpal.in");
    int n, s;

    fin >> n >> s;
    solve(n, s, fout);
    return 0;
}
