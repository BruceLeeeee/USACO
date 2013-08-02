/*
ID: jl39301
PROG: castle
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

struct module {
    bool wall[4];
};

void convert(int walls, bool wall[4]) {
    for (int i = 0; i < 4; i++) {
        int r = walls % 2;
        walls /= 2;
        if (r == 1)
            wall[i] = true;
        else
            wall[i] = false;
    }
}

void init(int n, int m, module floorplan[55][55], ifstream &fin) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int walls;
            fin >> walls;
            convert(walls, floorplan[i][j].wall);
        }
}

void dfs(int n, int m, int x, int y, module floorplan[55][55], bool visited[55][55], int &count) {
    visited[x][y] = true;
    count++;
    int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    for (int i = 0; i < 4; i++) {
        int xNext = x + dir[i][0];
        int yNext = y + dir[i][1];
        if (xNext < 1 || xNext > n || yNext < 1 || yNext > m)
            continue;
        if (visited[xNext][yNext] == false && floorplan[x][y].wall[i] == false)
            dfs(n, m, xNext, yNext, floorplan, visited, count);
    }
}

void findAllRooms(int n, int m, module floorplan[55][55], int &roomNum, int &maxRoomSize) {
    int roomCount = 0;
    int maxRoom = 0;
    bool visited[55][55];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            visited[i][j] = false;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (visited[i][j] == false) {
                int count = 0;
                dfs(n, m, i, j, floorplan, visited, count);
                roomCount++;
                if (maxRoom < count)
                    maxRoom = count;
            }
    roomNum = roomCount;
    maxRoomSize = maxRoom;
}

bool isOuterEdge(int n, int m, int row, int col, int dir) {
    if (row == 1 && dir == 1)
        return true;
    if (col == m && dir == 2)
        return true;
    return false;
}

void removeWall(int x, int y, int dir, module floorplan[55][55]) {
    floorplan[x][y].wall[dir] = false;
    if (dir == 1)
        floorplan[x - 1][y].wall[3] = false;
    else
        floorplan[x][y + 1].wall[0] = false;
}

void installWall(int x, int y, int dir, module floorplan[55][55]) {
    floorplan[x][y].wall[dir] = true;
    if (dir == 1)
        floorplan[x - 1][y].wall[3] = true;
    else
        floorplan[x][y + 1].wall[0] = true;
}

void solve(int n, int m, module floorplan[55][55], ofstream &fout) {
    int roomNum;
    int maxRoomSize;
    int x, y, dir;

    findAllRooms(n, m, floorplan, roomNum, maxRoomSize);
    fout << roomNum << endl;
    fout << maxRoomSize << endl;
    for (int j = m; j >= 1; j--)
        for (int i = 1; i <= n; i++)
            for (int k = 2; k >= 1; k--)
                if (floorplan[i][j].wall[k]) {
                    if (isOuterEdge(n, m, i, j, k))
                        continue;
                    removeWall(i, j, k, floorplan);
                    int maxRoomSizeTmp = 0;
                    findAllRooms(n, m, floorplan, roomNum, maxRoomSizeTmp);
                    if (maxRoomSizeTmp >= maxRoomSize) {
                        maxRoomSize = maxRoomSizeTmp;
                        x = i;
                        y = j;
                        dir = k;
                    }
                    installWall(i, j, k, floorplan);
                }
    fout << maxRoomSize << endl;
    fout << x << " " << y << " ";
    if (dir == 1)
        fout << "N" << endl;
    else
        fout << "E" << endl;
}

int main() {
    ofstream fout("castle.out");
    ifstream fin("castle.in");
    int m, n;
    fin >> m >> n;
    module floorplan[55][55];
    init(n, m, floorplan, fin);
    solve(n, m, floorplan, fout);
    return 0;
}
