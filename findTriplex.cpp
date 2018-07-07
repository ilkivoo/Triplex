#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <cstring>
using namespace std;

class bindRNA {
private:
	string rna;
	string name;
	vector<long long> countWindowsBindingNuckleotid;
	void startRNAplfold(int l, int length) {
		string rnaSites = rna.substr(l, length);
		/** TODO  вызов RNAplfold*/
		string commandString = "echo \"" + rnaSites + "\" | ./ViennaRNA-2.4.6/src/bin/RNAplfold --print_onthefly --cutoff=0.7 ";
		system(commandString.c_str());
	}

	void parse(int l, int r) {
		cout << "parse " << l << " " << r << endl;
    	ifstream resultRNAplfold("plfold_basepairs");
    	int leftPair = -1, rightPair = -1;
    	double probability = 0;
    	while (!resultRNAplfold.eof()) {
        	resultRNAplfold >> leftPair >> rightPair >> probability;
        	countWindowsBindingNuckleotid[leftPair + l - 1]++;
        	countWindowsBindingNuckleotid[rightPair + r - 1]++;
    	}
    	remove("plfold_basepairs");
	}
public:
	bindRNA(string name, string rna) {
		this->rna = rna;
		this->name = name;
		countWindowsBindingNuckleotid.resize(rna.length());
	}

	void bind() {
		cout << "Bind started " << endl;
    	int l = 0;
    	int r = 199;
    	while (l < rna.length()) {
			startRNAplfold(l, r - l + 1);
			parse(l, r);
			l += 50;
			r += 50;
			if (r > rna.length()) {
				r = rna.length() - 1;
			}
		}
	}

	void printResult(string filename) {
		cout << "printResult \n";
		int ind = 0;
    	vector<pair<long long, long long>> ans;
		
		pair<long long, long long> curPair(-1, -1);

    	for (int i = 0; i < countWindowsBindingNuckleotid.size(); i++) {
    		if (countWindowsBindingNuckleotid[i] == 0) {
    			if (curPair.first == -1) {
    				curPair.first = i;
    				curPair.second = i;
    			}
    			else {
    				curPair.second = i;
    			}
    		}
    		else {
    			if (curPair.first != -1) {
    				ans.push_back(curPair);
    			}
    			curPair.first = -1;
    			curPair.second = -1;
    		}
    	}
    	if (curPair.first != -1) {
    		ans.push_back(curPair);
    	}

    	ofstream resultBind(filename);
    	for (int i = 0; i  <  ans.size(); i++) {
    		resultBind << name << ":" << ans[i].first << "-" << ans[i].second << endl << rna.substr(ans[i].first, ans[i].second - ans[i].first + 1) << endl;
    	}
	}
};




class Triplex {

};






int main() {
	string rna = "AGCCCCTAGCGCAGACGGCGGAGAGCAGAGAGGGAGCGCGCCTTGGCTCGCTGGCCTTGGCGGCGGCTCCTCAGGAGAGCTGGGGCGCCCACGAGAGGATCCCTCACCCGGGTCTCTCCTCAGGGATGACATCATCCGTCCACCTCCTTGTCTTCAAGGACCACCTCCTCTCCATGCTGAGCTGCTGCCAAGGGGCCTGCTGCCCATCTACACCTCACGAGGGCACTAGGAGCACGGTTTCCTGGATCCCACCAACATACAAAGCAGCCACTCACTGACCCCCAGGACCAGGATGGCAAAGGATGAAGAGGACCGGAACTGACCAGCCAGCTGTCCCTCTTACCTAAAGACTTAAACCAATGCCCTAGTGAGGGGGCATTGGGCATTAAGCCCTGACCTTTGCTATGCTCATACTTTGACTCTATGAGTACTTTCCTATAAGTCTTTGCTTGTGTTCACCTGCTAGCAAACTGGAGTGTTTCCCTCCCCAAGGGGGTGTCAGTCTTTGTCGACTGACTCTGTCATCACCCTTATGATGTCCTGAATGGAAGGATCCCTTTGGGAAATTCTCAGGAGGGGGACCTGGGCCAAGGGCTTGGCCAGCATCCTGCTGGCAACTCCAAGGCCCTGGGTGGGCTTCTGGAATGAGCATGCTACTGAATCACCAAAGGCACGCCCGACCTCTCTGAAGATCTTCCTATCCTTTTCTGGGGGAATGGGGTCGATGAGAGCAACCTCCTAGGGTTGTTGTGAGAATTAAATGAGATAAAAGAGGCCTCAGGCAGGATCTGGCATAGAGGAGGTGATCAGCAAATGTTTGTTGAAAAGGTTTGACAGGTCAGTCCCTTCCCACCCCTCTTGCTTGTCTTACTTGTCTTATTTATTCTCCAACAGCACTCCAGGCAGCCCTTGTCCACGGGCTCTCCTTGCATCAGCCAAGCTTCTTGAAAGGCCTGTCTACACTTGCTGTCTTCCTTCCTCACCTCCAATTTCCTCTTCAACCCACTGCTTCCTGACTCGCTCTACTCCGTGGAAGCACGCTCACAAAGGCACGTGGGCCGTGGCCCGGCTGGGTCGGCTGAAGAACTGCGGATGGAAGCTGCGGAAGAGGCCCTGATGGGGCCCACCATCCCGGACCCAAGTCTTCTTCCTGGCGGGCCTCTCGTCTCCTTCCTGGTTTGGGCGGAAGCCATCACCTGGATGCCTACGTGGGAAGGGACCTCGAATGTGGGACCCCAGCCCCTCTCCAGCTCGAAATCCCTCCACAGCCACGGGGACACCCTGCACCTATTCCCACGGGACAGGCTGGACCCAGAGACTCTGGACCCGGGGCCTCCCCTTGAGTAGAGACCCGCCCTCTGACTGATGGACGCCGCTGACCTGGGGTCAGACCCGTGGGCTGGACCCCTGCCCACCCCGCAGGAACCCTGAGGCCTAGGGGAGCTGTTGAGCCTTCAGTGTCTGCATGTGGGAAGTGGGCTCCTTCACCTACCTCACAGGGCTGTTGTGAGGGGCGCTGTGATGCGGTTCCAAAGCACAGGGCTTGGCGCACCCCACTGTGCTCTCAATAAATGTGTTTCCTGTCTTAACAAAAA";
	bindRNA tmp(">NR_002766", rna);
	tmp.bind();
	tmp.printResult("bindRNA");
}