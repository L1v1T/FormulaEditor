#pragma once

#include<fstream>
#include<iostream>

#define SUCCEED 0
#define FAIL 1

#define UNDERSCORE 0
#define CARET 1
#define L_BRACE 2
#define R_BRACE 3
#define L_PAR 4
#define R_PAR 5
#define INT 6
#define SUM 7
#define ID 8
#define NUMBER 9
#define BLANK 10
#define DOLLAR 11
#define S 12
#define B 13
#define _S 14

#define INI 52

#define SPA_TAB	99	//����һ��space��tab
#define CORRECT 100	//����һ����ȷ�ļǺ�
#define ERROR1 101	//'\'������ַ�������
#define ERROR2 102	//����һ���Ƿ��ַ�

#define MAXSTREAMLEN 512

/*���ż̳�size����ʱ��ѡ��*/
#define NORMAL 0
#define SHRINK 1
#define ENLAGER 2

/*���ż̳�top����ʱ��ѡ��*/
//#define NORMAL 0
#define UPER 1
#define DOWNER 2

#define RATE 0.5

using namespace std;

void readinnum(ifstream &in_f, char *ch);	//�ݹ齫���ֺ�������ֶ���

void readinletterornum(ifstream &in_f, char *ch);	//�ݹ齫��ĸ������ŵ����ֻ���ĸ����

bool x7issum(ifstream &in_f);	//����һ��'\'�Ժ��жϺ�����û�и�"sum"

bool x7isint(ifstream &in_f);	//����һ��'\'�Ժ��жϺ�����û�и�"int"

bool x7isblank(ifstream &in_f);	//����һ��'\'�Ժ��жϺ�����û�и�"blank"

class symbol {
private:
	char value[MAXSTREAMLEN];
	int type;
	int left;
	int top;
	int len;
	int size;
public:
	int linkpos;
	symbol() :type(INI), left(-1), top(-1), len(-1), size(-1), linkpos(-1) {
		for (int i = 0;i < MAXSTREAMLEN;i++) { value[i] = 0; }
	}

	/*��ʼ��size��top��left���ֵ*/
	void init(int inisize, int initop, int inileft);

	/*����һ���Ǻſ���size��top��left��len����*/
	void copyattributes(symbol sym);

	void nonter(int symtype);	//���ս��
	int readin(ifstream &in_f);	//��ifstream����򿪵��ļ������ַ������ؼǺ�

	char* seevalue() { return value; }	//�ⲿ�鿴�Ǻ�ֵ
	int seetype() { return type; }	//�ⲿ�鿴�Ǻ�����
	int seeleft() { return left; }	//�ⲿ�鿴lelft����ֵ
	int seetop() { return top; }	//�ⲿ�鿴top����ֵ
	int seelen() { return len; }	//�ⲿ�鿴len����ֵ
	int seesize() { return size; }	//�ⲿ�鿴size����ֵ

	symbol& operator=(const symbol &);	//���ظ�ֵ������=

	/*�鿴�����Ƿ��Ѿ����㣬�Ѽ��������true�����򷵻�false*/
	bool checkleft();
	bool checktop();
	bool checklen();
	bool checksize();

	/*����top����*/
	void computetop(symbol parent, int func);

	/*����size����*/
	void computesize(symbol parent, int func);

	/*����len����*/
	void computelen();	//���ȿ�ֱ�Ӽ���
	void computelen(symbol child);	//���ڵ㳤����һ�����ӽ��ĳ���
	void computelen(symbol child1, symbol child2);	//���ڵ㳤�����������ӽ��֮��
	void computelen(symbol child1, symbol child2, symbol child3);	//���ڵ㳤�����������ӽ��֮��

	/*����left����*/
	void computeleft(symbol parent);	//ֱ�Ӽ̳�
	void computeleft(symbol parent, int offset);	//ƫ��
};

int x7getsymbolstream(ifstream &in_f, symbol symstream[MAXSTREAMLEN]);	//���ļ������ַ����������ɷ�����������symstream