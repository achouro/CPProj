#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int alphabet_size=5;

int get_index(char c){
  switch(c){
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
    default : return 0;}}

vector<int> sort_double(const string& s, int L, const vector<int>& order, const vector<int>& cclass){

  vector<int> count(s.size());
  vector<int> new_order(s.size());

  for(int i=0; i< s.size(); ++i)
    ++count[cclass[i]];

  for(int j=1; j<s.size(); ++j)
    count[j]+=count[j-1];

  for(int i=s.size()-1; i>=0; --i){
    int start= (order[i] -L +s.size())%s.size();
    int cl=cclass[start];
    new_order[--count[cl]]=start;}
  return new_order;}

vector<int> compute_character_classes(const string& s, const vector<int>& order){
  vector<int> cclass(s.size());
  for(int i=1;i<s.size(); ++i){
    if(s[order[i]]!=s[order[i-1]]){
      cclass[order[i]]=cclass[order[i-1]]+1;}
    else{
      cclass[order[i]]=cclass[order[i-1]];}}

  return cclass;}

vector<int> counting_character_sort(const string& s){
  vector<int> order(s.size());
  vector<int> count(alphabet_size);

  for(auto& c:s){ ++count[get_index(c)];}

  for(int j=1; j<alphabet_size; ++j){ count[j]+=count[j-1];}

  for(int i=s.size()-1;i>=0; --i){
    char c=s[i];
    count[get_index(c)]-=1;
    order[count[get_index(c)]]=i;}
  return order;}

vector<int> update_class(const vector<int>& new_order,const vector<int>& cclass, int L){
  const int n=new_order.size();
  vector<int> new_cclass(n);

  for(int i=1; i<n; ++i){
    int curr=new_order[i], prev=new_order[i-1];
    int mid=curr+L, mid_prev=(prev+L)%n;

    if(cclass[curr]!= cclass[prev] || cclass[mid]!=cclass[mid_prev]){
      new_cclass[curr]=new_cclass[prev]+1;}

    else{
      new_cclass[curr]=new_cclass[prev];} }
  return move(new_cclass);}

vector<int> construct_suffix_array(const string& s){
  vector<int> order= counting_character_sort(s);
  vector<int> cclass=compute_character_classes(s,order);
  int L=1;

  while(L<s.size()){
    order=sort_double(s,L,order,cclass);
    cclass=update_class(order,cclass,L);
    L*=2;}

  return move(order);}

int main(){

  string s;
  cin>>s;

  auto order= construct_suffix_array(s);

  for( auto i:order){
    cout<<i<<' ';}
  return 0;}



