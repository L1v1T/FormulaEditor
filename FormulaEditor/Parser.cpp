#include"Parser.h"
#include<stack>
#include<string>

/*�ķ�����ʽ*/
const int gramrprodu[NUMOFPROC][MAXPROLEN] = {
	{ _S, S ,INI},
	{ S, DOLLAR, B, DOLLAR ,INI },
	{ B, B, B ,INI },
	{ B, B, UNDERSCORE, CARET, L_BRACE, B, R_BRACE, L_BRACE, B, R_BRACE ,INI },
	{ B, B, CARET, L_BRACE, B, R_BRACE ,INI },
	{ B, B, UNDERSCORE, L_BRACE, B, R_BRACE ,INI },
	{ B, INT, L_BRACE, B, R_BRACE, L_BRACE, B, R_BRACE, L_BRACE, B, R_BRACE ,INI },
	{ B, SUM, L_BRACE, B, R_BRACE, L_BRACE, B, R_BRACE, L_BRACE, B, R_BRACE ,INI },
	{ B, ID ,INI },
	{ B, NUMBER ,INI },
	{ B, BLANK ,INI },
	{ B, L_PAR, B, R_PAR ,INI }
};

/*����������action������goto����*/
const int table[47][14] = {
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	102,	1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	ACC,	-1,	-1,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	3,
	112,	113,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	ACC,	-1,	11,
	-1,	-1,	114,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	115,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	208,	208,	-1,	208,	208,	208,	208,	208,	208,	208,	208,	208,	-1,	-1,
	209,	209,	-1,	209,	209,	209,	209,	209,	209,	209,	209,	209,	-1,	-1,
	210,	210,	-1,	210,	210,	210,	210,	210,	210,	210,	210,	210,	-1,	-1,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	16,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	112,	113,	-1,	202,	202,	202,	202,	202,	202,	202,	202,	202,	-1,	11,
	-1,	117,	118,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	119,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	20,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	21,
	112,	113,	-1,	-1,	109,	122,	104,	105,	106,	107,	108,	-1,	-1,	11,
	-1,	-1,	123,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	24,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	25,
	112,	113,	-1,	126,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	112,	113,	-1,	127,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	211,	211,	-1,	211,	211,	211,	211,	211,	211,	211,	211,	211,	-1,	-1,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	28,
	112,	113,	-1,	129,	109, - 1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	112,	113,	-1,	130,	109, -1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	-1,	-1,	131,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	132,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	112,	113,	-1,	133,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	205,	205,	-1,	205,	205,	205,	205,	205,	205,	205,	205,	205,	-1,	-1,
	204,	204,	-1,	204,	204,	204,	204,	204,	204,	204,	204,	204,	-1,	-1,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	34,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	35,
	-1,	-1,	136,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	112,	113,	-1,	137,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	112,	113,	-1,	138,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	39,
	-1,	-1,	140,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	141,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	112,	113,	-1,	142,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	43,
	-1,	-1,	-1,	-1,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	44,
	203,	203,	-1,	203,	203,	203,	203,	203,	203,	203,	203,	203,	-1,	-1,
	112,	113,	-1,	145,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	112,	113,	-1,	146,	109,	-1,	104,	105,	106,	107,	108,	-1,	-1,	11,
	206,	206,	-1,	206,	206,	206,	206,	206,	206,	206,	206,	206,	-1,	-1,
	207,	207,	-1,	207,	207,	207,	207,	207,	207,	207,	207,	207,	-1,	-1,
};

/*���ص�i������ʽ�ұߵķ��Ÿ���*/
int numofsym(int i) {
	int len = 0;
	while (gramrprodu[i][len + 1] != INI) { len++; }
	return len;
}

int action(int status, int symtype) {	//�����״̬statusʱ����symtype���ŵ���һ������
	return table[status][symtype];
}

void transform(char sym_str[MAXSTREAMLEN], int sym_int) {	//�ѷ�����int����ת�����ַ�������char��������
	for (int i = 0;i < MAXSTREAMLEN;i++) { sym_str[i] = 0; }	//sym_str����
	switch (sym_int)
	{
	case UNDERSCORE:
		sym_str[0] = '_';
		break;
	case CARET:
		sym_str[0] = '^';
		break;
	case L_BRACE:
		sym_str[0] = '{';
		break;
	case R_BRACE:
		sym_str[0] = '}';
		break;
	case L_PAR:
		sym_str[0] = '(';
		break;
	case R_PAR:
		sym_str[0] = ')';
		break;
	case INT: {
		sym_str[0] = '\\';
		sym_str[1] = 'i';
		sym_str[2] = 'n';
		sym_str[3] = 't';
		break;
	}
	case SUM: {
		sym_str[0] = '\\';
		sym_str[1] = 's';
		sym_str[2] = 'u';
		sym_str[3] = 'm';
		break;
	}
	case ID: {
		sym_str[0] = 'i';
		sym_str[1] = 'd';
		break;
	}
	case NUMBER: {
		sym_str[0] = 'n';
		sym_str[1] = 'u';
		sym_str[2] = 'm';
		break;
	}
	case BLANK: {
		sym_str[0] = '\\';
		sym_str[1] = 'b';
		sym_str[2] = 'l';
		sym_str[3] = 'a';
		sym_str[4] = 'n';
		sym_str[5] = 'k';
		break;
	}
	case DOLLAR:
		sym_str[0] = '$';
		break;
	case S:
		sym_str[0] = 'S';
		break;
	case B:
		sym_str[0] = 'B';
		break;
	case _S: {
		sym_str[0] = '_';
		sym_str[1] = 'S';
		break;
	}
	default:
		break;
	}
}

int production::rightlen() {	//���ز���ʽ�ұߵķ�������
	int i = 0;
	while (rights[i].seetype() != INI) { i++; }
	return i;
}

/*����ʽ���Լ������*/
void production::rule1() {
	if (!rights[1].checksize()) { rights[1].computesize(left, NORMAL); }
	if (!rights[1].checktop()) { rights[1].computetop(left, NORMAL); }
	if (!rights[1].checkleft()) { rights[1].computeleft(left); }
	if (!left.checklen()) { left.computelen(rights[1]); }
}

void production::rule2() {
	if (!rights[0].checksize()) { rights[0].computesize(left, NORMAL); }
	if (!rights[0].checktop()) { rights[0].computetop(left, NORMAL); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[1].checksize()) { rights[1].computesize(left, NORMAL); }
	if (!rights[1].checktop()) { rights[1].computetop(left, NORMAL); }
	if (!rights[1].checkleft()) { rights[1].computeleft(left, rights[0].seelen()); }
	if (!left.checklen()) { left.computelen(rights[0], rights[1]); }
}

void production::rule3() {
	if (!rights[0].checksize()) { rights[0].computesize(left, NORMAL); }
	if (!rights[0].checktop()) { rights[0].computetop(left, NORMAL); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[4].checksize()) { rights[4].computesize(left, SHRINK); }
	if (!rights[4].checktop()) { rights[4].computetop(left, DOWNER); }
	if (!rights[4].checkleft()) { rights[4].computeleft(left, rights[0].seelen()); }
	if (!rights[7].checksize()) { rights[7].computesize(left, SHRINK); }
	if (!rights[7].checktop()) { rights[7].computetop(left, UPER); }
	if (!rights[7].checkleft()) { rights[7].computeleft(rights[4]); }
	if (!left.checklen()) {
		if (rights[4].seelen() < rights[7].seelen()) { left.computelen(rights[0], rights[7]); }
		else { left.computelen(rights[0], rights[4]); }
	}
}

void production::rule4() {
	if (!rights[0].checksize()) { rights[0].computesize(left, NORMAL); }
	if (!rights[0].checktop()) { rights[0].computetop(left, NORMAL); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[3].checksize()) { rights[3].computesize(left, SHRINK); }
	if (!rights[3].checktop()) { rights[3].computetop(left, UPER); }
	if (!rights[3].checkleft()) { rights[3].computeleft(left, rights[0].seelen()); }
	if (!left.checklen()) { left.computelen(rights[0], rights[3]); }
}

void production::rule5() {
	if (!rights[0].checksize()) { rights[0].computesize(left, NORMAL); }
	if (!rights[0].checktop()) { rights[0].computetop(left, NORMAL); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[3].checksize()) { rights[3].computesize(left, SHRINK); }
	if (!rights[3].checktop()) { rights[3].computetop(left, DOWNER); }
	if (!rights[3].checkleft()) { rights[3].computeleft(left, rights[0].seelen()); }
	if (!left.checklen()) { left.computelen(rights[0], rights[3]); }
}

void production::rule6() {
	if (!rights[0].checksize()) { rights[0].computesize(left, ENLAGER); }
	if (!rights[0].checktop()) { rights[0].computetop(left, UPER); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[0].checklen()) { rights[0].computelen(); }
	if (!rights[2].checksize()) { rights[2].computesize(left, SHRINK); }
	if (!rights[2].checktop()) { rights[2].computetop(rights[0], DOWNER); }
	if (!rights[2].checkleft()) { rights[2].computeleft(left, rights[0].seelen()); }
	if (!rights[5].checksize()) { rights[5].computesize(left, SHRINK); }
	if (!rights[5].checktop()) { rights[5].computetop(rights[0], UPER); }
	if (!rights[5].checkleft()) { rights[5].computeleft(left, rights[0].seelen()); }
	if (!rights[8].checksize()) { rights[8].computesize(left, NORMAL); }
	if (!rights[8].checktop()) { rights[8].computetop(left, NORMAL); }
	int max;
	if (rights[2].seelen() < rights[5].seelen()) { max = 5; }
	else { max = 2; }
	if (!rights[8].checkleft()) { rights[8].computeleft(rights[max], rights[max].seelen()); }
	if (!left.checklen()) { left.computelen(rights[0], rights[max], rights[8]); }
}

void production::rule7() {
	if (!rights[0].checksize()) { rights[0].computesize(left, ENLAGER); }
	if (!rights[0].checktop()) { rights[0].computetop(left, UPER); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[0].checklen()) { rights[0].computelen(); }
	if (!rights[2].checksize()) { rights[2].computesize(left, SHRINK); }
	if (!rights[2].checktop()) { rights[2].computetop(rights[0], DOWNER); }
	if (!rights[2].checkleft()) { rights[2].computeleft(left, rights[0].seelen()); }
	if (!rights[5].checksize()) { rights[5].computesize(left, SHRINK); }
	if (!rights[5].checktop()) { rights[5].computetop(rights[0], UPER); }
	if (!rights[5].checkleft()) { rights[5].computeleft(left, rights[0].seelen()); }
	if (!rights[8].checksize()) { rights[8].computesize(left, NORMAL); }
	if (!rights[8].checktop()) { rights[8].computetop(left, NORMAL); }
	int max;
	if (rights[2].seelen() < rights[5].seelen()) { max = 5; }
	else { max = 2; }
	if (!rights[8].checkleft()) { rights[8].computeleft(rights[max], rights[max].seelen()); }
	if (!left.checklen()) { left.computelen(rights[0], rights[max], rights[8]); }
}

void production::rule8() {
	if (!rights[0].checksize()) { rights[0].computesize(left, NORMAL); }
	if (!rights[0].checktop()) { rights[0].computetop(left, NORMAL); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[0].checklen()) { rights[0].computelen(); }
	if (!left.checklen()) { left.computelen(rights[0]); }
}

void production::rule9() {
	if (!rights[0].checksize()) { rights[0].computesize(left, NORMAL); }
	if (!rights[0].checktop()) { rights[0].computetop(left, NORMAL); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[0].checklen()) { rights[0].computelen(); }
	if (!left.checklen()) { left.computelen(rights[0]); }
}

void production::rule10() {
	if (!rights[0].checksize()) { rights[0].computesize(left, NORMAL); }
	if (!rights[0].checktop()) { rights[0].computetop(left, NORMAL); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[0].checklen()) { rights[0].computelen(); }
	if (!left.checklen()) { left.computelen(rights[0]); }
}

void production::rule11() {
	if (!rights[0].checksize()) { rights[0].computesize(left, NORMAL); }
	if (!rights[0].checktop()) { rights[0].computetop(left, NORMAL); }
	if (!rights[0].checkleft()) { rights[0].computeleft(left); }
	if (!rights[0].checklen()) { rights[0].computelen(); }
	if (!rights[1].checksize()) { rights[1].computesize(left, NORMAL); }
	if (!rights[1].checktop()) { rights[1].computetop(left, NORMAL); }
	if (!rights[1].checkleft()) { rights[1].computeleft(left, rights[0].seelen()); }
	if (!rights[2].checksize()) { rights[2].computesize(left, NORMAL); }
	if (!rights[2].checktop()) { rights[2].computetop(left, NORMAL); }
	if (!rights[2].checkleft()) { rights[2].computeleft(rights[1], rights[1].seelen()); }
	if (!rights[2].checklen()) { rights[2].computelen(); }
	if (!left.checklen()) { left.computelen(rights[0], rights[1], rights[2]); }
}

/*�������ʽ������*/
void production::computeattributes() {
	switch (type) {
	case 1:
		rule1();
		break;
	case 2:
		rule2();
		break;
	case 3:
		rule3();
		break;
	case 4:
		rule4();
		break;
	case 5:
		rule5();
		break;
	case 6:
		rule6();
		break;
	case 7:
		rule7();
		break;
	case 8:
		rule8();
		break;
	case 9:
		rule9();
		break;
	case 10:
		rule10();
		break;
	case 11:
		rule11();
		break;
	default:
		cout << "�����ڵĲ���ʽ" << endl;
		break;
	}
}

/*��������*/
const int errortype1[1] = { 0 };
const int errortype2[34] = { 2,3,6,7,8,9,11,14,15,16,18,19,20,21,22,23,24,25,28,29,30,31,32,34,35,36,39,40,41,42,43,44,45,46 };
const int errortype3[10] = { 4,5,12,13,17,26,27,33,37,38 };

/*�﷨���������*/
void erroranalyzer(int status, symbol nextsym) {
	string errmsg;
	cout << "�﷨����";
	if(status == errortype1[0]){
		cout << "���ʽӦ�� '$' ��ͷ��" << endl;
		return;
	}
	int i = 0;
	while (i != 34) {
		if (status == errortype2[i]) { break; }
		i++;
	}
	if (i != 34) {
		char temp = *nextsym.seevalue();
		cout << "����ķ��� '" << temp << "' �� '" << temp << "' ǰȱ�����ݡ�" << endl;
		return;
	}
	i = 0;
	while (i != 10) {
		if (status == errortype3[i]) { break; }
		i++;
	}
	if (i != 10) {
		string sym1, sym2, sym3;
		switch (status)
		{
		case 4:
			sym1 = "\\int";
			sym2 = "{";
			break;
		case 5:
			sym1 = "\\sum";
			sym2 = "{";
			break;
		case 12:
			sym1 = "_";
			sym2 = "^";
			sym3 = "{";
			break;
		case 13:
			sym1 = "^";
			sym2 = "{";
			break;
		case 17:
			sym1 = "^";
			sym2 = "{";
			break;
		default:
			sym1 = "}";
			sym2 = "{";
			break;
		}
		string errmsg;
		if (status == 12 && nextsym.seetype() == L_BRACE) {
			errmsg = " '" + sym1 + "'�� '" + sym3 + "' �м��ж�������ݻ�ȱ�����ݡ�\n";
		}
		else{ errmsg = " '" + sym1 + "'�� '" + sym2 + "' �м��ж�������ݻ�ȱ�����ݡ�\n"; }
		cout << errmsg;
		return;
	}
	cout << "δ֪���͵Ĵ���" << endl;
	return;
}

/*�﷨�������������������������Ĳ���ʽѹ������*/
int parser(symbol symstream[], vector<production>& produs) {
	stack<int> status;
	vector<symbol> syms;
	status.push(0);
	int i = 0;
	int x7act, complete = 0;
	while (!complete) {
		int nextsymtype = symstream[i].seetype();
		if (nextsymtype == INI) {
			cout << "���󣺲������ı��ʽ�����ܽ�βȱ�� '$' ��" << endl;
			return FAIL;
		}
		x7act = action(status.top(), symstream[i].seetype());
		if (x7act != -1) {
			switch (x7act / 100)
			{
				//sxx
			case 1: {
				syms.push_back(symstream[i]);	//������ѹ������
				status.push(x7act % 100);	//��״̬ѹ��ջ
				i++;	//ָ����һ������
				break;
			}
					//rxx
			case 2: {
				production pro;
				pro.type = x7act % 100;	//�õ�(x7act % 100)������ʽ��Լ
				int n = numofsym(x7act % 100);

				/*�˵� ����ʽ�ұ߷����� �����ź�״̬*/
				for (int count = 0;count < n;count++) {
					status.pop();
					pro.rights[n - count -1] = syms.back();
					syms.pop_back();
				}

				/*����ʽ��߷���A*/
				symbol lsym;
				lsym.nonter(gramrprodu[x7act % 100][0]);
				pro.left = lsym;
				int t = status.top();	//��ʱջ��״̬
				syms.push_back(lsym);	//ѹ�����ʽ��߷���A
				status.push(action(t, lsym.seetype()));	//ѹ��goto[t,A]
				produs.push_back(pro);	//������ʽѹ������

				/*�������ʽ*/
				char output[MAXSTREAMLEN];
				transform(output, pro.left.seetype());
				cout << "������ʽ " << output << "-->";
				int k = 0;
				while (k < pro.rightlen()) {
					transform(output, pro.rights[k++].seetype());
					cout << output;
				}
				cout<< " ��Լ" <<endl;
				break;
			}
					//accept
			case 3: {
				complete = 1;	//��������

				/*ʵ��������ʽS-->$B$*/
				symbol lsym, rsym[3];
				lsym.nonter(S);
				rsym[0].nonter(DOLLAR);
				rsym[1].nonter(B);
				rsym[2].nonter(DOLLAR);
				production pro;
				pro.type = 1;
				pro.left = lsym;
				for (int i = 0;i < 3;i++) { pro.rights[i] = rsym[i]; }
				produs.push_back(pro);	//������ʽѹ������

				/*�������ʽ*/
				char output[MAXSTREAMLEN];
				transform(output, pro.left.seetype());
				cout << "������ʽ " << output << "-->";
				int k = 0;
				while (k < pro.rightlen()) {
					transform(output, pro.rights[k++].seetype());
					cout << output;
				}
				cout << " ��Լ\n" << endl;
				break;
			}
			default:
				complete = 1;
				cout << "δ֪����" << endl;
				return FAIL;
			}
		}
		else {	//�﷨����
			complete = 1;
			erroranalyzer(status.top(), symstream[i]);
			int errorpos = 0, pos = 0;
			while (pos != i) {
				int j = 0;
				while (symstream[pos].seevalue()[j] != 0) { j++; }
				errorpos += j;
				pos++;
			}
			cout << "����λ�ã��� " << errorpos  << " ���ֽ�֮��" << endl;
			return FAIL;
		}
	}
	return SUCCEED;
}