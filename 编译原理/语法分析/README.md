## 编译原理

### 自顶向下得语法分析

- 文法数据结构
```c++
struct product {  //产生式
	string left;
	string right;
	product() {}
	product(string left, string right) {
		this->left = left;
		this->right = right;
	}
	friend ostream & operator << (ostream &out, const product &p) {
		out << p.left << "->" << p.right;
		return out;
	}
};
struct grammar {  //文法四元组
	set<string> Vt;
	set<string> Vn;
	vector<product> P;
	string startSymbol;
};
```
- first 集合的构造
```c++
set<string> getfirst(string x, grammar g) {
	set<string> first;
	if (g.Vt.count(x) != 0) {
		first.insert(x);
		return first;
	} 
	if (check(x, g)) {
		first.insert("ε");
	}
	for (vector<product>::iterator it = g.P.begin(); it != g.P.end(); it++) {
		if (it->left == x) {
			int i = 0;
			for (char c : it->right) {
				i++;
				string y{ c };
				set<string> temp = getfirst(y, g);
				if (temp.count("ε") != 0) {
					for (string s : temp) {
						if (s != "ε") {
							first.insert(s);
							if (i == it->right.length()) {
								first.insert("ε");
							}
						}
					}
				} else {
					for (string s : temp) {
						if (s != "ε") {
							first.insert(s);
						}
					}
					break;
				}
				temp.clear();
			}
		}
	}
	return first;
}
```
- follow 集合的构造
```c++
set<string> getfollow(string x, grammar g) {
	set<string>  follow;
	if (x == g.startSymbol) {
		follow.insert("#");
		//return follow;
	}
	for (product p : g.P) {
		if (p.right.size() >= 3) {
			size_t index = p.right.find(x);
			if (index != string::npos && index != p.right.size() - 1) {
				string b{ p.right[index + 1]};
				set<string> temp = getfirst(b, g);
				if (temp.count("ε") != 0) {
					for (string s : temp) {
						if (s != "ε") {
							follow.insert(s);
						}
					}
					set<string> temp2 = getfollow(p.left, g);
					for (string s : temp2) {
						follow.insert(s);
					}
				} else {
					for (string s : temp) {
						follow.insert(s);

					}
				}
			}
		}
	}
	for (product p : g.P) {
		if (p.right.size() >= 2 && p.left != x) {
			size_t index = p.right.find(x);
			if (index != string::npos && index == p.right.size() - 1) {
				set<string> temp2 = getfollow(p.left, g);
				for (string s : temp2) {
					follow.insert(s);
				}
			}
		}
	}
	return follow;
}
```