// grammar_analysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "analysis.h"

int main() {
	string v;
	grammar g = create("product.txt");
	cout << g.P.size() << endl;
	for (vector<product>::iterator it = g.P.begin(); it != g.P.end(); it++) {
		cout << *it << endl;
	}
	while (true) {
		cin >> v;
		cout << "非终结符得follow集合:" << endl;
		set<string> result = getfollow(v, g);
		cout << v << ":";
		for (string x : result) {
			cout << x << " ";
		}
		cout << endl;
		
	}
}
