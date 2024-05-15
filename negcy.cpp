#include <iostream>
#include <vector>
#include <climits>
using namespace std;

bool bellman_ford(vector<vector<int> > & adj, vector<vector<int> > & cost, int s){

  vector<long long > dist(adj.size());
  for(int i=0; i<adj.size(); i++){ dist[i]=INT_MIN;}
  dist[s]=0;
   
  for(int rep=0; rep<adj.size()-1; rep++){
    for(int i=0; i<adj.size(); i++){
      for(int j=0; j<adj[i].size();j++){
         int vertex= adj[i][j];
         if(dist[vertex]> dist[i] + cost[i][j])
           dist[vertex]= dist[i] + cost[i][j];
           }}}
   
  for(int i=0;i<adj.size();i++){
    for(int j=0;j<adj[i].size();j++){
      int vertex=adj[i][j];
      if(dist[vertex]>dist[i]+ cost[i][j]) 
        return true;
        }}
  return false;
}

bool negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  for(int i =0; i<adj.size(); i++){
    if(bellman_ford(adj,cost,i)) return true;}
  return false;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  cout << negative_cycle(adj, cost);
}

