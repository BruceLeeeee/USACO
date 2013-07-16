/*
ID: jl39301
PROG: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define M 5000
#define N 15

using namespace std;

char keypad[15][4] = {{'*', '*', '*'},
                       {'*', '*', '*'},
                       {'A', 'B', 'C'},
                       {'D', 'E', 'F'},
                       {'G', 'H', 'I'},
                       {'J', 'K', 'L'},
                       {'M', 'N', 'O'},
                       {'P', 'R', 'S'},
                       {'T', 'U', 'V'},
                       {'W', 'X', 'Y'}};
int wordCount;
bool flag;

int readDict(char lexicon[M][N], ifstream& dict) {
    int count = 0;

    while (dict >> lexicon[count]) {
        count++;
    }
    return count;
}

bool bsearch(string& name, char lexicon[][N]) {
    int i, j, m;
    i = 0;
    j = wordCount - 1;

    while (i <= j) {
        m = (i + j) / 2;
        if (strcmp(name.c_str(), lexicon[m]) == 0)
            return true;
        else if (strcmp(name.c_str(), lexicon[m]) < 0)
            j = m - 1;
        else
            i = m + 1;
    }
    return false;
}

void dfs(string& num, string& name, int i, ofstream& fout, char lexicon[][N]) {
    if (i >= num.length()) {
        if (bsearch(name, lexicon)) {
            fout << name << endl;
            flag = false;
        }
        return;
    }
    for (int j = 0; j < 3; j++) {
        name[i] = keypad[num[i] - '0'][j];
        dfs(num, name, i + 1, fout, lexicon);
    }
}

int main() {
    ofstream fout("namenum.out");
    ifstream fin("namenum.in");
    ifstream dict("dict.txt");
    char lexicon[M][N];

    wordCount = readDict(lexicon, dict);
    string num;
    string name;

    fin >> num;
    name = num;
    flag = true;
    dfs(num, name, 0, fout, lexicon);
    if (flag)
        fout << "NONE" << endl;
    return 0;
}
