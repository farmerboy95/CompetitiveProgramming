/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: More or less like this submission https://github.com/thecodingwizard/competitive-programming/blob/master/IOI/IOI%2019-vision.cpp
*/

#include <bits/stdc++.h>
#include "vision.h"

using namespace std;

void construct_network(int H, int W, int K) {
	vector<int> lefDi, rigDi;

	for (int i = H-1; i >= 0; i--) {
		vector<int> a;
		for (int x = i, y = 0; x < H && y < W; x++, y++) a.push_back(x * W + y);
		if (i == H-1) rigDi.push_back(add_xor(a));
		else rigDi.push_back(add_xor({ rigDi.back(), add_xor(a) }));
	}
	for (int i = 1; i < W; i++) {
		vector<int> a;
		for (int x = 0, y = i; x < H && y < W; x++, y++) a.push_back(x * W + y);
		rigDi.push_back(add_xor({ rigDi.back(), add_xor(a) }));
	}

	for (int i = 0; i < W; i++) {
		vector<int> a;
		for (int x = 0, y = i; x < H && y >= 0; x++, y--) a.push_back(x * W + y);
		if (i == 0) lefDi.push_back(add_xor(a));
		else lefDi.push_back(add_xor({ lefDi.back(), add_xor(a) }));
	}
	for (int i = 1; i < H; i++) {
		vector<int> a;
		for (int x = i, y = W-1; x < H && y >= 0; x++, y--) a.push_back(x * W + y);
		lefDi.push_back(add_xor({ lefDi.back(), add_xor(a) }));
	}

	vector<int> lefDiCheck1, rigDiCheck1;
	for (int i = 0; i < int(rigDi.size()) - K; i++) rigDiCheck1.push_back(add_and({rigDi[i], rigDi[i+K]}));
	for (int i = 0; i < int(lefDi.size()) - K; i++) lefDiCheck1.push_back(add_and({lefDi[i], lefDi[i+K]}));

	vector<int> lefDiCheck2, rigDiCheck2;
	for (int i = 0; i < int(rigDi.size()) - (K-1); i++) rigDiCheck2.push_back(add_and({rigDi[i], rigDi[i+K-1]}));
	for (int i = 0; i < int(lefDi.size()) - (K-1); i++) lefDiCheck2.push_back(add_and({lefDi[i], lefDi[i+K-1]}));

	add_and({ add_or({ add_or(lefDiCheck2), add_or(rigDiCheck2) }), add_not(add_or(lefDiCheck1)), add_not(add_or(rigDiCheck1)) });
}
