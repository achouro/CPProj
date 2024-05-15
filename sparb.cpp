#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Number{
public: long long value; bool is_inf;
        Number(): is_inf(true) {}
        void set_value(long long value){ this->value=value; this->is_inf=false;}

//operator overload, bear with us 
       
        Number operator+(const long long &rhs){ Number nb=Number();
						if(not is_inf){ nb.set_value(value+rhs);}						 return nb;}
	Number operator+(const Number &rhs){Number nb=Number();
					    nb.is_inf= is_inf or rhs.is_inf;
					    if(not is_inf){ nb.set_value(value + rhs.value);}
					    return nb;}    
	bool operator>(const Number & rhs){ if(is_inf){ return !rhs.is_inf;}
					    else if(rhs.is_inf){ return false;}
					    else{ return value > rhs.value;} }};

struct Result{ vector<Number> dist; vector<int> prev; set<int> neg_inf;
               Result(vector<Number> dist, vector<int> prev, set<int> neg_inf):
               dist(dist), prev(prev), neg_inf(neg_inf){} };

Result bellman_ford(vector<vector<int> > &adj, vector<vector<int> > &cost, int s) {

  vector <Number> dist(adj.size());
  vector <int> prec(adj.size(),-1);

  dist[s].set_value(0);
  prec[s] = 0;

  for (int rep = 0; rep < adj.size() - 1; rep++) {
    for (int i = 0; i < adj.size(); i++) {
      for (int j = 0; j < adj[i].size(); j++) {
	int vertex = adj[i][j];
	if (dist[vertex] > dist[i] + cost[i][j]){
		dist[vertex] = dist[i] + cost[i][j];
                prec[vertex]=i;
                  }}}}
  queue<int> Q;
  set<int> neg_inf;
  set<int> done;
  
  for(int i=0;i<adj.size(); i++){
    for(int j=0; j<adj[i].size();j++){
      int vertex= adj[i][j];
      if(dist[vertex]> dist[i]+ cost[i][j]){
        dist[vertex]= dist[i] + cost[i][j];
        Q.push(vertex);
        done.insert(vertex);}}}

  while(!Q.empty()){
    auto u= Q.front();
    Q.pop();
    
    neg_inf.insert(u);

   for(auto j=0; j<adj[u].size(); j++){
     int n= adj[u][j];
     if(done.find(n)== done.end()){
       Q.push(n);
       done.insert(n);}}}
  return Result(dist, prec, neg_inf);
}

int main() {
  int n, m, s;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  cin >> s;
  auto res= bellman_ford(adj, cost, s-1 );

  for (int i = 0; i < n; i++) {
    if (res.prev[i]==-1) {
      cout << "*\n"; }
     else if (res.neg_inf.find(i) != res.neg_inf.end()) {
      cout << "-\n";}
      else {
      cout << res.dist[i].value << "\n";  }
  }
  return 0;
}

