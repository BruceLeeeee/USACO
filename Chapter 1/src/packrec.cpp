/*
ID: jl39301
PROG: packrec
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
#include <climits>

using namespace std;

typedef struct rect rect;
struct rect {
    int w, l;
};

void rotate(rect &r) {
    int tmp;
    tmp = r.w;
    r.w = r.l;
    r.l = tmp;

}

int eval1(vector<rect> &permut, rect &r) {
    r.w = permut[0].w + permut[1].w + permut[2].w + permut[3].w;
    r.l = max(max(max(permut[0].l, permut[1].l), permut[2].l), permut[3].l);
    return r.w * r.l;
}

int eval2(vector<rect> &permut, rect &r) {
    r.w = max(permut[3].w, permut[0].w + permut[1].w + permut[2].w);
    r.l = max(max(permut[0].l, permut[1].l), permut[2].l) + permut[3].l;
    return r.w * r.l;
}

int eval3(vector<rect> &permut, rect &r) {
    r.w = permut[2].w + max(permut[0].w + permut[1].w, permut[3].w);
    r.l = max(permut[2].l, max(permut[0].l, permut[1].l) + permut[3].l);
    return r.w * r.l;
}

int eval4(vector<rect> &permut, rect &r) {
    r.w = permut[0].w + permut[2].w + max(permut[1].w, permut[3].w);
    r.l = max(permut[1].l + permut[3].l, max(permut[0].l, permut[2].l));
    return r.w * r.l;
}

int eval5(vector<rect> &permut, rect &r) {
    r.w = permut[1].w + permut[2].w + max(permut[0].w, permut[3].w);
    r.l = max(permut[0].l + permut[3].l, max(permut[1].l, permut[2].l));
    return r.w * r.l;
}

int eval6(vector<rect> &permut, rect &r) {
    r.l = max(permut[1].l + permut[2].l, permut[0].l + permut[3].l);

    if (permut[1].l + permut[2].l <= permut[3].l)
        r.w = max(permut[0].w, permut[3].w + max(permut[1].w, permut[2].w));
    else if (permut[3].l > permut[2].l && permut[3].l < permut[1].l + permut[2].l)
        r.w = max(permut[0].w + permut[1].w, max(permut[1].w + permut[3].w, permut[3].w + permut[2].w));
    else if (permut[3].l > permut[2].l && permut[3].l < permut[0].l + permut[2].l)
        r.w = max(permut[0].w + permut[1].w, max(permut[0].w + permut[3].w, permut[2].w + permut[3].w));
    else if (permut[3].l > permut[0].l + permut[2].l)
        r.w = max(permut[1].w, max(permut[0].w + permut[3].w, permut[2].w + permut[3].w));
    else if (permut[2].l == permut[3].l)
        r.w = max(permut[0].w + permut[1].w, permut[2].w + permut[3].w);
    return r.w * r.l;
}
void dfs(int i, int &min, vector<rect> &permut, vector<rect> &rest, vector<rect> &ans) {
    if (i >= 4) {

        rect r;
        int area;

        //layout 1
        area = eval1(permut, r);
        if (area < min)
            min = area;
        ans.push_back(r);

        //layout 2
        area = eval2(permut, r);
        if (area < min)
            min = area;
        ans.push_back(r);

        //layout 3
        area = eval3(permut, r);
        if (area < min)
            min = area;
        ans.push_back(r);

        //layout 4
        area = eval4(permut, r);
        if (area < min)
            min = area;
        ans.push_back(r);

        //layout 5
        area = eval5(permut, r);
        if (area < min)
            min = area;
        ans.push_back(r);

        //layout 6
        area = eval6(permut, r);
        if (area < min)
            min = area;
        ans.push_back(r);

        return;
    } else {
        for (int j = 0; j < rest.size(); j++) {
            rect r = rest[j];
            permut.push_back(r);
            vector<rect> restTmp = rest;
            restTmp.erase(restTmp.begin() + j);
            dfs(i + 1, min, permut, restTmp, ans);
            permut.pop_back();

            rotate(r);
            permut.push_back(r);
            dfs(i + 1, min, permut, restTmp, ans);

            permut.pop_back();
        }
    }
}

void output(vector<rect> &ans, ofstream &fout, int min) {
    set<int> widthS;

    for (int i = 0; i < ans.size(); i++) {
        if (ans[i].w > ans[i].l) {
            int tmp = ans[i].w;
            ans[i].w = ans[i].l;
            ans[i].l = tmp;
        }
        if (ans[i].w * ans[i].l == min)
            widthS.insert(ans[i].w);
    }
    for (set<int>::iterator itr = widthS.begin(); itr != widthS.end(); itr++)
        fout << *itr << " " << min / (*itr) << endl;
}

int main() {
    ofstream fout("packrec.out");
    ifstream fin("packrec.in");
    vector<rect> rects;
    int min = INT_MAX;

    for (int i = 0; i < 4; i++) {
        int w, l;
        fin >> w >> l;
        if (w > l) {
            int tmp = w;
            w = l;
            l = tmp;
        }
        rect r;
        r.w = w;
        r.l = l;
        rects.push_back(r);
    }
    vector<rect> permut;
    vector<rect> rest = rects;
    vector<rect> ans;
    dfs(0, min, permut, rest, ans);
    fout << min << endl;
    output(ans, fout, min);
    return 0;
}
