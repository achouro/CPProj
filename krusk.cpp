#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <set>

using namespace std;

struct point{ int x,y; point(): x(0),y(0){}; point(int x,int y):x(x),y(y) {};
	      
             // bool operator<( const point &rhs){
	     //	return this->x<rhs.x || (this->.x==rhs.x && this->.y<rhs.y);};

	      friend ostream &operator<<(ostream &os, const point &pts){
	        os<<"("<<pts.x<<","<<pts.y<<")";
                return os; }  };

struct sset{ int rank; int parent; sset(): rank(0), parent(-1) {}; };

class disjoint_set{
  vector<sset> sets;
  public:
 	disjoint_set(int size){ 
	  sets.resize(size);
	  for(int i=0;i<size;i++)
	    sets[i].parent=i;};

	int find(int u){ 
	  int index=u; 
	  if(sets[index].parent!=index)
	  sets[index].parent=find(sets[index].parent);
	  return sets[index].parent;}

	void take_union(int a, int b){  
	  auto a_id= find(a);
	  auto b_id= find(b);

	  if(a_id==b_id) return;
	  if(sets[a_id].rank> sets[b_id].rank)
	    sets[b_id].parent=a_id;

	  else{
	    sets[a_id].parent=b_id;
	    if(sets[a_id].rank=sets[b_id].rank)
 	      sets[b_id].rank++;}}
	
	bool same_set(int a,int b){
	  return(find(a)==find(b));}  };


double distance(const point &a,const point &b){ 
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));}
//	return hypot(a.x-b.x, a.y-b.y);}

/*
auto comparator[](const pair<int,int> &a,const pair<int,int> &b){
        auto norm_a=distance(a.first , a.second);
        auto norm_b= distance(b.first,b.second);
        return norm_a< norm_b; };
*/

double cluster_kruskal(vector<point> points, int k) {
  int n=points.size();
  int n_clusters=n ;

  disjoint_set DS(n);

  vector<pair<int,int> > edges;
  edges.reserve((int) n*(n-1)/2 );  //~resize to total nb of pairs

  for(int i=0; i<n; i++)
    for(int j=i+1;j<n;j++)
      edges.push_back(make_pair(i,j)); //fill with pairs
  

/*  sort(edges.begin(), edges.end(),
     [points](const pair<int,int> &a,const pair<int,int> &b){
        auto norm_a=distance(points[a.first] ,points[a.second]);
        auto norm_b= distance(points[b.first],points[b.second]);
        return norm_a< norm_b; });
*/

  sort(edges.begin(), edges.end());

  int index=0;

  while(n_clusters>=k){
    auto edge= edges[index];
    if(DS.find(edge.first)!=DS.find(edge.second)){
      DS.take_union(edge.first, edge.second);
      n_clusters--;}
      index++;}
  
  auto edge=edges[--index];

  return distance(points[edge.first], points[edge.second]);
} 

int main() {
  size_t n;
  cin >> n;
  vector<point> points(n);
  for (size_t i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
  }
  int k;
  cin>>k;
  cout << setprecision(10) << cluster_kruskal(points,k) << endl;
}

