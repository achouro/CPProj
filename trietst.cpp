#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
//error here
using edges = map<char, int>;
using trie = vector<edges>;

trie build_trie(vector<string>& patterns) {

	if (patterns.empty())
		return trie();

	trie t((edges()));

	int root = 0;
	int count = 0;

	for(auto& pattern : patterns){

		int current = root;

		for (auto s: pattern) {

			if (t[current].find(s) != t[current].end())
				current = t[current][s];

			else {

				t.__emplace_back(edges());
				t[current][s] = ++count;
				current = count; }}}
	return t;

}

int main() {

	int n;
	cin >> n;
	// n = 1;

	vector<string> patterns(n);

	for (int i = 0; i < n; i++) {

		string s;
		cin >> s;
		// s = "ATA";

		patterns.push_back(s);

	}

	trie t = build_trie(patterns);

	for (int i = 0; i < t.size(); i++) {

		for (auto j : t[i])
			cout << i << "->" << j.second << ":" << j.first << endl;
	}

	return 0;


}
