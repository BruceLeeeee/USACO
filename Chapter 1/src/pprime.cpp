/*
ID: jl39301
PROG: pprime
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
#include <cstdlib>

using namespace std;

bool isPrime(int num) {
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0)
            return false;
    return true;
}

string intToStr(int num) {
    string res;
    while (true) {
        int r = num % 10;
        char ch = '0' + r;
        res = ch + res;
        num /= 10;
        if (num == 0)
            break;
    }
    return res;
}

void solve(int a, int b, ofstream &fout) {
    int start[] = {1, 1, 1, 10, 10, 100, 100, 1000, 1000};
    for (int l = 1; l <= 8; l++) {
        int count = start[l];
        int endCount = count * 10;
        for (; count < endCount; count++) {
            string num = intToStr(count);
            string reverseNum = num;
            reverse(reverseNum.begin(), reverseNum.end());
            if (l % 2 == 0)
                num = num + reverseNum;
            else if (num.length() > 1)
                num = num + reverseNum.substr(1);
            if (atoi(num.c_str()) > b)
                return;
            if (atoi(num.c_str()) >= a && isPrime(atoi(num.c_str())))
                fout << num << endl;
        }
    }
}

int main() {
    ofstream fout("pprime.out");
    ifstream fin("pprime.in");
    int a, b;
    fin >> a >> b;
    solve(a, b, fout);
    return 0;
}
