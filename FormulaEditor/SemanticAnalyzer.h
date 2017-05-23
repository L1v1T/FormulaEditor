#pragma once

#include"Parser.h"

extern const char* framehead;
extern const char* framebody1;
extern const char* framebody2;
extern const char* framebody3;
extern const char* framebody4;
extern const char* framebody5;
extern const char* framebody6;
extern const char* frameend;
extern const char* font_id;
extern const char* font_ot;

/*找到产生式下一个符号B*/
int findnextB(production produ, int pos);

/*返回下一个未被标记的产生式的坐标*/
int findnextunmark(vector<production> produs, bool mark[], int pos);

/*递归计算容器中坐标为pos的符号的link、top、size域的值*/
void produslink(vector<production>& produs,int pos, bool mark[]);

/*返回输入坐标后面的下一个符号B的位置，若未找到则返回-1*/
int findnext(production produ, int pos);

/*自顶向下递归计算属性*/
void finalcompute(vector<production>& produs, int pos);

/*	返回坐标pos后最近的一个应输出的符号或符号B的坐标
flag == 0表示是应输出的符号
flag == 1表示是符号B*/
int findnextprin(production produ, int pos, int& flag);

/*将符号的属性输出到文件*/
void htmlprin(ofstream& out_f,symbol sym);

/*从容器中坐标pos递归生成html*/
void produce_html(ofstream& out_f, vector<production> produs, int pos);