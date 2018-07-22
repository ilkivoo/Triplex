//
// Created by olya on 22.07.18.
//

#ifndef TRIPLEX_TRIPLEXATOR_H
#define TRIPLEX_TRIPLEXATOR_H

#include "../structRNASites.h"

class Triplexator {
private:
    std::string pathForTriplexator;
public:
    void callTriplexator(const std::string &rnaFileName, const std::vector<RnaSites> &rnaSites,
                         const std::string &dnaFileName, const std::string &dirName, const std::string &outputfile);

    Triplexator(const std::string &pathForTriplexator);
};


#endif //TRIPLEX_TRIPLEXATOR_H
