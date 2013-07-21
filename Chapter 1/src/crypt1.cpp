/*
ID: jl39301
PROG: crypt1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<int> getDigits(set<int> &digitSet) {
    vector<int> digits;
    for (set<int>::iterator itr = digitSet.begin(); itr != digitSet.end(); itr++)
        digits.push_back(*itr);
    return digits;
}

bool isValid(int num, int len, set<int> &digitSet) {
    int count = 0;

    while (true) {
        if (num == 0)
            break;
        count++;
        int r = num % 10;
        if (digitSet.find(r) == digitSet.end())
            return false;
        num /= 10;
    }
    if (count == len)
        return true;
    return false;
}

int solve(int n, set<int> &digitSet) {
    vector<int> digits = getDigits(digitSet);
    int count = 0;

    for (int i = 0; i < digits.size(); i++)
        for (int j = 0; j < digits.size(); j++)
            for (int k = 0; k < digits.size(); k++) {
                int firstNum = digits[i] * 100 + digits[j] * 10 + digits[k];
                for (int I = 0; I < digits.size(); I++)
                    for (int J = 0; J < digits.size(); J++) {
                        int partial1 = firstNum * digits[I];
                        int partial2 = firstNum * digits[J];
                        if (!isValid(partial1, 3, digitSet))
                            continue;
                        if (!isValid(partial2, 3, digitSet))
                            continue;
                        int product = partial1 + partial2 * 10;
                        if (!isValid(product, 4, digitSet))
                            continue;
                        count++;
                    }

            }
    return count;
}

int main() {
    ofstream fout("crypt1.out");
    ifstream fin("crypt1.in");
    int n;
    set<int> digitSet;
    fin >> n;
    for (int i = 0; i < n; i++) {
        int digit;
        fin >> digit;
        digitSet.insert(digit);
    }
    fout << solve(n, digitSet) << endl;

    return 0;
}
