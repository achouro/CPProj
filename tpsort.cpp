#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;


void explore(int v, vector<vector<int> > &adj, vector<bool> &visited, stack<int> &ordering){
  visited[v]=true;
  for(int i=0; i<adj[v].size(); i++){
    int w=adj[v][i];
    if(!visited[w]) 
      explore(w, adj, visited, ordering);} 
  ordering.push(v);}

stack<int> toposort(vector<vector<int> > adj) {
  vector<bool> used(adj.size(), 0);
  stack<int> order;
  for(int i =0; i<adj.size(); i++)
    if(!used[i])
      explore(i, adj, used, order);
  return order;
}

void dfs(vector<vector<int> > &adj) {
  stack<int> ordering = toposort(adj);
  while(!ordering.empty()){
    int n= ordering.top();
    ordering.pop();
    cout<< n+1<<" ";} // display stack top values, topologically sorted adj then pop
  cout<<endl;
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
  dfs(adj);
}

