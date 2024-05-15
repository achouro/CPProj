//#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <set>

using namespace std;

struct point{ int x,y; point(): x(0),y(0){}; point(int x,int y):x(x),y(y) {};  };
struct node { size_t index; double dist; 
	      node(size_t index, double dist): index(index), dist(dist){}; 
	      bool operator>(const node &rhs) const{return this->dist > rhs.dist;} };

double distance(const point &a,const point &b){ 
	      return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));}


double min_dist_prim(vector<point> &points) {
  vector<double> dist(points.size(),INT_MAX);
  dist[0]=0;
  
  priority_queue<node, vector<node> , greater<node> > PQ;
  PQ.push(node(0,0));

  //ordered sets
  set<int> done, to_do;

  for(int i=0; i<points.size(); i++)
    to_do.insert(i);  //all unknown initially i.e not in forest

  double result=0;

  while(!PQ.empty()){
    auto u=PQ.top(); //smallest element 
    PQ.pop();

    if(done.set::find(u.index)!=done.end())
      continue;

    result+=u.dist;
    to_do.erase(u.index);

    //explore,relax
   // for(auto i=0; i<to_do.size(); i++){
   for(auto i: to_do){
      auto d= distance(points[u.index],points[i]);
      if(dist[i]> d){
	dist[i]=d;
	PQ.push(node(i,d));}}

    done.insert(u.index);}

  return result;
} 

int main() {
  size_t n;
  cin >> n;
  vector<point> points(n);
  for (size_t i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
  }
  cout << setprecision(10) << min_dist_prim(points) << endl;
}

