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

/*�ҵ�����ʽ��һ������B*/
int findnextB(production produ, int pos);

/*������һ��δ����ǵĲ���ʽ������*/
int findnextunmark(vector<production> produs, bool mark[], int pos);

/*�ݹ��������������Ϊpos�ķ��ŵ�link��top��size���ֵ*/
void produslink(vector<production>& produs,int pos, bool mark[]);

/*������������������һ������B��λ�ã���δ�ҵ��򷵻�-1*/
int findnext(production produ, int pos);

/*�Զ����µݹ��������*/
void finalcompute(vector<production>& produs, int pos);

/*	��������pos�������һ��Ӧ����ķ��Ż����B������
flag == 0��ʾ��Ӧ����ķ���
flag == 1��ʾ�Ƿ���B*/
int findnextprin(production produ, int pos, int& flag);

/*�����ŵ�����������ļ�*/
void htmlprin(ofstream& out_f,symbol sym);

/*������������pos�ݹ�����html*/
void produce_html(ofstream& out_f, vector<production> produs, int pos);