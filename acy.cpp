#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool explore(int v, vector<vector<int> > &adj, vector<bool>visited, vector<bool> &res_stack){
  visited[v]=true;
  res_stack[v]=true;

  for(int i=0; i<adj[v].size();i++){
    int w=adj[v][i];
    if(!visited[w] && explore(w,adj,visited, res_stack)) return true;
    else if (res_stack[w]) return true;}
  res_stack[v]=false;
  return false;}
   

bool acyclic(vector<vector<int> > &adj) {
  vector<bool> reached;
  reached.resize(adj.size());
  vector<bool> rstack;
  rstack.resize(adj.size());

  for(int i=0; i< adj.size(); i++)
    if(explore(i, adj, reached, rstack)) 
      return true;
  
  return false;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}

