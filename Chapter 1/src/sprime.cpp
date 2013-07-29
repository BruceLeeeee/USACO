/*
ID: jl39301
PROG: sprime
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

void output(vector<int> &ans, ofstream &fout) {
    for (int i = 0; i < ans.size(); i++)
        fout << ans[i] << endl;
}

bool isPrime(int num) {
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0)
            return false;
    return true;
}

void solve(int n, ofstream &fout) {
    vector<vector<int> > sprimeVs;
    vector<int> sprimes1;
    sprimes1.push_back(2);
    sprimes1.push_back(3);
    sprimes1.push_back(5);
    sprimes1.push_back(7);
    sprimeVs.push_back(sprimes1);
    for (int i = 0; i < 9; i++) {
        vector<int> prev = sprimeVs[i];
        if (i == n - 1) {
            output(prev, fout);
            return;
        }
        vector<int> cur;
        for (int j = 0; j < prev.size(); j++)
            for (int d = 1; d <= 9; d++) {
                int num = prev[j];
                num = num * 10 + d;
                if (isPrime(num))
                    cur.push_back(num);
            }
        sprimeVs.push_back(cur);
    }
}

int main() {
    ofstream fout("sprime.out");
    ifstream fin("sprime.in");
    int n;
    fin >> n;
    solve(n, fout);
    return 0;
}
