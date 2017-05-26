#include"Lexer.h"

void readinnum(ifstream &in_f, char *ch) {	//�ݹ齫���ֺ�������ֶ���value
	char temp;
	in_f.get(temp);
	if (temp > 47 && temp < 58) {
		*ch = temp;
		readinnum(in_f, ch + 1);
		return;
	}
	else {
		in_f.seekg(-1, ios::cur);
		return;
	}
}

void readinletterornum(ifstream &in_f, char *ch) {	//�ݹ齫��ĸ������ŵ����ֻ���ĸ����value
	char temp;
	in_f.get(temp);
	if (temp > 47 && temp < 58) {
		*ch = temp;
		readinletterornum(in_f, ch + 1);
		return;
	}
	else if (temp > 64 && temp < 91 || temp >96 && temp < 123) {
		*ch = temp;
		readinletterornum(in_f, ch + 1);
		return;
	}
	else {
		in_f.seekg(-1, ios::cur);
		return;
	}
}

bool x7issum(ifstream &in_f) {
	char ch;
	in_f.get(ch);
	if (ch != 's') {
		in_f.seekg(-1, ios::cur);
		return false;
	}
	else {
		in_f.get(ch);
		if (ch != 'u') {
			in_f.seekg(-2, ios::cur);
			return false;
		}
		else {
			in_f.get(ch);
			if (ch != 'm') {
				in_f.seekg(-3, ios::cur);
				return false;
			}
			else {	//��"sum"
				in_f.seekg(-3, ios::cur);
				return true;
			}
		}
	}
}

bool x7isint(ifstream &in_f) {
	char ch;
	in_f.get(ch);
	if (ch != 'i') {
		in_f.seekg(-1, ios::cur);
		return false;
	}
	else {
		in_f.get(ch);
		if (ch != 'n') {
			in_f.seekg(-2, ios::cur);
			return false;
		}
		else {
			in_f.get(ch);
			if (ch != 't') {
				in_f.seekg(-3, ios::cur);
				return false;
			}
			else {	//��"int"
				in_f.seekg(-3, ios::cur);
				return true;
			}
		}
	}
}

bool x7isblank(ifstream &in_f) {
	char ch;
	in_f.get(ch);
	if (ch != 'b') {
		in_f.seekg(-1, ios::cur);
		return false;
	}
	else {
		in_f.get(ch);
		if (ch != 'l') {
			in_f.seekg(-2, ios::cur);
			return false;
		}
		else {
			in_f.get(ch);
			if (ch != 'a') {
				in_f.seekg(-3, ios::cur);
				return false;
			}
			else {
				in_f.get(ch);
				if (ch != 'n') {
					in_f.seekg(-4, ios::cur);
					return false;
				}
				else {
					in_f.get(ch);
					if (ch != 'k') {
						in_f.seekg(-5, ios::cur);
						return false;
					}
					else {	//��"blank"
						in_f.seekg(-5, ios::cur);
						return true;
					}
				}
			}
		}
	}
}

/*��ʼ��size��top��left���ֵ*/
void symbol::init(int inisize, int initop, int inileft) {
	size = inisize;
	top = initop;
	left = inileft;
}

/*����һ���Ǻſ���size��top��left��len����*/
void symbol::copyattributes(symbol sym) {
	size = sym.size;
	top = sym.top;
	left = sym.left;
	len = sym.len;
}

int symbol::readin(ifstream &in_f) {	//��ifstream����򿪵��ļ������ַ���������һ���Ǻ�
	char ch;
	in_f.get(ch);
	
	if (ch > 47 && ch < 58) {
		value[0] = ch;
		readinnum(in_f, value + 1);
		type = NUMBER;
		return CORRECT;
	}
	else if (ch > 64 && ch < 91 || ch>96 && ch < 123) {
		value[0] = ch;
		readinletterornum(in_f, value + 1);
		type = ID;
		return CORRECT;
	}
	else if (ch == 92) {	//����һ��'\',�жϺ���ʱ����"sum"��"blank"��"int"
		if (x7issum(in_f)) {
			value[0] = ch;
			for (int i = 1;i < 4;i++)
				in_f.get(value[i]);
			type = SUM;
			return CORRECT;
		}
		else if (x7isint(in_f)) {
			value[0] = ch;
			for (int i = 1;i < 4;i++)
				in_f.get(value[i]);
			type = INT;
			return CORRECT;
		}
		else if (x7isblank(in_f)) {
			value[0] = ch;
			for (int i = 1;i < 6;i++)
				in_f.get(value[i]);
			type = BLANK;
			return CORRECT;
		}
		else {	//����
			return ERROR1;
		}
	}
	else if (ch == 123) {
		value[0] = ch;
		type = L_BRACE;
		return CORRECT;
	}
	else if (ch == 125) {
		value[0] = ch;
		type = R_BRACE;
		return CORRECT;
	}
	else if (ch == 40) {
		value[0] = ch;
		type = L_PAR;
		return CORRECT;
	}
	else if (ch == 41) {
		value[0] = ch;
		type = R_PAR;
		return CORRECT;
	}
	else if (ch == 95) {
		value[0] = ch;
		type = UNDERSCORE;
		return CORRECT;
	}
	else if (ch == 94) {
		value[0] = ch;
		type = CARET;
		return CORRECT;
	}
	else if (ch == 36) {
		value[0] = ch;
		type = DOLLAR;
		return CORRECT;
	}
	else if (ch == 32 || ch == 9 || ch == '\n')
		return SPA_TAB_ENTER;
	else {	//�����Ƿ������ַ�
		in_f.seekg(-1, ios::cur);
		return ERROR2;
	}
}

void symbol::nonter(int symtype) {	//���ս��
	switch (symtype) {
	case S: {
		type = S;
		value[0] = 'S';
		break;
	}
	case B: {
		type = B;
		value[0] = 'B';
		break;
	}
	case DOLLAR: {
		type = DOLLAR;
		value[0] = '$';
		break;
	}
	default: {
		cout << "���󣺲���ȷ�ķ�������" << endl;
		break;
	}
	}
}

symbol& symbol::operator=(const symbol &sym) {	//���ظ�ֵ������=
	int i = 0;
	while (sym.value[i] != 0) { value[i] = sym.value[i++]; }
	type = sym.type;
	linkpos = sym.linkpos;
	left = sym.left;
	top = sym.top;
	len = sym.len;
	size = sym.size;
	return *this;
}

/*�鿴�����Ƿ��Ѿ����㣬�Ѽ��������true�����򷵻�false*/
bool symbol::checkleft() {
	if (left != -1) { return true; }
	return false;
}
bool symbol::checktop() {
	if (top != -1) { return true; }
	return false;
}
bool symbol::checklen() {
	if (len != -1) { return true; }
	return false;
}
bool symbol::checksize() {
	if (size != -1) { return true; }
	return false;
}

/*����top����*/
void symbol::computetop(symbol parent, int func) {
	switch (func) {
	case NORMAL:
		if (parent.top != -1) { top = parent.top; }
		break;
	case UPER:
		if (parent.top != -1 && size != -1) {
			if (type == INT || type == SUM) { top = parent.top - (int)(0.1875*(double)size); }
			else { top = (int)(parent.top - RATE * size); }
		}
		break;
	case DOWNER:
		if (parent.top != -1 && size != -1 && parent.size != -1) {
			top = (int)(parent.top + parent.size - RATE * size);
		}
		break;
	default:
		break;
	}
}

/*����size����*/
void symbol::computesize(symbol parent, int func) {
	if (parent.size != -1) {
		switch (func)
		{
		case NORMAL:
			size = parent.size;
			break;
		case SHRINK:
			size = (int)(0.6*(double)parent.size);
			break;
		case ENLAGER:
			size = (int)(1.6*(double)parent.size);
			break;
		default:
			break;
		}
	}
}

/*����len����*/
void symbol::computelen() {	//���ȿ�ֱ�Ӽ���
	if (size != -1) {
		int valuelen = 0;
		if (type == SUM || type == INT || type == BLANK) { valuelen++; }
		else {
			while (value[valuelen] != 0) { valuelen++; }
		}
		double rate = 0.5;
		if (type == SUM) { rate = 0.9; }
		if (type == INT) { rate = 0.8; }
		len = (int)(rate*(double)size*(double)valuelen);
	}
}

void symbol::computelen(symbol child) {	//���ڵ㳤����һ�����ӽ��ĳ���
	if (child.len != -1) { len = child.len; }
}

void symbol::computelen(symbol child1, symbol child2) {	//���ڵ㳤�����������ӽ��֮��
	if (child1.len != -1 && child2.len != -1) { len = child1.len + child2.len; }
}

void symbol::computelen(symbol child1, symbol child2, symbol child3) {	//���ڵ㳤�����������ӽ��֮��
	if (child1.len != -1 && child2.len != -1 && child3.len != -1) {
		len = child1.len + child2.len + child3.len;
	}
}

/*����left����*/
void symbol::computeleft(symbol parent) {	//ֱ�Ӽ̳�
	if (parent.left != -1) { left = parent.left; }
}
void symbol::computeleft(symbol parent, int offset) {	//ƫ��
	if (parent.left != -1 && offset != -1) { left = parent.left + offset; }
}

int x7getsymbolstream(ifstream &in_f, symbol symstream[MAXSTREAMLEN])	//���ļ������ַ����������ɷ�����������symstream
{
	int i = 0;
	do {
		int result = symstream[i].readin(in_f);
		if (result == SPA_TAB_ENTER)
			continue;
		else if (result == ERROR1) {
			cout << "���󣺶���� '\\' ��" << endl;
			cout << "����λ�ã��� " << in_f.tellg() << " ���ֽڡ�" << endl;
			return FAIL;
		}
		else if (result == ERROR2) {
			char erchar;
			in_f.get(erchar);
			cout << "���󣺶���һ���Ƿ��ַ� '" << erchar << "\' ��" << endl;
			cout << "����λ�ã��� " << in_f.tellg() << " ���ֽڡ�" << endl;
			return FAIL;
		}
		else {
			switch (symstream[i].seetype())
			{
			case NUMBER:
				cout << "����һ�� num ���ͷ���";
				break;
			case ID:
				cout << "����һ�� id ���ͷ���";
				break;
			case L_BRACE:
				cout << "����һ��������";
				break;
			case R_BRACE:
				cout << "����һ���һ�����";
				break;
			case L_PAR:
				cout << "����һ����Բ����";
				break;
			case R_PAR:
				cout << "����һ����Բ����";
				break;
			case SUM:
				cout << "����һ����ͷ���";
				break;
			case INT:
				cout << "����һ�����ַ���";
				break;
			case BLANK:
				cout << "����һ���ո�";
				break;
			case UNDERSCORE:
				cout << "����һ���»���";
				break;
			case CARET:
				cout << "����һ���˷�����";
				break;
			case DOLLAR:
				cout << "����һ��dollar��";
				break;
			default:
				break;
			}
			cout << ",ֵΪ '" << symstream[i++].seevalue() << "' ��" << endl;
		}
	} while (in_f.peek() != EOF);
	return SUCCEED;
}