#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.

struct node{ int start=0; int end=0; int next=0;
	     node(int next, int start, int end): next(next),start(start),end(end){} };

using edges= vector<node>;

class suffix_tree{
  string text;
  int length;
  vector<edges> tree;
  int current;
  int root;
public:
	suffix_tree(const string& text){
	  this->text=text;
	  length=text.size();
	  root=0;
	  current=1;

	  tree.reserve(length/10);
	  tree.emplace_back(edges{});}

	void add_node(int start, int i){
	  tree.emplace_back(edges{});
	  tree[i].emplace_back(node(current++,start,length));}

	void add_node_branch(node& nd, int k, int m){
	  if(!tree[nd.next].empty()){
	    tree.emplace_back(edges{});
	    tree.emplace_back(edges{});

	    tree[current]=move(tree[nd.next]);
	    tree[nd.next].emplace_back(node(current++, m, nd.end));
	    tree[nd.next].emplace_back(node(current++, k, length));
	    nd.end=m;}


	  else{
	    add_node(m,nd.next);
	    add_node(k,nd.next);
	    nd.end=m;} }

	void build_tree() {
	  for(int i=0;i<length;i++){
	    int current= root;
	    for(int j=i; true;){

	      char symbol= text[j];
	      auto it= find_if(tree[current].begin(),tree[current].end(),[&](const node& nd){
	        return text[nd.start]==symbol;});
	      if(it== tree[current].end()){
		add_node(j,current); break;}

	      node& nd= *it;
	      int m=nd.start;

	      for(; j<length &&  m<nd.end; j++,m++){
		if(text[j]!=text[m]){
		  add_node_branch(nd,j,m);
		  goto inner_loop_wayout;}}
	      	
		if(m==nd.end && j==length) break;

		else if(m=nd.end){
		  if(tree[nd.next].empty()){
		    add_node(j,nd.next); break;}

		  current=nd.next; continue;}
	  	
		else {
		  if(tree[nd.next].empty()){
		    add_node(m,nd.next); 
		    nd.end=m;
		    break;}
		  tree.emplace_back(edges{});
		  tree[current].emplace_back(node(nd.next,m,nd.end));
		  nd.next=current;
		  nd.end=m;
		  break;}

		inner_loop_wayout: break; }}}
	void display(){
	  for(const auto& edges:tree)
	    for(const auto& e:edges){
	      for(int i=e.start;i<e.end;i++)
		cout<<text[i];
	      cout<<endl;}}
};



int main() {
  string text;
  cin >> text;

  suffix_tree suff_tree(text);
  suff_tree.build_tree();
  suff_tree.display();
  return 0;
}

