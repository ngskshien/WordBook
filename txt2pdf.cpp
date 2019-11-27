#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stdlib.h>
using namespace std;

int main(){
	vector<string> left;
	vector<string> right;
	string temp;
	ifstream finput("test.txt");
	while(true){
		finput >> temp;
		if(!finput) break;
		left.push_back(temp);
		finput >> temp;
		right.push_back(temp);
	}
	finput.close();
	ofstream foutput("draft.tex");
	foutput <<"\\documentclass{jsarticle}\n";
	foutput <<"\\begin{document}\n";
	foutput <<"\\begin{table}\n";
	foutput <<"\\begin{tabular}{|l|l|}\\hline\n";
	foutput <<"left column & right column \\\\\\hline\\hline \n";
	for(int i=0;i<right.size();i++){
		foutput << left[i] <<"&"<<right[i]<<"\\\\\\hline\n";
	}
	foutput <<"\\end{tabular}\n";
	foutput <<"\\end{table}\n";
	foutput <<"\\end{document}";
	foutput.close();
	system("ptex2pdf -l -ot -kanji=utf8 draft.tex");
	system("del draft.aux");
	system("del draft.log");
	system("del draft.tex");
	return 0;
}