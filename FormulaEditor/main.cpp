#include"SemanticAnalyzer.h"

int main() {
	ifstream x7infile;
	ofstream x7outfile;
	symbol x7symstream[MAXSTREAMLEN];
	vector<production> produs;
	const int initsize = 50, initleft = 500, inittop = 175;
	int flag = SUCCEED;

	/*从test.txt读入字符并转换成符号流*/
	x7infile.open("test.txt", ios::in);
	if (!x7infile) {
		cout << "打开文件test.txt失败!" << endl;
		goto end;
	}
	if (x7getsymbolstream(x7infile, x7symstream) != SUCCEED) { goto end; }
	x7infile.close();
	cout << "\n词法分析完毕\n" << endl;

	/*语法分析，输出的表达式按输出顺序压入容器里*/
	if (parser(x7symstream, produs) != SUCCEED) { goto end; }
	cout << "语法分析完毕\n" << endl;

	/*翻译*/
	int end = produs.size();
	bool* mark = new bool[end];
	for (int i = 0;i < end;i++) { mark[i] = false; }
	produs[end - 1].left.init(initsize, inittop, initleft);
	produslink(produs, end - 1, mark);

	/*自顶向下计算剩余属性值*/
	for (int i = 0;i < 2;i++) { finalcompute(produs, end - 1); }
	cout << "符号属性计算完毕\n" << endl;

	/*生成html*/
	x7outfile.open("test.html", ios::out);
	if (!x7outfile) {
		cout << "打开test.html失败" << endl;
		goto end;
	}
	x7outfile << framehead;
	produce_html(x7outfile, produs, end - 1);
	x7outfile << frameend;
	x7outfile.close();
	cout << "完成。\ntest.html已经生成。" << endl;
end:	system("pause");
	return 0;
}