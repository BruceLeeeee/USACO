/*
ID: jl39301
PROG: lamps
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

#define SIZE 110

using namespace std;

void init(int &n, int &c, vector<int> &onLamps,
          vector<int> &offLamps, ifstream &fin) {
    fin >> n >> c;
    while(true) {
        int num;
        fin >> num;
        if (num == -1)
            break;
        onLamps.push_back(num);
    }
    while(true) {
        int num;
        fin >> num;
        if (num == -1)
            break;
        offLamps.push_back(num);
    }

}

void pressButton(vector<int> &ops, vector<int> &lamps) {
    for (int i = 0; i < ops.size(); i++) {
        switch(ops[i]) {
        case 1:
            for (int i = 1; i < lamps.size(); i++)
                lamps[i] ^= 1;
            break;
        case 2:
            for (int i = 1; i < lamps.size(); i += 2)
                lamps[i] ^= 1;
            break;
        case 3:
            for (int i = 2; i < lamps.size(); i += 2)
                lamps[i] ^= 1;
            break;
        case 4:
            for (int i = 1; i < lamps.size(); i += 3)
                lamps[i] ^= 1;
            break;
        }
    }
}

bool isConsistent(vector<int> &lamps, vector<int> &onLamps, vector<int> &offLamps) {
    for (int i = 0; i < onLamps.size(); i++)
        if (lamps[onLamps[i]] != 1)
            return false;
    for (int i = 0; i < offLamps.size(); i++)
        if (lamps[offLamps[i]] != 0)
            return false;
    return true;
}

string toString(vector<int> &lamps) {
    string str;
    for (int i = 1; i < lamps.size(); i++)
        str += (lamps[i] + '0');
    return str;
}

void dfs(int n, int count, vector<int> &onLamps, vector<int> &offLamps,
         vector<int> &ops, set<string> &ans) {
    if (count == 0) {
        vector<int> lamps;
        lamps.assign(n + 1, 1);
        pressButton(ops, lamps);
        if (isConsistent(lamps, onLamps, offLamps)) {
            string str = toString(lamps);
            //cout << str << endl;
            ans.insert(str);
        }
        return;
    }

    for (int i = 1; i <= 4; i++) {
        ops.push_back(i);
        dfs(n, count - 1, onLamps, offLamps, ops, ans);
        ops.pop_back();
    }

}

void solve(int n, int c, vector<int> &onLamps, vector<int> &offLamps, set<string> &ans) {
    if (c > 4)
        c = c - (c - 3) / 2 * 2;
    vector<int> ops;
    dfs(n, c, onLamps, offLamps, ops, ans);
}

void output(set<string> &ans, ofstream &fout) {
    if (ans.size() == 0) {
        fout << "IMPOSSIBLE" << endl;
        return;
    }
    for (set<string>::iterator itr = ans.begin(); itr != ans.end(); itr++)
        fout << *itr << endl;
}

int main() {
    ofstream fout("lamps.out");
    ifstream fin("lamps.in");
    int n, c;
    vector<int> onLamps;
    vector<int> offLamps;
    set<string> ans;
    init(n, c, onLamps, offLamps, fin);
    solve(n, c, onLamps, offLamps, ans);
    output(ans, fout);
    return 0;
}
