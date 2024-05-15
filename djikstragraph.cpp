//Part A: Graph class

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include <map>
#include <queue>
using namespace std;

const int big_num=9999;

//node number into character
inline char num_to_char(int n){ if (n<26) return static_cast<char>('A'+n);
				else      return static_cast<char>('a'+n); }

ostream &operator<<(ostream &output, list<char> L)
{
   list<char>::iterator i;
   for(i=L.begin(); i != L.end(); ++i)
     output << *i << " ";
   return output;
}
//node struct has a number, weight and list of edges to leading neighbours

typedef struct node{ int number; int weight; list<node> edges;} node;

//

class graph
{
public:
	graph();
	graph(int num_nodes, int init_val);
	
//functions
	char get_node_value(int n);
	void set_node_value(char x, char name);
	int get_edge_value(char name1, char name2);
	void set_edge_value(char name1, char name2, int value);

	void add_w(char name1, char name2, int value);	
	bool adjascent(char name1, char name2);
	list<char> neighbours(char name);	
	int N();
	int E();
	list<char> vertices();
	void show();


private:
	int n_nodes;
	int n_edges;
	list<node> adj_list; //list of adjascent nodes on the graph
	
	vector<char> node_names; // map node number into name
	map<char, int> node_number; //map node name into number
};

graph::graph() // default constructor, empty graph
{
int n_nodes=0;
int n_edges=0;
adj_list.clear();
}

graph::graph(int num_nodes, int init_val=big_num)
{
n_nodes= num_nodes;
n_edges=0;

node_names.resize(n_nodes);

for( int i=0; i<num_nodes; ++i) //assign names A-Z,a-z to node numbers 0-51
	{
	node_names[i]= num_to_char(i);
	node_number[num_to_char(i)]=i;
	}
adj_list.clear();

for(int i=0; i<num_nodes; ++i) //create adjascency list 
	{
	node new_node;
	new_node.number=i;
	new_node.weight=0;
	new_node.edges.clear();
	adj_list.push_back(new_node); //stack new node on adj_list
	}
}

inline char graph::get_node_value(int n){ return node_names[n];}

void graph::set_node_value(char x, char name) //node name change from x to name
{
int pos_x= node_number[x];
node_names[pos_x]= name;
node_number[name]= pos_x;
}

int graph::get_edge_value(char name1, char name2)// return edge weight
{
// iterate over adj_list values

for(list<node>::iterator  i=adj_list.begin(); i!=adj_list.end(); ++i)
	{
	if ((*i).number==node_number[name1])
		for(list<node>::iterator j=adj_list.begin();j!=adj_list.end(); ++j)
			{
			if((*j).number==node_number[name2])
				return j->weight;
			}
	}
	//return big_num;	
}

void graph::set_edge_value(char name1, char name2, int value)
{
bool found;
for(list<node>::iterator  i=adj_list.begin(); i!=adj_list.end(); ++i)
	{
	if((*i).number==node_number[name1])
		{
		found=false;
		for(list<node>::iterator j=adj_list.begin(); j!=adj_list.end(); ++j)
		{
		if((*j).number==node_number[name2])
			{
			j->weight=value;
			found=true;
			}
		}
		if (found==false)
			{
			node new_node_name2;
			new_node_name2.number= node_number[name2];
			new_node_name2.weight= value;
			new_node_name2.edges.clear();
			(*i).edges.push_back(new_node_name2);
			}
		}
	}
}

void graph::add_w(char name1, char name2, int value)
{
bool found;
for(list<node>::iterator i=adj_list.begin(); i!=adj_list.end(); ++i)
	{
	if((*i).number==node_number[name1])
		{
		found= false;
		for(list<node>::iterator j=adj_list.begin();j!=adj_list.end(); ++j)
			{
			if ((*j).number==node_number[name2])
				{
				(*j).weight=value;
				found=true;
				}
			}
		if(found==false)
			{
			node new_node_name2;
			new_node_name2.number= node_number[name1];
			new_node_name2.weight= value;
			new_node_name2.edges.clear();
			(*i).edges.push_back(new_node_name2);
			++n_edges;
			}
		}
	}
}


bool graph::adjascent(char name1, char name2)
{
for(list<node>::iterator i=adj_list.begin(); i!=adj_list.end(); ++i)
        {
        if((*i).number==node_number[name1])
                {
                for(list<node>::iterator j=adj_list.begin();j!=adj_list.end(); ++j)
                        {
                        if ((*j).number==node_number[name2])
                                {	
				return true;
				}
			}
		}
	}
	return false;
}

list<char> graph::neighbours(char name)
{
list<char> adj_nodes;

for(list<node>::iterator i=adj_list.begin(); i!=adj_list.end(); ++i)
	{
	if((*i).number==node_number[name])
		{
		for(list<node>::iterator j=(*i).edges.begin(); j!=(*i).edges.end();++j)
			{
			adj_nodes.push_back(node_names[(*j).number]);
			}
		}
	}
	return adj_nodes;
}

inline int graph::N(){ return n_nodes;}

inline int graph::E(){ return n_edges;}


list<char> graph::vertices()
{
list<char> node_name;

for(list<node>::iterator i=adj_list.begin(); i!=adj_list.end(); ++i)
	{
	node_name.push_back(node_names[ (*i).number]);
	}
	return node_name;
}


void graph::show()
{
cout<<"  ";
for(list<node>::iterator i= adj_list.begin(); i!=adj_list.end(); ++i)
	cout<<node_names[(*i).number]<<" ";
cout<<endl;

for(list<node>::iterator i=adj_list.begin(); i!=adj_list.end(); ++i)
{
cout<<node_names[(*i).number];
int shift=0;
for(list<node>::iterator j=(*i).edges.begin(); j!=(*i).edges.end(); ++j)
	{
	int walk= (*j).number - shift;  //define a walk to iterator over
	for(int k=0; k<walk; ++k)
		{
		cout<<" -";
		shift++;
		}
	cout<<" "<<(*j).weight;
	shift++;
	}
while(shift< n_nodes)
{
cout<<" -";
shift++;
}
cout<<endl;
}

}






//at each node we will have access to information about adjascent nodes in the form of the following

struct node_inf{
		char node_name;
		int min_dist; //shortest path to node_name
		char prec;  //preceding node
		};

typedef struct node_inf node_inf;

bool compare_min_dist(node_inf& n1, node_inf& n2)
{
if(n1.min_dist<n2.min_dist) return true;
else return false;
}


//############################
// Part B: Priority queue class

class Priority_queue 
{
public:
	Priority_queue();
	void change_priority(node_inf n);
	void remove_min_priority();
	bool contains(node_inf n);
	bool is_better(node_inf n);
	void insert(node_inf n);
	
	node_inf Top();
	int size();

private:
	list<node_inf> pq;  //list of know priority queue nodes and paths
};

typedef class Priority_queue Priority_queue;

Priority_queue::Priority_queue()
{
pq.clear();
}


void Priority_queue::change_priority(node_inf n)  //change position of node n in priority queue
{
for (list<node_inf>::iterator i=pq.begin(); i!=pq.end(); ++i)
	{
	if ((*i).node_name==n.node_name)
		{
		(*i).min_dist=n.min_dist;
		(*i).prec    =n.prec;
		}
	}
	pq.sort(compare_min_dist);  //ordering of pq's i following  boolean compare_min_dist
//the result is a weakly ascending list pq (could be descending if n1>n2 in compare_min_dist)
}

void Priority_queue::remove_min_priority() //remove node with lowest min distance from priority queue
{
if(! pq.empty()) { pq.pop_front(); }
}

bool Priority_queue::contains(node_inf n)
{
for(list<node_inf>::iterator i=pq.begin(); i!=pq.end(); ++i)
	if ((*i).node_name==n.node_name)
		return true;
	return false;
}

bool Priority_queue::is_better(node_inf n)
{
for(list<node_inf>::iterator i=pq.begin(); i!=pq.end(); ++i)
	if((*i).node_name==n.node_name)
		if((*i).min_dist<n.min_dist)
			return true;
	return false;
}


void Priority_queue::insert(node_inf n)  //insert node at the back of priority queue
{
pq.push_back(n);
pq.sort(compare_min_dist);	 //sort in ascending order 
}

node_inf Priority_queue::Top()
{
node_inf n={' ', 0};

if(!pq.empty())
	{	
	list<node_inf>::iterator i=pq.begin();  //only first value of pq
	n.node_name= (*i).node_name;
	n.min_dist = (*i).min_dist;
	n.prec     = (*i).prec;
	}
	return n;
}

inline int Priority_queue::size(){ return pq.size();}

//###########################################################

//Part C: Shortest path class

class shortest_path
{
public:
	shortest_path();
	shortest_path( graph g);
	list<char> path( char name_a, char name_b);
        int path_size(char name_a, char name_b);

private:
	graph graphe;
};

shortest_path::shortest_path() {}

shortest_path::shortest_path( graph g){ graphe =g;}

list<char> shortest_path::path(char name_a,char name_b)
{

list<char> candidates= graphe.vertices(); //initialise a list of all possible candidate nodes in graph
list<char>optimal_path;
list<node_inf> min_paths;               // minimum paths list of nodes 
Priority_queue prq;      
node_inf last_selected, n;   //last selected node and current node

candidates.list::remove(name_a);  //origin name_a is out of candidates

last_selected.node_name= name_a;  //initialise last selected node to name_a
last_selected.min_dist = 0;
last_selected.prec     = name_a;

min_paths.push_back(last_selected);   //insert into the back of the list of min paths

while( (!candidates.empty()) && (last_selected.node_name!=name_b))
{
	for(list<char>::iterator i=candidates.begin(); i!=candidates.end(); ++i)
	{
	n.node_name=*i;
	n.min_dist = last_selected.min_dist + graphe.get_edge_value(last_selected.node_name, *i);
	n.prec     = last_selected.node_name;
	
	if(!prq.contains(n)) prq.insert(n);
	else if(prq.is_better(n)) prq.change_priority(n);
	}
//reorder priority list with n in ascending order resulting in the lowest value/cost floating to the front of the list
	
	last_selected= prq.Top(); //collect top of ordered queue in last selected 
	prq.remove_min_priority();  // remove lowest value above from queue 
	min_paths.push_back(last_selected); // add it to min_paths list
	candidates.list::remove(last_selected.node_name); //remove for candidate names
}

// the while loop loads a list of min paths from a to b which we sweep backward now

while(last_selected.node_name!=name_a) //a is destination from b
{
for(list<node_inf>::iterator i=min_paths.begin(); i!=min_paths.end(); ++i)
	if((*i).node_name==last_selected.prec) //i is the precedent ls node
	{	
	(*i)=last_selected; // move i from precedent to node itself
	optimal_path.push_front(last_selected.node_name);
	}
}
return optimal_path;
}
	

int shortest_path::path_size(char name_a, char name_b)
{
int path_cost=0;
list<char> sp;
char current, next;

sp=path(name_a, name_b);

current=sp.front();
sp.pop_front();

for(list<char>::iterator i=sp.begin(); i!=sp.end(); ++i)
{
next=(*i);
path_cost += graphe.get_edge_value(current,next);
current =next;
}
return path_cost;
}

//##############################################
// Part D: Monte Carlo simulation

class monte_carlo
{
public:
	monte_carlo();
	graph mt_graph(int num_vertices, double density, int min_dist, int max_dist);
	void run( graph g);
private: 
};


monte_carlo::monte_carlo() { srand(time(NULL));}

graph monte_carlo::mt_graph( int num_vertices, double density, int min_dist, int max_dist)
{
char depart_node, dest_node;  //departure and destination vertices/nodes
int rand_dist;  //random edge distance

graph g(num_vertices);

for(int i=0; i!=g.N(); ++i)
	for (int j=i+1; j!=g.N(); ++j)
	{
	double p= rand()/RAND_MAX;   //we allow for a random distribution between 0 and 1
//      double p= rand()%10/50;     // or hand_pick a distribution around density of 0.1

	if (p<density)
		{
		rand_dist= rand()%(max_dist- min_dist) + min_dist;
		depart_node=i;
		dest_node  =j;
		g.set_edge_value(depart_node, dest_node, rand_dist);
		}
	}
return g;
}


void monte_carlo::run(graph g)
{

static int turn=0;
cout<<endl<<"Simulation number "<<++turn<<":"<<endl;

//Graph info
double rd= static_cast<double>(g.E())/((static_cast<double>(g.N())*static_cast<double>(g.N()-1))/2);
cout<<"Nodes/Vertices: "<<g.N()<<endl;
cout<<"Edges/Distance: "<<g.E()<<endl;
cout<<"Real density  : "<<rd<< endl;
cout<<"Graph         : "<<endl;
g.show();                           //to be defined below

// Shortest path info

list<char> v= g.vertices();
//cout<<"Shortest path : "<<endl;
//cout<<"Nodes/Vertice : "<<v<<endl;

shortest_path sp= shortest_path(g);  //initiate path

int reached_nodes=0, sum_path=0, avg_path_size;  // sum of path size and reached nodes
double p;

for(list<char>::iterator i=++v.begin(); i!=v.end(); ++i)
{
char start_node= v.front();
char destination_node= (*i); //per iteration destination node

list<char>path= sp.path(start_node, destination_node); //run djikstra on paths
int         ps= sp.path_size(start_node, destination_node);

//return shortest path

if(ps!=big_num)
	cout<<"Shortest path from "<<start_node<<" to "<<destination_node<<" : "<<p<<endl;
else
	cout<<"Shortest path from "<<start_node<<" to "<<destination_node<<" is unreachable."<<endl;

if(ps!=big_num)
{
reached_nodes++;
sum_path += ps; //sum shortest paths output
}
}
if (reached_nodes!=0)
	int avg_path_size= sum_path/reached_nodes;
else   
	int avg_path_size=0;

cout<<endl<<"Reached nodes: "<<reached_nodes<<endl;
cout<<      "Sum of paths : "<<sum_path<<endl;
cout<<"Average shortest path:"<<avg_path_size<<endl;
}


//##############################################

int main()
{

monte_carlo simulation;
graph g;

g=simulation.mt_graph(10, 0.5, 1, 5);

simulation.run(g);

return 0;
}

