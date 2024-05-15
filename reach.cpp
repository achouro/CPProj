#include <iostream>
#include <vector>

using std::vector;
using std::pair;


void explore(int v, vector<vector<int> > & adj, vector<bool> &visited){

  visited[v]=true;
  for (int i =0; i<adj[v].size();i++){
    int w=adj[v][i];
    if(!visited[w])
      explore(w, adj, visited); } }

int reach(vector<vector<int> > &adj, int x, int y) {
  
  vector<bool> reached;
  reached.resize(adj.size());
  
  explore(x, adj,reached);

  if (reached[x] && reached[y]) return 1; 
  return 0;
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}

