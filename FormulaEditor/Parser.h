#pragma once

#include"Lexer.h"
#include<vector>

#define NUMOFPROC 12
#define MAXPROLEN 32
#define ACC 300

/*返回第i个产生式右边的符号个数*/
int numofsym(int i);

/*用int类型数据代表action函数和goto函数的返回值,用int类型1xx代表动作sxx,2xx代表动作rxx,goto函数的返回值直接用小于100的数表示*/

int action(int status, int symtype);	//查表获得状态status时读入symtype符号的下一步动作

void transform(char sym_str[MAXSTREAMLEN], int sym_int);	//把符号由int类型转换成字符储存在char型数组里

class production {
private:
	/*产生式属性计算规则*/
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
	int type;	//是第几个产生式
	production() :type(-1) {} //{ for (int i = 0;i < MAXPROLEN;i++)rights[i] = NULL; }
	int rightlen();	//返回产生式右边的符号数量

	/*计算产生式的属性*/
	void computeattributes();
};

/*语法错误分析器*/
void erroranalyzer(int ststus, symbol nextsym);

/*语法分析器，输入符号流，将输出的产生式压入容器*/
int parser(symbol symstream[], vector<production>& produs);