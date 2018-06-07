#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
using namespace std;


struct classcomp {
	bool operator() (const double& a, const double& b) const {
  		return a > b;
  	}
};

void getTotalRel(string fileName, unordered_map<string, double>& map, vector<string>& keys, set<double>& values)
{
    ifstream fis(fileName);
    string strtmp;
    getline(fis, strtmp);

    string dnaName, rnaName;
    double totalAbs, totalRel, gaAbs, gaRel, tcAbs, tcRel, gtAbs, gtRel;
    while (!fis.eof()) {
        fis >> dnaName >> rnaName >> totalAbs >> totalRel >> gaAbs >> gaRel >> tcAbs >> tcRel >> gtAbs >> gtRel;
        if (map.count(dnaName) == 0) {
            map[dnaName] = 1 - totalRel;
            keys.push_back(dnaName);
        }
        else {
            map[dnaName] *= (1 - totalRel);
        }
    }
    for (string key : keys) {
        values.insert(1 - map[key]);
        map[key] = 1 - map[key];
    }
}

int main()
{
    cout.setf(std::ios::fixed);
    cout.precision(11);
    unordered_map<string, double> triplexWithBkg;
    vector<string> keysOfTriplexWithBkg;
    set<double> valuesOfTriplexWithBkg;
    getTotalRel("../MEG3WithBkg/triplexMEG3andBkg.tpx.summary", triplexWithBkg, keysOfTriplexWithBkg, valuesOfTriplexWithBkg);

    unordered_map<string, double> triplexWithPeaks;
    vector<string> keysOfTriplexWithPeaks;
    set<double> valuesOfTriplexWithPeaks;
    getTotalRel("../MEG3WithPeaks/triplexMEG3andPeaks.tpx.summary", triplexWithPeaks, keysOfTriplexWithPeaks, valuesOfTriplexWithPeaks);

    set<double, classcomp> all;
    for (double x : valuesOfTriplexWithBkg) {
        all.insert(x);
    }
    for (double x : valuesOfTriplexWithPeaks) {
        all.insert(x);
    }

    int y = 0;
    int x = 0;
    double s = 0;
    double last = 0;
    vector<double> xs;
    vector<double> ys;
    for (double triplex : all) {
        if (valuesOfTriplexWithPeaks.find(triplex) != valuesOfTriplexWithPeaks.end()) {
            y++;
        }
        if (valuesOfTriplexWithBkg.find(triplex) != valuesOfTriplexWithBkg.end()) {
            x++;
        }
        xs.push_back((double)x);
        ys.push_back((double)y);
    }
    s = 0;
    last = 0;

    double maxx = 0, maxy = 0;
    for (int i  = 0; i < xs.size(); i++) {
    	if (xs[i] > maxx) {
    		maxx = xs[i];
    	}
    	if (ys[i] >maxy) {
    		maxy = ys[i];
    	}
    }

    for (int i = 0; i < xs.size(); i++) {
    	xs[i] = xs[i]/maxx;
    	ys[i] = ys[i]/maxy;
    }

    for (int i = 0; i < xs.size(); i++) {
        s += (xs[i] - last) * ys[i];
        last = xs[i];
    }
    cout << "AUC = " << s << endl;

    //xs and ys -  координаты для ROC кривой
}