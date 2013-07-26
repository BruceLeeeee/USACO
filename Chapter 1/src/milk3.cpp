/*
ID: jl39301
PROG: milk3
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

#define SIZE 22

using namespace std;

typedef struct node node;

void init(bool ans[SIZE], bool visisted[SIZE][SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        ans[i] = false;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++)
                visisted[i][j][k] = false;

}

void dfs(vector<int> &amount, vector<int> &capacity, bool ans[SIZE], bool visisted[SIZE][SIZE][SIZE]) {
    visisted[amount[0]][amount[1]][amount[2]] = true;
    if (amount[0] == 0)
        ans[amount[2]] = true;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i != j) {
                vector<int> amountTmp = amount;
                if (amountTmp[i] >= capacity[j] - amountTmp[j]) {
                    amountTmp[i] -= capacity[j] - amountTmp[j];
                    amountTmp[j] = capacity[j];
                } else {
                    amountTmp[j] += amountTmp[i];
                    amountTmp[i] = 0;
                }
                if (visisted[amountTmp[0]][amountTmp[1]][amountTmp[2]] == false)
                    dfs(amountTmp, capacity, ans, visisted);
            }
}

void output(int C, bool ans[SIZE], ofstream &fout) {
    int count = 0;
    for (int i = 0; i <= C; i++)
        if (ans[i]) {
            count++;
            if (count == 1)
                fout << i;
            else
                fout << " " << i;
        }
    fout << endl;
}

int main() {
    ofstream fout("milk3.out");
    ifstream fin("milk3.in");
    int A, B, C;
    bool ans[SIZE];
    bool visited[SIZE][SIZE][SIZE];
    vector<int> amount(3);
    vector<int> capacity(3);
    init(ans, visited);
    fin >> A >> B >> C;
    amount[0] = 0;
    amount[1] = 0;
    amount[2] = C;
    capacity[0] = A;
    capacity[1] = B;
    capacity[2] = C;
    dfs(amount, capacity, ans, visited);
    output(C, ans, fout);
    return 0;
}
