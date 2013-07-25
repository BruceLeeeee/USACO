/*
ID: jl39301
PROG: clocks
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
#include <queue>
#include <cmath>
#include <cstring>

using namespace std;

typedef struct state state;
struct state {
    vector<int> clocks;
    vector<int> moves;
    int count[10];
    int opt;
};

vector<string> table(10);

void changeClocks(vector<int> &clocks, int m) {
    for (int i = 0; i < table[m].size(); i++) {
        int index = table[m][i] - 'A';
        clocks[index] = (clocks[index] + 3) % 12;
        if (clocks[index] == 0)
            clocks[index] = 12;
    }
}

bool isEndState(vector<int> &clocks) {
    for (int i = 0; i < clocks.size(); i++)
        if (clocks[i] != 12)
            return false;
    return true;
}

void output(vector<int> moves, ofstream &fout) {
    fout << moves[0];
    for (int i = 1; i < moves.size(); i++)
        fout << " " << moves[i];
    fout << endl;
}

int getClocksValue(vector<int> &clocks) {
    int clocksValue = 0;

    for (int i = 0; i < clocks.size(); i++)
        clocksValue += clocksValue * 4 + clocks[i] % 12 / 3;
    return clocksValue;
}

void initCount(state &s) {
    for (int i = 1; i <= 9; i++)
        s.count[i] = 0;
}

void bfs(vector<int> &clocks, ofstream &fout) {
    queue<state> q;
    //map<int, bool> visisted;
    bool visisted[2048576];
    state s;
    s.clocks = clocks;
    s.opt = 1;
    initCount(s);
    q.push(s);
    memset(visisted, 0, sizeof(visisted));
    if (isEndState(clocks))
        return;
    while (!q.empty()) {
        state cur = q.front();
        for (int i = cur.opt; i <= 9; i++) {
            state nextState = cur;
            changeClocks(nextState.clocks, i);
            nextState.moves.push_back(i);
            if (isEndState(nextState.clocks)) {
                output(nextState.moves, fout);
                return;
            }
            int clocksValue = getClocksValue(nextState.clocks);
            nextState.count[i]++;
            nextState.opt = i;
            if (nextState.count[i] <= 3 && visisted[clocksValue] == false) {
                q.push(nextState);
                visisted[clocksValue] = true;
            }
        }
        q.pop();
    }
}

void initTable() {
    table[0] = "ABDE";
    table[1] = "ABDE";
    table[2] = "ABC";
    table[3] = "BCEF";
    table[4] = "ADG";
    table[5] = "BDEFH";
    table[6] = "CFI";
    table[7] = "DEGH";
    table[8] = "GHI";
    table[9] = "EFHI";
}

int main() {
    ofstream fout("clocks.out");
    ifstream fin("clocks.in");
    vector<int> clocks;
    for (int i = 0; i < 9; i++) {
        int clock;
        fin >> clock;
        clocks.push_back(clock);
    }
    initTable();
    bfs(clocks, fout);
    return 0;
}
