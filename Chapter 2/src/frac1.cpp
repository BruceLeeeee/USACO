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

using namespace std;

struct fraction {
    int num;
    int den;
};

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool cmp(const fraction &a, const fraction &b) {
    return a.num * b.den <= b.num * a.den;
}

void solve(int n, vector<fraction> &ans) {

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            int num = i;
            int den = j;
            int factor = gcd(num, den);
            if (factor != 1)
                continue;
            fraction frac;
            frac.num = num;
            frac.den = den;
            ans.push_back(frac);
        }
    sort(ans.begin(), ans.end(), cmp);
}

void output(vector<fraction> &ans, ofstream &fout) {
    for (int i = 0; i < ans.size(); i++)
        fout << ans[i].num << "/" << ans[i].den << endl;
}

int main() {
    ofstream fout("frac1.out");
    ifstream fin("frac1.in");
    int n;
    vector<fraction> ans;
    fraction frac;
    frac.den = 1;
    frac.num = 0;
    ans.push_back(frac);
    fin >> n;
    solve(n, ans);
    output(ans, fout);
    return 0;
}
