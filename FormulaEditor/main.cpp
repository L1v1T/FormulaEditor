#include"SemanticAnalyzer.h"

int main() {
	ifstream x7infile;
	ofstream x7outfile;
	symbol x7symstream[MAXSTREAMLEN];
	vector<production> produs;
	const int initsize = 50, initleft = 500, inittop = 175;
	int flag = SUCCEED;

	/*��test.txt�����ַ���ת���ɷ�����*/
	x7infile.open("test.txt", ios::in);
	if (!x7infile) {
		cout << "���ļ�test.txtʧ��!" << endl;
		goto end;
	}
	if (x7getsymbolstream(x7infile, x7symstream) != SUCCEED) { goto end; }
	x7infile.close();
	cout << "\n�ʷ��������\n" << endl;

	/*�﷨����������ı��ʽ�����˳��ѹ��������*/
	if (parser(x7symstream, produs) != SUCCEED) { goto end; }
	cout << "�﷨�������\n" << endl;

	/*����*/
	int end = produs.size();
	bool* mark = new bool[end];
	for (int i = 0;i < end;i++) { mark[i] = false; }
	produs[end - 1].left.init(initsize, inittop, initleft);
	produslink(produs, end - 1, mark);

	/*�Զ����¼���ʣ������ֵ*/
	for (int i = 0;i < 4;i++) { finalcompute(produs, end - 1); }
	cout << "�������Լ������\n" << endl;

	/*����html*/
	x7outfile.open("test.html", ios::out);
	if (!x7outfile) {
		cout << "��test.htmlʧ��" << endl;
		goto end;
	}
	x7outfile << framehead;
	produce_html(x7outfile, produs, end - 1);
	x7outfile << frameend;
	x7outfile.close();
	cout << "��ɡ�\ntest.html�Ѿ����ɡ�" << endl;
end:	system("pause");
	return 0;
}