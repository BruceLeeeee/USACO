/*
ID: jl39301
PROG: calfflac
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

using namespace std;

typedef struct location location;
struct location {
    int r, c;
};

void init(vector<string> &original, string &letterStr, vector<location> &locs) {
    for (int i = 0; i < original.size(); i++) {
        string str = original[i];
        for (int j = 0; j < str.size(); j++)
            if (isalpha(str[j])) {
                char ch = str[j];
                ch = tolower(ch);
                letterStr += ch;
                location loc;
                loc.r = i;
                loc.c = j;
                locs.push_back(loc);
            }
    }

}

void output(vector<string> &original, int max, location &ansStart, location &ansEnd, ofstream &fout) {
    fout << max << endl;
    string str = original[ansStart.r];

    if (ansStart.r == ansEnd.r) {
        fout << str.substr(ansStart.c, ansEnd.c - ansStart.c + 1) << endl;
    } else {
        fout << str.substr(ansStart.c) << endl;

        for (int i = ansStart.r + 1; i < ansEnd.r; i++)
            fout << original[i] << endl;

        str = original[ansEnd.r];
        fout << str.substr(0, ansEnd.c + 1) << endl;
    }


}

void solve(vector<string> &original, string &letterStr, vector<location> &locs, ofstream &fout) {
    int max = 0;
    location ansStart;
    location ansEnd;

    for (int m = 0; m < letterStr.size(); m++) {
        int count = 1;
        int p = 0;
        for (int i = 1; i <= 1000; i++)
            if (m - i >= 0 && m + i < letterStr.size()
                && letterStr[m - i] == letterStr[m + i]) {
                count += 2;
                p = i;
            } else break;
        if (count > max) {
            max = count;
            ansStart = locs[m - p];
            ansEnd = locs[m + p];
        }

        count = 0;
        p = 0;
        for (int i = 1; i <= 1000; i++)
            if (m - i + 1 >= 0 && m + i < letterStr.size()
                && letterStr[m - i + 1] == letterStr[m + i]) {
                    count += 2;
                    p = i;
                } else break;
        if (count > max) {
            max = count;
            ansStart = locs[m - p + 1];
            ansEnd = locs[m + p];
        }
    }
    output(original, max, ansStart, ansEnd, fout);
}

int main() {
    ofstream fout("calfflac.out");
    ifstream fin("calfflac.in");
    vector<string> original;
    string letterStr;
    vector<location> locs;

    while (!fin.eof()) {
        string str;
        getline(fin, str);
        original.push_back(str);
    }
    init(original, letterStr, locs);
    solve(original, letterStr, locs, fout);
    return 0;
}
