#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> compute_prefix_function(const string & str){

  vector<int> prefix(str.size());
  for(int j=1, border=0, n=str.size(); j<n; j++){

    while(border && str[j] !=str[border]) 
      border= prefix[border-1];
  
    border=(str[j]==str[border]) ? ++border : 0;
    prefix[j]=border; } 
 return prefix;}

vector<int> find_pattern(const string& genome, const string& pattern){

  string str= pattern + '$' + genome;

  vector<int> pref_str= compute_prefix_function(str);
  vector<int> result;

  for(int i=pattern.size()+1; i<str.size(); i++){
    if(pref_str[i]== pattern.size())
      result.push_back(i-2* pattern.size());}
  return result;}
 
int main(){
  string pattern, genome;
  cin>>pattern>>genome;

  auto result= find_pattern(genome,pattern);
  for(auto x: result)
    cout<<x<<" ";
  cout<<endl;
}
