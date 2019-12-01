#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<random>
#include<algorithm>
#include<stdlib.h>
using namespace std;

int main(){
	//����A�i���A�������ꂼ��vector�Ɋi�[
	vector<string> left;
	vector<string> center;
	vector<string> right;
	
	//�t�@�C���X�g���[�����當������ꎞ�I�Ɏ󂯎��ϐ���ݒ�
	string temp;
	
	//�Ƃ肠����test.txt�Ƃ����t�@�C����ǂݎ�邱�Ƃɂ���
	ifstream finput("test.txt");
	
	//���͂�tab��؂��2��ɌŒ肷��i������ς��邩���j
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
	
	//�����_���ɌĂяo�����߂̔ԍ������
	vector<int> order;
	for(int i=0;i<right.size();i++){
		order.push_back(i);
	}
	random_device rdm;
	shuffle(order.begin(),order.end(),rdm);
	
	//TeX�\�[�X�R�[�h�̍쐬
	ofstream foutput("draft.tex");
	foutput <<"\\documentclass[11pt,twocolumn,dvipdfmx]{jsarticle}\n";
	foutput <<"\\usepackage[french]{babel}";
	foutput <<"\\begin{document}\n";
	foutput <<"\\begin{table}[t]\n";
	foutput <<"\\begin{tabular}{|l|l|l|}\\hline\n";
	for(int i=0;i<right.size();i++){
		if(((i+1)%30==1)&&(i!=1)){	//30�ꂸ�V�����\�ɕύX����
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
	
	//�R���p�C�����s���]���ȃt�@�C��������
	system("ptex2pdf -l -ot -kanji=utf8 draft.tex");
	system("del draft.aux");
	system("del draft.log");
	system("del draft.tex");
	return 0;
}