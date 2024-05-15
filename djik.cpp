#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>


using namespace std;
struct Node { int vertex; int dist; 
              Node(int vertex, int dist): vertex(vertex), dist(dist){};
	      bool operator>(const Node & rhs) const{ return this->dist > rhs.dist;} };              

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  vector<int> dist(adj.size(),INT_MAX);

  dist[s]=0;
  priority_queue<Node, vector<Node>, greater<Node> > PQ;
  PQ.push(Node(s,0));

  while(!PQ.empty()){
    auto u=PQ.top();
    PQ.pop();
    
    for(auto i=0; i!=adj[u.vertex].size(); i++){
      int n= adj[u.vertex][i];
      if(dist[n]> dist[u.vertex] + cost[u.vertex][i]){
        dist[n]= dist[u.vertex] + cost[u.vertex][i];
        PQ.push(Node(n, dist[n]));}}

        } 
  if(dist[t]==INT_MAX){ return -1;}

  else
    return dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}

