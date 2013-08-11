/*
ID: jl39301
PROG: preface
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

#define SIZE 3500

using namespace std;

struct number {
    bool computed;
    vector<int> markCount;
};

void init(int n, number num[SIZE]) {
    for (int i = 1; i <= n; i++)
        num[i].computed = false;

    for (int i = 1; i <= 10; i++) {
        num[i].markCount.assign(10, 0);
        num[i].computed = true;
    }

    num[1].markCount[0] = 1;
    num[2].markCount[0] = 2;
    num[3].markCount[0] = 3;
    num[4].markCount[0] = 1;
    num[4].markCount[1] = 1;
    num[5].markCount[1] = 1;
    num[6].markCount[0] = 1;
    num[6].markCount[1] = 1;
    num[7].markCount[0] = 2;
    num[7].markCount[1] = 1;
    num[8].markCount[0] = 3;
    num[8].markCount[1] = 1;
    num[9].markCount[0] = 1;
    num[9].markCount[2] = 1;
    num[10].markCount[2] = 1;

    for (int i = 10; i <= 100; i += 10) {
        num[i].markCount = num[i / 10].markCount;
        num[i].markCount.insert(num[i].markCount.begin(), 0);
        num[i].markCount.insert(num[i].markCount.begin(), 0);
        num[i].computed = true;
    }

    for (int i = 100; i <= 1000; i += 100) {
        num[i].markCount = num[i / 10].markCount;
        num[i].markCount.insert(num[i].markCount.begin(), 0);
        num[i].markCount.insert(num[i].markCount.begin(), 0);
        num[i].computed = true;
    }

    for (int i = 1000; i <= 3000; i += 1000) {
        num[i].markCount = num[i / 10].markCount;
        num[i].markCount.insert(num[i].markCount.begin(), 0);
        num[i].markCount.insert(num[i].markCount.begin(), 0);
        num[i].computed = true;
    }
}

void add(vector<int> &v1, vector<int> &v2) {
    for (int i = 0; i < 7; i++)
        v1[i] += v2[i];
}

void dp(int n, number num[SIZE], vector<int> &markCount) {
    for (int i = 1; i <= n; i++)
        if (num[i].computed) {
            add(markCount, num[i].markCount);
        } else {
            num[i].markCount.assign(10, 0);
            int firstDigit;
            int tmp;
            int r;
            if (i / 1000 != 0) {
                firstDigit = i / 1000;
                tmp = 1000;
                r = i % 1000;
            } else if (i / 100 != 0) {
                firstDigit = i / 100;
                tmp = 100;
                r = i % 100;
            } else if (i / 10 != 0) {
                firstDigit = i / 10;
                tmp = 10;
                r = i % 10;
            }
            add(num[i].markCount, num[firstDigit * tmp].markCount);
            add(num[i].markCount, num[r].markCount);
            add(markCount, num[i].markCount);
            num[i].computed = true;
        }
}

void output(vector<int> &markCount, ofstream &fout) {
    string mark = "IVXLCDM";
    int highest;
    for (int i = 6; i >= 0; i--)
        if (markCount[i] != 0) {
            highest = i;
            break;
        }
    for (int i = 0; i <= highest; i++)
        fout << mark[i] << " " << markCount[i] << endl;
}

int main() {
    ofstream fout("preface.out");
    ifstream fin("preface.in");
    number num[SIZE];
    vector<int> markCount;
    int n;
    fin >> n;
    init(n, num);
    markCount.assign(10, 0);
    dp(n, num, markCount);
    output(markCount, fout);
    return 0;
}
