/*
ID: jl39301
PROG: ariprog
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
#include <cstring>

using namespace std;

#define SIZE 125010

typedef struct sequence sequence;
struct sequence {
    int a, b;
};

void createSet(int m, bool hash[], vector<int> &bisquares) {
    //memset(hash, 0, sizeof(hash));
    for (int i = 0; i <= m * m * 2; i++)
        hash[i] = false;
    for (int p = 0; p <= m; p++)
        for (int q = 0; q <= m; q++)
            hash[p * p + q * q] = true;
    for (int i = 0; i <= m * m * 2; i++)
        if (hash[i])
            bisquares.push_back(i);
}

bool seqInSet(int a, int b, int n, bool hash[]) {
    for (int i = 1; i < n - 1; i++) {
        int Xi = a + b * i;
        if (!hash[Xi])
            return false;
    }
    return true;
}

bool cmp(const sequence &s1, const sequence &s2) {
    if (s1.b < s2.b)
        return true;
    else if (s1.b == s2.b && s1.a <= s2.a)
        return true;
    return false;
}

void output(vector<sequence> &ans, ofstream &fout) {
    if (ans.size() == 0)
        fout << "NONE" << endl;
    else {
        for (int i = 0; i < ans.size(); i++)
            fout << ans[i].a << " " << ans[i].b << endl;
    }
}

void solve(int n, int m, ofstream &fout) {
    bool hash[SIZE];
    vector<sequence> ans;
    vector<int> bisquares;

    createSet(m, hash, bisquares);
    for (int i = 0; i < bisquares.size(); i++) {
        int a = bisquares[i];
        for (int j = bisquares.size() - 1; j >= i; j--) {
            int Xn = bisquares[j];
            int b = (Xn - a) / (n - 1);
            if (b * (n - 1) != (Xn - a) || b == 0)
                continue;
            if (seqInSet(a, b, n, hash)) {
                sequence s;
                s.a = a;
                s.b =b;
                ans.push_back(s);
            }
        }
    }
    sort(ans.begin(), ans.end(), cmp);
    output(ans, fout);
}

int main() {
    ofstream fout("ariprog.out");
    ifstream fin("ariprog.in");
    int n, m;
    fin >> n >> m;
    solve(n, m, fout);
    return 0;
}
