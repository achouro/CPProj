#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
int max_i(vector<double>density, vector<double> weights)
{
int n=density.size();
double largest;
int max_index=0;

for(int i=0; i<=n;i++)
	{
	if (density[i]>largest && weights[i]>0){max_index=i;}
	}

return max_index; 
}

double min(double a, double b){if(a<b) return a; return b;}

double get_optimal_value(double capacity, vector<double> weights, vector<double> values) 
{
double value=0.0, amount;

int n=weights.size(), m;

vector<double> density(n);

for( int i=0; i<n; i++) { density[i]=values[i]/weights[i];}

for(int i=0; i<n; i++)
	{
	if (capacity==0) {return value;}

	m=max_i(density, weights);

	amount= min(weights[m], capacity);

	value = values[m]*(amount/weights[m]);

	weights[m]-=amount;
	capacity-=amount;
	}
 	

return value;
}

int main() {
  int n;
  double capacity;
  std::cin >> n >> capacity;
  vector<double> values(n);
  vector<double> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  //printf("%.4lf",optimal_value);
  return 0;
}
