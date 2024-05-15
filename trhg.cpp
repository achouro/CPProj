#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class tree_{ 
int n; 
vector<int> parent; 
vector<int> depth;
public:
  void read(){cin>>n; parent.resize(n); depth.resize(n);
              for(int i=0; i<n; i++){ cin>> parent[i];}}

  int compute_height(){ int max_height=0; if(n==0) return n;
                        for(int i=0;i<n;i++){fill_depth(i);}
                        for(int i=0;i<n;i++){
                          int height=depth[i];
                          max_height= max(max_height, height);}
                        return max_height;}

  void fill_depth(int node_number){
    if(parent[node_number]==-1){depth[node_number]=1; return;
    
    if(depth[node_number]) return;
   
    if(!depth[parent[node_number]]) fill_depth(parent[node_number]);

    depth[node_number]= depth[parent[node_number]]+1;}}
};

int main(){
ios_base::sync_with_stdio(0);
tree_ tree;

tree.read();

cout<<tree.compute_height()<<endl;}


