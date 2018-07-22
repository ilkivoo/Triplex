//
// Created by olya on 22.07.18.
//

#ifndef TRIPLEX_BINDRNA_H
#define TRIPLEX_BINDRNA_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include "../structRNASites.h"
class BindRNA {
private:
    std::string rna;
    std:: string rnaName;
    std::string pathForRNAplfold;
    std::vector<bool> isBind;

    void callRNAplFold(unsigned long l, unsigned long r);

    void getBasePair(unsigned long l, unsigned long r);

    std::vector<RnaSites> getFreeSites();


public:
    BindRNA(const std::string &rna,  const std::string &rnaName, const std::string &pathForRNAplfold);
    BindRNA(const std:: string fileName, const std::string &pathForRNAplfold) ;

    std::vector<RnaSites> bind();
};

#endif //TRIPLEX_BINDRNA_H
