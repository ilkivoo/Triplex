#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
using namespace std;

struct piece {
    int l;
    int r;
    string str;
};

string meg3, name;
vector<long long> a;
vector<piece> ans;

void writeMeg3Sites(int l, int r)
{
    cout << "writeMeg3Sites" << endl;
    ofstream outMeg3Site("Meg3Site.fna");
    outMeg3Site << name << endl;
    for (int i = l; i <= r; i++) {
        outMeg3Site << meg3[i];
    }
}

void startScript()
{
    cout << "startScript" << endl;
    system("./startVienna.sh");
}

void parse(int l1, int r1)
{
    cout << "parse " << l1 << " " << r1 << endl;
    ifstream inbindNuck("NR_002766_basepairs");
    int l = -1, r = -1;
    double pr = 0;
    while (!inbindNuck.eof()) {
        inbindNuck >> l >> r >> pr;
        a[l1 + l - 1]++;
        a[l1 + r - 1]++;
    }
}

int move()
{
    cout << "move" << endl;
    int l = 0;
    int r = 200;
    while (r < meg3.length()) {
		writeMeg3Sites(l, r);
		startScript();
		parse(l, r);
		l += 50;
		r += 50;
	}
    r = meg3.length() - 1;
    writeMeg3Sites(l, r);
    startScript();
    parse(l, r);
}

int main()
{
    ifstream inMeg3("../data/_MEG3.fna");
    inMeg3 >> name;
    inMeg3 >> meg3;
    a.resize(meg3.length(), 0);
    move();

    int l = -1;
    int r = -1;
    int ind = 0;

    piece tmp;
    tmp.l = -1;
    tmp.r = -1;
    tmp.str = "";

    ans.push_back(tmp);

    for (int i = 0; i < a.size(); i++) {
        if (a[i] == 0) {
            if (l == -1) {
                ans[ind].l = i;
                ans[ind].r = i;
                l = i;
                r = i;
            }
            r = i;
            ans[ind].r = i;
            ans[ind].str = ans[ind].str + meg3[i];
        }
        else {
            if (r != -1) {
                ans[ind].r = r;
                ans.push_back(tmp);
                ind++;
            }

            l = -1;
            r = -1;
        }
    }

    if (r != -1) {
        ans[ind].r = r;
    }

    ofstream out("MEG3sites");
    for (int i = 0; i < ans.size() - 1; i++) {
        out << name << ":" << ans[i].l << "-" << ans[i].r << endl
            << ans[i].str << endl;
    }
    remove("Meg3Site.fna");
    remove("1.out");
}
