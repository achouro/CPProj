#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

using edges=map<char,int>;
using trie=vector<edges>;

//vector<map<char,int> > trie_build (vector<string>& patterns)
trie trie_build(vector<string>& pattern)
{
//  map<char,int> edges;
//  vector<map<char,int> > trie;  
  
  if(patterns.empty()) return trie;

  vector<map<char,int> > t;

  int root=0, count=0;

  for(auto& pattern: patterns){
    int current= root;
    for(auto str:pattern){

      if(t[current].find(str)!=t[current].end())
        current= t[current][str];
      else{
        t.__emplace_back(edges);
        t[current][str]=++count;
        current=count; }}}

  return t;
}

int main (void)
{
	int n;
	cin>>n;
	vector<string> patterns(n);

	for(int i=0; i<n; i++){
  	  string str;
	  cin >> str;
          patterns.push_back(str);}
	
	vector<map<char,int> > t=trie_build(patterns);

	for(int i=0;i<t.size();i++){
	  for(auto j: t[i])
	    cout<<i<<"->"<<j.second<<":"<<j.first<<endl;}

	return 0;
}
