#include <iostream>
#include <cstring>
#include "bindRNA/BindRNA.h"
#include "Triplexator/Triplexator.h"
using namespace std;

void callTriplexator() {

}

int main(int argc, char* argv[]) {

    string rnaFile;
    string dnaFile;
    string outputDirectory;
    string outputFile;
    string commandForRNAplfold;
    string commandForTriplexator;
    string fileForFreeRNASites;

    cout << " введите файл с рнк" << endl;
    cin >> rnaFile;
    cout << " Введите файл с днк" << endl;
    cin >> dnaFile;
    cout << "Введите команду для запуска триплексатора ( по умолчанию triplexator)" << endl;
    cin >> commandForTriplexator;
    if (commandForTriplexator.empty()) {
        commandForTriplexator = "triplexator";
    }

    cout << "Введите команду для запуска RNAplfold ( по умолчанию RNAplfold )" << endl;
    cin >> commandForRNAplfold;
    if (commandForRNAplfold.empty()) {
        commandForRNAplfold = "RNAplfold ";
    }

    cout << "Введите папку для сохранения результата (по умолчанию текущая директория" << endl;
    cin >> outputDirectory;
    if (outputDirectory.empty()) {
        outputDirectory = "." ;
    }

    cout << "Введите выходной файл ( по умолчанию triplex.tpx)" << endl;
    cin >> outputFile;
    if (outputFile.empty()) {
        outputFile = "triplex.tpx" ;
    }

    cout << "Введите файл, в который будут записаны свободные участки РНК(по умолчанию freeSitesRna)" << endl;
    cin >> fileForFreeRNASites;
    if (fileForFreeRNASites.empty()) {
        fileForFreeRNASites = "freeSitesRna";
    }

    BindRNA bindRNA(rnaFile, commandForRNAplfold);
    Triplexator triplexator(commandForTriplexator);
    triplexator.callTriplexator(fileForFreeRNASites, bindRNA.bind(), dnaFile, outputDirectory, outputFile);
    /*string rna = "AGCCCCTAGCGCAGACGGCGGAGAGCAGAGAGGGAGCGCGCCTTGGCTCGCTGGCCTTGGCGGCGGCTCCTCAGGAGAGCTGGGGCGCCCACGAGAGGATCCCTCACCCGGGTCTCTCCTCAGGGATGACATCATCCGTCCACCTCCTTGTCTTCAAGGACCACCTCCTCTCCATGCTGAGCTGCTGCCAAGGGGCCTGCTGCCCATCTACACCTCACGAGGGCACTAGGAGCACGGTTTCCTGGATCCCACCAACATACAAAGCAGCCACTCACTGACCCCCAGGACCAGGATGGCAAAGGATGAAGAGGACCGGAACTGACCAGCCAGCTGTCCCTCTTACCTAAAGACTTAAACCAATGCCCTAGTGAGGGGGCATTGGGCATTAAGCCCTGACCTTTGCTATGCTCATACTTTGACTCTATGAGTACTTTCCTATAAGTCTTTGCTTGTGTTCACCTGCTAGCAAACTGGAGTGTTTCCCTCCCCAAGGGGGTGTCAGTCTTTGTCGACTGACTCTGTCATCACCCTTATGATGTCCTGAATGGAAGGATCCCTTTGGGAAATTCTCAGGAGGGGGACCTGGGCCAAGGGCTTGGCCAGCATCCTGCTGGCAACTCCAAGGCCCTGGGTGGGCTTCTGGAATGAGCATGCTACTGAATCACCAAAGGCACGCCCGACCTCTCTGAAGATCTTCCTATCCTTTTCTGGGGGAATGGGGTCGATGAGAGCAACCTCCTAGGGTTGTTGTGAGAATTAAATGAGATAAAAGAGGCCTCAGGCAGGATCTGGCATAGAGGAGGTGATCAGCAAATGTTTGTTGAAAAGGTTTGACAGGTCAGTCCCTTCCCACCCCTCTTGCTTGTCTTACTTGTCTTATTTATTCTCCAACAGCACTCCAGGCAGCCCTTGTCCACGGGCTCTCCTTGCATCAGCCAAGCTTCTTGAAAGGCCTGTCTACACTTGCTGTCTTCCTTCCTCACCTCCAATTTCCTCTTCAACCCACTGCTTCCTGACTCGCTCTACTCCGTGGAAGCACGCTCACAAAGGCACGTGGGCCGTGGCCCGGCTGGGTCGGCTGAAGAACTGCGGATGGAAGCTGCGGAAGAGGCCCTGATGGGGCCCACCATCCCGGACCCAAGTCTTCTTCCTGGCGGGCCTCTCGTCTCCTTCCTGGTTTGGGCGGAAGCCATCACCTGGATGCCTACGTGGGAAGGGACCTCGAATGTGGGACCCCAGCCCCTCTCCAGCTCGAAATCCCTCCACAGCCACGGGGACACCCTGCACCTATTCCCACGGGACAGGCTGGACCCAGAGACTCTGGACCCGGGGCCTCCCCTTGAGTAGAGACCCGCCCTCTGACTGATGGACGCCGCTGACCTGGGGTCAGACCCGTGGGCTGGACCCCTGCCCACCCCGCAGGAACCCTGAGGCCTAGGGGAGCTGTTGAGCCTTCAGTGTCTGCATGTGGGAAGTGGGCTCCTTCACCTACCTCACAGGGCTGTTGTGAGGGGCGCTGTGATGCGGTTCCAAAGCACAGGGCTTGGCGCACCCCACTGTGCTCTCAATAAATGTGTTTCCTGTCTTAACAAAAA" << endl;
    string command = "./../../../ViennaRNA-2.4.8/src/bin/RNAplfold" << endl;
    BindRNA bind(rna, ">NR_002766", command);
    for (auto str : bind.bind()) {
        cout << str.site << " " << str.left << " " << str.right << endl;
    }
    const string x = "./../../triplexator/bin/triplexator" << endl;
    Triplexator triplexator(x);
    string a1 = "lalalala" << endl;
    string a2 = "../../data/_bkg.fna" << endl;
    string a3 = "tmp" << endl;
    string a4 = "tmp.tpx" << endl;
    triplexator.callTriplexator(a1, bind.bind(), a2, a3, a4);*/
    return 0;
}