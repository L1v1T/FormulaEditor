#include"SemanticAnalyzer.h"

const char* framehead = "<html>\n<head>\n<META content = \"text/html; charset=gb2312\">\n</head>\n<body>\n";
const char* framebody1 = "<div style=\"position: absolute; top:";
const char* framebody2 = "px; left:";
const char* framebody3 = "px;\"><span style = \"font-size:";
const char* framebody4 = "px; font-style:";
const char* framebody5 = "; line-height:100%;\">";
const char* framebody6 = "</span></div>\n";
const char* frameend = "</body>\n</html>";
const char* font_id = "oblique";
const char* font_ot = "normal";

/*�ҵ�����ʽ��һ������B*/
int findnextB(production produ, int pos) {
	int i = pos;
	while (i != -1) {
		if (produ.rights[i].seetype() == B) { return i; }
		i--;
	}
	return i;
}

/*������һ��δ����ǵĲ���ʽ������*/
int findnextunmark(vector<production> produs, bool mark[], int pos) {
	int i = pos;
	while (i != -1) {
		if (mark[i] == false) { return i; }
		i--;
	}
	cout << "����ʽ���Ӵ���" << endl;
	return i;
}

/*�ݹ��������������Ϊpos�ķ��ŵ�link��top��size���ֵ*/
void produslink(vector<production>& produs, int pos, bool mark[]) {
	/*�������ʽ������*/
	produs[pos].computeattributes();

	int nextB = produs[pos].rightlen() - 1;
	nextB = findnextB(produs[pos], nextB);
	while (nextB != -1) {
		/*������ʽ�ұߵ�B��B�Ĳ���ʽ����*/
		int unmark = findnextunmark(produs, mark, pos - 1);
		produs[pos].rights[nextB].linkpos = unmark;
		produs[unmark].left.linkpos = pos;

		/*������������*/
		produs[unmark].left.copyattributes(produs[pos].rights[nextB]);

		/*�ݹ�*/
		produslink(produs, unmark, mark);

		/*������������*/
		produs[pos].rights[nextB].copyattributes(produs[unmark].left);
		
		/*�������ʽ������*/
//		produs[pos].computeattributes();
		nextB = findnextB(produs[pos], nextB - 1);
	}
	mark[pos] = true;
}

/*������������������һ������B��λ�ã���δ�ҵ��򷵻�-1*/
int findnext(production produ, int pos) {
	int i = pos + 1;
	while(i != produ.rightlen()) {
		if (produ.rights[i].seetype() == B) { return i; }
		i++;
	}
	return -1;
}

/*�Ե����ϵݹ��������*/
void finalcompute(vector<production>& produs, int pos) {
	produs[pos].computeattributes();
	int nextB = -1;
	nextB = findnext(produs[pos], nextB);
	while (nextB != -1) {
		/*������������*/
		int nextnode = produs[pos].rights[nextB].linkpos;
		produs[nextnode].left.copyattributes(produs[pos].rights[nextB]);

		/*������һ�������*/
		finalcompute(produs, nextnode);

		/*������������*/
		produs[pos].rights[nextB].copyattributes(produs[nextnode].left);

		/*��һ������B*/
		nextB = findnext(produs[pos], nextB);
	}
	produs[pos].computeattributes();
}

/*	��������pos�������һ��Ӧ����ķ��Ż����B������
	flag == 0��ʾ��Ӧ����ķ���
	flag == 1��ʾ�Ƿ���B*/
int findnextprin(production produ, int pos, int& flag) {
	int i = pos + 1;
	while (i != produ.rightlen()) {
		int type = produ.rights[i].seetype();
		if (type >= L_PAR&&type <= BLANK) { break; }
		i++;
	}
	int nextB = findnext(produ, pos);
	if (nextB != -1 && i != produ.rightlen()) {
		if (nextB > i) {
			flag = 0;
			return i;
		}
		else {
			flag = 1;
			return nextB;
		}
	}
	else if (i == produ.rightlen()) {
		if (nextB == -1) { return -1; }
		else{
			flag = 1;
			return nextB;
		}
	}
	else {
		flag = 0;
		return i;
	}
}

/*�����ŵ�����������ļ�*/
void htmlprin(ofstream& out_f, symbol sym) {
	out_f << framebody1 << sym.seetop() << framebody2 << sym.seeleft()
		<< framebody3 << sym.seesize() << framebody4;
	if (sym.seetype() == ID) { out_f << font_id << framebody5; }
	else { out_f << font_ot << framebody5; }
	if (sym.seetype() == INT) { out_f << "&int;" << framebody6; }
	else if (sym.seetype() == SUM) { out_f << "&sum;" << framebody6; }
	else if (sym.seetype() == BLANK) { out_f << ' ' << framebody6; }
	else { out_f << sym.seevalue() << framebody6; }
}

/*������������pos�ݹ�����html*/
void produce_html(ofstream& out_f, vector<production> produs, int pos) {
	int nextprin = -1;
	int flag = 1;
	nextprin = findnextprin(produs[pos], nextprin, flag);
	while (nextprin != -1) {
		if (flag == 1) {	//������²�ķ���
			int lower = produs[pos].rights[nextprin].linkpos;
			/*�ݹ����*/
			produce_html(out_f, produs, lower);
		}
		else {
			htmlprin(out_f, produs[pos].rights[nextprin]);	//�����html
		}
		nextprin = findnextprin(produs[pos], nextprin, flag);
	}
}