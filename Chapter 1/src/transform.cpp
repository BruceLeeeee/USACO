/*
ID: jl39301
PROG: transform
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

#define SIZE 11

using namespace std;

bool cmpSquare(int n, char square1[][SIZE], char square2[][SIZE]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (square1[i][j] != square2[i][j])
                return false;
    return true;
}

void copySquare(int n, char dst[][SIZE], char src[][SIZE]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dst[i][j] = src[i][j];
}

void transform1(int n, char before[][SIZE], char after[][SIZE]) {
    int k = 0;
    for (int j = 0; j < n; j++)
        for (int i = n - 1; i >= 0; i--) {
            after[k / n][k % n] = before[i][j];
            k++;
        }
}

void transform2(int n, char before[][SIZE], char after[][SIZE]) {
    int k = 0;
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j >= 0; j--) {
            after[k / n][k % n] = before[i][j];
            k++;
        }
}

void transform3(int n, char before[][SIZE], char after[][SIZE]) {
    int k = 0;
    for (int j = n - 1; j >= 0; j--)
        for (int i = 0; i < n; i++) {
            after[k / n][k % n] = before[i][j];
            k++;
        }
}

void transform4(int n, char before[][SIZE], char after[][SIZE]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            after[i][j] = before[i][n - j - 1];
}

void printSquare(int n, char square[][SIZE]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n;j ++)
            cout << square[i][j];
        cout << endl;
    }
}
int solve(int n, char beforeSquare[][SIZE], char afterSquare[][SIZE]) {
    char tmpSquare[SIZE][SIZE];
    char tmpSquare1[SIZE][SIZE];

    copySquare(n, tmpSquare, beforeSquare);
    transform1(n, beforeSquare, tmpSquare);
    //printSquare(n, tmpSquare);
    if (cmpSquare(n, tmpSquare, afterSquare))
        return 1;

    copySquare(n, tmpSquare, beforeSquare);
    transform2(n, beforeSquare, tmpSquare);
    if (cmpSquare(n, tmpSquare, afterSquare))
        return 2;

    copySquare(n, tmpSquare, beforeSquare);
    transform3(n, beforeSquare, tmpSquare);
    if (cmpSquare(n, tmpSquare, afterSquare))
        return 3;

    copySquare(n, tmpSquare, beforeSquare);
    transform4(n, beforeSquare, tmpSquare);
    if (cmpSquare(n, tmpSquare, afterSquare))
        return 4;

    copySquare(n, tmpSquare1, tmpSquare);
    transform1(n, tmpSquare, tmpSquare1);
    if (cmpSquare(n, tmpSquare1, afterSquare))
        return 5;

    copySquare(n, tmpSquare1, tmpSquare);
    transform2(n, tmpSquare, tmpSquare1);
    if (cmpSquare(n, tmpSquare1, afterSquare))
        return 5;

    copySquare(n, tmpSquare1, tmpSquare);
    transform3(n, tmpSquare, tmpSquare1);
    if (cmpSquare(n, tmpSquare1, afterSquare))
        return 5;

    if (cmpSquare(n, beforeSquare, afterSquare))
        return 6;
    return 7;
}

void test(int n, char beforeSquare[][SIZE]) {
    char tmp[SIZE][SIZE];
    transform1(n, beforeSquare, tmp);
    printSquare(n, tmp);
    cout << endl;

    transform2(n, beforeSquare, tmp);
    printSquare(n, tmp);
    cout << endl;

    transform3(n, beforeSquare, tmp);
    printSquare(n, tmp);
    cout << endl;

    transform4(n, beforeSquare, tmp);
    printSquare(n, tmp);
    cout << endl;
}

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
    int n;
    char beforeSquare[SIZE][SIZE];
    char afterSquare[SIZE][SIZE];

    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> beforeSquare[i];
    for (int i = 0; i < n; i++)
        fin >> afterSquare[i];
    //test(n, beforeSquare);
    fout << solve(n, beforeSquare, afterSquare) << endl;
    return 0;
}
