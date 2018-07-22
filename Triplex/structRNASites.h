//
// Created by olya on 22.07.18.
//

#ifndef TRIPLEX_STRUCTRNASITES_H
#define TRIPLEX_STRUCTRNASITES_H

#include <iostream>

struct RnaSites {
    std::string site;
    std::string rnaName;
    int left;
    int right;

    RnaSites(const std::string &site, const std::string &rnaName, int left, int right) {
        this->left = left;
        this->right = right;
        this->site = site;
        this->rnaName = rnaName;
    }
};

#endif //TRIPLEX_STRUCTRNASITES_H
