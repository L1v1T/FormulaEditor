#include"Lexer.h"

void readinnum(ifstream &in_f, char *ch) {	//递归将数字后面的数字读入value
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

void readinletterornum(ifstream &in_f, char *ch) {	//递归将字母后面跟着的数字或字母读入value
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
			else {	//是"sum"
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
			else {	//是"int"
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
					else {	//是"blank"
						in_f.seekg(-5, ios::cur);
						return true;
					}
				}
			}
		}
	}
}

/*初始化size、top、left域的值*/
void symbol::init(int inisize, int initop, int inileft) {
	size = inisize;
	top = initop;
	left = inileft;
}

/*从另一个记号拷贝size、top、left、len属性*/
void symbol::copyattributes(symbol sym) {
	size = sym.size;
	top = sym.top;
	left = sym.left;
	len = sym.len;
}

int symbol::readin(ifstream &in_f) {	//从ifstream对象打开的文件读入字符流，返回一个记号
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
	else if (ch == 92) {	//读到一个'\',判断后面时候是"sum"、"blank"或"int"
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
		else {	//错误
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
	else if (ch == 32 || ch == 9)
		return SPA_TAB;
	else {	//读到非法输入字符
		in_f.seekg(-1, ios::cur);
		return ERROR2;
	}
}

void symbol::nonter(int symtype) {	//非终结符
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
		cout << "错误：不正确的符号类型" << endl;
		break;
	}
	}
}

symbol& symbol::operator=(const symbol &sym) {	//重载赋值操作符=
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

/*查看属性是否已经计算，已计算过返回true，否则返回false*/
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

/*计算top属性*/
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

/*计算size属性*/
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

/*计算len属性*/
void symbol::computelen() {	//长度可直接计算
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

void symbol::computelen(symbol child) {	//父节点长度是一个孩子结点的长度
	if (child.len != -1) { len = child.len; }
}

void symbol::computelen(symbol child1, symbol child2) {	//父节点长度是两个孩子结点之和
	if (child1.len != -1 && child2.len != -1) { len = child1.len + child2.len; }
}

void symbol::computelen(symbol child1, symbol child2, symbol child3) {	//父节点长度是三个孩子结点之和
	if (child1.len != -1 && child2.len != -1 && child3.len != -1) {
		len = child1.len + child2.len + child3.len;
	}
}

/*计算left属性*/
void symbol::computeleft(symbol parent) {	//直接继承
	if (parent.left != -1) { left = parent.left; }
}
void symbol::computeleft(symbol parent, int offset) {	//偏移
	if (parent.left != -1 && offset != -1) { left = parent.left + offset; }
}

int x7getsymbolstream(ifstream &in_f, symbol symstream[MAXSTREAMLEN])	//从文件读入字符串流，生成符号流储存在symstream
{
	int i = 0;
	do {
		int result = symstream[i].readin(in_f);
		if (result == SPA_TAB)
			continue;
		else if (result == ERROR1) {
			cout << "错误：多余的 '\\' 。" << endl;
			cout << "错误位置：第 " << in_f.tellg() << " 个字节。" << endl;
			return FAIL;
		}
		else if (result == ERROR2) {
			char erchar;
			in_f.get(erchar);
			cout << "错误：读入一个非法字符 '" << erchar << "\' 。" << endl;
			cout << "错误位置：第 " << in_f.tellg() << " 个字节。" << endl;
			return FAIL;
		}
		else {
			switch (symstream[i].seetype())
			{
			case NUMBER:
				cout << "读入一个 num 类型符号";
				break;
			case ID:
				cout << "读入一个 id 类型符号";
				break;
			case L_BRACE:
				cout << "读入一个左花括号";
				break;
			case R_BRACE:
				cout << "读入一个右花括号";
				break;
			case L_PAR:
				cout << "读入一个左圆括号";
				break;
			case R_PAR:
				cout << "读入一个右圆括号";
				break;
			case SUM:
				cout << "读入一个求和符号";
				break;
			case INT:
				cout << "读入一个积分符号";
				break;
			case BLANK:
				cout << "读入一个空格";
				break;
			case UNDERSCORE:
				cout << "读入一个下划线";
				break;
			case CARET:
				cout << "读入一个乘方符号";
				break;
			case DOLLAR:
				cout << "读入一个dollar符";
				break;
			default:
				break;
			}
			cout << ",值为 '" << symstream[i++].seevalue() << "' 。" << endl;
		}
	} while (in_f.peek() != EOF);
	return SUCCEED;
}