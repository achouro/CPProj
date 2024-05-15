#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

bool distance(vector<vector<int> > &adj, int s, vector<int> &colour) {

  colour[s]=1;
  queue<int> Q;
  Q.push(s);

  while(!Q.empty()){
    int u=Q.front();
    Q.pop();

    for(auto i=adj[u].begin(); i!=adj[u].end(); i++){
      if(colour[*i]==-1){
        Q.push(*i);
        colour[*i]= 1- colour[u];}  //1 0 1 0 per breadth
      else if (colour[*i]== colour[u])
        return false;}}

  return true;
}
int bipartite(vector<vector<int> > &adj) {
  vector<int> colour;
  colour.resize(adj.size());
  for(int i=0;i<adj.size();i++)
    colour[i]=-1;
  
  for(int i=0; i<adj.size(); i++){
    if(colour[i]==-1)
      if(!distance(adj, i, colour))
        return false;}
  return true;
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
  std::cout << bipartite(adj);
}

