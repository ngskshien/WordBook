#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<random>
#include<algorithm>
#include<stdlib.h>
using namespace std;

int main(){
	//原語、品詞、訳語をそれぞれvectorに格納
	vector<string> left;
	vector<string> center;
	vector<string> right;
	
	//ファイルストリームから文字列を一時的に受け取る変数を設定
	string temp;
	
	//とりあえずtest.txtというファイルを読み取ることにする
	ifstream finput("test.txt");
	
	//入力はtab区切りで2列に固定する（いずれ変えるかも）
	while(true){
		getline(finput,temp,'\t');
		if(!finput) break;
		left.push_back(temp);
		getline(finput,temp,'\t');
		center.push_back(temp);
		getline(finput,temp,'\n');
		right.push_back(temp);
	}
	finput.close();
	
	//ランダムに呼び出すための番号を作る
	vector<int> order;
	for(int i=0;i<right.size();i++){
		order.push_back(i);
	}
	random_device rdm;
	shuffle(order.begin(),order.end(),rdm);
	
	//TeXソースコードの作成
	ofstream foutput("draft.tex");
	foutput <<"\\documentclass[11pt,twocolumn,dvipdfmx]{jsarticle}\n";
	foutput <<"\\usepackage[french]{babel}";
	foutput <<"\\begin{document}\n";
	foutput <<"\\begin{table}[t]\n";
	foutput <<"\\begin{tabular}{|l|l|l|}\\hline\n";
	for(int i=0;i<right.size();i++){
		if(((i+1)%30==1)&&(i!=1)){	//30語ずつ新しい表に変更する
			foutput <<"\\end{tabular}\n";
			foutput <<"\\end{table}\n";
			foutput <<"\\newpage";
			foutput <<"\\begin{table}[t]\n";
			foutput <<"\\begin{tabular}{|l|l|l|}\\hline\n";
		}
		foutput << left[order[i]] <<"&"<<center[order[i]]<<"&"<<right[order[i]]<<"\\\\\\hline\n";
	}
	foutput <<"\\end{tabular}\n";
	foutput <<"\\end{table}\n";
	foutput <<"\\end{document}";
	foutput.close();
	
	//コンパイルを行い余分なファイルを消す
	system("ptex2pdf -l -ot -kanji=utf8 draft.tex");
	system("del draft.aux");
	system("del draft.log");
	system("del draft.tex");
	return 0;
}