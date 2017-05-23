#pragma once

#include"Lexer.h"
#include<vector>

#define NUMOFPROC 12
#define MAXPROLEN 32
#define ACC 300

/*���ص�i������ʽ�ұߵķ��Ÿ���*/
int numofsym(int i);

/*��int�������ݴ���action������goto�����ķ���ֵ,��int����1xx������sxx,2xx������rxx,goto�����ķ���ֱֵ����С��100������ʾ*/

int action(int status, int symtype);	//�����״̬statusʱ����symtype���ŵ���һ������

void transform(char sym_str[MAXSTREAMLEN], int sym_int);	//�ѷ�����int����ת�����ַ�������char��������

class production {
private:
	/*����ʽ���Լ������*/
	void rule1();
	void rule2();
	void rule3();
	void rule4();
	void rule5();
	void rule6();
	void rule7();
	void rule8();
	void rule9();
	void rule10();
	void rule11();
public:
	symbol left;
	symbol rights[MAXPROLEN];
	int type;	//�ǵڼ�������ʽ
	production() :type(-1) {} //{ for (int i = 0;i < MAXPROLEN;i++)rights[i] = NULL; }
	int rightlen();	//���ز���ʽ�ұߵķ�������

	/*�������ʽ������*/
	void computeattributes();
};

/*�﷨���������*/
void erroranalyzer(int ststus, symbol nextsym);

/*�﷨�������������������������Ĳ���ʽѹ������*/
int parser(symbol symstream[], vector<production>& produs);