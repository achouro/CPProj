#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

using edges=map<char,int>;
using trie=vector<map<char,int> >;

trie trie_build(vector<string>& patterns){
  if(patterns.empty()){return trie{};}
  
  trie triet{edges{}}; // vector<map<char,int> >
  int root=0;
  int count=0;

//  for(auto& pattern=patterns.begin(); pattern!=patterns.end();pattern++){
    for(auto& pattern:patterns){
    int current=root;
//    for(auto charc=pattern.begin(); charc!=pattern.end();charc++){
      for(auto charc:pattern){
        if(triet[current].find(charc)!=triet[current].end()){
	  current=triet[current][charc];}

        else{ //triet[current].find(charc)=triet[current].end()
	  triet.emplace_back(edges{});
          triet[current][charc]=++count;
	  current=count;} } }

  return triet;
}

vector<int> trie_matching(const string& text, int n, vector<string>& patterns){

  vector<int> positions;
  trie patt_trie= trie_build(patterns);

  for(int i=0; i<text.size(); i++){
    int index=0;
    int index_symbol=i;
    char symbol=text[index_symbol];

    while(true){
      if(patt_trie[index].empty()){
        positions.push_back(i);
	break;}

      else if(patt_trie[index].find(symbol)!=patt_trie[index].end()){
	index=patt_trie[index][symbol];
	symbol=text[++index_symbol];}

      else break; }  }

  return positions;
}    
  


int main(){
  string text;
  cin>>text;
 
  int n;
  cin>>n;

  vector<string> patterns(n);

  for(int i=0;i<n;i++){
	string charc;
	cin>>charc;
	patterns.push_back(charc);}

//  auto solution=trie_build(patterns);

  auto solution=trie_matching(text, n, patterns);

  for(int i=0;i<(int)solution.size();i++){
    cout<<solution[i];

    if(i+1<(int)solution.size()) cout<<" ";
    else cout<<endl;}

//    for(auto j:solution[i]){
//      cout<<i<<"->"<<j.second<<":"<<j.first<<endl
  return 0;
}
