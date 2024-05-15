#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(int v, vector<vector<int> > &adj, vector<bool> &visited){
  visited[v]=true;
  for(int i=0; i<adj[v].size(); i++){
    int w=adj[v][i];
    if(!visited[w]) 
      explore(w, adj, visited);} } 

int number_of_components(vector<vector<int> > &adj) {
  vector<bool> reached;
  reached.resize(adj.size());
 
  int res = 0;
  for(int i=0; i<adj.size(); i++){
    if(!reached[i]){
      explore(i, adj, reached);
      res++;   }}

  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}

