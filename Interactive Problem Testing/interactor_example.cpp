// problem link: https://www.codechef.com/LTIME109A/problems/XORDETECTIVE

#include <bits/stdc++.h>

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

const int L = 29;

void interact() {
	int q = 30;
	cout << q << endl;
	int a = 0, b = 0;
	for (int i = 0; i < L; ++i) {
		a |= (rand() % 2) << i;
		b |= (rand() % 2) << i;
	}
	if (a > b) {
		swap(a, b);
	}
	++q;
	while (q--) {
		string type;
		cin >> type;
		if (type == "?") {
			int x = nxt();
			assert(x < (1 << (L + 1)));
			cout << ((a + x) ^ (b + x)) << endl;
		} else if (type == "!") {
			int ga = nxt(), gb = nxt();
			if (ga == a && gb == b) {
				return;
			}
			cerr << "wrong, I guessed " << bitset<L>(a) << " and " << bitset<L>(b) << ", got " << bitset<L>(ga) << " and " << bitset<L>(gb) << "\n";
			exit(1);
		} else {
			cerr << "expected ?/!, got " << type << "\n";
			exit(3);
		}
	}
	cerr << "qle\n";
	exit(2);
}

int main() {
	int t = 10;
	cout << t << endl;
	while (t--) {
		interact();
	}

	return 0;
}
