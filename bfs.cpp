#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  vector<int> dist;
  dist.resize(adj.size());
  
  for(int i=0; i<adj.size(); i++)
    dist[i]=-1;
  
  dist[s]=0;
  queue<int> Q;
  Q.push(s);

  while(!Q.empty()){
    int u=Q.front();
    Q.pop();

    for(auto i=adj[u].begin(); i!=adj[u].end(); i++){
      if(dist[*i]==-1){
        Q.push(*i);
        dist[*i]=dist[u]+1;}}}

  return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
