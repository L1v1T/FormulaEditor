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

#define SPA_TAB_ENTER	99	//读到一个space或tab或enter
#define CORRECT 100	//读入一个正确的记号
#define ERROR1 101	//'\'后面的字符串不对
#define ERROR2 102	//读到一个非法字符

#define MAXSTREAMLEN 512

/*符号继承size属性时的选项*/
#define NORMAL 0
#define SHRINK 1
#define ENLAGER 2

/*符号继承top属性时的选项*/
#define UPER 1
#define DOWNER 2

#define RATE 0.5

using namespace std;

void readinnum(ifstream &in_f, char *ch);	//递归将数字后面的数字读入

void readinletterornum(ifstream &in_f, char *ch);	//递归将字母后面跟着的数字或字母读入

bool x7issum(ifstream &in_f);	//读到一个'\'以后判断后面有没有跟"sum"

bool x7isint(ifstream &in_f);	//读到一个'\'以后判断后面有没有跟"int"

bool x7isblank(ifstream &in_f);	//读到一个'\'以后判断后面有没有跟"blank"

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

	/*初始化size、top、left域的值*/
	void init(int inisize, int initop, int inileft);

	/*从另一个记号拷贝size、top、left、len属性*/
	void copyattributes(symbol sym);

	void nonter(int symtype);	//非终结符
	int readin(ifstream &in_f);	//从ifstream对象打开的文件读入字符，返回记号

	char* seevalue() { return value; }	//外部查看记号值
	int seetype() { return type; }	//外部查看记号类型
	int seeleft() { return left; }	//外部查看lelft属性值
	int seetop() { return top; }	//外部查看top属性值
	int seelen() { return len; }	//外部查看len属性值
	int seesize() { return size; }	//外部查看size属性值

	symbol& operator=(const symbol &);	//重载赋值操作符=

	/*查看属性是否已经计算，已计算过返回true，否则返回false*/
	bool checkleft();
	bool checktop();
	bool checklen();
	bool checksize();

	/*计算top属性*/
	void computetop(symbol parent, int func);

	/*计算size属性*/
	void computesize(symbol parent, int func);

	/*计算len属性*/
	void computelen();	//长度可直接计算
	void computelen(symbol child);	//父节点长度是一个孩子结点的长度
	void computelen(symbol child1, symbol child2);	//父节点长度是两个孩子结点之和
	void computelen(symbol child1, symbol child2, symbol child3);	//父节点长度是三个孩子结点之和

	/*计算left属性*/
	void computeleft(symbol parent);	//直接继承
	void computeleft(symbol parent, int offset);	//偏移
};

int x7getsymbolstream(ifstream &in_f, symbol symstream[MAXSTREAMLEN]);	//从文件读入字符串流，生成符号流储存在symstream