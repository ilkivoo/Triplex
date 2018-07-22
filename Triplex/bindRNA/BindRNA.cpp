//
// Created by olya on 22.07.18.
//

#include "BindRNA.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void BindRNA::callRNAplFold(unsigned long l, unsigned long r) {
    cout << "call RNAplfold" << endl;
    string rnaSite = rna.substr(l, r - l + 1);
    string command = "echo \"" + rnaSite + "\" | " + pathForRNAplfold + " --print_onthefly --cutoff=0.7 ";
    system(command.c_str());
    cout << "RNAplfold finished" << endl;
}

void BindRNA::getBasePair(unsigned long l, unsigned long r) {
    cout << "get bind pairs" << endl;
    FILE *basePairFile = fopen("plfold_basepairs", "r");
    if (basePairFile == nullptr) {
        cout << "Cannot open file: plfold_basepairs" << endl;
    }
    ifstream basePairInputStream("plfold_basepairs");
    long long fisrt, second;
    double probability;
    while (!basePairInputStream.eof()) {
        basePairInputStream >> fisrt >> second >> probability;
        cout << l + fisrt - 1 << " " << l + second - 1 << " "<< isBind.size() << endl;
        isBind[l + fisrt - 1] = true;
        isBind[l + second - 1] = true;
    }
    cout << "finished parse bind pairs" << endl;
}

vector<RnaSites> BindRNA::getFreeSites() {
    vector<RnaSites> result;
    RnaSites curSite("", rnaName, 0, 0);
    for (int i = 0; i < rna.size(); i++) {
        if (isBind[i]) {
            if (!curSite.site.empty()) {
                curSite.right = i - 1;
                result.push_back(curSite);
                curSite.site = "";
            }
            curSite.left = i + 1;
        } else {
            curSite.site += rna[i];
        }
    }
    if (!curSite.site.empty()) {
        result.push_back(curSite);
    }
    for (auto rnaSite : result) {
        rnaSite.left++;
        rnaSite.right++;
    }
    return result;
}


BindRNA::BindRNA(const string &rna, const string &rnaName, const string &pathForRNAplfold) {
    this->rna = rna;
    this->rnaName = rnaName;
    this->pathForRNAplfold = pathForRNAplfold;
    isBind.resize(rna.size());
}

BindRNA::BindRNA(const std::string fileName, const std::string &pathForRNAplfold) {
    ifstream rnaIfstream(fileName);
    rnaIfstream >> rnaName;
    rnaIfstream >> rna;
    this->pathForRNAplfold = pathForRNAplfold;
    isBind.resize(rna.size());
}

vector<RnaSites> BindRNA::bind() {
    cout << "bind started" << endl;
    callRNAplFold(0, rna.size() - 1);
    getBasePair(0, rna.size() - 1);
    cout << "bind finished" << endl;
    return getFreeSites();
}

