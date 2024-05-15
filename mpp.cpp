//Maximum pairwise product
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

long long naive_mpp(vector<int>& numbers)
{
long long result=0;
int n=numbers.size();

for(int i=0; i<n; ++i)
{	
	for(int j=i+1; j<n; ++j)
	{
		if (result <(long long) numbers[i]*numbers[j])
		{
		result=(long long) numbers[i]*numbers[j];
		}
	}
}
return result;
}

long long mpp(vector<int>& numbers)
{
int n=numbers.size();

int max_index_1=-1;

for(int i=0; i<n; ++i)
	if((max_index_1==-1)||(numbers[i]>numbers[max_index_1]))
		max_index_1= i;

int max_index_2=-1;
for (int j=0; j<n;++j)
	if((j!=max_index_1) && ((max_index_2==-1) || (numbers[j]>numbers[max_index_2])))
		max_index_2=j;
//cout<<"Function thinks maximum indices are:"<< max_index_1<<" "<<max_index_2<<endl;

return((long long) numbers[max_index_1]*numbers[max_index_2]);
}


int main()
{
//stress test
/*while(true)
{
int n= rand()%100 +2;
cout<< n<<endl;

vector<int> a;
for( int i=0; i<n;++i) {a.push_back(rand()%100000);}

for(int i =0; i<n; ++i) {cout<<a[i]<<" ";}

long long res_1=naive_mpp(a);
long long res_2=mpp(a);

if (res_1 != res_2)
{
cout<<"Error message: "<<res_1<<" not equal to "<<res_2<<endl;
break;
}
else { cout<<"All good."<<endl;}
}
*/

int n;		
cin>> n;
vector<int> numbers(n);
for(int i=0; i<n; ++i)
	cin>>numbers[i];

long long result= mpp(numbers);
cout<< result<<endl;

return 0;
}

