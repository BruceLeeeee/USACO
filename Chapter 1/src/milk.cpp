/*
ID: jl39301
PROG: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef struct farmer farmer;
struct farmer {
    int price;
    int amount;
};

bool cmp(const farmer &f1, const farmer &f2) {
    if (f1.price == f2.price)
        return f1.amount > f2.amount;
    return f1.price < f2.price;
}

int main() {
    ofstream fout("milk.out");
    ifstream fin("milk.in");
    vector<farmer> farmers;
    int gross = 0;
    int n, m;

    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        farmer f;
        fin >> f.price >> f.amount;
        farmers.push_back(f);
    }
    sort(farmers.begin(), farmers.end(), cmp);
    int i = 0;
    while (true) {
        if (i >= m)
            break;
        if (farmers.at(i).amount < n) {
            n -= farmers.at(i).amount;
            gross += farmers.at(i).price * farmers.at(i).amount;
        } else {
            gross += farmers.at(i).price * n;
            n = 0;
        }
        if (n == 0)
            break;
        i++;
    }
    fout << gross << endl;
    return 0;
}
