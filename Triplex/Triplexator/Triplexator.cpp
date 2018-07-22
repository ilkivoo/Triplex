//
// Created by olya on 22.07.18.
//

#include <vector>
#include "Triplexator.h"
#include <fstream>
#include <sys/stat.h>

using namespace std;

void printRNASites(const string &filename, const vector<RnaSites> &rnaSites) {
    ofstream rnaSitesOfstream(filename);
    for (auto rnaSite:rnaSites) {
        rnaSitesOfstream << rnaSite.rnaName << ":" << rnaSite.left << "-" << rnaSite.right << endl;
        rnaSitesOfstream << rnaSite.site << endl;
        rnaSitesOfstream << endl;
    }

}
/* sudo triplexator/bin/triplexator -l 10 -fm 0 -of 1 -od MEG3WithBkg -o triplexMEG3andBkg.tpx -ss data/_MEG3.fna -ds data/_bkg.fna */

void Triplexator::callTriplexator(const string &rnaFileName, const vector<RnaSites> &rnaSites,
                                  const string &dnaFileName, const string &dirName, const string &outputfile) {
    cout << "call triplexator" << endl;
    printRNASites(rnaFileName, rnaSites);
    mkdir(dirName.c_str(), NULL);
    string command = pathForTriplexator + " -l 10 -fm 0 -of 1 -od " + dirName+" -o "+ outputfile+" -ss " + rnaFileName + " -ds " + dnaFileName;
    system(command.c_str());
    cout << "triplexator finished" << endl;

}

Triplexator::Triplexator(const std::string &pathForTriplexator) {
    this->pathForTriplexator = pathForTriplexator;
}