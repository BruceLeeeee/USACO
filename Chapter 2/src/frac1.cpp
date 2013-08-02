/*
ID: jl39301
PROG: frac1
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

#define SIZE 165

using namespace std;

struct fraction {
    int num;
    int den;
};

int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

bool cmp(const fraction &a, const fraction &b) {
    if (a.num * b.den <= b.num * a.den)
        return true;
    else
        return false;
}

void solve(int n, bool flag[SIZE][SIZE], vector<fraction> &ans) {

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            int num = i;
            int den = j;
            int factor = gcd(num, den);
            num /= factor;
            den /= factor;
            fraction frac;
            frac.num = num;
            frac.den = den;
            if (flag[num][den] == false) {
                ans.push_back(frac);
                flag[num][den] = true;
            }
        }
    sort(ans.begin(), ans.end(), cmp);
}

void init(int n, bool flag[SIZE][SIZE]) {
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            flag[i][j] = false;
}

void output(vector<fraction> &ans, ofstream &fout) {
    for (int i = 0; i < ans.size(); i++)
        fout << ans[i].num << "/" << ans[i].den << endl;
}

int main() {
    ofstream fout("frac1.out");
    ifstream fin("frac1.in");
    int n;
    bool flag[SIZE][SIZE];
    vector<fraction> ans;
    fraction frac;
    frac.den = 1;
    frac.num = 0;
    ans.push_back(frac);
    fin >> n;
    init(n, flag);
    solve(n, flag, ans);
    output(ans, fout);
    return 0;
}
