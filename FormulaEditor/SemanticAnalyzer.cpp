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

/*找到产生式下一个符号B*/
int findnextB(production produ, int pos) {
	int i = pos;
	while (i != -1) {
		if (produ.rights[i].seetype() == B) { return i; }
		i--;
	}
	return i;
}

/*返回下一个未被标记的产生式的坐标*/
int findnextunmark(vector<production> produs, bool mark[], int pos) {
	int i = pos;
	while (i != -1) {
		if (mark[i] == false) { return i; }
		i--;
	}
	cout << "产生式连接错误" << endl;
	return i;
}

/*递归计算容器中坐标为pos的符号的link、top、size域的值*/
void produslink(vector<production>& produs, int pos, bool mark[]) {
	/*计算产生式的属性*/
	produs[pos].computeattributes();

	int nextB = produs[pos].rightlen() - 1;
	nextB = findnextB(produs[pos], nextB);
	while (nextB != -1) {
		/*将产生式右边的B与B的产生式连接*/
		int unmark = findnextunmark(produs, mark, pos - 1);
		produs[pos].rights[nextB].linkpos = unmark;
		produs[unmark].left.linkpos = pos;

		/*属性向下流动*/
		produs[unmark].left.copyattributes(produs[pos].rights[nextB]);

		/*递归*/
		produslink(produs, unmark, mark);

		/*属性向上流动*/
		produs[pos].rights[nextB].copyattributes(produs[unmark].left);
		
		/*计算产生式的属性*/
//		produs[pos].computeattributes();
		nextB = findnextB(produs[pos], nextB - 1);
	}
	mark[pos] = true;
}

/*返回输入坐标后面的下一个符号B的位置，若未找到则返回-1*/
int findnext(production produ, int pos) {
	int i = pos + 1;
	while(i != produ.rightlen()) {
		if (produ.rights[i].seetype() == B) { return i; }
		i++;
	}
	return -1;
}

/*自底向上递归计算属性*/
void finalcompute(vector<production>& produs, int pos) {
	produs[pos].computeattributes();
	int nextB = -1;
	nextB = findnext(produs[pos], nextB);
	while (nextB != -1) {
		/*属性向下流动*/
		int nextnode = produs[pos].rights[nextB].linkpos;
		produs[nextnode].left.copyattributes(produs[pos].rights[nextB]);

		/*计算下一层的属性*/
		finalcompute(produs, nextnode);

		/*属性向上流动*/
		produs[pos].rights[nextB].copyattributes(produs[nextnode].left);

		/*下一个符号B*/
		nextB = findnext(produs[pos], nextB);
	}
	produs[pos].computeattributes();
}

/*	返回坐标pos后最近的一个应输出的符号或符号B的坐标
	flag == 0表示是应输出的符号
	flag == 1表示是符号B*/
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

/*将符号的属性输出到文件*/
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

/*从容器中坐标pos递归生成html*/
void produce_html(ofstream& out_f, vector<production> produs, int pos) {
	int nextprin = -1;
	int flag = 1;
	nextprin = findnextprin(produs[pos], nextprin, flag);
	while (nextprin != -1) {
		if (flag == 1) {	//先输出下层的符号
			int lower = produs[pos].rights[nextprin].linkpos;
			/*递归输出*/
			produce_html(out_f, produs, lower);
		}
		else {
			htmlprin(out_f, produs[pos].rights[nextprin]);	//输出到html
		}
		nextprin = findnextprin(produs[pos], nextprin, flag);
	}
}